#include "open.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "ogrsf_frmts.h"
#include "algorithms.h"

// Load polygons from a simple text file (x,y points, separated by commas)
QVector<QPolygonF> Open::openFile(const QString& fileName)
{
    QVector<QPolygonF> polygons;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file:" << file.errorString();
        return polygons;
    }

    QTextStream text(&file);
    QVector<QPointF> currentPolygon;

    // Read file line by line
    while (!text.atEnd()) {
        QString line = text.readLine().trimmed();

        // Empty line indicates end of a polygon
        if (line.isEmpty()) {
            if (!currentPolygon.isEmpty()) {
                polygons.append(QPolygonF(currentPolygon));
                currentPolygon.clear();
            }
            continue;
        }

        // Split line into coordinates
        QStringList coords = line.split(",");
        if (coords.size() == 2) {
            bool okX, okY;
            double x = coords[0].toDouble(&okX);
            double y = coords[1].toDouble(&okY);
            if (okX && okY) {
                currentPolygon.append(QPointF(x, y));
            }
        }
    }

    // Add last polygon if needed
    if (!currentPolygon.isEmpty()) {
        polygons.append(QPolygonF(currentPolygon));
    }

    return polygons;
}

// Load polygons from a shapefile using GDAL
QVector<QPolygonF> Open::openSHP(const QString& fileName, int widgetWidth, int widgetHeight)
{
    QVector<QPolygonF> polygons;

    // Register all GDAL drivers
    GDALAllRegister();

    // Open the shapefile
    GDALDataset *poDS = (GDALDataset *)GDALOpenEx(fileName.toUtf8().constData(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr);
    if (!poDS) {
        qDebug() << "Open failed";
        return polygons;
    }

    // Access the first layer of the shapefile
    OGRLayer *poLayer = poDS->GetLayer(0);
    if (!poLayer) {
        qDebug() << "No layer in shapefile";
        GDALClose(poDS);
        return polygons;
    }

    // Read each feature (geometry object) from the layer
    OGRFeature *poFeature = nullptr;
    poLayer->ResetReading();
    while ((poFeature = poLayer->GetNextFeature()) != nullptr) {
        OGRGeometry *poGeometry = poFeature->GetGeometryRef();

        // Only process polygons
        if (poGeometry && wkbFlatten(poGeometry->getGeometryType()) == wkbPolygon) {
            OGRPolygon *poPolygon = dynamic_cast<OGRPolygon *>(poGeometry);
            if (poPolygon) {
                QPolygonF qPolygon;
                OGRLinearRing *poRing = poPolygon->getExteriorRing();

                // Extract the outer ring of the polygon
                if (poRing) {
                    int numPoints = poRing->getNumPoints();
                    for (int i = 0; i < numPoints; i++) {
                        double x = poRing->getX(i);
                        double y = poRing->getY(i);
                        qPolygon.append(QPointF(x, y));
                    }
                }
                polygons.append(qPolygon);
            }
        }

        // Clean up
        OGRFeature::DestroyFeature(poFeature);
    }

    // Close the dataset
    GDALClose(poDS);

    // Normalize coordinates to fit widget dimensions
    algorithms::normalizePolygons(polygons, widgetWidth, widgetHeight);

    return polygons;
}

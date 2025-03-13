#include "draw.h"
#include <QtGui>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>


#include <iostream>
using namespace std;

#include <fstream>

#include <ogrsf_frmts.h>
#include "algorithms.h"


Draw::Draw(QWidget *parent)
    : QWidget{parent}
{
    q.setX(0);
    q.setY(0);
    add_point = false;
    isShapefileLoaded = false;

}


void Draw::mousePressEvent(QMouseEvent *e)
{


    //Get x, y coordinates
    double x = e->pos().x();
    double y = e->pos().y();

    // Set x,y to q
    if (add_point) {

        q.setX(x);
        q.setY(y);

    } else {

        QPointF p(x, y);
        if (!polygons.isEmpty()) {
            polygons.last().append(p); // Přidáváme do posledního polygonu
        }
    }
    //Repaint screen
    repaint();
}



// Vykreslení všech polygonů
void Draw::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.begin(this);

    // Draw all polygons
    painter.setPen(Qt::GlobalColor::red);
    painter.setBrush(Qt::GlobalColor::yellow);
    for (int i = 0; i < polygons.size(); i++) {
        if (i != highlightedIndex) {
            painter.drawPolygon(polygons[i]); // Draw all except the highlighted polygon
        }
    }

    // Draw the highlighted polygon (if any)
    if (highlightedIndex >= 0 && highlightedIndex < polygons.size()) {
        painter.setPen(Qt::GlobalColor::red);
        painter.setBrush(Qt::GlobalColor::green);
        painter.drawPolygon(polygons[highlightedIndex]);
    }

    // Draw point q
    painter.setPen(Qt::GlobalColor::black);
    painter.setBrush(Qt::GlobalColor::blue);
    int r = 5;
    painter.drawEllipse(q.x() - r, q.y() - r, 2 * r, 2 * r);

    painter.end();
}

void Draw::switch_source()
{
    //input q or polzgon vertex
    add_point = !add_point;
}




void Draw::highlightPolygon(int index)
{
    // Check if index is valid
    if (index < 0 || index >= polygons.size()) {
        qDebug() << "Invalid polygon index!";
        return;
    }

    highlightedIndex = index;  // Set the highlighted polygon index
    repaint();  // Repaint the widget to show the highlighted polygon
}




void Draw::openFile()
{
    // Open txt file with polygons
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));

    if (fileName.isEmpty()) {
        return; // If the user cancels the file selection
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file:" << file.errorString();
        return;
    }

    QTextStream text(&file);
    polygons.clear();  // Clear previous polygons

    QVector<QPointF> currentPolygon;  // Temporary container for points of a polygon

    while (!text.atEnd()) {
        QString line = text.readLine().trimmed();  // Trim white spaces

        if (line.isEmpty()) {
            if (!currentPolygon.isEmpty()) {
                polygons.push_back(QPolygonF(currentPolygon));  // Push the polygon to the vector
                currentPolygon.clear();  // Start a new polygon
            }
            continue;
        }

        QStringList coordinates = line.split(",");

        if (coordinates.size() == 2) {
            bool okX, okY;
            double x = coordinates[0].toDouble(&okX);
            double y = coordinates[1].toDouble(&okY);

            if (okX && okY) {
                // Add the point to the current polygon
                currentPolygon.append(QPointF(x, y));
            }
        }
    }

    if (!currentPolygon.isEmpty()) {
        polygons.push_back(QPolygonF(currentPolygon));  // Add last polygon
    }

    file.close();
    repaint();  // Repaint the widget to show the new polygons

    add_point = true;  // Switch to add points mode
}


// **Načítání polygonů ze SHP souboru**
void Draw::openSHP()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Shape Files (*.shp);;All Files (*)"));
    if (fileName.isEmpty()) return;

    GDALAllRegister();
    GDALDataset *poDS = (GDALDataset *)GDALOpenEx(fileName.toUtf8().constData(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr);
    if (!poDS) {
        qDebug() << "Open failed\n";
        return;
    }

    OGRLayer *poLayer = poDS->GetLayer(0);
    if (!poLayer) {
        qDebug() << "Chyba: SHP soubor neobsahuje žádnou vrstvu!";
        GDALClose(poDS);
        return;
    }

    polygons.clear();

    OGRFeature *poFeature = nullptr;
    poLayer->ResetReading();
    while ((poFeature = poLayer->GetNextFeature()) != nullptr) {
        OGRGeometry *poGeometry = poFeature->GetGeometryRef();
        if (poGeometry && wkbFlatten(poGeometry->getGeometryType()) == wkbPolygon) {
            OGRPolygon *poPolygon = dynamic_cast<OGRPolygon *>(poGeometry);
            if (poPolygon) {
                QPolygonF qPolygon;
                OGRLinearRing *poRing = poPolygon->getExteriorRing();
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
        OGRFeature::DestroyFeature(poFeature);
    }

    GDALClose(poDS);

    algorithms::normalizePolygons(polygons, width(), height());

    repaint();

    add_point = true;  // Switch to add points mode
}





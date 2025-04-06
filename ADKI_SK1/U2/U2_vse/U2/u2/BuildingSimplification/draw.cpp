#include "draw.h"
#include <QtGui>

// z U1
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

//přidávám zatím všechno co máme navíc v U1 a může se hodit


/*
void Draw::setPol(const QPolygonF &newPol)
{
    pol = newPol;
}
*/
/*
Draw::Draw(QWidget *parent)
    : QWidget{parent}
{

}
*/

// U1
Draw::Draw(QWidget *parent)
    : QWidget{parent}
{
    q.setX(0);
    q.setY(0);
    isShapefileLoaded = false;

}

/*
void Draw::mousePressEvent(QMouseEvent *e)
{
    //Get x, y coordinates
    double x = e->pos().x();
    double y = e->pos().y();

    //create point
    QPointF p(x, y);

    //Add point to polygon
    building.push_back(p);


    //Repaint screen
    repaint();
}
*/

// U1
void Draw::mousePressEvent(QMouseEvent *e)
{


    //Get x, y coordinates
    double x = e->pos().x();
    double y = e->pos().y();

    //create polygon
    QPointF p(x, y);

    //building.push_back(p);

    if (polygons.isEmpty()) {
        polygons.append(QPolygonF());
    }
    polygons.last().append(p);

    //Repaint screen
    repaint();
}




void Draw::paintEvent(QPaintEvent *event)
{
    //Draw
    QPainter painter(this);

    //Create object for drawing
    painter.begin(this);

    //Set graphic attributes, polygon
    painter.setPen(Qt::GlobalColor::black);
    painter.setBrush(Qt::GlobalColor::lightGray);

    // Draw all polygons
    for (int i = 0; i < polygons.size(); i++) {
        painter.drawPolygon(polygons[i]);
    }


    //Set graphic for MAER
    QPen pen_maer;
    pen_maer.setColor(Qt::GlobalColor::cyan);   // Nastavení barvy na magentu
    //pen_maer.setWidth(3);                          // Nastavení tloušťky čáry
    //pen_maer.setStyle(Qt::DashLine);               // Nastavení čárkované čáry

    painter.setPen(pen_maer);  // Použití nastaveného pinu
    //painter.setPen(Qt::GlobalColor::magenta);
    //painter.setPen(Qt::PenStyle::DashDotLine);
    painter.setBrush(Qt::GlobalColor::transparent);

    //Draw building
    for (int i = 0; i < maer.size(); i++) {
        painter.drawPolygon(maer[i]);
    }


    //Set graphic for PCA
    painter.setPen(Qt::GlobalColor::darkGreen);
    painter.setBrush(Qt::GlobalColor::transparent);
    //Draw building
    for (int i = 0; i < erpca.size(); i++) {
        painter.drawPolygon(erpca[i]);
    }

    //Set graphic for LE
    painter.setPen(Qt::GlobalColor::blue);
    painter.setBrush(Qt::GlobalColor::transparent);
    //Draw building
    for (int i = 0; i < le.size(); i++) {
        painter.drawPolygon(le[i]);
    }


    //Set graphic for WE
    // Nastavení barvy pera na oranžovou
    QPen penWE;
    penWE.setColor(QColor(255, 165, 0));  // RGB hodnoty pro oranžovou
    painter.setPen(penWE);
    painter.setBrush(Qt::GlobalColor::transparent);
    //Draw building
    for (int i = 0; i < we.size(); i++) {
        painter.drawPolygon(we[i]);
    }

    //Set graphic for WA
    // Nastavení barvy pera na oranžovou
    //QPen penWA;
    //penWA.setColor(QColor(255, 50, 0));  // RGB hodnoty pro oranžovou
    //painter.setPen(penWA);
    painter.setPen(Qt::GlobalColor::yellow);
    painter.setBrush(Qt::GlobalColor::transparent);
    //Draw building
    for (int i = 0; i < wa.size(); i++) {
        painter.drawPolygon(wa[i]);
    }

    //Set graphic for CH Jarvis
    painter.setPen(Qt::GlobalColor::magenta);
    painter.setBrush(Qt::GlobalColor::transparent);
    //Draw building
    for (int i = 0; i < ch.size(); i++) {
        painter.drawPolygon(ch[i]);
    }

    //Set graphic for CH Graham
    painter.setPen(Qt::GlobalColor::cyan);
    painter.setBrush(Qt::GlobalColor::transparent);
    //Draw building
    for (int i = 0; i < chGraham.size(); i++) {
        painter.drawPolygon(chGraham[i]);
    }




    //End draw
    painter.end();
}


// U1
void Draw::clear()
{
    polygons.clear();
    maer.clear();
    erpca.clear();
    le.clear();
    we.clear();
    wa.clear();
    ch.clear();
    chGraham.clear();

    repaint();

}

void Draw::clearResults()
{
    maer.clear();
    erpca.clear();
    le.clear();
    we.clear();
    wa.clear();
    ch.clear();
    chGraham.clear();

    repaint();
}



// U1
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

    //add_point = true;  // Switch to add points mode
}

// U1
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
        qDebug() << "Error: Shape file doesn't contain any layers!";
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

    Algorithms::normalizePolygons(polygons, width(), height());

    repaint();

    //add_point = true;  // Switch to add points mode
}

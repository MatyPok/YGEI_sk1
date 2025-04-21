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

#include "open.h"


Draw::Draw(QWidget *parent)
    : QWidget{parent}
{
    q.setX(0);
    q.setY(0);
    isShapefileLoaded = false;

}


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
    QPen penWE;
    penWE.setColor(QColor(255, 165, 0));  // orange
    painter.setPen(penWE);
    painter.setBrush(Qt::GlobalColor::transparent);
    //Draw building
    for (int i = 0; i < we.size(); i++) {
        painter.drawPolygon(we[i]);
    }

    //Set graphic for WA
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



void Draw::drawPolygonsFromTXT()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) return;

    polygons = Open::openFile(fileName);
    repaint();
}


void Draw::drawPolygonsFromSHP()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Shape Files (*.shp);;All Files (*)"));
    if (fileName.isEmpty()) return;

    polygons = Open::openSHP(fileName, width(), height());
    repaint();
}

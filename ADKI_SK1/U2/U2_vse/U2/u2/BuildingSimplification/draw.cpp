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



/*
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
}*/

void Draw::paintEvent(QPaintEvent *event)
{
    // Vytvoření objektu pro kreslení
    QPainter painter(this); // Toto automaticky zahájí kreslení

    // Nastavení grafických atributů pro polygon
    painter.setPen(Qt::GlobalColor::black);
    painter.setBrush(Qt::GlobalColor::lightGray);

    // Kreslení všech polygonů
    for (int i = 0; i < polygons.size(); i++) {
        painter.drawPolygon(polygons[i]);
    }

    // Nastavení grafiky pro MAER
    QPen pen_maer;
    pen_maer.setColor(Qt::GlobalColor::cyan);   // Nastavení barvy na cyan
    painter.setPen(pen_maer);  // Použití nastaveného pinu
    painter.setBrush(Qt::GlobalColor::transparent);

    // Kreslení MAER
    for (int i = 0; i < maer.size(); i++) {
        painter.drawPolygon(maer[i]);
    }

    // Nastavení grafiky pro PCA
    painter.setPen(Qt::GlobalColor::darkGreen);
    painter.setBrush(Qt::GlobalColor::transparent);
    // Kreslení PCA
    for (int i = 0; i < erpca.size(); i++) {
        painter.drawPolygon(erpca[i]);
    }

    // Nastavení grafiky pro LE
    painter.setPen(Qt::GlobalColor::blue);
    painter.setBrush(Qt::GlobalColor::transparent);
    // Kreslení LE
    for (int i = 0; i < le.size(); i++) {
        painter.drawPolygon(le[i]);
    }

    // Nastavení grafiky pro WE (orange)
    QPen penWE;
    penWE.setColor(QColor(255, 165, 0));  // Oranžová
    painter.setPen(penWE);
    painter.setBrush(Qt::GlobalColor::transparent);
    // Kreslení WE
    for (int i = 0; i < we.size(); i++) {
        painter.drawPolygon(we[i]);
    }

    // Nastavení grafiky pro WA (yellow)
    painter.setPen(Qt::GlobalColor::yellow);
    painter.setBrush(Qt::GlobalColor::transparent);
    // Kreslení WA
    for (int i = 0; i < wa.size(); i++) {
        painter.drawPolygon(wa[i]);
    }

    // Nastavení grafiky pro CH Jarvis (magenta)
    painter.setPen(Qt::GlobalColor::magenta);
    painter.setBrush(Qt::GlobalColor::transparent);
    // Kreslení CH Jarvis
    for (int i = 0; i < ch.size(); i++) {
        painter.drawPolygon(ch[i]);
    }

    // Nastavení grafiky pro CH Graham (cyan)
    painter.setPen(Qt::GlobalColor::cyan);
    painter.setBrush(Qt::GlobalColor::transparent);
    // Kreslení CH Graham
    for (int i = 0; i < chGraham.size(); i++) {
        painter.drawPolygon(chGraham[i]);
    }

    // Není potřeba volat `painter.end()` – destruktor `QPainter` to provede automaticky.
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

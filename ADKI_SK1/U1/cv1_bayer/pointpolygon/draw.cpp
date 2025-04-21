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
            polygons.last().append(p);
        }
    }
    //Repaint screen
    repaint();
}

void Draw::clearPolygons()
{
    polygons.clear();
    repaint();

}

void Draw::clear()
{
    polygons.clear();
    q.setX(0);
    q.setY(0);
    repaint();

}

void Draw::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.begin(this);

    // Draw all polygons
    painter.setPen(Qt::GlobalColor::red);
    painter.setBrush(Qt::GlobalColor::yellow);
    for (int i = 0; i < polygons.size(); i++) {
        if (!highlightedIndex.contains(i)) {  // draw only unhighlightened polygons
            painter.drawPolygon(polygons[i]);
        }
    }


    painter.setPen(Qt::GlobalColor::red);
    painter.setBrush(Qt::GlobalColor::green);
    for (int ind : highlightedIndex){
        // Draw the highlighted polygon (if any)
        if (ind >= 0 && ind < polygons.size()) {
            painter.drawPolygon(polygons[ind]);
        }
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


void Draw::highlightPolygon(const QVector<int>& indices)
{
    highlightedIndex = indices;  // save higlighted polygons to a list
    repaint();
}

void Draw::clearHighlighted()
{
    highlightedIndex.clear();
    repaint();
}


void Draw::drawPolygonsFromTXT()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) return;

    polygons = Open::openFile(fileName);
    repaint();
    add_point = true;
}

void Draw::drawPolygonsFromSHP()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Shape Files (*.shp);;All Files (*)"));
    if (fileName.isEmpty()) return;

    polygons = Open::openSHP(fileName, width(), height());
    repaint();
    add_point = true;
}




#include "draw.h"
#include <QtGui>
#include <time.h>

#include "draw.h"
#include <QtGui>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>

#include "algorithms.h"

#include "open.h"

Draw::Draw(QWidget *parent)
    : QWidget{parent}
{
    view_points = true;
    view_dt = true;
    view_contour_lines = true;
    view_slope = true;
    view_aspect = true;
    //QPoint3DF a(50,70);
    //QPoint3DF c(150,130);
    //QPoint3DF d(50,150);

    //points.push_back(a);
   // points.push_back(b);
    //points.push_back(c);
   // points.push_back(d);

    //Initalize random number generator
    srand(time(NULL));


}



void Draw::mousePressEvent(QMouseEvent *e)
{
    //Get x, y coordinates
    double x = e->pos().x();
    double y = e->pos().y();

    //Random height of the point
    double z = rand()%1000 + 100.0;

    //Create point
    QPoint3DF p(x, y, z);

    //Add point to cloud
    points.push_back(p);

    //Repaint screen
    repaint();
}


void Draw::paintEvent(QPaintEvent *event)
{

    //Draw
    QPainter painter(this);

    //Create object for drawing
    painter.begin(this);

    //Draw slope
    if (view_slope)
    {
        for (Triangle t: triangles)
        {

            //Get vertices
            QPoint3DF p1  = t.getP1();
            QPoint3DF p2  = t.getP2();
            QPoint3DF p3  = t.getP3();

            QPolygonF vert = {p1, p2, p3};

            //Get slope
            double slope = t.getSlope();

            //Convert slope to color
            int color = 255 - 255/M_PI * slope;

            //Set brush
            painter.setBrush(QColor(color, color, color));

            //Draw triangle
            painter.drawPolygon(vert);

        }
    }

    //Set graphic attributes, point
    if(view_points)
    {
        painter.setPen(Qt::GlobalColor::black);
        painter.setBrush(Qt::GlobalColor::blue);

        //Draw points
        const int r = 5;
        for (QPoint3DF point: points)
        {
           painter.drawEllipse(point.x()-r,point.y()-r, 2*r,2*r);
        }
    }

    //Draw DT
    if(view_dt)
    {

        painter.setPen(Qt::GlobalColor::green);
        for (Edge e: dt)
        {
            painter.drawLine(e.getStart(), e.getEnd());
        }
    }

    //Draw contour lines
    if(view_contour_lines)
    {
        painter.setPen(Qt::GlobalColor::darkGray);

        for (Edge e: contour_lines)
        {
            painter.drawLine(e.getStart(), e.getEnd());
        }
    }


    //Draw aspect
    if (view_aspect)
    {
        for (Triangle t: triangles)
        {

            //Get vertices
            QPoint3DF p1  = t.getP1();
            QPoint3DF p2  = t.getP2();
            QPoint3DF p3  = t.getP3();

            QPolygonF vert = {p1, p2, p3};

            //Get slope
            double aspect = t.getAspect();

            //Convert slope to color
            int color = 255 - 255/M_PI * aspect;

            //Set brush
            painter.setBrush(QColor(color, color, color));

            //Draw triangle
            painter.drawPolygon(vert);

        }
    }


    //End draw
    painter.end();

}


void Draw::pointsFromTXT()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) return;

    std::vector<QPoint3DF> points0 = Open::openFile(fileName, width(), height());

    for (QPoint3DF p: points0){
       points.push_back(p);
    }

    repaint();
}

void Draw::clear()
{

    dt.clear();
    points.clear();
    contour_lines.clear();
    triangles.clear();

    repaint();

}

void Draw::clearResults()
{
    dt.clear();
    contour_lines.clear();
    triangles.clear();

    repaint();
}




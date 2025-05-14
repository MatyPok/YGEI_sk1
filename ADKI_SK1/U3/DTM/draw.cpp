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
            // Get vertices
            QPoint3DF p1  = t.getP1();
            QPoint3DF p2  = t.getP2();
            QPoint3DF p3  = t.getP3();

            QPolygonF vert = {p1, p2, p3};

            // Get aspect (orientation)
            double aspect = t.getAspect();

            // Convert aspect to degrees (0-360°)
            double aspect_deg = aspect * 180.0 / M_PI;
            if (aspect_deg < 0) aspect_deg += 360.0;

            // Define fixed colors for specific orientations
            QColor color;
            if (aspect_deg >= 0 && aspect_deg < 45) {
                color = QColor(255, 0, 0); // Red (North)
            } else if (aspect_deg >= 45 && aspect_deg < 90) {
                color = QColor(255, 165, 0); // Orange (Northeast)
            } else if (aspect_deg >= 90 && aspect_deg < 135) {
                color = QColor(255, 255, 0); // Yellow (East)
            } else if (aspect_deg >= 135 && aspect_deg < 180) {
                color = QColor(0, 255, 0); // Green (Southeast)
            } else if (aspect_deg >= 180 && aspect_deg < 225) {
                color = QColor(0, 0, 255); // Blue (South)
            } else if (aspect_deg >= 225 && aspect_deg < 270) {
                color = QColor(128, 0, 128); // Purple (Southwest)
            } else if (aspect_deg >= 270 && aspect_deg < 315) {
                color = QColor(255, 192, 203); // Pink (West)
            } else {
                color = QColor(139, 69, 19); // Brown (Northwest)
            }

            // Set the brush to the fixed color
            painter.setBrush(color);
            painter.setPen(Qt::NoPen); // No outline
            painter.drawPolygon(vert);
        }
    }

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
            //Set brush and pen
            painter.setBrush(QColor(color, color, color));
            painter.setPen(Qt::black);
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




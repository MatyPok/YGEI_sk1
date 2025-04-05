#include "draw.h"
#include <QtGui>

/*
void Draw::setPol(const QPolygonF &newPol)
{
    pol = newPol;
}
*/
Draw::Draw(QWidget *parent)
    : QWidget{parent}
{

}


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


void Draw::paintEvent(QPaintEvent *event)
{
    //Draw
    QPainter painter(this);

    //Create object for drawing
    painter.begin(this);

    //Set graphic attributes, polygon
    painter.setPen(Qt::GlobalColor::black);
    painter.setBrush(Qt::GlobalColor::lightGray);

    //Draw building
    painter.drawPolygon(building);

    //Set graphic for CH
    //painter.setPen(Qt::GlobalColor::cyan);
    //painter.setPen(Qt::PenStyle::DashLine);
   // painter.setBrush(Qt::GlobalColor::transparent);

    //Draw building
    //painter.drawPolygon(ch);

    //Set graphic for MAER
    QPen pen_maer;
    pen_maer.setColor(Qt::GlobalColor::cyan);   // Nastavení barvy na magentu
    pen_maer.setWidth(3);                          // Nastavení tloušťky čáry
    pen_maer.setStyle(Qt::DashLine);               // Nastavení čárkované čáry

    painter.setPen(pen_maer);  // Použití nastaveného pinu
    //painter.setPen(Qt::GlobalColor::magenta);
    //painter.setPen(Qt::PenStyle::DashDotLine);
    painter.setBrush(Qt::GlobalColor::transparent);

    //Draw building
    painter.drawPolygon(maer);


    //Set graphic for PCA
    painter.setPen(Qt::GlobalColor::magenta);
    painter.setBrush(Qt::GlobalColor::transparent);
    //Draw building
    painter.drawPolygon(erpca);

    //Set graphic for LE
    painter.setPen(Qt::GlobalColor::blue);
    painter.setBrush(Qt::GlobalColor::transparent);
    //Draw building
    painter.drawPolygon(le);



    //End draw
    painter.end();
}




#include "draw.h"
#include <QtGui>
#include <QFileDialog>

#include <iostream>
using namespace std;

Draw::Draw(QWidget *parent)
    : QWidget{parent}
{
    q.setX(0);
    q.setY(0);
    add_point = false;

}


void Draw::mousePressEvent(QMouseEvent *e)
{


    //Get x, y coordinates
    double x = e->pos().x();
    double y = e->pos().y();

    // Set x,y to q
    if(add_point)
    {
        q.setX(x);
        q.setY(y);
    }

        //add point to polygon
    else
    {

        //Create point
        QPointF p(x, y);

        //Add point to polygon
        pol.push_back(p);
    }

    //Repaint screen
    repaint();
}


void Draw::paintEvent(QPaintEvent *event)
{
    //Draw
    QPainter painter(this);

    //Create object for drawing
    painter.begin(this);

    //Set graphic attributes for polygon
    painter.setPen(Qt::GlobalColor::red);
    painter.setBrush(Qt::GlobalColor::yellow);

    //Draw draw
    painter.drawPolygon(pol);

    //Set graphic attributes for point
    painter.setPen(Qt::GlobalColor::black);
    painter.setBrush(Qt::GlobalColor::blue);

    int r = 5; // nastavim velikost polomeru bodu v px

    //Draw point
    painter.drawEllipse(q.x()-r, q.y()-r,2*r,2*r);


    //End draw
    painter.end();
}

void Draw::switch_source()
{
    //input q or polzgon vertex
    add_point = !add_point;
}



void Draw::openFile()
{
    add_point = false;
    // open txt file with polygons
    // open dialog for finding the txt file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));

    if (fileName.isEmpty()) {
        return; // Pokud uživatel zrušil výběr souboru
    }

    QFile file(fileName);

    QTextStream text(&file);
    pol.clear();

    while(!text.atEnd()){
        QString line = text.readLine().trimmed(); // delete white spaces

        if (line.isEmpty()) {
            continue;  // skip empty lines
        }

        QStringList coordinates = line.split(",");

        if (coordinates.size() == 2) {
            bool okX, okY;
            double x = coordinates[0].toDouble(&okX);
            double y = coordinates[1].toDouble(&okY);

            if (okX && okY) {

                //Create point
                QPointF p(x, y);

                //Add point to polygon
                pol.push_back(p);

                cout<<"point ";

            } //else {
            //    QMessageBox::warning(this, tr("Invalid Data"), tr("Invalid coordinates format in the file."));
            //    return;
            //}
        }
    }



    file.close();


    // Pokud polygon obsahuje alespoň 3 body, nastavíme ho do Canvasu
    //if (pol.size() >= 3) {
    //    ui->Canvas->setPolygon();  // Nastavení polygonu do Canvasu
    //    setWindowTitle("Polygon Loaded");
    //} //else {
    //    QMessageBox::warning(this, tr("Invalid Polygon"), tr("The polygon is invalid. Please ensure it has at least 3 points."));
    //}


    repaint();

}


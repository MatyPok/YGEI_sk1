#ifndef DRAW_H
#define DRAW_H

#include <QObject>
#include <QVector>
#include <QPolygonF>
#include <QFile>
#include "ogrsf_frmts.h"

#include <QWidget>

#include <vector>

class Draw : public QWidget
{
    Q_OBJECT

private:
    QPointF q;
    QPolygonF pol;

    QVector<QPolygonF> polygons;
    int highlightedIndex = -1;

    bool add_point;
    bool isShapefileLoaded;

public:
    explicit Draw(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *event);
    void switch_source();
    void highlightPolygon(int index);

    QPointF getQ() const{return q;}
    QPolygonF getPol() const{return pol;}
    QVector<QPolygonF> getPolygons() const{return polygons;}
    void clearPolygons();

    void openFile();
    void openSHP();

    void clear();

signals:
};

#endif // DRAW_H

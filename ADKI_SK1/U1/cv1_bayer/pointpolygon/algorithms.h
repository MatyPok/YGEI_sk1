#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include<QtGui>

class algorithms
{
public:
    algorithms();
    static short analyzePointndPolPosition(const QPointF &q,const QPolygonF &pol);
    static double get2LineAngle(const QPointF &p1,const QPointF &p2,const QPointF &p3,const QPointF &p4);
    static int WindingNumber(const QPointF &q, const QPolygonF &pol);
    static bool isPointInMinMaxBoxOfPolygon(const QPointF &q, const QPolygonF &pol);

    static QPolygonF normalizePolygon(const QPolygonF &pol, double canvasWidth, double canvasHeight);
    static QPointF calculateCentroid(const QVector<QPolygonF>& polygons);
    static void normalizePolygons(QVector<QPolygonF>& polygons, int width, int height);
};

#endif // ALGORITHMS_H


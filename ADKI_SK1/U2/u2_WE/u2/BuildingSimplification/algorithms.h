#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <QtGui>
#include <tuple>
#include "Eigen/Dense"
#include "Eigen/Core"

class Algorithms
{
public:
    Algorithms();
    static double get2LinesAngle(const QPointF &p1, const QPointF &p2, const QPointF &p3, const QPointF &p4);

    static QPolygonF createCH(const QPolygonF &pol);
    static std::tuple<QPolygonF, double> minmaxBox(const QPolygonF &pol);
    static QPolygonF rotate(const QPolygonF &pol, double sigma);
    static double get_area(const QPolygonF &pol);
    static QPolygonF resize(const QPolygonF &pol, const QPolygonF &mmbox);
    static QPolygonF createMAER(const QPolygonF &pol);
    static QPolygonF createERPCA(const QPolygonF &pol);
    static QPolygonF createLongesEdge(const QPolygonF &pol);
    static double getDistance(const QPointF &p1, const QPointF &p2);
    static QPolygonF createWE(const QPolygonF &pol);



};

#endif // ALGORITHMS_H

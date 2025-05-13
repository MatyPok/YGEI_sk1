#ifndef QPOINT3DF_H
#define QPOINT3DF_H

#include <QPointF>

class QPoint3DF : public QPointF
{
private:
    double z;

public:

    QPoint3DF() : QPointF(0,  0), z(0) {}
    QPoint3DF(double x_, double y_) : QPointF(x_,  y_), z(0) {}
    QPoint3DF(double x_, double y_, double z_) : QPointF(x_,  y_), z(z_) {}

    void setX(double x_) { QPointF::setX(x_); }
    void setY(double y_) { QPointF::setY(y_); }
    void setZ(double z_){z = z_;}

    double getZ() const {return z;}



};
#endif // QPOINT3DF_H

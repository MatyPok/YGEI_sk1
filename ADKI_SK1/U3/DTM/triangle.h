#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <QtGui>

#include "qpoint3df.h"

class Triangle
{

private:
    QPoint3DF p1, p2, p3;
    double slope, aspect;

public:
    Triangle();

    Triangle(QPoint3DF p1_, QPoint3DF p2_, QPoint3DF p3_)
    {
        p1 = p1_;
        p2 = p2_;
        p3 = p3_;
        aspect = 0;
        slope = 0;
    }

    Triangle(QPoint3DF p1_, QPoint3DF p2_, QPoint3DF p3_, double slope_, double aspect_)
    {
        p1 = p1_;
        p2 = p2_;
        p3 = p3_;
        aspect = aspect_;
        slope = slope_;
    }

    QPoint3DF getP1() const {return p1;}
    QPoint3DF getP2() const {return p2;}
    QPoint3DF getP3() const {return p3;}

    double getSlope() const {return slope;}
    double getAspect() const {return aspect;}
    void setSlope(double slope_){slope = slope_;}
    void setAspect(double aspect_){aspect = aspect_;}

};

#endif // TRIANGLE_H

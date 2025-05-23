#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include "qpoint3df.h"
#include "edge.h"
#include "triangle.h"

class Draw : public QWidget
{
    Q_OBJECT

private:
    bool view_points, view_dt, view_contour_lines, view_aspect, view_slope;
    std::vector<QPoint3DF> points;
    std::vector<Edge> dt;
    std::vector<Edge> contour_lines;
    std::vector<Triangle> triangles;


public:
    explicit Draw(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *event);

    void pointsFromTXT();

    std::vector<QPoint3DF> getPoints()const {return points;}
    std::vector<Edge> getDT()const {return dt;}
    std::vector<Triangle> getTriangles() const {return triangles;}
    void setDT(const std::vector<Edge> &dt_){dt = dt_;}
    void setCL(const std::vector<Edge> &contour_lines_){contour_lines = contour_lines_;}
    void setTR(const std::vector<Triangle> &triangles_){triangles = triangles_;}

    void setViewPoints(const bool &view_points_){view_points=view_points_;}
    void setViewDT(const bool &view_dt_){view_dt=view_dt_;}
    void setViewContourLines(const bool &view_contour_lines_){view_contour_lines=view_contour_lines_;}
    void setViewSlope(const bool &view_slope_){view_slope=view_slope_;}
    void setViewAspect(const bool &view_aspect_){view_aspect=view_aspect_;}

    void clear();
    void clearResults();


signals:
};

#endif // DRAW_H

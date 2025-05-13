#include "algorithms.h"
#include <cmath>

Algorithms::Algorithms() {}



void Algorithms::normalizePoints(std::vector<QPoint3DF>& points, int width, int height)
{
    if (points.empty())
        return;

    QPointF centroid = calculateCentroid(points);

    qreal offsetX = width / 2.0 - centroid.x();
    qreal offsetY = height / 2.0 - centroid.y();

    for (QPoint3DF& point : points) {
        point.setX(point.x() + offsetX);
        point.setY(height - (point.y() + offsetY));
    }
}

QPointF Algorithms::calculateCentroid(const std::vector<QPoint3DF>& points)
{
    if (points.empty())
        return QPointF(0, 0);

    qreal totalX = 0;
    qreal totalY = 0;

    for (const QPoint3DF& point : points) {
        totalX += point.x();
        totalY += point.y();
    }

    return QPointF(totalX / points.size(), totalY / points.size());
}



short Algorithms::getPointAndLinePosition(const QPoint3DF &p,const QPoint3DF &p1,const QPoint3DF &p2){
    //Analyze Point and Line position
    double epsilon = 1e-6;

    //Direction vectors
    double ux = p2.x() - p1.x();
    double uy = p2.y() - p1.y();

    double vx = p.x() - p1.x();
    double vy = p.y() - p1.y();

    // Determinant test
    double t = ux * vy - uy * vx;

    //Point in the left half plane
    if (t > epsilon)
        return 1;;

    //Point in the right half plane
    if (t < -epsilon)
        return 0;

    //Point on the line
    return -1;
}


double Algorithms::get2LinesAngle(const QPoint3DF &p1, const QPoint3DF &p2, const QPoint3DF &p3, const QPoint3DF &p4)
{
    //Compute angle between two lines
    double u_x = p2.x() - p1.x();
    double u_y = p2.y() - p1.y();

    double v_x = p4.x() - p3.x();
    double v_y = p4.y() - p3.y();

    //Dot product
    double dot = u_x*v_x + u_y*v_y;

    //Calculate norms
    double n_u = std::sqrt(u_x*u_x + u_y*u_y);
    double n_v = std::sqrt(v_x*v_x + v_y*v_y);

    return acos(dot/(n_u*n_v));
}


int Algorithms::findDelaunayPoint(const QPoint3DF &p1, const QPoint3DF &p2, const std::vector<QPoint3DF> &points)
{
    //Find optimal Delaunay point
    int idx_max = -1;
    double omega_max = 0;

    //Process points one-by-one
    for (int i = 0; i<points.size(); i++)
    {
        // Point in the left half plane
        if (getPointAndLinePosition(points[i],p1,p2)==1)
        {
            //Compute angle
            double omega = get2LinesAngle(points[i],p1,points[i],p2);

            //Update maximum
            if (omega > omega_max)
            {
                omega_max = omega;
                idx_max = i;
            }
        }
    }

    return idx_max;
}


double Algorithms::get2DDistance(const QPoint3DF &p1, const QPoint3DF &p2)
{
    //Compute 2D Euclidean distance
    double dx = p1.x()-p2.x();
    double dy = p1.y()-p2.y();

    return sqrt(dx*dx+dy*dy);
}


int Algorithms::findNearestPoint(const QPoint3DF &p,const std::vector<QPoint3DF> &points)
{
    //Find Nearest Point
    int idx_min = -1;
    double eps = 1.0e-16, d_min = 1e16;

    //Process points one-by-one
    for (int i=0; i < points.size(); i++)
    {
        //Is points[i] different from p
        if (p != points[i])
        {
            //Compute distance
            double d = get2DDistance(p, points[i]);

            // Update minimum
            if (d < d_min)
            {
                d_min = d;
                idx_min = i;
            }
        }
    }

    return idx_min;

}


std::vector<Edge> Algorithms::DT(const std::vector<QPoint3DF> &points)
{
    //Create Delaunay triangulation using incremental method
    std::vector<Edge> dt;
    std::list<Edge> ael;

    //Get pivot p1
    QPoint3DF p1 = *std::min_element(points.begin(), points.end(), sortPointsByX());

    //Find nearest point
    int idx = findNearestPoint(p1,points);
    QPoint3DF p2 = points[idx];

    //Create initial edges
    Edge e1(p1, p2);
    Edge e2(p2, p1);

    //Add to AEL
    ael.push_back(e1);
    ael.push_back(e2);

    //Repeat until AEl is empty
    while (!ael.empty())
    {
        //Get edge
        Edge e = ael.back();

        //Remove e from AEL
        ael.pop_back();

        //Switch orientation
        Edge es = e.changeOrientation();

        //Find Delaunay point
        int idx_del = findDelaunayPoint(es.getStart(),es.getEnd(),points);

        //Del. point found
        if (idx_del != -1)
        {
            //Create new edges
            Edge e2s(es.getEnd(), points[idx_del]);
            Edge e3s(points[idx_del],es.getStart());

            //Add edges do DT
            dt.push_back(es);
            dt.push_back(e2s);
            dt.push_back(e3s);

            //Update AEL
            updateAEL(e2s, ael);
            updateAEL(e3s, ael);
        }
    }
    return dt;
}

void Algorithms::updateAEL(const Edge &e, std::list<Edge> &ael)
{
    //Update active edges list
    Edge es = e.changeOrientation();

    //Find edge with changed orientation
    auto i_e = std::find(ael.begin(), ael.end(), es);

    //We did not find this edge
    if (i_e == ael.end())
    {
        //Add edge to AEl, adjacent triangle exists
        ael.push_back(e);
    }

    //We found this edge
    else
    {
        //Remove from the list
        ael.erase(i_e);
    }
}


QPoint3DF Algorithms::countourLinePoint(const QPoint3DF &p1, const QPoint3DF &p2, double z)
{
    //Compute contour point
    double xb = ((p2.x() - p1.x())/(p2.getZ() - p1.getZ()))*(z - p1.getZ()) + p1.x();
    double yb = ((p2.y() - p1.y())/(p2.getZ() - p1.getZ()))*(z - p1.getZ()) + p1.y();

    return QPoint3DF (xb, yb, z);
}


std::vector<Edge> Algorithms::createContourLines(const std::vector<Edge> &dt, const double zmin, const double zmax, const double dz)
{
    //Generate contourlines
    std::vector<Edge> contour_lines;

    //Generate controur lines
    for(double z = zmin; z <= zmax; z += dz)
    {
        //Browse triangles one by one
        for (int i = 0; i<dt.size(); i+=3){
            //Get vertices
            QPoint3DF p1 = dt[i].getStart();
            QPoint3DF p2 = dt[i+1].getStart();
            QPoint3DF p3 = dt[i+2].getStart();

            // Height differences
            double dz1 = z - p1.getZ();
            double dz2 = z - p2.getZ();
            double dz3 = z - p3.getZ();

            //Triangle is coplanar
            if(dz1 == 0 && dz2 == 0 && dz3 ==0)
                continue;

            //Edge 1, 2 is the contour line
            if(dz1 == 0 && dz2 == 0)
            {
                //Add edge
                contour_lines.push_back(dt[i]);
            }

            //Edge 2, 3 is the contour line
            if(dz2 == 0 && dz3 == 0)
            {
                //Add edge
                contour_lines.push_back(dt[i+1]);
            }

            //Edge 3, 1 is the contour line
            if(dz3 == 0 && dz1 == 0)
            {
                //Add edge
                contour_lines.push_back(dt[i+2]);
            }

            //Plane intersects edges 1,2 and 2,3
            if((dz1*dz2 <= 0 && dz2*dz3<0) || (dz1*dz2 < 0 && dz2*dz3<=0))
            {
                //Compute intersections
                QPoint3DF a = countourLinePoint(p1, p2,z);
                QPoint3DF b = countourLinePoint(p2, p3,z);

                //Create contour segment
                Edge e(a,b);

                //Add contour segment to the list
                contour_lines.push_back(e);
            }

            //Plane intersects edges 2,3 and 3,1
            if((dz2*dz3 <= 0 && dz3*dz1<0) || (dz2*dz3 < 0 && dz3*dz1<=0))
            {
                //Compute intersections
                QPoint3DF a = countourLinePoint(p2, p3,z);
                QPoint3DF b = countourLinePoint(p3, p1,z);

                //Create contour segment
                Edge e(a,b);

                //Add contour segment to the list
                contour_lines.push_back(e);
            }

            //Plane intersects edges 3,1 and 1,2
            if((dz3*dz1 <= 0 && dz1*dz2<0) || (dz3*dz1 < 0 && dz1*dz2<=0))
            {
                //Compute intersections
                QPoint3DF a = countourLinePoint(p3, p1,z);
                QPoint3DF b = countourLinePoint(p1, p2,z);

                //Create contour segment
                Edge e(a,b);

                //Add contour segment to the list
                contour_lines.push_back(e);
            }
        }
    }

    return contour_lines;
}

double Algorithms::computeSlope(const QPoint3DF &p1, const QPoint3DF &p2, const QPoint3DF &p3)
{
    //Compute slope of the triangle

    //Directions
    double ux = p3.x() - p2.x();
    double uy = p3.y() - p2.y();
    double uz = p3.getZ() - p2.getZ();

    double vx = p1.x() - p2.x();
    double vy = p1.y() - p2.y();
    double vz = p1.getZ() - p2.getZ();

    //Normal vector
    double nx = uy*vz - uz*vy;
    double ny = -(ux*vz - uz*vx);
    double nz = ux*vy - uy*vx;

    //Norm
    double n = sqrt(nx*nx + ny*ny + nz*nz);

    return acos(nz/n);
}


void Algorithms::analyzeSlope(const std::vector<Edge> &dt,  std::vector<Triangle> &triangles)
{
    //Analyze DTM slope
    if (triangles.size() == 0)
        edgesToTriangles(dt, triangles);
    //Browse DTM by triangles

    /*
    for (Triangle t: triangles)
    {
        //Compute slope
        double slope = computeSlope(t.getP1(), t.getP2(), t.getP3());

        //Create new triangle
        t.setSlope(slope);
    }
    */

    for (int i = 0; i<triangles.size(); i++)
    {
        QPoint3DF p1 = triangles[i].getP1();
        QPoint3DF p2 = triangles[i].getP2();
        QPoint3DF p3 = triangles[i].getP3();

        double slope = computeSlope(p1, p2, p3);

        triangles[i].setSlope(slope);
    }

}


double Algorithms::computeAspect(const QPoint3DF &p1, const QPoint3DF &p2, const QPoint3DF &p3)
{
    //Compute aspect of the triangle

    //Directions
    double ux = p3.x() - p2.x();
    double uy = p3.y() - p2.y();
    double uz = p3.getZ() - p2.getZ();

    double vx = p1.x() - p2.x();
    double vy = p1.y() - p2.y();
    double vz = p1.getZ() - p2.getZ();

    //Normal vector
    double nx = uy*vz - uz*vy;
    double ny = -(ux*vz - uz*vx);

    return atan2(ny,nx);
}


void  Algorithms::analyzeAspect(const std::vector<Edge> &dt,  std::vector<Triangle> &triangles){
    //Analyze DTM slope
    if (triangles.size() == 0)
        edgesToTriangles(dt, triangles);
    /*
    //Browse DTM by triangles
    for (Triangle &t: triangles)
    {
        //Compute slope
        double aspect = computeAspect(t.getP1(), t.getP2(), t.getP3());

        //Create new triangle
        t.setSlope(aspect);
    }
    */

    for (int i = 0; i<triangles.size(); i++)
    {
        QPoint3DF p1 = triangles[i].getP1();
        QPoint3DF p2 = triangles[i].getP2();
        QPoint3DF p3 = triangles[i].getP3();

        double aspect = computeAspect(p1, p2, p3);

        triangles[i].setAspect(aspect);
    }
}


std::vector<Triangle>  Algorithms::edgesToTriangles(const std::vector<Edge> &dt, std::vector<Triangle> &triangles)
{
    //Convert Delaunay edges to triangles
    for (int i = 0; i<dt.size(); i+=3)
    {
        //Get vertices
        QPoint3DF p1 = dt[i].getStart();
        QPoint3DF p2 = dt[i+1].getStart();
        QPoint3DF p3 = dt[i+2].getStart();

        //Create new triangle
        Triangle t(p1, p2, p3);

        //Add triangle to the list
        triangles.push_back(t);
    }
}

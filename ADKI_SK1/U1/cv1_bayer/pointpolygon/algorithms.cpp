#include "algorithms.h"

algorithms::algorithms() {}
short algorithms::analyzePointndPolPosition(const QPointF &q,const QPolygonF &pol){
    // RAY CROSSING ALGORITHM

    int k = 0; // number of intersection, pocet pruseciku
    int n = pol.size(); //number of polygon edges, pocet vrcholu polygonu

    //
    for(int i = 0; i<n; i++){

        //GET COORDINATES

        // xi redukovany
        double xir = pol[i].x() - q.x();
        double yir = pol[i].y() - q.y();

        // xi + 1 redukovany
        double xi1r = pol[(i+1)%n].x() - q.x();
        double yi1r = pol[(i+1)%n].y() - q.y();

        //DO WE HAVE SUITABLE SEGMENT?
        if((yi1r > 0)&& (yir<=0) || (yir > 0)&&(yi1r<=0)){
            //point M in the right half-plane
            double xm = (xi1r*yir - xir*yi1r)/(yi1r-yir);
            if(xm>0){
                k++;
            }
        }
    }
    return k%2;

}
 // algoritmus pro vypocet uhlu meyi dvema vektory
double algorithms::get2LineAngle(const QPointF &p1,const QPointF &p2,const QPointF &p3,const QPointF &p4)
{
    // Compute angle between two lines
    double u_x = p2.x() - p1.x();
    double u_y = p2.y() - p1.y();

    double v_x = p4.x() - p3.x();
    double v_y = p4.y() - p3.y();

    //Dot product, skalarni soucin
    double dot = u_x*v_x + u_y*v_y;

    // Calculate norms,   normy kterymi delime
    double n_u = std::sqrt(u_x*u_x + u_y*u_y);
    double n_v = std::sqrt(v_x*v_x + v_y*v_y);

    return acos(dot/(n_u*n_v));

}

// DETERMINATION OD MATRIX
double determinant2x2(double a, double b, double c, double d) {
    return a * d - b * c;
}


bool algorithms::WindingNumber(const QPointF &q, const QPolygonF &pol){


    // WINDING NUMBER ALGORITHM

    // INITIALIZE OMEGA
    int n = pol.size(); // number of polygon edges.
    double omega = 0;
    double eps = 0.0001; // tolerance epsilon




    for(int i = 0; i<n; i++){
        // POSITION OF q (RIGHT/LEFT)
        double a = pol[(i + 1) % n].x() - pol[i].x();
        double b = pol[(i + 1) % n].y() - pol[i].y();
        double c = q.x()-pol[i].x();
        double d = q.y()-pol[i].y();
        double t = determinant2x2(a,b,c,d);


        // ANGLE BETWEEN TWO VECTORS
        double angle = get2LineAngle(pol[i], q, pol[(i + 1) % n], q);


        // podminka pro levou a pravou polorovinu
        if(t>0){
            omega = omega + angle;
        } else if(t<0){
            omega = omega-angle;
        }
    }
    return std::abs(std::abs(omega) - 2 * M_PI) < eps;
}




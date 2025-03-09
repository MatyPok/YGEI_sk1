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




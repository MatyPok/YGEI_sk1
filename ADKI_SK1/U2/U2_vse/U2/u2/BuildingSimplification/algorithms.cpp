#include "algorithms.h"
#include "sortpointsbyx.h"
#include "sortpointsbyy.h"
#include <cmath>


Algorithms::Algorithms() {}

// U1

void Algorithms::normalizePolygons(QVector<QPolygonF>& polygons, int width, int height)
{
    // center of mass of all polygons
    QPointF centroid = calculateCentroid(polygons);

    // move all polygons so they are at the center of window
    qreal offsetX = width / 2 - centroid.x();
    qreal offsetY = height / 2 - centroid.y();

    for (QPolygonF& polygon : polygons) {
        for (QPointF& point : polygon) {
            point.setX(point.x() + offsetX);
            point.setY(height - (point.y() + offsetY));
        }
    }
}

// U1
QPointF Algorithms::calculateCentroid(const QVector<QPolygonF>& polygons)
{
    qreal totalX = 0;
    qreal totalY = 0;
    int pointCount = 0;

    for (const QPolygonF& polygon : polygons) {
        for (const QPointF& point : polygon) {
            totalX += point.x();
            totalY += point.y();
            pointCount++;
        }
    }

    if (pointCount == 0) {
        return QPointF(0, 0); // return (0,0) if there is no such a point
    }

    return QPointF(totalX / pointCount, totalY / pointCount);
}




double Algorithms::get2LinesAngle(const QPointF &p1, const QPointF &p2, const QPointF &p3, const QPointF &p4)
{
    //Compute angle between two lines
    double u_x  = p2.x() - p1.x();
    double u_y  = p2.y() - p1.y();

    double v_x  = p4.x() - p3.x();
    double v_y  = p4.y() - p3.y();

    //Dot product
    double dot = u_x*v_x + u_y*v_y;

    //Calculate norms
    double n_u = std::sqrt(u_x*u_x + u_y*u_y);
    double n_v = std::sqrt(v_x*v_x + v_y*v_y);

    return acos(dot/(n_u*n_v));
}


QPolygonF Algorithms::createCH(const QPolygonF &pol)
{
    QPolygonF ch;

    // check polygon size
    if (pol.size() < 3) {
        qWarning() << "Input polygon has too few points!";
        return ch; // return empty polygon if it is not a polygon 
    }

    // Get pivot q
    auto q = *std::min_element(pol.begin(), pol.end(), sortPointsByY());

    // Get point r
    auto r = *std::min_element(pol.begin(), pol.end(), sortPointsByX());

    // Initialize pj, pj1
    QPointF pj = q;
    QPointF pj1(r.x(), q.y());

    // first point in CH
    ch.push_back(pj);

    // find all points of CH
    do {
        // Maximum a index
        double omega_max = 0;
        int i_max = -1;

        // find point generating max angle
        for (int i = 0; i < pol.size(); i++) {
            double omega = get2LinesAngle(pj, pj1, pj, pol[i]);

            // if angle > omega, actualize
            if (omega > omega_max) {
                omega_max = omega;
                i_max = i;
            }
        }

        // if no point found, stop
        if (i_max == -1) {
            qWarning() << "Error: Could not compute convex hull. No valid points found.";
            break;
        }

        // add point to CH
        ch.push_back(pol[i_max]);

        // actualize 
        pj1 = pj;
        pj = pol[i_max];

    } while (pj != q);
    
    // Check: If CH has less than 3 points, return empty polygon
    if (ch.size() < 3) {
        qWarning() << "Convex hull has less than 3 points!";
        return QPolygonF();
    }

    return ch;
}


QPolygonF Algorithms::createCH_Graham(const QPolygonF &pol) {
    if (pol.size() < 3) {
        return QPolygonF();
    }

    // CONVEX HULL - GRAHAM SCAN
    QPolygonF ch_g;

    // get pivot with minimal Y
    auto q = *std::min_element(pol.begin(), pol.end(), sortPointsByY());

    // create new polygon, which doesn't contain q
    QPolygonF new_pol;
    for (const auto &pt : pol) {
        if (pt != q) new_pol.append(pt);
    }

    if (new_pol.isEmpty()) {
        return QPolygonF();
    }

    // Structure for saving point and angle 
    struct PointAngle {
        QPointF point;
        double angle;
    };

    // count angles between points and pivot
    QVector<PointAngle> points_with_angles;
    for (int i = 0; i < new_pol.size(); ++i) {
        double dx = new_pol[i].x() - q.x();
        double dy = new_pol[i].y() - q.y();
        double angle = atan2(dy, dx);

        PointAngle pa;
        pa.point = new_pol[i];
        pa.angle = angle;

        points_with_angles.append(pa);
    }

    std::sort(points_with_angles.begin(), points_with_angles.end(), [](const PointAngle &a, const PointAngle &b) {
        return a.angle < b.angle;
    });

    // reconstruction of polygon from points
    new_pol.clear();
    for (const auto &pt : points_with_angles) {
        new_pol.append(pt.point);
    }

    // add pivot to CH
    ch_g.push_back(q);

    // add first two points
    ch_g.push_back(new_pol[0]);
    ch_g.push_back(new_pol[1]);

    for (int j = 2; j < new_pol.size(); ++j) {
        QPointF pj = new_pol[j];

        while (ch_g.size() >= 2) {
            QPointF pt = ch_g.back();
            QPointF pt_1 = ch_g[ch_g.size() - 2];

            double orientation = (pt.x() - pt_1.x()) * (pj.y() - pt_1.y()) -
                                 (pt.y() - pt_1.y()) * (pj.x() - pt_1.x());

            if (orientation > 0) break; // CCW - right direction
            ch_g.pop_back();            // CW - delete
        }

        ch_g.push_back(pj);
    }

    return ch_g;
}


std::tuple<QPolygonF, double> Algorithms::minmaxBox(const QPolygonF &pol)
{
    // CREATE MIN MAX BOX
    //GET PIVOT q
    auto qymin = *std::min_element(pol.begin(), pol.end(), sortPointsByY());
    auto qxmin = *std::min_element(pol.begin(), pol.end(), sortPointsByX());
    auto qymax = *std::max_element(pol.begin(), pol.end(), sortPointsByY());
    auto qxmax = *std::max_element(pol.begin(), pol.end(), sortPointsByX());

    //get extreme coordinates
    double xmin = qxmin.x();
    double ymin = qymin.y();

    double xmax = qxmax.x();
    double ymax = qymax.y();

    // create vertices of min max box
    QPointF v1(xmin,ymin);
    QPointF v2(xmax,ymin);
    QPointF v3(xmax,ymax);
    QPointF v4(xmin,ymax);

    //create new polygon
    //QPolygonF pol_new = {v1, v2, v3, v4}; // PROBLEM S VERZI
    QPolygonF pol_new({v1, v2, v3, v4});

    /*pol_new.push_back(v1);
    pol_new.push_back(v2);
    pol_new.push_back(v3);
    pol_new.push_back(v4);*/

    // compute area
    double area = (xmax-xmin)*(ymax - ymin);


    return {pol_new, area};

}

QPolygonF Algorithms::rotate(const QPolygonF &pol, double sigma){
    //rotate polygon to angle sigma
    QPolygonF rotated;

    //process polygon one by one
    for(QPointF point: pol){
        //get coordinates
        double xp = point.x();
        double yp = point.y();

        //rotate point
        double xpr = xp*cos(sigma) - yp*sin(sigma);
        double ypr = xp*sin(sigma) + yp*cos(sigma);

        QPointF p(xpr, ypr);

        rotated.push_back(p);

    }
    return rotated;
}


double Algorithms::get_area(const QPolygonF &pol){
    //compute area using LH FORMULA
    int n = pol.size();
    double area = 0;

    for (int i = 0; i < n; ++i) {
        area += pol[i].x() * (pol[(i+1)%n].y() - pol[(i-1+n)%n].y());

    }
    return fabs(area/2);
}

QPolygonF Algorithms::resize(const QPolygonF &pol, const QPolygonF &mmbox){
    //resize minimum area enclosing rectangle

    //compute area of polygon and mn max box
    double Ab = get_area(pol);
    double A = get_area(mmbox);

    //compute kj
    if (A == 0) {
        qWarning() << "Area of bounding box is zero!";
        return QPolygonF();
    }

    double k = Ab/A;

    //compute center of gravity
    double xt = (mmbox[0].x() + mmbox[1].x() + mmbox[2].x() + mmbox[3].x())/4;
    double yt = (mmbox[0].y() + mmbox[1].y() + mmbox[2].y() + mmbox[3].y())/4;

    //create vectors
    double u1x = mmbox[0].x() - xt;
    double u1y = mmbox[0].y() - yt;

    double u2x = mmbox[1].x() - xt;
    double u2y = mmbox[1].y() - yt;


    double u3x = mmbox[2].x() - xt;
    double u3y = mmbox[2].y() - yt;


    double u4x = mmbox[3].x() - xt;
    double u4y = mmbox[3].y() - yt;

    //compute vertices of the resized rectangle

    double x1r = xt - sqrt(k)*u1x;
    double y1r = yt - sqrt(k)*u1y;

    double x2r = xt - sqrt(k)*u2x;
    double y2r = yt - sqrt(k)*u2y;

    double x3r = xt - sqrt(k)*u3x;
    double y3r = yt - sqrt(k)*u3y;

    double x4r = xt - sqrt(k)*u4x;
    double y4r = yt - sqrt(k)*u4y;

    //create new points
    QPointF p1(x1r,y1r);
    QPointF p2(x2r,y2r);
    QPointF p3(x3r,y3r);
    QPointF p4(x4r,y4r);

    // create resized mmbox
    QPolygonF pol_res({p1, p2, p3, p4});
    return pol_res;


}



QPolygonF Algorithms::createMAER(const QPolygonF &pol){

    //create niminum enclosing rectangle over the building
    double sigma_min = 2*M_PI;
    //compute minimum area enclosing rectangle
    auto [mmbox_min, area_min] = minmaxBox(pol);

    //create CH
    QPolygonF ch = createCH(pol);

    //process all segments of cgint
    int n = ch.size();

    if (ch.size() < 2) {
        qWarning() << "Convex hull has too few points!";
        return QPolygonF(); // nebo vhodná výchozí hodnota
    }

    for (int i = 0; i < n; ++i) {
        //get ch segment and ints differencies
        double dx = ch[(i+1)%n].x() - ch[i].x();
        double dy = ch[(i+1)%n].y() - ch[i].y();

        //get angle of rotation
        double sigma = atan2(dy, dx);

        //rotation by -sigma
        QPolygonF ch_rotate = rotate(ch, -sigma);

        //compute min max box
        auto [mmbox, area] = minmaxBox(ch_rotate);

        //rotate backj - nemusim protoze mam nakopirovanou tu vstupni hodnotu.

        //update minimum
        if(area<area_min){
            area_min = area;
            sigma_min = sigma;
            mmbox_min = mmbox;

        }
    }

    // resize minmaxbox
    QPolygonF mmbox_min_res = resize(pol, mmbox_min);

    // rotate minmaxbox
    return rotate(mmbox_min_res, sigma_min);


}

// ENCLOSING RECTANGLE USING PCA
QPolygonF Algorithms::createERPCA(const QPolygonF &pol){
    // Create area enclosing rectangle minimum
    int n = pol.size();

    //Create matrix A
    Eigen::MatrixXd A(n, 2);

    //Add values to matrix
    for (int i = 0; i < n; ++i) {
        A(i, 0) = pol[i].x();
        A(i, 1) = pol[i].y();

    }

    //Compute means of coordinates over columns
    Eigen::RowVectorXd M = A.colwise().mean();

    //Subtract mean: B = A - M
    Eigen::MatrixXd B = A.rowwise() - M;

    //Covariance matrix: C = B' * B / (m - 1)
    Eigen::MatrixXd C = (B.adjoint() * B) / double(A.rows() - 1);

    //Compute SVD, full version: [U, S, V] = svd(C)
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(C, Eigen::ComputeFullV | Eigen::ComputeFullU);

    //
    Eigen::MatrixXd U = svd.matrixU();
    Eigen::MatrixXd S = svd.singularValues();
    Eigen::MatrixXd V = svd.matrixV();

    //compute sigma

    //get angle of rotation
    double sigma = atan2(V(1, 0), V(0, 1));

    //rotation by -sigma
    QPolygonF pol_rot = rotate(pol, -sigma);

    //compute min max box
    auto [mmbox, area] = minmaxBox(pol_rot);

    // resize minmaxbox
    QPolygonF mmbox_res = resize(pol, mmbox);

    // rotate minmaxbox
    return rotate(mmbox_res, sigma);

}




double Algorithms::getDistance(const QPointF &p1, const QPointF &p2){
    //Compute 2D distance
    double dx = p1.x() - p2.x();
    double dy = p1.y() - p2.y();

    double d = sqrt(dx*dx + dy*dy);
    return d;

}


QPolygonF Algorithms::createLongesEdge(const QPolygonF &pol){

    //INICIALIZACE
    double max_d = 0;
    int max_index = -1;
    double max_dx = 0;
    double max_dy = 0;


    for (int i = 0; i < pol.size(); i++) {
        QPointF p1 = pol[i];
        QPointF p2 = pol[(i + 1) % pol.count()]; // Další bod (pro poslední bod je to opět první bod)

        //Compute 2D distance
        double dx = p1.x() - p2.x();
        double dy = p1.y() - p2.y();

        double d = sqrt(dx*dx + dy*dy);

        if ( d > max_d){
            max_d = d;
            max_index = i;
            max_dx = dx;
            max_dy =dy;
        }

    }

    //VYPOCET HLAVNI SMERNICE
    double sigma = atan2(max_dy, max_dx);

    //rotation by -sigma
    QPolygonF pol_rot = rotate(pol, -sigma);

    //compute min max box
    auto [mmbox, area] = minmaxBox(pol_rot);

    // resize minmaxbox
    QPolygonF mmbox_res = resize(pol, mmbox);

    // rotate minmaxbox
    return rotate(mmbox_res, sigma);

}



QPolygonF Algorithms::createWE(const QPolygonF &pol){
    // INICIALIZACE
    int n = pol.size();
    double d1max = 0;
    double d2max = 0;
    double dx1 = 0;
    double dy1 = 0;
    double dx2 = 0;
    double dy2 = 0;


    // nalezeni dvou nejdelsich diagonal
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            //Compute 2D distance
            QPointF p1 = pol[(i + j + 2) % n];
            QPointF p2 = pol[i % n];

            double dx = p1.x() - p2.x();
            double dy = p1.y() - p2.y();

            double d = sqrt(dx*dx1 + dy*dy);

            if (d > d1max){
                d2max = d1max;
                d1max = d;
                dx1 = dx;
                dy1 = dy;
                dx2 = dx1;
                dy2 = dy1;


            }else if (d > d2max && d < d1max){
                d2max = d;
                dx2 = dx;
                dy2 = dy;
            }
        }
    }

    //SMERNICE
    double sigma1 = atan2(dx1, dy1);
    double sigma2 = atan2(dx2, dy2);
    double sigma = (d1max*sigma1 + d2max*sigma2)/(d1max + d2max);


    //rotation by -sigma
    QPolygonF pol_rot = rotate(pol, -sigma);

    //compute min max box
    auto [mmbox, area] = minmaxBox(pol_rot);

    // resize minmaxbox
    QPolygonF mmbox_res = resize(pol, mmbox);

    // rotate minmaxbox
    return rotate(mmbox_res, sigma);
}

QPolygonF Algorithms::createWA(const QPolygonF &pol){
    int n = pol.size();
    std::vector<double> sigmas;   // směry hran
    std::vector<double> lengths;  // délky hran

    // Spočítáme směry a délky všech hran
    for (int i = 0; i < n; ++i) {
        QPointF p1 = pol[i];
        QPointF p2 = pol[(i + 1) % n];
        double dx = p2.x() - p1.x();
        double dy = p2.y() - p1.y();

        double sigma = atan2(dy, dx);  // směr hrany
        double length = std::sqrt(dx*dx + dy*dy);  // délka hrany

        sigmas.push_back(sigma);
        lengths.push_back(length);
    }

    // Zvolíme referenční směr sigma'
    double sigma_ref = sigmas[0]; // zkusíme první hranu jako výchozí směr

    // Krok 3: Spočítáme r_i a vážený průměr
    double sum_r_s = 0.0;
    double sum_s = 0.0;

    for (int i = 0; i < n; ++i) {
        double delta_sigma = sigmas[i] - sigma_ref;

        // Normalizace směru do rozsahu (-PI, PI)
        while (delta_sigma <= -M_PI) delta_sigma += 2*M_PI;
        while (delta_sigma > M_PI) delta_sigma -= 2*M_PI;

        // Výpočet k_i a r_i
        int k_i = round((2.0 * delta_sigma) / M_PI); // zaokrouhlený podíl
        double r_i = delta_sigma - k_i * (M_PI / 2.0);

        sum_r_s += r_i * lengths[i];
        sum_s += lengths[i];
    }

    double sigma = sigma_ref + (sum_r_s / sum_s);

    // Krok 4: Rotace, bounding box, resize, zpětná rotace
    QPolygonF pol_rot = rotate(pol, -sigma);
    auto [mmbox, area] = minmaxBox(pol_rot);
    QPolygonF mmbox_res = resize(pol, mmbox);
    return rotate(mmbox_res, sigma);
}

























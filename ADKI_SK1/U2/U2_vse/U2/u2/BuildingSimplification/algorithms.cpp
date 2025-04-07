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

    // Check polygon size
    if (pol.size() < 3) {
        qWarning() << "Input polygon has too few points!";
        return ch; // Returns an empty polygon
    }

    // Get pivot point q (point with the smallest y-coordinate)
    auto q = *std::min_element(pol.begin(), pol.end(), sortPointsByY());

    // Get point r (point with the smallest x-coordinate)
    auto r = *std::min_element(pol.begin(), pol.end(), sortPointsByX());

    // Initialize points pj and pj1
    QPointF pj = q;
    QPointF pj1(r.x(), q.y());

    // Add the first point to the convex hull
    ch.push_back(pj);

    // Find all points of the convex hull
    do {
        // Maximum angle and index of the point
        double omega_max = 0;
        int i_max = -1;

        // Find the point generating the maximum angle
        for (int i = 0; i < pol.size(); i++) {
            double omega = get2LinesAngle(pj, pj1, pj, pol[i]);

            // If the angle is greater than omega_max, update
            if (omega > omega_max) {
                omega_max = omega;
                i_max = i;
            }
        }

        // If no point was found (for invalid polygons), stop
        if (i_max == -1) {
            qWarning() << "Error: Could not compute convex hull. No valid points found.";
            break;
        }

        // Add the point to the convex hull
        ch.push_back(pol[i_max]);

        // Update the vertices
        pj1 = pj;
        pj = pol[i_max];

    } while (pj != q);

    // Check: If the convex hull has less than 3 points, return an empty polygon
    if (ch.size() < 3) {
        qWarning() << "Convex hull has less than 3 points!";
        return QPolygonF(); // Empty polygon indicates an issue
    }

    return ch;
}


QPolygonF Algorithms::createCH_Graham(const QPolygonF &pol) {
    if (pol.size() < 3) {
        return QPolygonF();
    }

    // CONVEX HULL - GRAHAM SCAN
    QPolygonF ch_g;

    // Get pivot point q (point with the smallest y-coordinate)
    auto q = *std::min_element(pol.begin(), pol.end(), sortPointsByY());

    // Create a new polygon excluding the pivot point q
    QPolygonF new_pol;
    for (const auto &pt : pol) {
        if (pt != q) new_pol.append(pt);
    }

    if (new_pol.isEmpty()) {
        return QPolygonF();
    }

    // Structure to store point and its angle relative to the pivot
    struct PointAngle {
        QPointF point;
        double angle;
    };

    // Calculate angles relative to the pivot
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

    // Sort points by their angle relative to the pivot
    std::sort(points_with_angles.begin(), points_with_angles.end(), [](const PointAngle &a, const PointAngle &b) {
        return a.angle < b.angle;
    });

    // Rebuild the polygon from points sorted by angle
    new_pol.clear();
    for (const auto &pt : points_with_angles) {
        new_pol.append(pt.point);
    }

    // Add the pivot point to the convex hull
    ch_g.push_back(q);

    // Add the first two points
    ch_g.push_back(new_pol[0]);
    ch_g.push_back(new_pol[1]);

    // Process remaining points and build the convex hull
    for (int j = 2; j < new_pol.size(); ++j) {
        QPointF pj = new_pol[j];

        while (ch_g.size() >= 2) {
            QPointF pt = ch_g.back();
            QPointF pt_1 = ch_g[ch_g.size() - 2];

            double orientation = (pt.x() - pt_1.x()) * (pj.y() - pt_1.y()) -
                                 (pt.y() - pt_1.y()) * (pj.x() - pt_1.x());

            if (orientation > 0) break; // Left turn - correct direction
            ch_g.pop_back();            // Right turn or collinear - remove point
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

    // Create minimum enclosing rectangle over the building
    double sigma_min = 2 * M_PI;
    // Compute the minimum area enclosing rectangle
    auto [mmbox_min, area_min] = minmaxBox(pol);

    // Create the convex hull (CH) of the input polygon
    QPolygonF ch = createCH(pol);

    // Process all segments of the convex hull (CH)
    int n = ch.size();

    // If the convex hull has too few points, return an empty polygon
    if (ch.size() < 2) {
        qWarning() << "Convex hull has too few points!";
        return QPolygonF(); // or an appropriate default value
    }

    // Iterate over all edges (segments) of the convex hull
    for (int i = 0; i < n; ++i) {
        // Get the current segment of the convex hull and calculate its differences
        double dx = ch[(i + 1) % n].x() - ch[i].x();
        double dy = ch[(i + 1) % n].y() - ch[i].y();

        // Calculate the angle of rotation for the current segment
        double sigma = atan2(dy, dx);

        // Rotate the convex hull by -sigma to align the segment horizontally
        QPolygonF ch_rotate = rotate(ch, -sigma);

        // Compute the minimum bounding box for the rotated convex hull
        auto [mmbox, area] = minmaxBox(ch_rotate);

        // No need to rotate back since we copied the original value already

        // Update the minimum area if a smaller area is found
        if (area < area_min) {
            area_min = area;
            sigma_min = sigma;
            mmbox_min = mmbox;
        }
    }

    // Resize the minimum bounding box to fit the original polygon
    QPolygonF mmbox_min_res = resize(pol, mmbox_min);

    // Rotate the resized minimum bounding box to its optimal orientation
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


QPolygonF Algorithms::createLongesEdge(const QPolygonF &pol) {

    // INITIALIZATION
    double max_d = 0; // maximum distance
    int max_index = -1; // index of the longest edge
    double max_dx = 0; // x component of the longest edge
    double max_dy = 0; // y component of the longest edge

    // Iterate through all the edges to find the longest one
    for (int i = 0; i < pol.size(); i++) {
        QPointF p1 = pol[i];
        QPointF p2 = pol[(i + 1) % pol.count()]; // Next point (for the last point, it's the first point)

        // Compute 2D distance
        double dx = p1.x() - p2.x();
        double dy = p1.y() - p2.y();

        double d = sqrt(dx * dx + dy * dy); // Distance formula

        // Update the maximum distance and its components if the current distance is greater
        if (d > max_d) {
            max_d = d;
            max_index = i;
            max_dx = dx;
            max_dy = dy;
        }
    }

    // COMPUTE THE MAIN DIRECTION
    double sigma = atan2(max_dy, max_dx); // Compute the direction of the longest edge

    // Rotate by -sigma to align the edge with the x-axis
    QPolygonF pol_rot = rotate(pol, -sigma);

    // Compute the minimal bounding box
    auto [mmbox, area] = minmaxBox(pol_rot);

    // Resize the minimal bounding box to match the original polygon's size
    QPolygonF mmbox_res = resize(pol, mmbox);

    // Rotate the bounding box back by sigma to the original orientation
    return rotate(mmbox_res, sigma);
}

QPolygonF Algorithms::createWE(const QPolygonF &pol) {
    // INITIALIZATION
    int n = pol.size();
    double d1max = 0; // longest diagonal
    double d2max = 0; // second longest diagonal
    double dx1 = 0; // x component of the first diagonal
    double dy1 = 0; // y component of the first diagonal
    double dx2 = 0; // x component of the second diagonal
    double dy2 = 0; // y component of the second diagonal

    // Find the two longest diagonals
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue; // Skip the same points

            // Compute 2D distance between the two points
            QPointF p1 = pol[(i + j + 2) % n];
            QPointF p2 = pol[i % n];

            double dx = p1.x() - p2.x();
            double dy = p1.y() - p2.y();

            double d = sqrt(dx * dx + dy * dy); // Distance formula

            // Update the maximum diagonals
            if (d > d1max) {
                d2max = d1max;
                d1max = d;
                dx1 = dx;
                dy1 = dy;
                dx2 = dx1;
                dy2 = dy1;
            } else if (d > d2max && d < d1max) {
                d2max = d;
                dx2 = dx;
                dy2 = dy;
            }
        }
    }

    // Compute the directions of the diagonals
    double sigma1 = atan2(dx1, dy1); // direction of the first diagonal
    double sigma2 = atan2(dx2, dy2); // direction of the second diagonal
    double sigma = (d1max * sigma1 + d2max * sigma2) / (d1max + d2max); // Weighted average direction

    // Rotate by -sigma to align the diagonals
    QPolygonF pol_rot = rotate(pol, -sigma);

    // Compute the minimal bounding box
    auto [mmbox, area] = minmaxBox(pol_rot);

    // Resize the minimal bounding box
    QPolygonF mmbox_res = resize(pol, mmbox);

    // Rotate the bounding box back by sigma to the original orientation
    return rotate(mmbox_res, sigma);
}

QPolygonF Algorithms::createWA(const QPolygonF &pol) {
    int n = pol.size();
    std::vector<double> sigmas;   // Directions of the edges
    std::vector<double> lengths;  // Lengths of the edges

    // Compute the directions and lengths of all edges
    for (int i = 0; i < n; ++i) {
        QPointF p1 = pol[i];
        QPointF p2 = pol[(i + 1) % n];
        double dx = p2.x() - p1.x();
        double dy = p2.y() - p1.y();

        double sigma = atan2(dy, dx);  // Direction of the edge
        double length = std::sqrt(dx * dx + dy * dy);  // Length of the edge

        sigmas.push_back(sigma);
        lengths.push_back(length);
    }

    // Choose a reference direction sigma' (we will try the first edge as the reference)
    double sigma_ref = sigmas[0];

    // Step 3: Compute r_i and weighted average
    double sum_r_s = 0.0;
    double sum_s = 0.0;

    for (int i = 0; i < n; ++i) {
        double delta_sigma = sigmas[i] - sigma_ref;

        // Normalize the direction to the range (-PI, PI)
        while (delta_sigma <= -M_PI) delta_sigma += 2 * M_PI;
        while (delta_sigma > M_PI) delta_sigma -= 2 * M_PI;

        // Compute k_i and r_i
        int k_i = round((2.0 * delta_sigma) / M_PI); // Rounded quotient
        double r_i = delta_sigma - k_i * (M_PI / 2.0);

        sum_r_s += r_i * lengths[i];
        sum_s += lengths[i];
    }

    double sigma = sigma_ref + (sum_r_s / sum_s); // Final direction

    // Step 4: Rotate, compute bounding box, resize, and rotate back
    QPolygonF pol_rot = rotate(pol, -sigma);
    auto [mmbox, area] = minmaxBox(pol_rot);
    QPolygonF mmbox_res = resize(pol, mmbox);
    return rotate(mmbox_res, sigma);
}
























#include "algorithms.h"

algorithms::algorithms() {}

// RAY CROSSING ALGORITHM TO DETERMINE POINT IN POLYGON POSITION
short algorithms::analyzePointndPolPosition(const QPointF &q, const QPolygonF &pol) {
    int k = 0; // NUMBER OF INTERSECTIONS
    int n = pol.size(); // NUMBER OF POLYGON EDGES

    // LOOP THROUGH EACH EDGE OF THE POLYGON
    for (int i = 0; i < n; i++) {

        // GET COORDINATES OF THE POINT RELATIVE TO THE POLYGON VERTICES
        double xir = pol[i].x() - q.x(); // xi REDUCED
        double yir = pol[i].y() - q.y(); // yi REDUCED

        double xi1r = pol[(i + 1) % n].x() - q.x(); // xi+1 REDUCED
        double yi1r = pol[(i + 1) % n].y() - q.y(); // yi+1 REDUCED

        // CHECK IF WE HAVE A SUITABLE SEGMENT TO CONSIDER
        if ((yi1r > 0) && (yir <= 0) || (yir > 0) && (yi1r <= 0)) {
            // POINT M IS IN THE RIGHT HALF-PLANE
            double xm = (xi1r * yir - xir * yi1r) / (yi1r - yir);
            if (xm > 0) {
                k++;
            }
        }
    }
    return k % 2; // IF THE NUMBER OF INTERSECTIONS IS ODD, THE POINT IS INSIDE
}

// FUNCTION TO CALCULATE THE ANGLE BETWEEN TWO VECTORS
double algorithms::get2LineAngle(const QPointF &p1, const QPointF &p2, const QPointF &p3, const QPointF &p4) {
    // CALCULATE THE COMPONENTS OF THE VECTORS
    double u_x = p2.x() - p1.x();
    double u_y = p2.y() - p1.y();

    double v_x = p4.x() - p3.x();
    double v_y = p4.y() - p3.y();

    // CALCULATE THE DOT PRODUCT OF THE VECTORS
    double dot = u_x * v_x + u_y * v_y;

    // CALCULATE THE MAGNITUDES (NORMS) OF THE VECTORS
    double n_u = std::sqrt(u_x * u_x + u_y * u_y);
    double n_v = std::sqrt(v_x * v_x + v_y * v_y);

    return acos(dot / (n_u * n_v)); // RETURN THE ANGLE BETWEEN THE VECTORS
}

// DETERMINANT FUNCTION FOR 2x2 MATRIX
double determinant2x2(double a, double b, double c, double d) {
    return a * d - b * c; // CALCULATE THE DETERMINANT OF A 2x2 MATRIX
}

// FUNCTION TO CHECK IF POINT IS ON THE EDGE OF THE POLYGON
bool isPointOnEdge(const QPointF &q, const QPolygonF &pol) {
    int n = pol.size();
    const double eps = 1e-6; // SMALL TOLERANCE FOR CROSS PRODUCT

    // LOOP THROUGH EACH EDGE OF THE POLYGON
    for (int i = 0; i < n; ++i) {
        // COMPUTE THE CROSS PRODUCT BETWEEN THE POINT AND THE EDGE
        double a = pol[(i + 1) % n].x() - pol[i].x();
        double b = pol[(i + 1) % n].y() - pol[i].y();
        double c = q.x() - pol[i].x();
        double d = q.y() - pol[i].y();
        double t = determinant2x2(a, b, c, d);

        if (std::abs(t) < eps) { // IF THE POINT IS COLLINEAR WITH THE EDGE
            // CHECK IF THE POINT IS BETWEEN THE TWO VERTICES OF THE EDGE
            if (q.x() >= std::min(pol[i].x(), pol[(i + 1) % n].x()) && q.x() <= std::max(pol[i].x(), pol[(i + 1) % n].x()) &&
                q.y() >= std::min(pol[i].y(), pol[(i + 1) % n].y()) && q.y() <= std::max(pol[i].y(), pol[(i + 1) % n].y())) {
                return true; // POINT IS ON THE EDGE
            }
        }
    }
    return false; // POINT IS NOT ON ANY EDGE
}

// WINDING NUMBER ALGORITHM TO CHECK IF POINT IS INSIDE A POLYGON
int algorithms::WindingNumber(const QPointF &q, const QPolygonF &pol) {

    // INITIALIZE OMEGA (THE WINDING NUMBER)
    int n = pol.size(); // NUMBER OF POLYGON EDGES
    double omega = 0;
    double eps = 0.0001; // TOLERANCE FOR COMPARING ANGLES

    // CHECK IF THE POINT IS AT ANY VERTEX
    for (int i = 0; i < n; ++i) {
        if (q == pol[i]) {
            return -2; // POINT IS AT A VERTEX
        }
    }

    // CHECK IF THE POINT IS ON ANY EDGE
    if (isPointOnEdge(q, pol)) {
        return -3; // POINT IS ON THE EDGE
    }

    // LOOP THROUGH EACH EDGE OF THE POLYGON
    for (int i = 0; i < n; i++) {

        // POSITION OF q (RIGHT/LEFT)
        double a = pol[(i + 1) % n].x() - pol[i].x();
        double b = pol[(i + 1) % n].y() - pol[i].y();
        double c = q.x() - pol[i].x();
        double d = q.y() - pol[i].y();
        double t = determinant2x2(a, b, c, d);

        // ANGLE BETWEEN TWO VECTORS
        double angle = get2LineAngle(pol[i], q, pol[(i + 1) % n], q);

        // CONDITION FOR LEFT AND RIGHT HALF-PLANE
        if (t > 0) {
            omega = omega + angle; // TURN LEFT
        } else if (t < 0) {
            omega = omega - angle; // TURN RIGHT
        }
    }

    // CHECK IF THE WINDING NUMBER IS CLOSE TO 2 * PI (INSIDE)
    if (std::abs(std::abs(omega) - 2 * M_PI) < eps) {
        return 1; // POINT IS INSIDE THE POLYGON
    } else {
        return 0; // POINT IS OUTSIDE THE POLYGON
    }
}


bool algorithms::isPointInMinMaxBoxOfPolygon(const QPointF &q, const QPolygonF &pol){

    double minx = -1e10;
    double maxx = 1e10;

    double miny = -1e10;
    double maxy = 1e10;

    // LOOP THROUGH EACH EDGE OF THE POLYGON
    for (const QPointF &point : pol) {

        // find the smallest and biggest x and y
        if (point.x() > maxx) {
            maxx = point.x();
        }

        if (point.x() < minx) {
            minx = point.x();
        }

        if (point.y() > maxy) {
            maxy = point.x();
        }

        if (point.y() < miny) {
            miny = point.x();
        }
    }


    if ( q.x() < maxx && q.x() > minx && q.y() < maxy && q.y() > miny){
        return true; // point q is in the min max box of polygon
    } else {
        return false; // point q is not in the min max box of polygon
    }

}


QPolygonF algorithms::normalizePolygon(const QPolygonF &inputPol, double canvasWidth, double canvasHeight) {
    if (inputPol.isEmpty()) {
        return {};
    }

    // Najdi minimální a maximální hodnoty souřadnic
    double minX = inputPol.first().x();
    double minY = inputPol.first().y();
    double maxX = minX, maxY = minY;

    for (const QPointF &p : inputPol) {
        minX = qMin(minX, p.x());
        minY = qMin(minY, p.y());
        maxX = qMax(maxX, p.x());
        maxY = qMax(maxY, p.y());
    }

    // Výpočet měřítka pro normalizaci na canvas (max 800 px)
    double scaleX = (maxX - minX) != 0 ? (canvasWidth / (maxX - minX)) : 1.0;
    double scaleY = (maxY - minY) != 0 ? (canvasHeight / (maxY - minY)) : 1.0;
    double scale = qMin(scaleX, scaleY); // Zachování poměru stran

    // Normalizace bodů
    QPolygonF normalizedPol;
    for (const QPointF &p : inputPol) {
        double normX = (p.x() - minX) * scale;
        double normY = (p.y() - minY) * scale;

        // Otočení osy Y
        normY = canvasHeight - normY;

        normalizedPol.append(QPointF(normX, normY));
    }

    return normalizedPol;
}


void algorithms::normalizePolygons(QVector<QPolygonF>& polygons, int width, int height)
{
    // Vypočítáme těžiště všech polygonů
    QPointF centroid = calculateCentroid(polygons);

    // Posuneme všechny polygony tak, aby těžiště bylo na středu okna
    qreal offsetX = width / 2 - centroid.x();
    qreal offsetY = height / 2 - centroid.y();

    // Pro každý polygon přepočítáme souřadnice bodů
    for (QPolygonF& polygon : polygons) {
        for (QPointF& point : polygon) {
            point.setX(point.x() + offsetX);
            point.setY(point.y() + offsetY);
        }
    }
}


QPointF algorithms::calculateCentroid(const QVector<QPolygonF>& polygons)
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
        return QPointF(0, 0);  // Vrátíme bod (0, 0) pokud žádný bod neexistuje
    }

    // Vraťte průměrné těžiště
    return QPointF(totalX / pointCount, totalY / pointCount);
}





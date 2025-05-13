#include "open.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegularExpression>

#include "algorithms.h"

// Load polygons from a simple text file (x,y points, separated by commas)
std::vector<QPoint3DF> Open::openFile(const QString& fileName, const int width, const int height)
{
    std::vector<QPoint3DF> points;


    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file:" << file.errorString();
        return points;
    }

    QTextStream text(&file);
    //QVector<QPointF> currentPolygon;

    // Read file line by line
    while (!text.atEnd()) {
        QString line = text.readLine().trimmed();

        if (line.isEmpty()) {
            continue;
        }


        // Split line into coordinates
        line.replace(","," ");
        QStringList coords = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        //QStringList coords = line.split(",");
        if (coords.size() == 3) {
            bool okX, okY, okZ;
            double x = coords[0].toDouble(&okX);
            double y = coords[1].toDouble(&okY);
            double z = coords[2].toDouble(&okZ);

            if (okX && okY && okZ) {
                points.push_back(QPoint3DF(x, y, z));
            }
        }
    }


    // Normalize coordinates to fit widget dimensions
    Algorithms::normalizePoints(points, width, height);

    return points;
}



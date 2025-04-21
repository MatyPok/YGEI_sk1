#ifndef OPEN_H
#define OPEN_H

#include <QString>
#include <QPolygonF>
#include <QVector>

class Open
{
public:
    Open();

    static QVector<QPolygonF> openFile(const QString& fileName);
    static QVector<QPolygonF> openSHP(const QString& fileName, int widgetWidth, int widgetHeight);

};

#endif // OPEN_H

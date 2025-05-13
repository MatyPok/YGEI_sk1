#ifndef OPEN_H
#define OPEN_H

#include <QString>
#include <vector>

#include "qpoint3df.h"

class Open
{
public:
    Open();

    static std::vector<QPoint3DF> openFile(const QString& fileName,  int width, int height);

};

#endif // OPEN_H

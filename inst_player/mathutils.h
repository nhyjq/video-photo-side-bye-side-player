#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <QtGlobal>
#include <QString>

class MathUtils
{
public:
    MathUtils();

    static QString millisecondToTimeString(qint64 millisecond);
};

#endif // MATHUTILS_H

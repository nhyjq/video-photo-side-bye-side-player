#include "mathutils.h"

MathUtils::MathUtils()
{

}

QString MathUtils::millisecondToTimeString(qint64 millisecond)
{
    int h,m,s;
    int totalSeconds = millisecond / 1000;  //获得的时间是以毫秒为单位的
    h = totalSeconds / 3600;
    m = (totalSeconds - h*3600) / 60;
    s = totalSeconds - h * 3600 - m*60;
    QString str = QString("%1:%2:%3").arg(h, 2, 10, QLatin1Char('0')).arg(m, 2, 10, QLatin1Char('0')).arg(s, 2, 10, QLatin1Char('0'));
    return str;
}

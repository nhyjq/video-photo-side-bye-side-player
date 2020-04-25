#ifndef LOGGER_H
#define LOGGER_H

#include <qapplication.h>

void logger(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#endif // LOGGER_H

#include <iostream>
#include <QDateTime>
#include <QTextStream>

#include <qapplication.h>

using namespace std;

void logger(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString current_date = QString("%1").arg(current_date_time);
    QString message;
    QTextStream output(stdout);

    switch (type) {
    case QtDebugMsg:
        message = QString("%1 [DEBUG] [%2] - %3").arg(current_date).arg(context.category).arg(msg);
        output<<message<<endl;
        break;
    case QtInfoMsg:
        message = QString("%1 [INFO] [%2] - %3").arg(current_date).arg(context.category).arg(msg);
        output<<message<<endl;
        break;
    case QtWarningMsg:
        message = QString("%1 [WARN] [%2] - %3").arg(current_date).arg(context.category).arg(msg);
        output<<message<<endl;
        break;
    case QtCriticalMsg:
        message = QString("%1 [CRITICAL] [%2] - %3").arg(current_date).arg(context.category).arg(msg);
        output<<message<<endl;
        break;
    case QtFatalMsg:
        message = QString("%1 [FATAL] [%2] - %3").arg(current_date).arg(context.category).arg(msg);
        output<<message<<endl;
        abort();
    }

}

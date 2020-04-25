#include "mainwindow.h"

#include <QApplication>
#include "logger.h"
#include <QMessageBox>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(logger);

    if(!QFile::exists("player.ini"))
    {
        QMessageBox::critical(NULL, "", "player.ini not exists!",
                             QMessageBox::Ok);
        exit(-1);
    }
    MainWindow w;
    w.show();
    return a.exec();
}

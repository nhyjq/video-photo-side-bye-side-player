#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QGridLayout>

#include "videoviewer.h"
#include "photoviewer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QWidget* centralWidget;
    QGridLayout *mainLayout;
    QSplitter * splitterMain;
    VideoViewer* videoViewer;
    PhotoViewer* photoViewer;

    bool isFullscreen;

    void initLayout();

     void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H

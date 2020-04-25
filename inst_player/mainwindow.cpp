#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QSplitter>
#include <QGridLayout>
#include <QKeyEvent>
#include <QGuiApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)    
{
    this->setWindowState(Qt::WindowMaximized);
    this->initLayout();
    this->setFocusPolicy(Qt::StrongFocus);

    isFullscreen = false;



}

void MainWindow::initLayout()
{
    mainLayout = new QGridLayout();
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    centralWidget ->setStyleSheet("background-color:black;");
    centralWidget->setLayout(mainLayout);

    splitterMain = new QSplitter(Qt::Horizontal, this);
    videoViewer= new VideoViewer();
    photoViewer = new PhotoViewer();

    QList<int> splitterSizes;

    splitterSizes.append(QGuiApplication::primaryScreen()->geometry().width() / 2);
    splitterSizes.append(QGuiApplication::primaryScreen()->geometry().width() / 2);

    splitterMain->addWidget(videoViewer);
    splitterMain->addWidget(photoViewer);

    splitterMain->setSizes(splitterSizes);

    mainLayout->addWidget(splitterMain);
    mainLayout->setMargin(0);
}

MainWindow::~MainWindow()
{
//    delete dbManager;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        QApplication::quit();
    }
    else if(event->key() == Qt::Key_F)
    {
        if(!isFullscreen)
        {
            this->showFullScreen();
            isFullscreen = true;
        }
        else
        {
            this->showMaximized();
            isFullscreen = false;
        }
    }
}

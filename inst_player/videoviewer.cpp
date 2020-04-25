#include "videoviewer.h"

#include <QGuiApplication>
#include <QScreen>

VideoViewer::VideoViewer(QWidget *parent) : QWidget(parent)
{
    splitter = new QSplitter(Qt::Vertical);
    layout = new QGridLayout(this);
    layout->addWidget(splitter);
    layout ->setMargin(0);

    QList<int> splitterSizes;
    splitterSizes.append(this->geometry().height() * 2 / 3);
    splitterSizes.append(this->geometry().height() / 3);

    splitterSizes.append(QGuiApplication::primaryScreen()->geometry().height() * 2 / 3);
    splitterSizes.append(QGuiApplication::primaryScreen()->geometry().height() / 3);


    videoPlayer = new VideoPlayer(splitter);
    videoCatalog = new VideoCatalog(splitter);

    connect(videoCatalog,  SIGNAL(fileSelected(QString)), videoPlayer, SLOT(onFileSelected(QString)));

    splitter->setSizes(splitterSizes);

}

VideoViewer::~VideoViewer()
{

}

void VideoViewer::resizeEvent(QResizeEvent* size)
{
    Q_UNUSED(size)
}



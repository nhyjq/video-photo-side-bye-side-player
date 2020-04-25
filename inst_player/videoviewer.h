#ifndef VIDEOVIEWER_H
#define VIDEOVIEWER_H

#include <QWidget>
#include <QGridLayout>
#include <QSplitter>

#include "videoplayer.h"
#include "videocatalog.h"

class VideoViewer : public QWidget
{
    Q_OBJECT
public:
    explicit VideoViewer(QWidget *parent = nullptr);
    ~VideoViewer();

signals:

private:
    void resizeEvent(QResizeEvent* size);

    QGridLayout* layout;
    QSplitter* splitter;

    VideoPlayer* videoPlayer;
    VideoCatalog* videoCatalog;

};

#endif // VIDEOVIEWER_H

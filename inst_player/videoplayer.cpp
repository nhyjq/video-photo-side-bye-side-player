#include "videoplayer.h"

#include <QDebug>
#include <QStyle>

#include "mathutils.h"

#define BUTTON_INFO "QPushButton\
{\
border: 1px solid rgb(50,50,50);\
border-radius:4px;\
color: rgb(0,0, 0); \
background-color: rgb(100, 100, 100); \
}"

VideoPlayer::VideoPlayer(QWidget *parent) : QWidget(parent)
{
    initLayout();
    initMedia();
}

void VideoPlayer::initLayout()
{
    mainLayout = new QVBoxLayout(this);
    panelLayout = new QHBoxLayout();

    playButton = new QPushButton(this->style()->standardIcon(QStyle::SP_MediaPause), "");
    initButtonStyle(playButton);
    stopButton = new QPushButton(this->style()->standardIcon(QStyle::SP_MediaStop), "");
    initButtonStyle(stopButton);
    previousButton = new QPushButton(this->style()->standardIcon(QStyle::SP_MediaSkipBackward), "");
    previousButton->setEnabled(false);
    initButtonStyle(previousButton);
    nextButton = new QPushButton(this->style()->standardIcon(QStyle::SP_MediaSkipForward), "");
    nextButton->setEnabled(false);
    initButtonStyle(nextButton);
    volumeMuteButton = new QPushButton(this->style()->standardIcon(QStyle::SP_MediaVolume), "");
    initButtonStyle(volumeMuteButton);
    progressSlider = new PlayerSlider();

    QFont ft;
    ft.setPointSize(12);
    mediaStatusLabel = new QLabel(tr("--:--:--/--:--:--"));
    mediaStatusLabel ->setMinimumSize(30, 30);
    mediaStatusLabel ->setFont(ft);
    mediaStatusLabel->setStyleSheet("color: white;");
    mediaStatusLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    mediaNameLabel = new QLabel();
    mediaNameLabel->setStyleSheet("color: white;");
    mediaNameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    mediaNameLabel->setFont(ft);
    mediaNameLabel->setMargin(10);

    videoWidget = new QVideoWidget();
    videoWidget -> setAutoFillBackground(true);

    videoWidget ->setAspectRatioMode(Qt::KeepAspectRatio);
    pMediaPlayer = new QMediaPlayer(this);
    pMediaPlaylist = new QMediaPlaylist(pMediaPlayer);
    pMediaPlayer->setVideoOutput(videoWidget);

    mainLayout->addWidget(videoWidget, 12);
    mainLayout->addWidget(progressSlider, 1);
    mainLayout->addWidget(mediaNameLabel, 1);
    mainLayout->addLayout(panelLayout);
    mainLayout->setMargin(0);

    panelLayout->addWidget(playButton, 2);
    panelLayout->addWidget(stopButton, 2);
    panelLayout->addWidget(previousButton, 2);
    panelLayout->addWidget(nextButton, 2);
    panelLayout->addWidget(volumeMuteButton, 1);
    panelLayout->addWidget(mediaStatusLabel, 3);
    panelLayout->setMargin(0);

    connect(playButton, SIGNAL(clicked()), this, SLOT(onPlayAndPause()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(onStop()));
    connect(previousButton, SIGNAL(clicked()), this, SLOT(onPrevious()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(onNext()));
    connect(progressSlider, SIGNAL(sigProgress(qint64)), pMediaPlayer, SLOT(setPosition(qint64)));
    connect(volumeMuteButton, SIGNAL(clicked()), this, SLOT(onVolumnMute()));

    connect(pMediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));
    connect(pMediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(onDurationChanged(qint64)));
    connect(pMediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(onStateChanged(QMediaPlayer::State)));
    connect(pMediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(pMediaPlaylist, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
    connect(progressSlider, SIGNAL(sigProgress(qint64)), pMediaPlayer, SLOT(setPosition(qint64)));

}

void VideoPlayer::initButtonStyle(QPushButton* button)
{
    QSize buttonSize(30, 30);

    button->setStyleSheet(BUTTON_INFO);
    button->setMinimumSize(buttonSize);
    button->setCursor(Qt::PointingHandCursor);
}

void VideoPlayer::initMedia()
{
    pMediaPlaylist->clear();
    pMediaPlayer->setPlaylist(pMediaPlaylist);
}

VideoPlayer::~VideoPlayer()
{

}

void VideoPlayer::resizeEvent(QResizeEvent* size)
{
    Q_UNUSED(size)
    //    videoWidget->move((size->size().width() - videoWidget->width())/2,(size->size().height() - videoWidget->height())/2);
}

void VideoPlayer::onPlayAndPause()
{
    switch(pMediaPlayer->state())
    {
    case QMediaPlayer::State::PlayingState:
        pMediaPlayer->pause();
        break;
    case QMediaPlayer::State::PausedState:
        pMediaPlayer->play();
        break;
    case QMediaPlayer::State::StoppedState:
        pMediaPlayer->play();
        break;
    default:
        break;
    }
}


void VideoPlayer::onStop()
{
    if(pMediaPlayer->state() == QMediaPlayer::State::PlayingState ||
            pMediaPlayer->state() == QMediaPlayer::State::PausedState)
    {
        pMediaPlayer->stop();
        pMediaPlayer->setPosition(0);
    }
}

void VideoPlayer::onNext()
{
    pMediaPlaylist->next();  
    pMediaPlayer->play();    
}

void VideoPlayer::onPrevious()
{
    pMediaPlaylist->previous();   
    pMediaPlayer->play();
}


void VideoPlayer::onPositionChanged(qint64 pos)
{
    QString str = QString("%1/%2").arg(MathUtils::millisecondToTimeString(pos)).arg(MathUtils::millisecondToTimeString(pMediaPlayer->duration()));
    mediaStatusLabel->setText(str);
    progressSlider->setProgress(pos);
}

void VideoPlayer::onDurationChanged(qint64 duration)
{
    if (duration > 0)
    {
        QString str = QString("%1/%2").arg(MathUtils::millisecondToTimeString(pMediaPlayer->position())).arg(MathUtils::millisecondToTimeString(duration));
        mediaStatusLabel->setText(str);
        progressSlider->setRange(0, duration);
    }
}

void VideoPlayer::onVolumnMute()
{
    if(pMediaPlayer->isMuted()) {
        pMediaPlayer->setMuted(false);
        volumeMuteButton->setIcon(this->style()->standardIcon(QStyle::SP_MediaVolume));
    }
    else {
        pMediaPlayer->setMuted(true);
        volumeMuteButton->setIcon(this->style()->standardIcon(QStyle::SP_MediaVolumeMuted));
    }
}

void VideoPlayer::onStateChanged(QMediaPlayer::State state)
{
    switch(state)
    {
    case QMediaPlayer::State::PlayingState:
        playButton->setIcon(this->style()->standardIcon(QStyle::SP_MediaPause));
        stopButton->setEnabled(true);
        progressSlider->setEnabled(true);
        break;
    case QMediaPlayer::State::PausedState:
        playButton->setIcon(this->style()->standardIcon(QStyle::SP_MediaPlay));
        stopButton->setEnabled(true);
        progressSlider->setEnabled(true);
        break;
    case QMediaPlayer::State::StoppedState:
        playButton->setIcon(this->style()->standardIcon(QStyle::SP_MediaPlay));
        stopButton->setEnabled(false);
        progressSlider->setEnabled(false);
        break;
    default:
        break;
    }
}

void VideoPlayer::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    qDebug()<<"onMediaStatusChanged:" << status;
//    if(status == QMediaPlayer::MediaStatus::LoadingMedia) {
//        pMediaPlayer->play();
//    }
}

void VideoPlayer::onCurrentIndexChanged(int index)
{
    Q_UNUSED(index)

    if(!pMediaPlaylist->currentMedia().isNull())
    {
        QString nameLabelString = QString("%1 (%2/%3)").arg(pMediaPlaylist->currentMedia().canonicalUrl().fileName()).arg(index + 1).arg(pMediaPlaylist->mediaCount());
        mediaNameLabel->setText(nameLabelString);
    }

    if(pMediaPlaylist->currentIndex() == pMediaPlaylist->mediaCount() - 1)
    {
        nextButton->setEnabled(false);
        if(pMediaPlaylist->mediaCount() > 1) previousButton->setEnabled(true);
    }
    else if(pMediaPlaylist->currentIndex() == 0)
    {
        previousButton->setEnabled(false);
        if(pMediaPlaylist->mediaCount() > 1) nextButton->setEnabled(true);
    }
    else
    {
        previousButton->setEnabled(true);
        nextButton->setEnabled(true);
    }
}

void VideoPlayer::onFileSelected(QString filePath)
{
    pMediaPlayer->stop();
    pMediaPlaylist->addMedia(QUrl::fromLocalFile(filePath));
    pMediaPlaylist->setCurrentIndex(pMediaPlaylist->mediaCount() - 1);
    pMediaPlayer->play();
}

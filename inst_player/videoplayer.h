#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include <playerslider.h>

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();

signals:

private:
    QVBoxLayout* mainLayout;
    QHBoxLayout* panelLayout;

    QVideoWidget* videoWidget;
    QMediaPlayer *pMediaPlayer;
    QMediaPlaylist *pMediaPlaylist;
    QPushButton* playButton;
    QPushButton* stopButton;
    QPushButton* nextButton;
    QPushButton* previousButton;
    QPushButton* volumeMuteButton;
    PlayerSlider* progressSlider;
    QLabel* mediaStatusLabel;
    QLabel* mediaNameLabel;

    void initLayout();    
    void initButtonStyle(QPushButton* button);
    void initMedia();

    void resizeEvent(QResizeEvent* size);

private slots:
    void onPlayAndPause();
    void onStop();
    void onNext();
    void onPrevious();
    void onPositionChanged(qint64 pos);
    void onDurationChanged(qint64 duration);
    void onVolumnMute();
    void onStateChanged(QMediaPlayer::State);
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void onCurrentIndexChanged(int index);
    void onFileSelected(QString filePath);

};

#endif // VIDEOPLAYER_H

#ifndef PHOTOVIEWER_H
#define PHOTOVIEWER_H

#include <QWidget>
#include <QResizeEvent>
#include <QLabel>
#include <QImage>
#include <QFileInfo>
#include <QGridLayout>

class PhotoViewer : public QWidget
{
    Q_OBJECT
public:
    explicit PhotoViewer(QWidget *parent = nullptr);
    ~PhotoViewer();

signals:

private:
    QGridLayout* layout;
    QFileInfoList fileInfoList;
    QLabel* imageLabel;
    QImage image;
    int currentFileIndex;
    void resizeEvent(QResizeEvent* size);
    void keyPressEvent(QKeyEvent *event);

    void resizeLabel();
    void loadImageList(int index);
    void loadImage(int currentFileIndex);

};

#endif // PHOTOVIEWER_H

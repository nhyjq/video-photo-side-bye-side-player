#include "photoviewer.h"

#include <QDebug>
#include <QDir>
#include <QSettings>
#include <QMessageBox>
#include <QTextCodec>

PhotoViewer::PhotoViewer(QWidget *parent) : QWidget(parent)
{

    this->layout = new QGridLayout(this);
    this->imageLabel = new QLabel(this);
    this->layout->addWidget((imageLabel));
    this->layout->setMargin(0);
    currentFileIndex = 0;

    this->loadImageList(0);
    this->setFocusPolicy(Qt::StrongFocus);

}

void PhotoViewer::resizeEvent(QResizeEvent* size)
{
    Q_UNUSED(size)
    this->resizeLabel();
}

void PhotoViewer::resizeLabel()
{
    QImage imgScaled;
    float scale = 0;

    if(image.isNull()) return;

    QPixmap pixmap = QPixmap::fromImage(image);
    QSize imageSize = pixmap.size();
    if(imageSize.width() > imageSize.height())
    {
        scale = this->width() / (float)imageSize.width();
        imgScaled = image.scaled(imageSize.width() * scale, imageSize.height() * scale, Qt::KeepAspectRatio);
    }
    else
    {
        scale = this->height() / (float)imageSize.height();
        imgScaled = image.scaled(imageSize.width() * scale, imageSize.height() * scale, Qt::KeepAspectRatio);
    }
    pixmap = QPixmap::fromImage(imgScaled);
    imageSize = pixmap.size();
    imageLabel->setPixmap(pixmap);
    imageLabel->resize(imageSize);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->move((this->width() - imageLabel->width())/2,(this->height() - imageLabel->height())/2);
}

PhotoViewer::~PhotoViewer()
{
    delete imageLabel;
}

void PhotoViewer::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_PageDown)
    {
        currentFileIndex++;
        if(currentFileIndex == fileInfoList.length())
            currentFileIndex = 0;
        this->loadImage(currentFileIndex);
    }
    else if (event->key() == Qt::Key_PageUp)
    {
        currentFileIndex--;
        if(currentFileIndex < 0)
            currentFileIndex = fileInfoList.length() - 1;
        this->loadImage(currentFileIndex);
    }
    else if (event->key() == Qt::Key_Home)
    {
        currentFileIndex=0;
        this->loadImage(currentFileIndex);
    }
    else if (event->key() == Qt::Key_End)
    {
        currentFileIndex = fileInfoList.length() - 1;
        this->loadImage(currentFileIndex);
    }
    else if (event->key() == Qt::Key_1)
    {
        this->loadImageList(0);
    }
    else if (event->key() == Qt::Key_2)
    {
        this->loadImageList(1);
    }
    else if (event->key() == Qt::Key_3)
    {
        this->loadImageList(2);
    }
    else if (event->key() == Qt::Key_4)
    {
        this->loadImageList(3);
    }
    else if (event->key() == Qt::Key_4)
    {
        this->loadImageList(4);
    }
    else if (event->key() == Qt::Key_5)
    {
        this->loadImageList(5);
    }
    else if (event->key() == Qt::Key_6)
    {
        this->loadImageList(6);
    }
    else if (event->key() == Qt::Key_7)
    {
        this->loadImageList(7);
    }
    else if (event->key() == Qt::Key_8)
    {
        this->loadImageList(8);
    }
    else if (event->key() == Qt::Key_9)
    {
        this->loadImageList(9);
    }
    else if (event->key() == Qt::Key_0)
    {
        this->loadImageList(10);
    }
    else {
        event->ignore();
    }
}

void PhotoViewer::loadImageList(int index)
{

    QSettings iniFile("player.ini", QSettings::IniFormat);
    iniFile.setIniCodec(QTextCodec::codecForName("UTF-8"));
    QString key = QString("Photo/PhotoFolder%1").arg(index+1);
    if(!iniFile.contains(key))
        return;

    QString folderPath = iniFile.value(key).toString();

    QDir dir(folderPath);
    if(!dir.exists(folderPath))
        return;

    QStringList filters;
    filters<<QString("*.jpeg")<<QString("*.jpg")<<QString("*.JPG")<<QString("*.bmp")<<QString("*.png");
    this->fileInfoList = dir.entryInfoList(filters, QDir::Files);
    currentFileIndex = 0;
    loadImage(0);
}
void PhotoViewer::loadImage(int currentFileIndex)
{
    image.load(fileInfoList.at(currentFileIndex).filePath());
    this->resizeLabel();
}

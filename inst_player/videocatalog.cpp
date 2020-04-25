#include "videocatalog.h"

#include <QDebug>

#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QSettings>
#include <QTextCodec>

VideoCatalog::VideoCatalog(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout(this);
    dirCombobox = new QComboBox();
    layout->addWidget(dirCombobox);

    QSettings iniFile("player.ini", QSettings::IniFormat);
    iniFile.setIniCodec(QTextCodec::codecForName("UTF-8"));
    iniFile.beginGroup("Video");
    QStringList folderKeyList = iniFile.childKeys();
    for(int i = 0; i < folderKeyList.count(); i++)
    {
        dirCombobox->addItem(iniFile.value(folderKeyList.at(i)).toString(), iniFile.value(folderKeyList.at(i)).toString());
    }

    dirCombobox->setStyleSheet("background-color:white;");
    connect(dirCombobox,SIGNAL(currentIndexChanged(int)),this,SLOT(onDirComboValueChanged(int)));
    this->initListWidget();
    layout->setMargin(0);
    refreshFileList(0);
}

VideoCatalog::~VideoCatalog()
{

}

void VideoCatalog::initListWidget()
{
    listWidget = new QListWidget(this);
    layout->addWidget(listWidget);
    listWidget->setResizeMode(QListView::Adjust);
    listWidget->setMovement(QListView::Static);
    listWidget->setSpacing(2);
    listWidget->setViewMode(QListView::ListMode);
    listWidget->setStyleSheet("background-color:white;");
    connect(listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(onItemDoubleClicked(QListWidgetItem *)));
}

void VideoCatalog::refreshFileList(int index)
{
    int roleId = Qt::UserRole + 1;
    QDir dir(dirCombobox->itemData(index).toString());
    QStringList filters;
    filters<<QString("*.avi")<<QString("*.mp4")<<QString("*.rm")<<QString("*.RM")<<QString("*.rmvb")<<QString("*.wmv")<<QString("*.bhd");
    QFileInfoList fileInfoList = dir.entryInfoList(filters, QDir::Files);
    listWidget->clear();
    for(int i = 0; i < fileInfoList.size(); i++)
    {
        QListWidgetItem *fileItem = new QListWidgetItem();
        QString fullPath = fileInfoList.at(i).filePath();
        QString fileName = fileInfoList.at(i).fileName();
        fileItem->setIcon(this->style()->standardIcon(QStyle::SP_FileIcon));
        fileItem->setText(fileName);
        fileItem->setData(roleId, fullPath);
        listWidget->addItem(fileItem);
    }
}

void VideoCatalog::onDirComboValueChanged(int index)
{
    refreshFileList(index);
}

void VideoCatalog::onItemDoubleClicked(QListWidgetItem *item)
{
    int roleId = Qt::UserRole + 1;
//    qDebug()<<item->data(roleId).toString();
//    qDebug()<<this->parent()->parent()->objectName();

    emit(fileSelected(item->data(roleId).toString()));
}

#ifndef VIDEOCATALOG_H
#define VIDEOCATALOG_H

#include <QWidget>
#include <QGridLayout>
#include <QListWidget>
#include <QComboBox>

class VideoCatalog : public QWidget
{
    Q_OBJECT
public:
    explicit VideoCatalog(QWidget *parent = nullptr);
    ~VideoCatalog();

signals:
    void fileSelected(QString filePath);

private:
    QGridLayout* layout;
    QListWidget* listWidget;
    QComboBox* dirCombobox;

    void initListWidget();
    void refreshFileList(int index);

private slots:
    void onDirComboValueChanged(int index);
    void onItemDoubleClicked(QListWidgetItem *item);
};

#endif // VIDEOCATALOG_H

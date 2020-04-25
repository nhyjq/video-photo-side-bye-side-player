#include "playerslider.h"

PlayerSlider::PlayerSlider(QWidget * parent) : QSlider(parent)
{
    this->setOrientation(Qt::Horizontal);
    m_bPressed = false;
}

void PlayerSlider::mousePressEvent(QMouseEvent *e)
{
    m_bPressed = true;
    QSlider::mousePressEvent(e);
}

void PlayerSlider::mouseMoveEvent(QMouseEvent *e)
{
//    m_bPressed = false;
    qint64 i64Pos = value();
    emit sigProgress(i64Pos);

    QSlider::mouseMoveEvent(e);
}

void PlayerSlider::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
//    qint64 i64Pos = value();
//    emit sigProgress(i64Pos);

    QSlider::mouseReleaseEvent(e);
}

void PlayerSlider::setProgress(qint64 i64Progress)
{
    if (!m_bPressed)
        setValue(i64Progress);
}




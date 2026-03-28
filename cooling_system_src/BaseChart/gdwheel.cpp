#include "gdwheel.h"

GDWheel::GDWheel(QWidget *parent)
    : QWidget{parent}
{}
void GDWheel::wheelEvent(QWheelEvent *event) {
    emit signalWheelEvent(event);
    QWidget::wheelEvent(event);
}
#if (QT_VERSION <= QT_VERSION_CHECK(6,0,0))
void GDWheel::enterEvent(QEvent* event)
{
    emit signalInterOut(1);
    QWidget::enterEvent(event);
}
#else
void GDWheel::enterEvent(QEnterEvent* event)
{
    emit signalInterOut(1);
    QWidget::enterEvent(event);
}
#endif
void GDWheel::leaveEvent(QEvent* event)
{
    emit signalInterOut(0);
    QWidget::leaveEvent(event);
}

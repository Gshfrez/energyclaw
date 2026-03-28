#ifndef GDWHEEL_H
#define GDWHEEL_H

#include <QWidget>

class GDWheel : public QWidget
{
    Q_OBJECT
public:
    explicit GDWheel(QWidget *parent = nullptr);
private slots:
    void wheelEvent(QWheelEvent *event);
#if (QT_VERSION <= QT_VERSION_CHECK(6,0,0))
    void enterEvent(QEvent* event);
#else
    void enterEvent(QEnterEvent* event);
#endif
    void leaveEvent(QEvent* event);
signals:
    void signalWheelEvent(QWheelEvent *event);
    void signalInterOut(bool midinout);
};

#endif // GDWHEEL_H

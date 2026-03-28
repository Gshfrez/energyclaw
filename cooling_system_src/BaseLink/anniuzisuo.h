#ifndef ANNIUZISUO_H
#define ANNIUZISUO_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>
#include <QPalette>

class AnNiuZiSuo : public QWidget
{
    Q_OBJECT

public:
    explicit AnNiuZiSuo(QWidget *parent = nullptr);

    void setpix(QPixmap midpix);
    void setpixDj(QPixmap midpixDj);

    void set_QText(QString midText);
    void set_QFont(QFont midFont);

    void set_QPlt(QPalette midPlt);
    void set_QPltDj(QPalette midPltDj);

    void setUpDown(int middown);
    void setAnNiuWH(int w,int h);
    void set_QType(int midtype);
signals:
    void AnNiuClicked();
private slots:
#if (QT_VERSION <= QT_VERSION_CHECK(6,0,0))
    void enterEvent(QEvent* event);
#else
    void enterEvent(QEnterEvent* event);
#endif
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    QPixmap pix;
    QPixmap pixDj;

    QLabel Tu;
    QLabel TuXf;
    QLabel TuDj;
    QLabel TuDjXf;

    QLabel Text;

    QPalette Plt;
    QPalette PltDj;

    int midW=10;
    int midH=10;
    int If_UpDown=0;
    int Type=0;
};

#endif // ANNIUZISUO_H

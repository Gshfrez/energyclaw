#ifndef ANNIUDIANDONG_H
#define ANNIUDIANDONG_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>
#include <QPalette>

class AnniuDiandong : public QWidget
{
    Q_OBJECT

public:
    explicit AnniuDiandong(QWidget *parent = nullptr);

    void setpix(QPixmap *midpix);
    void setpixXf(QPixmap *midpixXf);
    void setpixDj(QPixmap *midpixDj);
    void set_QText(QString midText);
    void set_QPlt(QPalette midPlt);
    void set_QPltDj(QPalette midPltDj);
    void set_QFont(QFont midFont);
    void setAnNiuWH(int w,int h);
protected:
#if (QT_VERSION <= QT_VERSION_CHECK(6,0,0))
    void enterEvent(QEvent* event);
#else
    void enterEvent(QEnterEvent* event);
#endif
    void leaveEvent(QEvent* event);
signals:
    void AnNiuClicked();
private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    QPixmap *pix;
    QPixmap *pixXf;
    QPixmap *pixDj;

    QLabel Tu;
    QLabel TuXf;
    QLabel TuDj;

    QLabel Text;

    QPalette Plt;
    QPalette PltDj;

    int midW=10;
    int midH=10;
};

#endif // ANNIUDIANDONG_H

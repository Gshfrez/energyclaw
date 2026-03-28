#ifndef ICON_ONOFF_H
#define ICON_ONOFF_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>
#include <BaseCache.h>
class Icon_OnOff : public QWidget
{
    Q_OBJECT
public:
    explicit Icon_OnOff(QWidget *parent = nullptr);
    void setOnOff(int midOnOff);
    void setShow();
    void setWH(int mid_W,int mid_H);
    void set_ZhuTi(bool mid_zhuti);
    bool GetOnOff();
    void CantClick();
signals:
    void OffOnClicked(int);
private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:

    QLabel Off;
    QLabel On;

    int midW=20;
    int midH=10;
    bool If_OffOn=0;
    bool midZhuTi=0;
    bool canbrclick=1;
};

#endif // ICON_ONOFF_H

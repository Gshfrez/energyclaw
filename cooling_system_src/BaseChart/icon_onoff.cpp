#include "icon_onoff.h"
Icon_OnOff::Icon_OnOff(QWidget *parent)
    : QWidget{parent}
{
    Off.setParent(this);
    On.setParent(this);
}
void Icon_OnOff::set_ZhuTi(bool mid_zhuti)
{
    midZhuTi=mid_zhuti;
}
bool Icon_OnOff::GetOnOff()
{
    return If_OffOn;
}
void Icon_OnOff::CantClick()
{
    canbrclick=0;
}
void Icon_OnOff::setShow()
{

    Off.setGeometry((this->width()-midW)/2,(this->height()-midH)/2,midW,midH);
    On.setGeometry((this->width()-midW)/2,(this->height()-midH)/2,midW,midH);

    QPixmap *midOnPix;
    QPixmap *midOffPix;
    if(midZhuTi==0)
    {
        midOnPix=new QPixmap(":/image/jisuan/ICON_ON.png");
        midOffPix=new QPixmap(":/image/jisuan/ICON_OFF.png");
    }
    else
    {
        midOnPix=new QPixmap(":/image/jisuan/ICON_ON_H.png");
        midOffPix=new QPixmap(":/image/jisuan/ICON_OFF_H.png");
    }

    Off.setPixmap(midOffPix->scaled(midW,midH,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    On.setPixmap(midOnPix->scaled(midW,midH,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    if(If_OffOn==0)
    {
        Off.setHidden(0);
        On.setHidden(1);
    }
    else
    {
        Off.setHidden(1);
        On.setHidden(0);
    }
}
void Icon_OnOff::mousePressEvent(QMouseEvent *)
{
}
void Icon_OnOff::mouseReleaseEvent(QMouseEvent *event)
{
    if(canbrclick)
    {
        if (event->button() == Qt::LeftButton)
        {
#if (QT_VERSION <= QT_VERSION_CHECK(6,0,0))
            int midx =event->x();
            int midy =event->y();
#else
            int midx =event->position().x();
            int midy =event->position().y();
#endif
            int midstartX=(this->width()-midW)/2;
            int midstartY=(this->height()-midH)/2;
            if(midx>midstartX&&midx<=midstartX+midW&&midy>midstartY&&midy<=midstartY+midH)
            {
                if(If_OffOn==0)
                {
                    Off.setHidden(1);
                    On.setHidden(0);
                    If_OffOn=1;
                    emit OffOnClicked(1);
                }
                else
                {
                    Off.setHidden(0);
                    On.setHidden(1);
                    If_OffOn=0;
                    emit OffOnClicked(0);
                }
            }
            else
            {
                if(If_OffOn==0)
                {
                    Off.setHidden(0);
                    On.setHidden(1);
                }
                else
                {
                    Off.setHidden(1);
                    On.setHidden(0);
                }
            }
        }
    }
}
void Icon_OnOff::setOnOff(int middown)
{
    If_OffOn=middown;
    if(If_OffOn==0)
    {
        Off.setHidden(0);
        On.setHidden(1);
    }
    else
    {
        Off.setHidden(1);
        On.setHidden(0);
    }
}
void Icon_OnOff::setWH(int mid_W,int mid_H)
{
    midW=mid_W;
    midH=mid_H;
}

#include "anniuzisuo.h"
AnNiuZiSuo::AnNiuZiSuo(QWidget *parent)
    : QWidget{parent}
{
    Tu.setParent(this);
    TuXf.setParent(this);
    TuDj.setParent(this);
    TuDjXf.setParent(this);

    Text.setParent(this);
    Text.setAlignment(Qt::AlignCenter);

    Plt.setColor(QPalette::WindowText, QColor(0, 0, 0));
    PltDj.setColor(QPalette::WindowText, QColor(0, 0, 0));

    pix.load(":/image/jisuan/KongPng.png");
    pixDj.load(":/image/jisuan/KongPng.png");
}
void AnNiuZiSuo::setpix(QPixmap midpix)
{
    pix=midpix;
}
void AnNiuZiSuo::setpixDj(QPixmap midpixDj)
{
    pixDj=midpixDj;
}
void AnNiuZiSuo::setAnNiuWH(int w,int h)
{
    if(Type==0)
    {
        int midwww=w/20;
        int midwwwX=w/10;
        int midhhh=h/20;
        int midhhhX=h/10;
        if(midwww<=1)
        {
            midwww=1;
            midwwwX=2;
            midhhh=1;
            midhhhX=2;
        }
        if(midhhh<=1)
        {
            midwww=1;
            midwwwX=2;
            midhhh=1;
            midhhhX=2;
        }

        Tu.setGeometry(midwww,midhhh,w-midwwwX,h-midhhhX);
        TuXf.setGeometry(0,0,w,h);
        TuDj.setGeometry(midwww,midhhh,w-midwwwX,h-midhhhX);
        TuDjXf.setGeometry(0,0,w,h);
        Tu.setPixmap(pix.scaled(w-midwwwX,h-midhhhX,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        TuXf.setPixmap(pix.scaled(w,h,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        TuDj.setPixmap(pixDj.scaled(w-midwwwX,h-midhhhX,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        TuDjXf.setPixmap(pixDj.scaled(w,h,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    else
    {
        Tu.setGeometry(0,0,w,h);
        TuXf.setGeometry(0,0,w,h);
        TuDj.setGeometry(0,0,w,h);
        TuDjXf.setGeometry(0,0,w,h);
        Tu.setPixmap(pix.scaled(w,h,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        TuXf.setPixmap(pixDj.scaled(w,h,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        TuDj.setPixmap(pixDj.scaled(w,h,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        TuDjXf.setPixmap(pixDj.scaled(w,h,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    Text.setGeometry(0,0,w,h);

    if(If_UpDown<0.5)
    {
        Text.setPalette(Plt);
        Tu.setHidden(0);
        TuXf.setHidden(1);
        TuDj.setHidden(1);
        TuDjXf.setHidden(1);
    }
    else
    {
        Text.setPalette(PltDj);
        Tu.setHidden(1);
        TuXf.setHidden(1);
        TuDj.setHidden(0);
        TuDjXf.setHidden(1);
    }
    midW=w;
    midH=h;
}
#if (QT_VERSION <= QT_VERSION_CHECK(6,0,0))
void AnNiuZiSuo::enterEvent(QEvent* event)
{
    Q_UNUSED(event)
    if(If_UpDown<0.5)
    {
        Tu.setHidden(1);
        TuXf.setHidden(0);
        TuDj.setHidden(1);
        TuDjXf.setHidden(1);
    }
    else
    {
        Tu.setHidden(1);
        TuXf.setHidden(1);
        TuDj.setHidden(1);
        TuDjXf.setHidden(0);
    }
}
#else
void AnNiuZiSuo::enterEvent(QEnterEvent* event)
{
    Q_UNUSED(event)
    if(If_UpDown<0.5)
    {
        Tu.setHidden(1);
        TuXf.setHidden(0);
        TuDj.setHidden(1);
        TuDjXf.setHidden(1);
    }
    else
    {
        Tu.setHidden(1);
        TuXf.setHidden(1);
        TuDj.setHidden(1);
        TuDjXf.setHidden(0);
    }
}
#endif
void AnNiuZiSuo::leaveEvent(QEvent* event)
{
    Q_UNUSED(event)
    if(If_UpDown<0.5)
    {
        Tu.setHidden(0);
        TuXf.setHidden(1);
        TuDj.setHidden(1);
        TuDjXf.setHidden(1);
    }
    else
    {
        Tu.setHidden(1);
        TuXf.setHidden(1);
        TuDj.setHidden(0);
        TuDjXf.setHidden(1);
    }
}
void AnNiuZiSuo::mousePressEvent(QMouseEvent *)
{
}
void AnNiuZiSuo::mouseReleaseEvent(QMouseEvent *event)
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
        if(midx>=0 && midx<midW && midy>=0 && midy<midH)
        {
            if(If_UpDown<0.5)
            {
                Tu.setHidden(1);
                TuXf.setHidden(1);
                TuDj.setHidden(1);
                TuDjXf.setHidden(0);
                Text.setPalette(PltDj);
                If_UpDown=1;
                emit AnNiuClicked();
            }
            else
            {
                Tu.setHidden(1);
                TuXf.setHidden(0);
                TuDj.setHidden(1);
                TuDjXf.setHidden(1);
                Text.setPalette(Plt);
                If_UpDown=0;
                emit AnNiuClicked();
            }
        }
        else
        {
            if(If_UpDown<0.5)
            {
                Tu.setHidden(0);
                TuXf.setHidden(1);
                TuDj.setHidden(1);
                TuDjXf.setHidden(1);
            }
            else
            {
                Tu.setHidden(1);
                TuXf.setHidden(1);
                TuDj.setHidden(0);
                TuDjXf.setHidden(1);
            }
        }
    }
}
void AnNiuZiSuo::set_QText(QString midText)
{
    Text.setText(midText);
}
void AnNiuZiSuo::set_QPlt(QPalette midPlt)
{
    Plt=midPlt;
    PltDj=midPlt;
}
void AnNiuZiSuo::set_QPltDj(QPalette midPltDj)
{
    PltDj=midPltDj;
}
void AnNiuZiSuo::set_QFont(QFont midFont)
{
    Text.setFont(midFont);
}
void AnNiuZiSuo::setUpDown(int middown)
{
    If_UpDown=middown;
    if(If_UpDown<0.5)
    {
        Text.setPalette(Plt);
        Tu.setHidden(0);
        TuXf.setHidden(1);
        TuDj.setHidden(1);
        TuDjXf.setHidden(1);
    }
    else
    {
        Text.setPalette(PltDj);
        Tu.setHidden(1);
        TuXf.setHidden(1);
        TuDj.setHidden(0);
        TuDjXf.setHidden(1);
    }
}
void AnNiuZiSuo::set_QType(int midtype)
{
    Type=midtype;
}

#include "anniudiandong.h"
AnniuDiandong::AnniuDiandong(QWidget *parent)
    : QWidget{parent}
{
    Tu.setParent(this);
    TuXf.setParent(this);
    TuDj.setParent(this);
    Text.setParent(this);
    Text.setText("");
    Text.setAlignment(Qt::AlignCenter);
    PltDj.setColor(QPalette::WindowText, QColor(0, 0, 0));
    Plt.setColor(QPalette::WindowText, QColor(0, 0, 0));
    pix.load(":/image/jisuan/KongPng.png");
    pixXf.load(":/image/jisuan/KongPng.png");
    pixDj.load(":/image/jisuan/KongPng.png");
}
void AnniuDiandong::setpix(QPixmap midpix)
{
    pix=midpix;
    pixXf=midpix;
    pixDj=midpix;
}
void AnniuDiandong::setpixXf(QPixmap midpixXf)
{
    pixXf=midpixXf;
    pixDj=midpixXf;
}
void AnniuDiandong::setpixDj(QPixmap midpixDj)
{
    pixDj=midpixDj;
}
void AnniuDiandong::setAnNiuWH(int w,int h)
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
    TuDj.setGeometry(0,0,w,h);

    Text.setGeometry(0,0,w,h);
    Text.setPalette(Plt);

    Tu.setPixmap(pix.scaled(w-midwwwX,h-midhhhX,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    TuXf.setPixmap(pixXf.scaled(w,h,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    TuDj.setPixmap(pixDj.scaled(w,h,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    Tu.setHidden(0);
    TuXf.setHidden(1);
    TuDj.setHidden(1);
    midW=w;
    midH=h;
}
#if (QT_VERSION <= QT_VERSION_CHECK(6,0,0))
void AnniuDiandong::enterEvent(QEvent* event)
{
    Q_UNUSED(event)
    Tu.setHidden(1);
    TuXf.setHidden(0);
    TuDj.setHidden(1);
}
#else
void AnniuDiandong::enterEvent(QEnterEvent* event)
{
    Q_UNUSED(event)
    Tu.setHidden(1);
    TuXf.setHidden(0);
    TuDj.setHidden(1);
}
#endif

void AnniuDiandong::leaveEvent(QEvent* event)
{
    Q_UNUSED(event)
    Tu.setHidden(0);
    TuXf.setHidden(1);
    TuDj.setHidden(1);
}
void AnniuDiandong::mousePressEvent(QMouseEvent *event)
{
    grabMouse();
    if (event->button() == Qt::LeftButton)
    {
        Tu.setHidden(1);
        TuXf.setHidden(1);
        TuDj.setHidden(0);
        Text.setPalette(PltDj);
    }
}
void AnniuDiandong::mouseReleaseEvent(QMouseEvent *event)
{
    releaseMouse();
    if (event->button() == Qt::LeftButton)
    {
        #if (QT_VERSION <= QT_VERSION_CHECK(6,0,0))
            int midx =event->x();
            int midy =event->y();
        #else
            int midx =event->position().x();
            int midy =event->position().y();
        #endif
        Text.setPalette(Plt);
        if(midx>=0 && midx<midW && midy>=0 && midy<midH)
        {
            Tu.setHidden(1);
            TuXf.setHidden(0);
            TuDj.setHidden(1);
            emit AnNiuClicked();
        }
        else
        {
            Tu.setHidden(0);
            TuXf.setHidden(1);
            TuDj.setHidden(1);
        }
    }
}
void AnniuDiandong::set_QText(QString midText)
{
    Text.setText(midText);
}
void AnniuDiandong::set_QPlt(QPalette midPlt)
{
    Plt=midPlt;
}
void AnniuDiandong::set_QPltDj(QPalette midPltDj)
{
    PltDj=midPltDj;
}
void AnniuDiandong::set_QFont(QFont midFont)
{
    Text.setFont(midFont);
}

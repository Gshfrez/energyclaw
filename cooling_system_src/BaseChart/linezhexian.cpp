#include "linezhexian.h"

LineZheXian::LineZheXian(QWidget *parent)
    : QWidget{parent}
{
    Psf.resize(0);
}
void LineZheXian::SetPointF(QVector<QPointF> midpsf,double midXMin)
{
    Psf=midpsf;
    XMin=midXMin;
}
void LineZheXian::midpaint()
{
    // 画一条直线
    painter.begin(this);
    pen.setWidth(1);
    pen.setColor("#feb834");
    painter.setPen(pen);                // 设置画笔
    painter.setRenderHint(QPainter::Antialiasing,true);//设置反锯齿
    QPointF midmidmid[1000];
    if(Psf.size()==0)
    {
        for(int zi=0;zi<1000;zi++)
        {
            midmidmid[zi].setX(zi);
            midmidmid[zi].setY(zi/2);
        }
        painter.drawPolyline(midmidmid, 1000);
    }
    else
    {
        for(int zi=0;zi<Psf.size();zi++)
        {

            midmidmid[zi].setX(Psf[zi].x()-XMin);

            midmidmid[zi].setY(Psf[zi].y());
        }
        painter.drawPolyline(midmidmid, Psf.size());
    }
    painter.end();
}
void LineZheXian::paintEvent(QPaintEvent *)
{
    midpaint();
}

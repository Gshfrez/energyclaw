#ifndef LINEZHEXIAN_H
#define LINEZHEXIAN_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
class LineZheXian : public QWidget
{
    Q_OBJECT
public:
    explicit LineZheXian(QWidget *parent = nullptr);
    void midpaint();
    void paintEvent(QPaintEvent *);
    void SetPointF(QVector<QPointF> midpsf,double midXMin);
private:
    QPainter painter;             // 创建QPainter一个对象
    QPen pen;
    QVector<QPointF> Psf;
    double XMin=0;
};

#endif // LINEZHEXIAN_H

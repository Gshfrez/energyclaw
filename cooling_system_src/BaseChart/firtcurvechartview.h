#ifndef FIRTCURVECHARTVIEW_H
#define FIRTCURVECHARTVIEW_H

#include <QtCharts>
#include <QtCharts/QChartView>
class FirtCurveChartView : public QChartView
{
    Q_OBJECT
public:
    explicit FirtCurveChartView(QWidget *parent = nullptr);//explicit
private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

signals:
    void signalMouseEvent(int eventId, QMouseEvent *event);
    void signalWheelEvent(QWheelEvent *event);
};

#endif // FIRTCURVECHARTVIEW_H

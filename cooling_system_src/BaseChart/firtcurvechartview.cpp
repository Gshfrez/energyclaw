#include "firtcurvechartview.h"

FirtCurveChartView::FirtCurveChartView(QWidget *parent)
    : QChartView{parent}
{}
void FirtCurveChartView::mousePressEvent(QMouseEvent *event) {
    emit signalMouseEvent(0, event);
    QChartView::mousePressEvent(event);
}

void FirtCurveChartView::mouseMoveEvent(QMouseEvent *event) {
    emit signalMouseEvent(1, event);
    QChartView::mouseMoveEvent(event);
}

void FirtCurveChartView::mouseReleaseEvent(QMouseEvent *event) {
    emit signalMouseEvent(2, event);
    QChartView::mouseReleaseEvent(event);
}

void FirtCurveChartView::mouseDoubleClickEvent(QMouseEvent *event) {
    emit signalMouseEvent(3, event);
    QChartView::mouseDoubleClickEvent(event);
}

void FirtCurveChartView::wheelEvent(QWheelEvent *event) {
    emit signalWheelEvent(event);
    QChartView::wheelEvent(event);
}

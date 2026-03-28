#ifndef BASEICON_H
#define BASEICON_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QDate>
#include <QDateTime>
#include <QLineEdit>
#include <QPushButton>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QLineSeries>
#include <QSplineSeries>
#include <QPieSeries>
#include <QScopedPointer>
#include <FirtCurveChartView.h>
#include <AnniuDiandong.h>
#include <Icon_OnOff.h>
#include "FOLDEREDIT.h"
#include "BaseChartCache.h"

QT_BEGIN_NAMESPACE
class BaseIcon : public QWidget
{
    Q_OBJECT
public:
    explicit BaseIcon(QWidget *parent = nullptr);
    void PjtNameSet(QString midPjtName);
    void SeriesReplaceEnd();
    void SeriesValue(int pjtnb,int midviewnb,int midlinenb,Chart_PointCache midpoint,Chart_CacheSx midCacheSx,int midAllSize);
    void HengzhouValue(int pjtnb,int midviewnb,Chart_PointCache midpoint,Chart_CacheSx midCacheSx,int AllSize);
    void ChartClear();
    void ChartPointTrue();
    void LintTypeSet(int midLintType);
    void ViewStart();
    void SetZhuTi(bool midZhuTi);
    void Add_Series();
    bool SeriesNameGet(int midNb,QString &midVarName);
    int LintTypeGet();
    void SeriesInfoSet(int Xian_Nb,QString midVarName);
    void SeriesInfoClear(int Xian_Nb);
    union QtLineInfo {
        QLineSeries* m_Series0;
        QSplineSeries* m_Series1;
        QScatterSeries* m_Series2;
        QPieSeries* m_Series3;
    };
    struct QtLineInfo_Name {
        QLineEdit* VarName;
        int CanBeShow;
        QPieSlice* pie_slice;
        QBarSeries *bar_series;
        int BarPieNb;
    };
signals:
    void VarNameOut(int midlineNb,QString midVarName);//,Chart_VarInfo mid_viv);
    void CloseView();
private slots:
    void closeEvent ( QCloseEvent * event );
    bool event(QEvent *ev);
private:
    FirtCurveChartView *View;
    QChart* m_chart;
    QValueAxis *m_axisX, *m_axisY;
    QVector<QtLineInfo>LI;
    QVector<QtLineInfo_Name>LIN;
    QVector<QPointF>midPs;
    QVector<QPointF>midHeng;
    bool HengZhouCanBeShow=0;
    bool HengZhouValueGet=0;
    int maxNb[6]={0,0,0,0,0,0};
    //下面的变量是不可能占用内存逐渐增大的
    double AXIS_MAX_X = 0.2, AXIS_MAX_Y = 10.0;
    double AXIS_Min_X = 0.0, AXIS_Min_Y = 0.0;
    double Line_Min_Y[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
    double Line_Max_Y[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
    double SuoFangXiShu=1;
    bool isPressed = false;
    QVector<bool>LIN_Start;
    QString PjtName="";
    bool ZhuTi=0;
    QPalette midPlt;
    QPalette midPlt_H;
    QFont AnNiuFont;
    QPoint pressedPoint;
    QStringList list_pie_color = {
        "#feb834","#01b59c",
        "#ff3f5f","#028599",
        "#3bc7e2","#73655d",
    };
    int LintType=0;//默认折、0折线、1曲线、2散点
    AnniuDiandong SeriesAdd;
    AnniuDiandong SeriesClose;
    AnniuDiandong SaveToPng;

    QLineEdit X_VarName;
    Icon_OnOff midOffOn;
    bool X_VarName_start=0;
    bool X_VarName_set=0;
};
#endif // BASEICON_H

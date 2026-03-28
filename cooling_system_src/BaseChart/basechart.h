#ifndef BASECHART_H
#define BASECHART_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QLineEdit>
#include <QPalette>
#include <AnniuDiandong.h>
#include <BaseIcon.h>
#include <AnniuDiandong.h>
#include <AnNiuZiSuo.h>
#include <GDWheel.h>
#include <BaseCache.h>
#include <FirtCurveChartView.h>
class BaseChart : public QMainWindow
{
    Q_OBJECT
public:
    BaseChart(QWidget *parent = nullptr);
    void PjtNameStart(QString midPjtName);
    void PjtNameSet(QString midPjtName);
    void AddView(int midType);
    void PaiBan();
    void closeEvent ( QCloseEvent * event );
private slots:
    bool event(QEvent *ev);
private:
    QTimer* m_timer;
    QPalette midPlt_H;
    QWidget *Group_Bg;
    QWidget *Group;
    QLabel *Gd;
    GDWheel *Gd_bg;
    QLabel *CaoZuoTiShi;
    double MoveY=0;
    double MoveH=0;

    AnniuDiandong ShiTu1;
    AnniuDiandong ShiTu2;
    AnniuDiandong ShiTu3;
int PaiBanType=0;
    AnniuDiandong btnClear;
    AnniuDiandong SaveToPng;
    AnniuDiandong SaveToProject;
    QVector<BaseIcon*> graphicsView;
    QVector<bool> if_ViewShow;
    AnniuDiandong AddViewName[4];
    bool if_xianshizuobiaodianzi=0;
    bool if_KaiQiJiLu=1;
    int PjtNb=-1;
    QLineEdit *PjtNameEdit;
    bool PjtNameEdit_start=0;
    bool PjtNameEdit_set=0;
    QLineEdit* HuanCunShu;
    bool HuanCunShu_start=0;
    QLabel *PIDShow;
    QLabel *NameTiShi;
    QLabel *HunCunTiShi;
    QString PjtName;
    int geometry_w=800;
    int geometry_h=600;
    bool ZhuTiStart=0;
    bool if_Show = 1;
    int midAllSize=0;
    int XianLiang=1000;
    Chart_VarInfo VIV_Kong={0,-1,-1,0,-1,0,-1};
};
#endif // BASECHART_H

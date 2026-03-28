#ifndef BASELINK_H
#define BASELINK_H

#include <QMainWindow>
#include <QTimer>
#include <QFile>
#include <QLabel>
#include <QLineEdit>
#include <QPalette>
#include <AnniuDiandong.h>
#include <AnNiuZiSuo.h>
#include <ComLink.h>
#include <TcpLink.h>
#include "FOLDEREDIT.h"
class BaseLink : public QMainWindow
{
    Q_OBJECT
public:
    BaseLink(QWidget *parent = nullptr);
    void PjtNameStart(QString midPjtName);
    void PjtNameSet(QString midPjtName);
    void AddView(ComSave midComSaveInfo);
    void PaiBan();
    void closeEvent ( QCloseEvent * event );
    union ComTcpLinkCache{
        ComLink*Com;
        TcpLink*Tcp;
    };

private slots:
    void ComCodeSave();
    bool event(QEvent *ev);
    void wheelEvent(QWheelEvent *event);
private:

    QPalette midPlt_H;
    QWidget *Group_Bg;
    QWidget *Group;
    QLabel *Gd;
    QLabel *Gd_bg;
    int PaiBanType=0;
    double MoveY=0;
    double MoveH=0;
    AnniuDiandong SaveToProject;
    AnniuDiandong ShiTu1;
    AnniuDiandong ShiTu2;
    AnniuDiandong ShiTu3;
    QVector<ComTcpLinkCache> ComTcp_Link;
    QVector<int> if_ComShow;
    AnniuDiandong AddViewName[2];
    bool if_xianshizuobiaodianzi=0;
    int PjtNb=-1;
    QLineEdit *PjtNameEdit;
    bool PjtNameEdit_start=0;
    bool PjtNameEdit_set=0;
    QLabel *PIDShow;
    QLabel *NameTiShi;
    QString PjtName;
    int geometry_w=800;
    int geometry_h=600;
    ComSave ComSaveInfoKong={
        "","",0,0};
};
#endif // BASELINK_H

#ifndef BASEKUANG_H
#define BASEKUANG_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <BaseCache.h>
class BaseKuang : public QWidget
{
    Q_OBJECT

public:
    explicit BaseKuang(QWidget *parent = nullptr);
    void SetWH(int x,int y);
    void SetBianW(int midw);
    void set_QText(QString midText);
    void set_QPlt(QPalette midPlt);
    void set_QFont(QFont midFont);
    void set_QTextZuo(int midZuo);
private:
    BasePixCache ModuBase;
    QLabel ModuBaseTu[9];
    QLabel Text;
    QPalette Plt;
    int W=20;
    int W2=40;
    int Zuo=0;
};

#endif // BASEKUANG_H

#include "basekuang.h"
BaseKuang::BaseKuang(QWidget *parent)
    : QWidget{parent}
{
    ModuBaseTu[0].setParent(this);
    ModuBaseTu[1].setParent(this);
    ModuBaseTu[2].setParent(this);
    ModuBaseTu[3].setParent(this);
    ModuBaseTu[4].setParent(this);
    ModuBaseTu[5].setParent(this);
    ModuBaseTu[6].setParent(this);
    ModuBaseTu[7].setParent(this);
    ModuBaseTu[8].setParent(this);

    Text.setParent(this);
    Text.setText("");
    Plt.setColor(QPalette::WindowText, QColor(0, 0, 0));

    ModuBase.BasePix[0]=new QPixmap(":/image/jisuan/TxtBase0.png");
    ModuBase.BasePix[1]=new QPixmap(":/image/jisuan/TxtBase1.png");
    ModuBase.BasePix[2]=new QPixmap(":/image/jisuan/TxtBase2.png");
    ModuBase.BasePix[3]=new QPixmap(":/image/jisuan/TxtBase3.png");
    ModuBase.BasePix[4]=new QPixmap(":/image/jisuan/TxtBase4.png");
    ModuBase.BasePix[5]=new QPixmap(":/image/jisuan/TxtBase5.png");
    ModuBase.BasePix[6]=new QPixmap(":/image/jisuan/TxtBase6.png");
    ModuBase.BasePix[7]=new QPixmap(":/image/jisuan/TxtBase7.png");
    ModuBase.BasePix[8]=new QPixmap(":/image/jisuan/TxtBase8.png");
}
void BaseKuang::SetWH(int x,int y)
{
    ModuBaseTu[0].setGeometry(0,  0,   W,   W);
    ModuBaseTu[1].setGeometry(W,  0,   x-W2,W);
    ModuBaseTu[2].setGeometry(x-W,0,   W,   W);
    ModuBaseTu[3].setGeometry(0,  W,   W,   y-W2);
    ModuBaseTu[4].setGeometry(x-W,W,   W,   y-W2);
    ModuBaseTu[5].setGeometry(0,  y-W, W,   W);
    ModuBaseTu[6].setGeometry(W,  y-W, x-W2,W);
    ModuBaseTu[7].setGeometry(x-W,y-W, W,   W);
    ModuBaseTu[8].setGeometry(W,  W,   x-W2,y-W2);

    ModuBaseTu[0].setPixmap(ModuBase.BasePix[0]->scaled(W,W,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ModuBaseTu[1].setPixmap(ModuBase.BasePix[1]->scaled(x-W2,W,Qt::IgnoreAspectRatio));
    ModuBaseTu[2].setPixmap(ModuBase.BasePix[2]->scaled(W,W,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ModuBaseTu[3].setPixmap(ModuBase.BasePix[3]->scaled(W,y-W2,Qt::IgnoreAspectRatio));
    ModuBaseTu[4].setPixmap(ModuBase.BasePix[4]->scaled(W,y-W2,Qt::IgnoreAspectRatio));
    ModuBaseTu[5].setPixmap(ModuBase.BasePix[5]->scaled(W,W,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ModuBaseTu[6].setPixmap(ModuBase.BasePix[6]->scaled(x-W2,W,Qt::IgnoreAspectRatio));
    ModuBaseTu[7].setPixmap(ModuBase.BasePix[7]->scaled(W,W,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ModuBaseTu[8].setPixmap(ModuBase.BasePix[8]->scaled(x-W2,y-W2,Qt::IgnoreAspectRatio));

    if(Zuo==0)
    {
        Text.setAlignment(Qt::AlignCenter);
    }
    Text.setGeometry(0,0,x,y);
    Text.setPalette(Plt);
}
void BaseKuang::SetBianW(int midw)
{
    W=midw;
    W2=2*midw;
}
void BaseKuang::set_QText(QString midText)
{
    Text.setText(midText);
}
void BaseKuang::set_QPlt(QPalette midPlt)
{
    Plt=midPlt;
}
void BaseKuang::set_QFont(QFont midFont)
{
    Text.setFont(midFont);
}
void BaseKuang::set_QTextZuo(int midZuo)
{
    Zuo=midZuo;
}

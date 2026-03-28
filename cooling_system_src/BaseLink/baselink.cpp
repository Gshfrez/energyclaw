#include "baselink.h"
#include "BaseCore.h"
BaseLink::BaseLink(QWidget *parent)
    : QMainWindow(parent)
{
    //背景挪动组、滚动调、滚动条鼠标的背景
    this->setPalette(QPalette(QPalette::Window,QColor(231, 231, 231)));
    Group_Bg=new QWidget(this);
    Group=new QWidget(Group_Bg);
    Gd=new QLabel(this);
    Gd->setAutoFillBackground(true);
    Gd->setPalette(QPalette(QPalette::Window,QColor(255, 153, 34)));
    Gd_bg=new QLabel(this);

    QPalette midPlt;
    midPlt.setColor(QPalette::Text, QColor(127, 127, 127));
    midPlt_H.setColor(QPalette::Text, QColor(40, 40, 40));

    QFont AnNiuFont;
    AnNiuFont.setFamily("宋体");
    AnNiuFont.setBold(false);//加粗
    AnNiuFont.setPixelSize(12);

    QPixmap AnNiu_Pix(":/image/jisuan/AnNiu.png");
    QPixmap AnNiu_FbPix(":/image/jisuan/AnNiu_Fb.png");
    QPalette midControl;
    midControl.setColor(QPalette::WindowText, QColor(255, 255, 255));
    QPalette midControl_Plt;
    midControl_Plt.setColor(QPalette::WindowText, QColor(255, 153, 34));
    QPixmap midControl_Pix;
    midControl_Pix.load(":/image/jisuan/AnNiu_BuJin.png");

    NameTiShi=new QLabel(this);
    NameTiShi->setText("项目名：");
    NameTiShi->setFont(AnNiuFont);

    PjtNameEdit = new QLineEdit(this);
    PjtNameEdit->setFrame(QFrame::NoFrame);
    PjtNameEdit->setFont(AnNiuFont);
    PjtNameEdit->setPalette(midPlt);
    PjtNameEdit->setText("请输入项目名");

    PIDShow=new QLabel(this);
    PIDShow->setFont(AnNiuFont);
    PIDShow->setText(" PID:N");

    for(int zi=0;zi<2;zi++)
    {
        AddViewName[zi].setParent(this);
        AddViewName[zi].setpix(AnNiu_Pix);
        AddViewName[zi].setpixDj(AnNiu_FbPix);
        AddViewName[zi].set_QFont(AnNiuFont);
        AddViewName[zi].set_QPlt(midControl);
        AddViewName[zi].set_QPltDj(midControl_Plt);
        AddViewName[zi].setAnNiuWH(45,24);
    }
    AddViewName[0].set_QText("+Com");
    AddViewName[1].set_QText("+TcpS");

    SaveToProject.setParent(this);
    SaveToProject.setpix(midControl_Pix);
    SaveToProject.setpixDj(AnNiu_FbPix);
    SaveToProject.set_QText("保存");
    SaveToProject.set_QFont(AnNiuFont);
    SaveToProject.set_QPlt(midControl);
    SaveToProject.set_QPltDj(midControl_Plt);
    SaveToProject.setAnNiuWH(45,24);

    QPixmap shitu1_Pix;
    QPixmap shitu1_FbPix;
    QPixmap shitu2_Pix;
    QPixmap shitu2_FbPix;
    QPixmap shitu3_Pix;
    QPixmap shitu3_FbPix;

    shitu1_Pix.load(":/image/jisuan/shitu1.png");
    shitu1_FbPix.load(":/image/jisuan/shitu1_Fb.png");
    shitu2_Pix.load(":/image/jisuan/shitu2.png");
    shitu2_FbPix.load(":/image/jisuan/shitu2_Fb.png");
    shitu3_Pix.load(":/image/jisuan/shitu3.png");
    shitu3_FbPix.load(":/image/jisuan/shitu3_Fb.png");

    ShiTu1.setParent(this);
    ShiTu1.setpix(shitu1_Pix);
    ShiTu1.setpixDj(shitu1_FbPix);
    ShiTu1.setAnNiuWH(24,24);

    ShiTu2.setParent(this);
    ShiTu2.setpix(shitu2_Pix);
    ShiTu2.setpixDj(shitu2_FbPix);
    ShiTu2.setAnNiuWH(24,24);

    ShiTu3.setParent(this);
    ShiTu3.setpix(shitu3_Pix);
    ShiTu3.setpixDj(shitu3_FbPix);
    ShiTu3.setAnNiuWH(24,24);

    connect(&ShiTu1, &AnniuDiandong::AnNiuClicked, this, [=](){PaiBanType=0;PaiBan();});
    connect(&ShiTu2, &AnniuDiandong::AnNiuClicked, this, [=](){PaiBanType=1;PaiBan();});
    connect(&ShiTu3, &AnniuDiandong::AnNiuClicked, this, [=](){PaiBanType=2;PaiBan();});

    connect(&AddViewName[0], &AnniuDiandong::AnNiuClicked, this, [=](){ComSave ComSaveInfoKong1=ComSaveInfoKong;ComSaveInfoKong1.Type=1;AddView(ComSaveInfoKong1);});
    connect(&AddViewName[1], &AnniuDiandong::AnNiuClicked, this, [=](){ComSave ComSaveInfoKong2=ComSaveInfoKong;ComSaveInfoKong2.Type=2;AddView(ComSaveInfoKong2);});

    connect(&SaveToProject, &AnniuDiandong::AnNiuClicked, this, [=](){ComCodeSave();});
    connect(PjtNameEdit, &QLineEdit::cursorPositionChanged,[=](){PjtNameStart("");});
    connect(PjtNameEdit, &QLineEdit::editingFinished, this, [=](){
        if(PjtNb<0)
        {
            QString midPjtName=PjtNameEdit->text();
            PjtNameSet(midPjtName);
        }
    });
    this->resize(960,800);
}
void BaseLink::ComCodeSave()
{
    if(PjtNb>=0)
    {
        ComSave ComSaveInfo[24];
        for(int zi=0;zi<24;zi++)
        {
            ComSaveInfo[zi]=ComSaveInfoKong;
        }
        for(int zi=0;zi<ComTcp_Link.size();zi++)
        {
            if(if_ComShow[zi]==1)
            {
                ComSaveInfo[zi].ComName=ComTcp_Link[zi].Com->GetComName();
                ComSaveInfo[zi].Lua=ComTcp_Link[zi].Com->GetLuaString();
                ComSaveInfo[zi].If_Sent=ComTcp_Link[zi].Com->GetIfSent();
                ComSaveInfo[zi].Type=1;
            }
            if(if_ComShow[zi]==2)
            {
                ComSaveInfo[zi].ComName=ComTcp_Link[zi].Tcp->GetPort();
                ComSaveInfo[zi].Lua=ComTcp_Link[zi].Tcp->GetLuaString();
                ComSaveInfo[zi].If_Sent=ComTcp_Link[zi].Tcp->GetIfSent();
                ComSaveInfo[zi].Type=2;
            }
        }
        BaseKuangPixSet(PjtName,ComSaveInfo);
    }
}
void BaseLink::PjtNameStart(QString midPjtName)
{
    if(PjtNameEdit_start==0)
    {
        PjtNameEdit_start=1;
        PjtNameEdit->setText(midPjtName);
        PjtNameEdit->setPalette(midPlt_H);
        PjtNameEdit_set=1;
    }
}
void BaseLink::PjtNameSet(QString midPjtName)
{
    if(PjtNameEdit_set==1)
    {
        if(midPjtName.length()>0)
        {
            PjtName=midPjtName;
            int midPjtNb=ProjectNameToID(midPjtName.toUtf8().data());
            if(midPjtNb>=0)
            {
                PjtNb=midPjtNb;
                PIDShow->setText(" PID:"+QString::number(PjtNb));
                PjtNameEdit->setReadOnly(true);

                //局部缓存变量，不要移动到别处，会影响下面conect的层级
                ComSave ComSaveInfo[24];
                for(int zi=0;zi<24;zi++)
                {
                    ComSaveInfo[zi]=ComSaveInfoKong;
                }
                int ArraySize=0;
                BaseKuangPixGet(PjtName,ComSaveInfo,ArraySize);//读取json
                for(int zi=0;zi<ArraySize;zi++)
                {
                    AddView(ComSaveInfo[zi]);
                }
            }
            else
            {
                PIDShow->setText(" PID:N");
            }
        }
    }
}
void BaseLink::AddView(ComSave midComSaveInfo)
{
    if(PjtNb>=0)
    {
        bool if_Add_ComTcp_Link=1;
        int mid_Nb=ComTcp_Link.size();
        for(int zi=0;zi<mid_Nb;zi++)
        {
            if(if_ComShow[zi]==0)
            {
                mid_Nb=zi;
                if_Add_ComTcp_Link=0;
                break;
            }
        }
        if(mid_Nb>=24){return;}
        if(if_Add_ComTcp_Link)
        {
            ComTcp_Link.resize(mid_Nb+1);
            if_ComShow.resize(mid_Nb+1);
            if_ComShow[mid_Nb]=0;
        }
        if(midComSaveInfo.Type==1)
        {
            ComTcp_Link[mid_Nb].Com=new ComLink(Group);
            ComTcp_Link[mid_Nb].Com->PjtNameSet(PjtName);//设置名称
            ComTcp_Link[mid_Nb].Com->SetComName(midComSaveInfo.ComName);//设置名称
            ComTcp_Link[mid_Nb].Com->SetLuaString(midComSaveInfo.Lua);//设置名称
            ComTcp_Link[mid_Nb].Com->SetIfSent(midComSaveInfo.If_Sent);//设置名称
            ComTcp_Link[mid_Nb].Com->show();//展示
            if_ComShow[mid_Nb]=midComSaveInfo.Type;
            connect(ComTcp_Link[mid_Nb].Com, &ComLink::CloseView, this, [=](){
                if_ComShow[mid_Nb]=0;
                ComTcp_Link[mid_Nb].Com->close();
                delete(ComTcp_Link[mid_Nb].Com);
                PaiBan();
            });
            connect(ComTcp_Link[mid_Nb].Com, &ComLink::SaveComLUA, this, [=](){
                ComCodeSave();
            });
        }
        if(midComSaveInfo.Type==2)
        {
            ComTcp_Link[mid_Nb].Tcp=new TcpLink(Group);
            ComTcp_Link[mid_Nb].Tcp->PjtNameSet(PjtName);//设置名称
            ComTcp_Link[mid_Nb].Tcp->SetPort(midComSaveInfo.ComName);//设置名称
            ComTcp_Link[mid_Nb].Tcp->SetLuaString(midComSaveInfo.Lua);//设置名称
            ComTcp_Link[mid_Nb].Tcp->SetIfSent(midComSaveInfo.If_Sent);//设置名称
            ComTcp_Link[mid_Nb].Tcp->show();//展示
            if_ComShow[mid_Nb]=midComSaveInfo.Type;
            connect(ComTcp_Link[mid_Nb].Tcp, &TcpLink::CloseView, this, [=](){
                if_ComShow[mid_Nb]=0;
                ComTcp_Link[mid_Nb].Tcp->close();
                delete(ComTcp_Link[mid_Nb].Tcp);
                PaiBan();
            });
            connect(ComTcp_Link[mid_Nb].Tcp, &TcpLink::SaveTcpLUA, this, [=](){
                ComCodeSave();
            });
        }
        PaiBan();
    }
}
void BaseLink::PaiBan()
{
    int mid_W=0;
    int mid_H=0;
    int midShowNb=0;
    for(int zi=0;zi<ComTcp_Link.size();zi++)
    {
        if(if_ComShow[zi]>=1)
        {
            midShowNb=midShowNb+1;
        }
    }
    int hangshu=0;
    int midW_sl=3;//目标并排数
    int MaxShuliang_W=geometry_w/600;//以最低分辨率计算,最大并排数
    if(PaiBanType==0)
    {
        midW_sl=1;
    }
    if(PaiBanType==1)
    {
        midW_sl=3;if(midShowNb<3){midW_sl=midShowNb;}
    }
    if(PaiBanType==2)
    {
        midW_sl=sqrt(midShowNb)+1;
    }
    if(MaxShuliang_W>midW_sl)
    {
        MaxShuliang_W=midW_sl;
    }
    if(MaxShuliang_W<1){MaxShuliang_W=1;}
    mid_W=geometry_w/MaxShuliang_W;//依照并排数计算宽度
    mid_H=mid_W*0.667;
    if(midShowNb>=1)
    {
        hangshu=(midShowNb-1)/MaxShuliang_W+1;
    }
    else
    {
        hangshu=1;
    }
    if(midShowNb<=1)//若表数小于并排数
    {
        mid_H=geometry_h;
    }
    int midDj=0;
    for(int zi=0;zi<hangshu;zi++)
    {
        for(int yi=0;yi<MaxShuliang_W;yi++)
        {
            for(int xi = midDj; xi < ComTcp_Link.size(); xi++)
            {
                if(if_ComShow[xi]==1)
                {
                    ComTcp_Link[xi].Com->setGeometry(yi*mid_W+10,zi*mid_H,mid_W-10,mid_H-10);
                    midDj=xi+1;
                    break;
                }
                if(if_ComShow[xi]==2)
                {
                    ComTcp_Link[xi].Tcp->setGeometry(yi*mid_W+10,zi*mid_H,mid_W-10,mid_H-10);
                    midDj=xi+1;
                    break;
                }
            }
        }
    }
    MoveH=hangshu*mid_H;
    if(MoveH>(geometry_h))
    {
        double midShowH=(geometry_h)*(geometry_h)/MoveH;
        double midShowY=((geometry_h)-midShowH)*MoveY/((geometry_h)-MoveH);
        Gd->setGeometry(geometry_w+9,midShowY+30,2,midShowH);
        Gd->show();
    }
    else
    {
        MoveY=0;
        Gd->setHidden(1);
    }
    Group->setGeometry(0,MoveY,geometry_w,MoveH);
}
void BaseLink::wheelEvent(QWheelEvent *event)
{
    QPoint numang=event->angleDelta();
    if(MoveH>(geometry_h))
    {
        MoveY=MoveY+numang.y()/3;
        if(MoveY>0)
        {
            MoveY=0;
        }
        if(MoveY<((geometry_h)-MoveH))
        {
            MoveY=(geometry_h)-MoveH;
        }
        double midShowH=(geometry_h)*(geometry_h)/MoveH;
        double midShowY=((geometry_h)-midShowH)*MoveY/((geometry_h)-MoveH);
        Gd->setGeometry(geometry_w+9,midShowY+30,2,midShowH);
        Gd->show();
    }
    else
    {
        MoveY=0;
        Gd->setHidden(1);
    }
    Group->move(0,MoveY);
}
bool BaseLink::event(QEvent *ev)
{
    if(ev->type() == QEvent::Resize)
    {
        QResizeEvent *re = static_cast<QResizeEvent*> (ev);
        geometry_w=re->size().width()-20;
        geometry_h=re->size().height()-30;
        if(geometry_w<600)
        {
            geometry_w=600;
        }
        Gd_bg->setGeometry(geometry_w,30,20,geometry_h);
        NameTiShi->setGeometry(5,3,280,24);
        PjtNameEdit->setGeometry(48,5,85,20);
        PIDShow->setGeometry(130,3,40,24);
        AddViewName[0].setGeometry(170,3,45,24);
        AddViewName[1].setGeometry(170+45,3,45,24);

        SaveToProject.setGeometry(geometry_w-30,3,45,24);
        Group_Bg->setGeometry(0,30,geometry_w,geometry_h);
        ShiTu1.setGeometry(geometry_w-15-96,3,24,24);
        ShiTu2.setGeometry(geometry_w-15-72,3,24,24);
        ShiTu3.setGeometry(geometry_w-15-48,3,24,24);
        PaiBan();
    }
    return QWidget::event(ev);
}
void BaseLink::closeEvent ( QCloseEvent * )
{
    for(int zi=0;zi<ComTcp_Link.size();zi++)
    {
        if(if_ComShow[zi]==1)
        {
            ComTcp_Link[zi].Com->close();
            if_ComShow[zi] = 0;
        }
        if(if_ComShow[zi]==2)
        {
            ComTcp_Link[zi].Tcp->close();
            if_ComShow[zi] = 0;
        }
    }
}

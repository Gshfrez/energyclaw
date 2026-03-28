#include "basechart.h"
Chart_PointCache mid_point[24][7];
Chart_CacheSx mid_cache_Sx[24][7];
BaseChart::BaseChart(QWidget *parent)
    : QMainWindow(parent)
{
    //获取主题
    QFile f(".\\ProjectZhuTi.json");if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){ZhuTiStart=0;}
    QTextStream txtInput(&f);while(!txtInput.atEnd()){ZhuTiStart=txtInput.readLine().toInt();}f.close();
    //调取OPENGL
    FirtCurveChartView*midFirtCurveChartView_start=new FirtCurveChartView(this);
    QChart*m_chart = new QChart();// 创建图表对象
    m_chart->setContentsMargins(0, 0, 0, 0);  //设置外边界全部为0
    m_chart->setMargins(QMargins(0, 0, 0, 0));//设置内边界全部为0
    midFirtCurveChartView_start->setChart(m_chart);
    QLineSeries *m_Series0=new QLineSeries();
    m_Series0->setUseOpenGL(true);
    m_chart->addSeries(m_Series0);
    midFirtCurveChartView_start->setHidden(1);
    //背景挪动组、滚动调、滚动条鼠标的背景
    Group_Bg=new QWidget(this);
    Group=new QWidget(Group_Bg);
    Gd=new QLabel(this);
    Gd->setAutoFillBackground(true);
    Gd->setPalette(QPalette(QPalette::Window,QColor(153, 153, 153)));
    Gd_bg=new GDWheel(this);
    CaoZuoTiShi=new QLabel(this);

    QPalette midPlt;
    QPixmap midSave_Pix[3];
    midSave_Pix[0].load(":/image/jisuan/Save.png");
    if(ZhuTiStart==0)
    {
        this->setPalette(QPalette(QPalette::Window,QColor(231, 231, 231)));
        midPlt.setColor(QPalette::Base, QColor(255, 255, 255));
        midPlt_H.setColor(QPalette::Base, QColor(255, 255, 255));
        midSave_Pix[1].load(":/image/jisuan/SaveXf.png");
        midSave_Pix[2].load(":/image/jisuan/SaveFb.png");
    }
    else
    {
        this->setPalette(QPalette(QPalette::Window,QColor(40, 40, 40)));
        midPlt.setColor(QPalette::Base, QColor(80, 80, 80));
        midPlt_H.setColor(QPalette::Base, QColor(80, 80, 80));
        midSave_Pix[1].load(":/image/jisuan/SaveXf_H.png");
        midSave_Pix[2].load(":/image/jisuan/SaveFb_H.png");
    }

    CaoZuoTiShi->setPalette(midPlt_H);
    CaoZuoTiShi->setText("滚轮：曲线缩放（图像区域）、上下滚动（滚动条区域）");

    QFont AnNiuFont;
    AnNiuFont.setFamily("宋体");
    AnNiuFont.setBold(false);//加粗
    AnNiuFont.setPixelSize(12);

    QPixmap AnNiu_Pix(":/image/jisuan/AnNiu.png");
    QPixmap AnNiu_FbPix(":/image/jisuan/AnNiu_Fb.png");
    QPalette midControl;
    midControl.setColor(QPalette::WindowText, QColor(255, 255, 255));
    QPalette midControl_Plt[3];
    midControl_Plt[0].setColor(QPalette::WindowText, QColor(0, 119, 170));
    midControl_Plt[1].setColor(QPalette::WindowText, QColor(0, 170, 119));
    midControl_Plt[2].setColor(QPalette::WindowText, QColor(255, 153, 34));
    QPixmap midControl_Pix[3];
    midControl_Pix[0].load(":/image/jisuan/AnNiu_Baocun.png");
    midControl_Pix[1].load(":/image/jisuan/AnNiu_YunXing.png");
    midControl_Pix[2].load(":/image/jisuan/AnNiu_BuJin.png");

    NameTiShi=new QLabel(this);
    NameTiShi->setText("项目名：");
    NameTiShi->setFont(AnNiuFont);


    HunCunTiShi=new QLabel(this);
    HunCunTiShi->setText("缓存数：");
    HunCunTiShi->setFont(AnNiuFont);

    btnClear.setParent(this);
    btnClear.setpix(&midControl_Pix[0]);
    btnClear.setpixDj(&AnNiu_FbPix);
    btnClear.set_QText("清除");
    btnClear.set_QFont(AnNiuFont);
    btnClear.set_QPlt(midControl);
    btnClear.set_QPltDj(midControl_Plt[0]);
    btnClear.setAnNiuWH(45,24);

    PjtNameEdit = new QLineEdit(this);
    PjtNameEdit->setFrame(QFrame::NoFrame);
    PjtNameEdit->setFont(AnNiuFont);
    PjtNameEdit->setPalette(midPlt);
    PjtNameEdit->setText("请输入项目名");

    HuanCunShu = new QLineEdit(this);
    HuanCunShu->setFrame(QFrame::NoFrame);
    HuanCunShu->setPalette(midPlt);
    HuanCunShu->setFont(AnNiuFont);
    HuanCunShu->setAlignment(Qt::AlignLeft);
    HuanCunShu ->setText(QString(QString::number(XianLiang)+"   "));

    PIDShow=new QLabel(this);
    PIDShow->setFont(AnNiuFont);
    PIDShow->setText(" PID:N");

    AddViewName[0].setParent(this);
    AddViewName[1].setParent(this);
    AddViewName[2].setParent(this);
    AddViewName[3].setParent(this);
    for(int zi=0;zi<4;zi++)
    {
        AddViewName[zi].setpix(&AnNiu_Pix);
        AddViewName[zi].setpixDj(&AnNiu_FbPix);
        AddViewName[zi].set_QFont(AnNiuFont);
        AddViewName[zi].set_QPlt(midControl);
        AddViewName[zi].set_QPltDj(midControl_Plt[2]);
        AddViewName[zi].setAnNiuWH(45,24);
    }
    AddViewName[0].set_QText("+折线");
    AddViewName[1].set_QText("+曲线");
    AddViewName[2].set_QText("+散点");
    AddViewName[3].set_QText("+饼图");

    connect(&AddViewName[0], &AnniuDiandong::AnNiuClicked, this, [=](){AddView(0);});
    connect(&AddViewName[1], &AnniuDiandong::AnNiuClicked, this, [=](){AddView(1);});
    connect(&AddViewName[2], &AnniuDiandong::AnNiuClicked, this, [=](){AddView(2);});
    connect(&AddViewName[3], &AnniuDiandong::AnNiuClicked, this, [=](){AddView(3);});

    SaveToPng.setParent(this);
    SaveToPng.setpix(&midSave_Pix[0]);
    SaveToPng.setpixXf(&midSave_Pix[1]);
    SaveToPng.setpixDj(&midSave_Pix[2]);
    SaveToPng.set_QFont(AnNiuFont);
    SaveToPng.setAnNiuWH(30,24);

    SaveToProject.setParent(this);
    SaveToProject.setpix(&midControl_Pix[2]);
    SaveToProject.setpixDj(&AnNiu_FbPix);
    SaveToProject.set_QText("保存");
    SaveToProject.set_QFont(AnNiuFont);
    SaveToProject.set_QPlt(midControl);
    SaveToProject.set_QPltDj(midControl_Plt[2]);
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
    ShiTu1.setpix(&shitu1_Pix);
    ShiTu1.setpixDj(&shitu1_FbPix);
    ShiTu1.setAnNiuWH(24,24);

    ShiTu2.setParent(this);
    ShiTu2.setpix(&shitu2_Pix);
    ShiTu2.setpixDj(&shitu2_FbPix);
    ShiTu2.setAnNiuWH(24,24);

    ShiTu3.setParent(this);
    ShiTu3.setpix(&shitu3_Pix);
    ShiTu3.setpixDj(&shitu3_FbPix);
    ShiTu3.setAnNiuWH(24,24);

    connect(&ShiTu1, &AnniuDiandong::AnNiuClicked, this, [=](){PaiBanType=0;PaiBan();});
    connect(&ShiTu2, &AnniuDiandong::AnNiuClicked, this, [=](){PaiBanType=1;PaiBan();});
    connect(&ShiTu3, &AnniuDiandong::AnNiuClicked, this, [=](){PaiBanType=2;PaiBan();});
    connect(&SaveToProject, &AnniuDiandong::AnNiuClicked, this, [=](){
        if(PjtNb>=0)
        {
            ChartSave midChartInfo;
            for(int zi=0;zi<24;zi++)
            {
                for(int yi=0;yi<6;yi++)
                {
                    midChartInfo.LineName[zi][yi].clear();
                }
                midChartInfo.Type[zi]=-1;
                midChartInfo.HengZhouName[zi].clear();
            }
            for(int zi=0;zi<graphicsView.size();zi++)
            {
                if(if_ViewShow[zi]==1)
                {
                    for(int yi=0;yi<6;yi++)
                    {
                        QString midname="";
                        if(graphicsView[zi]->SeriesNameGet(yi,midname))
                        {
                           midChartInfo.LineName[zi][yi]=midname;
                        }
                    }
                    midChartInfo.Type[zi]=graphicsView[zi]->LintTypeGet();
                    QString mid_name="";
                    if(graphicsView[zi]->SeriesNameGet(6,mid_name))
                    {
                        midChartInfo.HengZhouName[zi]=mid_name;
                    }
                }
            }
            BaseChartInfoSet(PjtName,midChartInfo);
        }
    });

    connect(PjtNameEdit, &QLineEdit::cursorPositionChanged,[=](int,int){PjtNameStart("");});
    connect(PjtNameEdit, &QLineEdit::editingFinished, this, [=](){
        if(PjtNb<0)
        {
            QString midPjtName=PjtNameEdit->text();
            PjtNameSet(midPjtName);
        }
    });
    connect(HuanCunShu, &QLineEdit::cursorPositionChanged,[=](int,int){
        if(HuanCunShu_start==0)
        {
            HuanCunShu->setText(QString::number(XianLiang));
            HuanCunShu->setPalette(midPlt_H);
            HuanCunShu_start=1;
        }
    });
    connect(HuanCunShu, &QLineEdit::editingFinished, this, [=](){
        QString midstring=HuanCunShu->text();
        if(HuanCunShu_start==1)
        {
            int midHuancunshu=midstring.toInt();
            if(if_KaiQiJiLu)//判断是否已开启，不可删除
            {
                if_KaiQiJiLu=0;//将状态记录改为已关闭
            }
            QThread::msleep(100);
            if(midHuancunshu<0)
            {
                midHuancunshu=0;
            }
            if(midHuancunshu>10000)
            {
                midHuancunshu=10000;
            }
            XianLiang=midHuancunshu;
            Chart_ValueClear(PjtNb);//清理多线程所有计数
            HuanCunShu->setText(QString::number(XianLiang));
            for(int zi=0;zi<graphicsView.size();zi++)//设置所有的子框框清零
            {
                graphicsView[zi]->ChartClear();
            }
            if_Show=1;
            if_KaiQiJiLu=1;
        }
    });
    connect(&btnClear, &AnniuDiandong::AnNiuClicked, this, [=](){
        if(PjtNb>=0&&PjtNb<=7)
        {
            if(if_KaiQiJiLu)//判断是否已开启，不可删除
            {
                if_KaiQiJiLu=0;//将状态记录改为已关闭
            }
            QThread::msleep(80);
            Chart_ValueClear(PjtNb);//清理多线程所有计数
            for(int zi=0;zi<graphicsView.size();zi++)//设置所有的子框框清零
            {
                graphicsView[zi]->ChartClear();
            }
            if_Show=1;
            if_KaiQiJiLu=1;
        }
    });
    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);
    connect(m_timer, &QTimer::timeout, this, [=](){
        if(if_KaiQiJiLu==1)
        {
            Chart_PointGet(PjtNb,mid_point,mid_cache_Sx);//获取最近的数据
            if(Chart_RunClearGet(PjtNb))
            {
                for(int zi=0;zi<graphicsView.size();zi++)//设置所有的子框框清零
                {
                    graphicsView[zi]->ChartClear();
                }
            }
            for(int midviewnb=0;midviewnb<graphicsView.size();midviewnb++)//View遍历
            {
                if(if_ViewShow[midviewnb]==1)
                {
                    //获取横轴
                    if(mid_point[midviewnb][6].VIV2.CanBeShow==1)
                    {
                        graphicsView[midviewnb]->HengzhouValue(PjtNb,midviewnb,
                            mid_point[midviewnb][6],mid_cache_Sx[midviewnb][6],XianLiang);
                    }
                    for(int midlinenb=0;midlinenb<6;midlinenb++)//线遍历
                    {
                        if(mid_point[midviewnb][midlinenb].VIV2.CanBeShow==1)
                        {
                            if(mid_point[midviewnb][midlinenb].VIV2.LineNb>=0)//必不可少，不可替代,lineNb为-1不行
                            {
                                graphicsView[midviewnb]->SeriesValue(PjtNb,midviewnb,midlinenb,
                                mid_point[midviewnb][midlinenb],mid_cache_Sx[midviewnb][midlinenb],XianLiang);//线的数据集
                            }
                        }
                    }
                    graphicsView[midviewnb]->SeriesReplaceEnd();
                }
            }
            if(Chart_PngSaveGet(PjtName.toUtf8().data()))
            {
                int mid_ww=this->width();
                int mid_hh=this->height();
                QDate currentDate = QDate::currentDate();
                int midRiQi=currentDate.year()*10000;
                midRiQi = midRiQi + currentDate.month()*100;
                midRiQi = midRiQi + currentDate.day();
                QString midYMD=QString::number(midRiQi);
                QDateTime currentDate2=QDateTime::currentDateTime();
                QString current_time = currentDate2.toString("hh_mm_ss_zzz");
                QString MidAddress=QT_FldAddress();
                MidAddress=MidAddress+"AlgProject\\"+PjtName+"\\"+PjtName+"_chart.png";
                /*QDir middir(MidAddress);
                if(!middir.exists())
                {
                    middir.mkdir(MidAddress);
                }
                MidAddress=MidAddress+PjtName+"_"+midYMD+"_"+current_time+".png";*/
                QRect midrect;
                midrect.setRect(0,0,5760,3240);//保存为6K的图片
                this->resize(5760,3240);
                QPixmap midpixmap=this->grab(midrect);
                midpixmap.save(MidAddress);
                this->resize(mid_ww,mid_hh);
            }
        }
    });
    m_timer->start(50);//25);
    connect(Gd_bg, &GDWheel::signalWheelEvent, this, [=](QWheelEvent *event){
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
        Group->setGeometry(0,MoveY,geometry_w,MoveH);
    });
    connect(Gd_bg, &GDWheel::signalInterOut, this, [=](bool midinout){
        if(midinout)
        {
            Gd->setPalette(QPalette(QPalette::Window,QColor(255, 153, 34)));
        }
        else
        {
            Gd->setPalette(QPalette(QPalette::Window,QColor(153, 153, 153)));
        }
    });
    connect(&SaveToPng, &AnniuDiandong::AnNiuClicked, this, [=](){
        int mid_ww=this->width();
        int mid_hh=this->height();
        QDate currentDate = QDate::currentDate();
        int midRiQi=currentDate.year()*10000;
        midRiQi = midRiQi + currentDate.month()*100;
        midRiQi = midRiQi + currentDate.day();
        QString midYMD=QString::number(midRiQi);
        QDateTime currentDate2=QDateTime::currentDateTime();
        QString current_time = currentDate2.toString("hh_mm_ss_zzz");
        QString MidAddress=QT_FldAddress();
        MidAddress=MidAddress+"image\\";
        QDir middir(MidAddress);
        if(!middir.exists())
        {
            middir.mkdir(MidAddress);
        }
        MidAddress=MidAddress+PjtName+"_"+midYMD+"_"+current_time+".png";
        QRect midrect;
        midrect.setRect(0,0,5760,3240);//保存为6K的图片
        this->resize(5760,3240);
        QPixmap midpixmap=this->grab(midrect);
        midpixmap.save(MidAddress);
        this->resize(mid_ww,mid_hh);
    });
    this->resize(960,800);
}
void BaseChart::PjtNameStart(QString midPjtName)
{
    if(PjtNameEdit_start==0)
    {
        PjtNameEdit_start=1;
        PjtNameEdit->setText(midPjtName);
        PjtNameEdit->setPalette(midPlt_H);
        PjtNameEdit_set=1;
    }
}
void BaseChart::PjtNameSet(QString midPjtName)
{
    if(PjtNameEdit_set==1)
    {
        if(midPjtName.length()>0)
        {
            PjtName=midPjtName;
            int midPjtNb=Chart_ProjectNameToID(midPjtName.toUtf8().data());
            if(midPjtNb>=0)
            {
                PjtNb=midPjtNb;
                PIDShow->setText(" PID:"+QString::number(PjtNb));
                PjtNameEdit->setReadOnly(true);
                ChartSave midChartInfo;
                for(int zi=0;zi<24;zi++)
                {
                    for(int yi=0;yi<6;yi++)
                    {
                        midChartInfo.LineName[zi][yi].clear();
                    }
                    midChartInfo.Type[zi]=-1;
                }
                int midViewSize=0;
                BaseChartInfoGet(PjtName,midChartInfo,midViewSize);
                for(int midviewnb=0;midviewnb<midViewSize;midviewnb++)
                {
                    if(midChartInfo.Type[midviewnb]>=0)
                    {
                        AddView(midChartInfo.Type[midviewnb]);//添加一个折线
                        for(int midlineNb=0;midlineNb<6;midlineNb++)
                        {
                            QString midName=midChartInfo.LineName[midviewnb][midlineNb];
                            if(midName.length()>0)
                            {
                                if(Chart_VarInfoSet(PjtNb, midName.toUtf8().data(), midviewnb, midlineNb))//将变量名字，输入给后台。
                                {
                                    graphicsView[midviewnb]->Add_Series();
                                    graphicsView[midviewnb]->SeriesInfoSet(midlineNb,midName);
                                }
                            }
                        }
                        QString mid_Name=midChartInfo.HengZhouName[midviewnb];
                        if(mid_Name.length()>0)
                        {
                            if(Chart_VarInfoSet(PjtNb, mid_Name.toUtf8().data(), midviewnb, 6))//将变量名字，输入给后台。
                            {
                                graphicsView[midviewnb]->SeriesInfoSet(6,mid_Name);
                            }
                        }
                    }
                }
            }
            else
            {
                PIDShow->setText(" PID:N");
            }
        }
    }
}
void BaseChart::AddView(int midType)
{
    if(PjtNb>=0)
    {
        bool if_Add_graphicsView=1;
        int midviewnb=graphicsView.size();
        for(int zi=0;zi<midviewnb;zi++)
        {
            if(if_ViewShow[zi]==0)
            {
                midviewnb=zi;
                if_Add_graphicsView=0;
                break;
            }
        }
        if(midviewnb>=24){return;}
        if(if_Add_graphicsView)
        {
            graphicsView.resize(midviewnb+1);
            if_ViewShow.resize(midviewnb+1);
        }
        graphicsView[midviewnb]=new BaseIcon(Group);
        graphicsView[midviewnb]->LintTypeSet(midType);//设置线的类型
        graphicsView[midviewnb]->SetZhuTi(ZhuTiStart);//设置主题
        graphicsView[midviewnb]->PjtNameSet(PjtName);//设置名称
        graphicsView[midviewnb]->ViewStart();//初始化
        graphicsView[midviewnb]->show();//展示
        if_ViewShow[midviewnb]=1;
        connect(graphicsView[midviewnb], &BaseIcon::VarNameOut, this, [=](int midlineNb,QString midVarName){
            if(Chart_VarInfoSet(PjtNb, midVarName.toUtf8().data(), midviewnb, midlineNb))
            {
                graphicsView[midviewnb]->SeriesInfoSet(midlineNb,midVarName);
            }
            else
            {
                graphicsView[midviewnb]->SeriesInfoClear(midlineNb);
            }
        });
        connect(graphicsView[midviewnb], &BaseIcon::CloseView, this, [=](){
           if(if_KaiQiJiLu)//判断是否已开启，不可删除
            {
                if_KaiQiJiLu=0;//将状态记录改为已关闭
            }
            QThread::msleep(100);
            Chart_ViewClose(PjtNb,midviewnb);
            if_ViewShow[midviewnb]=0;
            graphicsView[midviewnb]->close();
            delete(graphicsView[midviewnb]);
            PaiBan();
            if_KaiQiJiLu=1;

        });
        PaiBan();
    }
}
void BaseChart::PaiBan()
{
    int mid_W=0;
    int mid_H=0;
    int midShowNb=0;
    for(int zi=0;zi<graphicsView.size();zi++)
    {
        if(if_ViewShow[zi]==1)
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
    if(midW_sl<MaxShuliang_W)
    {
        MaxShuliang_W=midW_sl;
    }
    if(MaxShuliang_W<1){MaxShuliang_W=1;}
    mid_W=geometry_w/MaxShuliang_W;//依照并排数计算宽度
    mid_H=2*mid_W/3;
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
            for(int xi = midDj; xi < graphicsView.size(); xi++)
            {
                if(if_ViewShow[xi]==1)
                {
                    graphicsView[xi]->setGeometry(yi*mid_W,zi*mid_H,mid_W,mid_H);
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
bool BaseChart::event(QEvent *ev)
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


        NameTiShi->setGeometry(5,3,40,24);
        HunCunTiShi->setGeometry(170,3,45,24);
        PjtNameEdit->setGeometry(48,5,80,20);
        PIDShow->setGeometry(125,3,40,24);
        HuanCunShu->setGeometry(215,5,48,20);

        AddViewName[0].setGeometry(265,3,45,24);
        AddViewName[1].setGeometry(310,3,45,24);
        AddViewName[2].setGeometry(355,3,45,24);
        AddViewName[3].setGeometry(400,3,45,24);
        SaveToPng.setGeometry(445,3,30,24);
        CaoZuoTiShi->setGeometry(475,3,geometry_w-570,24);

        btnClear.setGeometry(geometry_w-85,3,45,24);//清理
        SaveToProject.setGeometry(geometry_w-30,3,45,24);
        Group_Bg->setGeometry(0,30,geometry_w,geometry_h);

        ShiTu1.setGeometry(geometry_w-70-96,3,24,24);
        ShiTu2.setGeometry(geometry_w-70-72,3,24,24);
        ShiTu3.setGeometry(geometry_w-70-48,3,24,24);
        PaiBan();
    }
    return QWidget::event(ev);
}
void BaseChart::closeEvent ( QCloseEvent * )
{
    //for(int midviewnb=0;midviewnb<graphicsView.size();midviewnb++)//View遍历
    //{
    //    if(if_ViewShow[midviewnb]==1)
    //    {
    //        graphicsView[midviewnb]->CloseView();
    //    }
    //}
}

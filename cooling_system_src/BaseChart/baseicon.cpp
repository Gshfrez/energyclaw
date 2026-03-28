#include "baseicon.h"
int maxPointNb = 500;
BaseIcon::BaseIcon(QWidget *parent)
    : QWidget{parent}
{
    this->setAutoFillBackground(true);
    midPs.resize(0);
    LI.resize(0);
}
void BaseIcon::SetZhuTi(bool midZhuTi)
{
    ZhuTi=midZhuTi;
}
void BaseIcon::ViewStart()
{
    AnNiuFont.setFamily("宋体");
    AnNiuFont.setBold(false);//加粗
    AnNiuFont.setPixelSize(12);

    m_chart = new QChart();// 创建图表对象
    m_chart->setTitleFont(AnNiuFont);
    m_chart->setContentsMargins(0, 0, 0, 0);  //设置外边界全部为0
    m_chart->setMargins(QMargins(0, 0, 0, 0));//设置内边界全部为0

    QPixmap midAdd_Pix[3];
    midAdd_Pix[0].load(":/image/jisuan/CreateProject.png");
    QPixmap midSave_Pix[3];
    midSave_Pix[0].load(":/image/jisuan/Save.png");
    QPixmap midClose_Pix[3];
    midClose_Pix[0].load(":/image/jisuan/AnNiu_GuanBi.png");
    if(ZhuTi==0)
    {
        this->setPalette(QPalette(QPalette::Window,QColor(239, 239, 239)));
        m_chart->setTheme(QChart::ChartThemeLight);
        midPlt.setColor(QPalette::Text, QColor(127, 127, 127));
        midPlt_H.setColor(QPalette::Text, QColor(40, 40, 40));//字体颜色
        midPlt.setColor(QPalette::Base, QColor(255, 255, 255));
        midPlt_H.setColor(QPalette::Base, QColor(255, 255, 255));
        midAdd_Pix[1].load(":/image/jisuan/CreateProjectXf.png");
        midAdd_Pix[2].load(":/image/jisuan/CreateProjectFb.png");
        midSave_Pix[1].load(":/image/jisuan/SaveXf.png");
        midSave_Pix[2].load(":/image/jisuan/SaveFb.png");
        midClose_Pix[1].load(":/image/jisuan/AnNiu_GuanBiXF.png");
        midClose_Pix[2].load(":/image/jisuan/AnNiu_GuanBiFb.png");
    }
    else
    {
        this->setPalette(QPalette(QPalette::Window,QColor(56, 56, 56)));
        m_chart->setTheme(QChart::ChartThemeDark);
        m_chart->setBackgroundBrush(QColor(80, 80, 80));
        midPlt.setColor(QPalette::Text, QColor(127, 127, 127));
        midPlt_H.setColor(QPalette::Text, QColor(247, 247, 247));//字体颜色
        midPlt.setColor(QPalette::Base, QColor(80, 80, 80));
        midPlt_H.setColor(QPalette::Base, QColor(80, 80, 80));
        midAdd_Pix[1].load(":/image/jisuan/CreateProjectXf_H.png");
        midAdd_Pix[2].load(":/image/jisuan/CreateProjectFb_H.png");
        midSave_Pix[1].load(":/image/jisuan/SaveXf_H.png");
        midSave_Pix[2].load(":/image/jisuan/SaveFb_H.png");
        midClose_Pix[1].load(":/image/jisuan/AnNiu_GuanBiXF_H.png");
        midClose_Pix[2].load(":/image/jisuan/AnNiu_GuanBiFb_H.png");
    }
    SeriesAdd.setParent(this);
    SeriesAdd.setpix(&midAdd_Pix[0]);
    SeriesAdd.setpixXf(&midAdd_Pix[1]);
    SeriesAdd.setpixDj(&midAdd_Pix[2]);
    SeriesAdd.set_QFont(AnNiuFont);
    SeriesAdd.setAnNiuWH(25,20);

    SaveToPng.setParent(this);
    SaveToPng.setpix(&midSave_Pix[0]);
    SaveToPng.setpixXf(&midSave_Pix[1]);
    SaveToPng.setpixDj(&midSave_Pix[2]);
    SaveToPng.set_QFont(AnNiuFont);
    SaveToPng.setAnNiuWH(25,20);

    SeriesClose.setParent(this);
    SeriesClose.setpix(&midClose_Pix[0]);
    SeriesClose.setpixXf(&midClose_Pix[1]);
    SeriesClose.setpixDj(&midClose_Pix[2]);
    SeriesClose.set_QFont(AnNiuFont);
    SeriesClose.setAnNiuWH(25,20);

    View=new FirtCurveChartView(this);
    m_axisX = new QValueAxis();
    m_axisY = new QValueAxis();
    m_axisX->setTitleText("时间轴-秒");
    m_axisY->setTitleText("变量轴");
    m_axisX->setMin(AXIS_Min_X);
    m_axisX->setMax(AXIS_MAX_X);
    m_axisY->setMin(AXIS_Min_Y);
    m_axisY->setMax(AXIS_MAX_Y);

    if(LintType<3)
    {
        midOffOn.setParent(this);
        midOffOn.set_ZhuTi(ZhuTi);
        midOffOn.CantClick();
        X_VarName.setParent(this);
        if(ZhuTi==0)
        {
            X_VarName.setStyleSheet("background-color: #dfdfdf;");
        }
        else
        {
            X_VarName.setStyleSheet("background-color: #686868;");
        }
        X_VarName.setFrame(QFrame::NoFrame);
        X_VarName.setFont(AnNiuFont);
        X_VarName.setPalette(midPlt);
        X_VarName.setText("请填入变量名称");

        connect(&X_VarName, &QLineEdit::cursorPositionChanged, this, [=](){
            if(X_VarName_start==0)
            {
                X_VarName.setText("");
                X_VarName.setPalette(midPlt_H);
                X_VarName_start=1;
            }
        });
        connect(&X_VarName, &QLineEdit::textEdited, this, [=](QString midstring){
            if(X_VarName_start==1)
            {
                emit VarNameOut(6,midstring);
            }
        });
    }
    connect(&SeriesAdd, &AnniuDiandong::AnNiuClicked, this, [=](){Add_Series();});
    connect(&SeriesClose, &AnniuDiandong::AnNiuClicked, this, [=](){emit CloseView();});
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
        if(!middir.exists()){middir.mkdir(MidAddress);}//若没有文件夹，则新建一个
        MidAddress=MidAddress+PjtName+"_"+midYMD+"_"+current_time+".png";
        QRect midrect;
        midrect.setRect(0,0,5760,3240);//保存为6K的图片
        this->resize(5760,3240);
        QPixmap midpixmap=this->grab(midrect);
        midpixmap.save(MidAddress);
        this->resize(mid_ww,mid_hh);
    });
    View->setChart(m_chart);                           // 将图表对象设置到graphicsView上进行显示
    View->setRenderHint(QPainter::Antialiasing);       // 设置渲染：抗锯齿，如果不设置那么曲线就显得不平滑
    connect(View, &FirtCurveChartView::signalMouseEvent, this,[=](int eventId, QMouseEvent *event){
        if(LintType<3)
        {
            if (eventId == 0)//单击按下
            {
                isPressed = true;
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                pressedPoint = mouseEvent->pos();
            }
            else if (eventId == 1)//鼠标移动
            {
                if (isPressed)
                {
                    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                    double DX=-(mouseEvent->pos().x() - pressedPoint.x());
                    double DY=(mouseEvent->pos().y() - pressedPoint.y());
                    m_chart->scroll(DX,DY);//Y轴坐标
                    pressedPoint = mouseEvent->pos();
                }
            }
            else if (eventId == 2)//单击抬起
            {
                isPressed = false;
            }
            else if (eventId == 3)//双击
            {
                m_axisX->setMin(AXIS_Min_X);
                m_axisX->setMax(AXIS_MAX_X);
                m_axisY->setMin(AXIS_Min_Y);
                m_axisY->setMax(AXIS_MAX_Y);
                SuoFangXiShu=1;
            }
        }
        else
        {
            if (eventId == 3)//双击
            {
                m_chart->zoomReset();
                SuoFangXiShu=1;
            }
        }
    });
    connect(View, &FirtCurveChartView::signalWheelEvent, this, [=](QWheelEvent *event){
        int delta = event->angleDelta().y();
        if (delta > 0)
        {
            m_chart->zoom(1.25);
            SuoFangXiShu=SuoFangXiShu*1.25;
        }
        else
        {
            if(SuoFangXiShu>1.20)
            {
                m_chart->zoom(0.8);
                SuoFangXiShu=SuoFangXiShu*0.8;
            }
        }
    });
    if(LintType<3)
    {
        m_chart->addAxis(m_axisX, Qt::AlignBottom);                      // 将X轴添加到图表上
        m_chart->addAxis(m_axisY, Qt::AlignLeft);                    // 将Y轴添加到图表上
    }
    else
    {
        if(LintType==3)
        {
            if(LI.size()<=0)
            {
                LI.resize(1);
                LI[0].m_Series3 = new QPieSeries();
                LI[0].m_Series3->setUseOpenGL(true);
                m_chart->addSeries(LI[0].m_Series3);
                m_chart->setAnimationOptions(QChart::SeriesAnimations);
                m_chart->legend()->setAlignment(Qt::AlignBottom);
                m_chart->legend()->setBackgroundVisible(false);
                m_chart->setTitle(PjtName);
                connect(LI[0].m_Series3, &QPieSeries::clicked, [=](QPieSlice *slice)mutable{
                    slice->setExploded(!slice->isExploded());
                });
            }
        }
    }
}
void BaseIcon::SeriesInfoClear(int Xian_Nb)
{
    if(Xian_Nb>=6)
    {
        if(LintType<3)
        {
            HengZhouCanBeShow=0;
            midOffOn.setOnOff(0);
        }
        return;
    }
    LIN[Xian_Nb].CanBeShow=1;
    if(LintType==0)
    {
        m_chart->removeSeries(LI[Xian_Nb].m_Series0);// 图例名称
        disconnect(LI[Xian_Nb].m_Series0, &QLineSeries::clicked, 0,0);
    }
    if(LintType==1)
    {
        m_chart->removeSeries(LI[Xian_Nb].m_Series1);// 图例名称
        disconnect(LI[Xian_Nb].m_Series1, &QLineSeries::clicked, 0,0);
    }
    if(LintType==2)
    {
        m_chart->removeSeries(LI[Xian_Nb].m_Series2);// 图例名称
        disconnect(LI[Xian_Nb].m_Series2, &QLineSeries::clicked, 0,0);
    }
    if(LintType==3)
    {
        if(LIN[Xian_Nb].BarPieNb>=0)
        {
            LI[0].m_Series3->remove(LIN[Xian_Nb].pie_slice);
        }
        for(int zi=0;zi<LIN.size();zi++)
        {
            if(zi!=Xian_Nb)
            {
                if(LIN[zi].BarPieNb>LIN[Xian_Nb].BarPieNb)
                {
                    LIN[zi].BarPieNb=LIN[zi].BarPieNb-1;
                }
            }
        }
        LIN[Xian_Nb].BarPieNb=-1;
    }
}
void BaseIcon::SeriesInfoSet(int Xian_Nb,QString midstring)
{
    if(Xian_Nb>=6)
    {
        ChartClear();
        if(LintType<3)
        {
            if(X_VarName_start == 0)//存在初始化时直接赋值的问题
            {
                X_VarName_start=1;
                X_VarName.setPalette(midPlt_H);
                X_VarName.setText(midstring);
            }
            midOffOn.setOnOff(1);
            HengZhouCanBeShow=1;
        }
        return;
    }
    if(LIN_Start[Xian_Nb] == 0)//初始化时，直接赋值，初始化后，不再赋值
    {
        LIN_Start[Xian_Nb]=1;
        LIN[Xian_Nb].VarName->setPalette(midPlt_H);
        LIN[Xian_Nb].VarName->setText(midstring);
    }
    LIN[Xian_Nb].CanBeShow=1;
    if(LintType==0)
    {
        LI[Xian_Nb].m_Series0->setName(midstring);
        m_chart->addSeries(LI[Xian_Nb].m_Series0);// 图例名称
        LI[Xian_Nb].m_Series0->attachAxis(m_axisX);// 曲线对象关联上X轴，此步骤必须在m_chart->addSeries之后
        LI[Xian_Nb].m_Series0->attachAxis(m_axisY);
        connect(LI[Xian_Nb].m_Series0, &QLineSeries::clicked, [=](const QPointF &point)mutable{
            QToolTip::showText(QCursor::pos(), QString("(%1,%2)").arg(point.x()).arg(point.y()));
        });
    }
    if(LintType==1)
    {
        LI[Xian_Nb].m_Series1->setName(midstring);
        m_chart->addSeries(LI[Xian_Nb].m_Series1);// 图例名称
        LI[Xian_Nb].m_Series1->attachAxis(m_axisX);// 曲线对象关联上X轴，此步骤必须在m_chart->addSeries之后
        LI[Xian_Nb].m_Series1->attachAxis(m_axisY);
        connect(LI[Xian_Nb].m_Series1, &QLineSeries::clicked, [=](const QPointF &point)mutable{
            QToolTip::showText(QCursor::pos(), QString("(%1,%2)").arg(point.x()).arg(point.y()));
        });
    }
    if(LintType==2)
    {
        LI[Xian_Nb].m_Series2->setName(midstring);
        m_chart->addSeries(LI[Xian_Nb].m_Series2);// 图例名称
        LI[Xian_Nb].m_Series2->attachAxis(m_axisX);// 曲线对象关联上X轴，此步骤必须在m_chart->addSeries之后
        LI[Xian_Nb].m_Series2->attachAxis(m_axisY);
        connect(LI[Xian_Nb].m_Series2, &QLineSeries::clicked, [=](const QPointF &point)mutable{
            QToolTip::showText(QCursor::pos(), QString("(%1,%2)").arg(point.x()).arg(point.y()));
        });
    }
    if(LintType==3)
    {
        if(LIN[Xian_Nb].BarPieNb<0)
        {
            LIN[Xian_Nb].pie_slice = new QPieSlice(this);
            LIN[Xian_Nb].pie_slice->setLabelVisible(true);
            LIN[Xian_Nb].pie_slice->setValue(3.33);
            LIN[Xian_Nb].pie_slice->setLabel(QString::number(3.33));//初始化数字
            LIN[Xian_Nb].pie_slice->setColor(list_pie_color[Xian_Nb]);
            LIN[Xian_Nb].pie_slice->setLabelColor(list_pie_color[Xian_Nb]);
            LIN[Xian_Nb].pie_slice->setBorderColor(list_pie_color[Xian_Nb]);
            LIN[Xian_Nb].BarPieNb=LI[0].m_Series3->slices().size();
            LI[0].m_Series3->append(LIN[Xian_Nb].pie_slice);
            m_chart->legend()->markers()[LI[0].m_Series3->slices().size()-1]->setLabel(midstring);
        }
        else
        {
            m_chart->legend()->markers()[LIN[Xian_Nb].BarPieNb]->setLabel(midstring);
        }
    }
}
int  BaseIcon::LintTypeGet()
{
    return LintType;
}
bool BaseIcon::SeriesNameGet(int midNb,QString &midVarName)
{
    if(midNb>=LIN.size())
    {
        if(midNb==6)
        {
            if(LintType<3)
            {
                if(HengZhouCanBeShow)
                {
                    midVarName=X_VarName.text();
                    return 1;
                }
            }
        }
        return 0;
    }
    if(LIN[midNb].CanBeShow == 1)
    {
        midVarName=LIN[midNb].VarName->text();
        return 1;
    }
    else
    {
        return 0;
    }
}
void BaseIcon::Add_Series()
{
    int Xian_Nb=LIN.size();//不能是LI，那个是曲线等，具体要判断带Name的
    if(Xian_Nb>=6){return;}
    LIN.resize(Xian_Nb+1);
    LIN[Xian_Nb].VarName = new QLineEdit(this);
    LIN[Xian_Nb].VarName ->setFrame(QFrame::NoFrame);
    LIN[Xian_Nb].VarName ->setFont(AnNiuFont);
    LIN[Xian_Nb].VarName ->setPalette(midPlt);
    LIN[Xian_Nb].VarName ->setText("请填入变量        ");
    LIN[Xian_Nb].VarName->show();
    LIN[Xian_Nb].CanBeShow=0;
    LIN[Xian_Nb].BarPieNb=-1;
    LIN_Start.resize(Xian_Nb+1);
    LIN_Start[Xian_Nb]=0;
    if(LintType<3)
    {
        LI.resize(Xian_Nb+1);
        if(LintType==0){LI[Xian_Nb].m_Series0 = new QLineSeries();
            LI[Xian_Nb].m_Series0->setUseOpenGL(true);
            LI[Xian_Nb].m_Series0->setPointsVisible(true);} //这里改为其他曲线类型          // 创建曲线绘制对象
        if(LintType==1){LI[Xian_Nb].m_Series1 = new QSplineSeries();
            LI[Xian_Nb].m_Series1->setUseOpenGL(true);
            LI[Xian_Nb].m_Series1->setPointsVisible(true);} //这里改为其他曲线类型          // 创建曲线绘制对象
        if(LintType==2){LI[Xian_Nb].m_Series2 = new QScatterSeries();
            LI[Xian_Nb].m_Series2->setUseOpenGL(true);
            LI[Xian_Nb].m_Series2->setPointsVisible(true);} //这里改为其他曲线类型          // 创建曲线绘制对象
    }
    connect(LIN[Xian_Nb].VarName, &QLineEdit::cursorPositionChanged, this, [=](){
        if(LIN_Start[Xian_Nb]==0)
        {
            LIN[Xian_Nb].VarName->setText("");
            LIN[Xian_Nb].VarName->setPalette(midPlt_H);
            LIN_Start[Xian_Nb]=1;
        }
    });
    connect(LIN[Xian_Nb].VarName, &QLineEdit::textEdited, this, [=](QString midstring){
        if(LIN_Start[Xian_Nb]==1)
        {
            emit VarNameOut(Xian_Nb,midstring);
        }
    });
    for(int zi=0;zi<LIN.size();zi++)
    {
        LIN[zi].VarName->setGeometry(zi*100+10,4,96,20);
    }
    SeriesAdd.setGeometry(LIN.size()*100+10,4,25,20);
}
void BaseIcon::LintTypeSet(int midLintType)
{
    LintType=midLintType;
}
void BaseIcon::PjtNameSet(QString midPjtName)
{
    PjtName=midPjtName;
}
void BaseIcon::ChartClear()
{
    if(LintType<3)
    {
        AXIS_MAX_X = 0.2;
        AXIS_MAX_Y = 10.0;
        AXIS_Min_X = 0.0;
        AXIS_Min_Y = 0.0;

        m_axisX->setMin(AXIS_Min_X);
        m_axisX->setMax(AXIS_MAX_X);
        m_axisY->setMin(AXIS_Min_Y);
        m_axisY->setMax(AXIS_MAX_Y);

        for(int zi=0;zi<LI.size();zi++)
        {
            if(LIN[zi].CanBeShow>0.5)
            {
                if(LintType==0)
                {
                    LI[zi].m_Series0->clear();
                }
                if(LintType==1)
                {
                    LI[zi].m_Series1->clear();
                }
                if(LintType==2)
                {
                    LI[zi].m_Series2->clear();
                }
            }
        }
    }
}

void BaseIcon::SeriesReplaceEnd()
{
    if(LintType<3)
    {
        if(HengZhouCanBeShow==1&&HengZhouValueGet==1)
        {
            return;
        }
        double midzuida_min=0;
        double midzuida_max=0;
        bool if_start_midzuida_min=0;
        for(int zi=0;zi<LI.size();zi++)
        {
            if(LIN[zi].CanBeShow>0.5)
            {
                if(if_start_midzuida_min==0)
                {
                    if(LintType==0)
                    {
                        if(LI[zi].m_Series0->count()>0)
                        {
                            midzuida_min=LI[zi].m_Series0->points()[0].x();
                            midzuida_max=LI[zi].m_Series0->points()[LI[zi].m_Series0->count()-1].x();
                        }
                    }
                    if(LintType==1)
                    {
                        if(LI[zi].m_Series1->count()>0)
                        {
                            midzuida_min=LI[zi].m_Series1->points()[0].x();
                            midzuida_max=LI[zi].m_Series1->points()[LI[zi].m_Series1->count()-1].x();
                        }
                    }
                    if(LintType==2)
                    {
                        if(LI[zi].m_Series2->count()>0)
                        {
                            midzuida_min=LI[zi].m_Series2->points()[0].x();
                            midzuida_max=LI[zi].m_Series2->points()[LI[zi].m_Series2->count()-1].x();
                        }
                    }
                    if_start_midzuida_min=1;
                }
                else
                {
                    if(LintType==0)
                    {
                        if(LI[zi].m_Series0->count()>0)
                        {
                            if(midzuida_min>LI[zi].m_Series0->points()[0].x())
                            {
                                midzuida_min=LI[zi].m_Series0->points()[0].x();
                            }
                            if(midzuida_max<LI[zi].m_Series0->points()[LI[zi].m_Series0->count()-1].x())
                            {
                                midzuida_max=LI[zi].m_Series0->points()[LI[zi].m_Series0->count()-1].x();
                            }
                        }
                    }
                    if(LintType==1)
                    {
                        if(LI[zi].m_Series1->count()>0)
                        {
                            if(midzuida_min>LI[zi].m_Series1->points()[0].x())
                            {
                                midzuida_min=LI[zi].m_Series1->points()[0].x();
                            }
                            if(midzuida_max<LI[zi].m_Series1->points()[LI[zi].m_Series1->count()-1].x())
                            {
                                midzuida_max=LI[zi].m_Series1->points()[LI[zi].m_Series1->count()-1].x();
                            }
                        }
                    }
                    if(LintType==2)
                    {
                        if(LI[zi].m_Series2->count()>0)
                        {
                            if(midzuida_min>LI[zi].m_Series2->points()[0].x())
                            {
                                midzuida_min=LI[zi].m_Series2->points()[0].x();
                            }
                            if(midzuida_max<LI[zi].m_Series2->points()[LI[zi].m_Series2->count()-1].x())
                            {
                                midzuida_max=LI[zi].m_Series2->points()[LI[zi].m_Series2->count()-1].x();
                            }
                        }
                    }
                }
            }
        }
        if(AXIS_Min_X<midzuida_min)
        {
            AXIS_Min_X=midzuida_min;
            m_axisX->setMin(AXIS_Min_X);
            AXIS_MAX_X=midzuida_max;
            m_axisX->setMax(AXIS_MAX_X);
        }
    }
}
void BaseIcon::SeriesValue(int pjtnb,int midviewnb,int midlinenb,Chart_PointCache midpoint,Chart_CacheSx midCacheSx,int AllSize)
{
    if(LintType<3)
    {
        if(midlinenb>=LI.size())
        {
            return;
        }
        if(AllSize<=maxPointNb)//当要求显示的数量小于高速缓存时，直接按照最简单逻辑读取高速缓存
        {
            if(midpoint.StartSize<99990)
            {
                if(AllSize>=midpoint.StartSize)
                {
                    if(midPs.size()!=midpoint.StartSize)
                    {
                        midPs.resize(midpoint.StartSize);
                    }
                    for(int zi=0;zi<midpoint.StartSize;zi++)
                    {
                        midPs[zi].setX(midpoint.point.x[zi]);
                        midPs[zi].setY(midpoint.point.y[zi]);
                    }
                }
                else
                {
                    if(midPs.size()!=AllSize)
                    {
                        midPs.resize(AllSize);
                    }
                    for(int zi=midpoint.StartSize-AllSize;zi<midpoint.StartSize;zi++)
                    {
                        midPs[zi-midpoint.StartSize+AllSize].setX(midpoint.point.x[zi]);
                        midPs[zi-midpoint.StartSize+AllSize].setY(midpoint.point.y[zi]);
                    }
                }
            }
            else
            {
                if(midPs.size()!=AllSize)
                {
                    midPs.resize(AllSize);
                }
                if(midpoint.StartNb>=AllSize)
                {
                    for(int zi=midpoint.StartNb-AllSize;zi<midpoint.StartNb;zi++)
                    {
                        midPs[zi-midpoint.StartNb+AllSize].setX(midpoint.point.x[zi]);
                        midPs[zi-midpoint.StartNb+AllSize].setY(midpoint.point.y[zi]);
                    }
                }
                else
                {
                    int end_chackNb=AllSize-midpoint.StartNb;
                    for(int zi=maxPointNb-end_chackNb;zi<maxPointNb;zi++)
                    {
                        midPs[zi-maxPointNb+end_chackNb].setX(midpoint.point.x[zi]);
                        midPs[zi-maxPointNb+end_chackNb].setY(midpoint.point.y[zi]);
                    }
                    for(int zi=0;zi<midpoint.StartNb;zi++)
                    {
                        midPs[zi+end_chackNb].setX(midpoint.point.x[zi]);
                        midPs[zi+end_chackNb].setY(midpoint.point.y[zi]);
                    }
                }
            }
        }
        else//当要求的数量高于高速缓存的maxPointNb时，要分具体情况进行
        {
            if(midpoint.StartSize<99990)//如果此时连point的start都没有填满，其他的都不满
            {
                //直接按照高速缓存来
                if(midPs.size()!=midpoint.StartSize)
                {
                    midPs.resize(midpoint.StartSize);
                }
                for(int zi=0;zi<midpoint.StartSize;zi++)
                {
                    midPs[zi].setX(midpoint.point.x[zi]);
                    midPs[zi].setY(midpoint.point.y[zi]);
                }
            }
            else//若point的start已填满，则cache至少size==1,判断Cache+point总数的值能不能满足显示数量
            {
                Chart_XY midPointXY={{0},{0}};
                int midCache_AllSize=midCacheSx.CanBeRead+midpoint.StartNb;
                if(AllSize>=midCache_AllSize)//此时Cache肯定未填满
                {
                    if(midPs.size()!=midCache_AllSize)
                    {
                        midPs.resize(midCache_AllSize);
                    }
                    int midWi=0;
                    for(int zi=0;zi<midCacheSx.StartSize;zi++)
                    {
                        midWi=zi*maxPointNb;
                        Chart_CacheGet(pjtnb,midviewnb,midlinenb,zi,midPointXY);
                        for(int yi=0;yi<maxPointNb;yi++)
                        {
                            midPs[midWi+yi].setX(midPointXY.x[yi]);
                            midPs[midWi+yi].setY(midPointXY.y[yi]);
                        }
                    }
                    midWi=midCacheSx.StartSize*maxPointNb;
                    for(int zi=0;zi<midpoint.StartNb;zi++)
                    {
                        midPs[midWi+zi].setX(midpoint.point.x[zi]);
                        midPs[midWi+zi].setY(midpoint.point.y[zi]);
                    }
                }
                else//当总数量大于要求数量，则size按照要求数量来
                {
                    if(midPs.size()!=AllSize)
                    {
                        midPs.resize(AllSize);
                    }
                    int midCache_ReadSize=AllSize-midpoint.StartNb;
                    //从Cache里面读取midCache_ReadSize个数
                    int midWi=0;
                    int midCache_RdNb = (midCache_ReadSize-1)/maxPointNb+1;//涉及到的缓存块数量
                    int midCache_YuShu = midCache_RdNb*maxPointNb-midCache_ReadSize;
                    if(midCacheSx.StartSize<99990)
                    {
                        for(int zi=midCacheSx.StartSize-midCache_RdNb;zi<midCacheSx.StartSize;zi++)
                        {
                            midWi=(zi-midCacheSx.StartSize+midCache_RdNb)*maxPointNb-midCache_YuShu;
                            Chart_CacheGet(pjtnb,midviewnb,midlinenb,zi,midPointXY);
                            for(int yi=0;yi<maxPointNb;yi++)
                            {
                                if((midWi+yi)>=0)
                                {
                                    midPs[midWi+yi].setX(midPointXY.x[yi]);
                                    midPs[midWi+yi].setY(midPointXY.y[yi]);
                                }
                            }
                        }
                    }
                    else
                    {
                        if(midCacheSx.StartNb>=midCache_RdNb)
                        {
                            for(int zi=midCacheSx.StartNb-midCache_RdNb;zi<midCacheSx.StartNb;zi++)
                            {
                                midWi=(zi-midCacheSx.StartNb+midCache_RdNb)*maxPointNb-midCache_YuShu;
                                Chart_CacheGet(pjtnb,midviewnb,midlinenb,zi,midPointXY);
                                for(int yi=0;yi<maxPointNb;yi++)
                                {
                                    if((midWi+yi)>=0)
                                    {
                                        midPs[midWi+yi].setX(midPointXY.x[yi]);
                                        midPs[midWi+yi].setY(midPointXY.y[yi]);
                                    }
                                }
                            }
                        }
                        else
                        {
                            int end_chackNb=midCache_RdNb-midCacheSx.StartNb;
                            for(int zi=60-end_chackNb;zi<60;zi++)
                            {
                                midWi=(zi-60+end_chackNb)*maxPointNb-midCache_YuShu;
                                Chart_CacheGet(pjtnb,midviewnb,midlinenb,zi,midPointXY);
                                for(int yi=0;yi<maxPointNb;yi++)
                                {
                                    if((midWi+yi)>=0)
                                    {
                                        midPs[midWi+yi].setX(midPointXY.x[yi]);
                                        midPs[midWi+yi].setY(midPointXY.y[yi]);
                                    }
                                }
                            }
                            for(int zi=0;zi<midCacheSx.StartNb;zi++)
                            {
                                midWi=(zi+end_chackNb)*maxPointNb-midCache_YuShu;
                                Chart_CacheGet(pjtnb,midviewnb,midlinenb,zi,midPointXY);
                                for(int yi=0;yi<maxPointNb;yi++)
                                {
                                    if((midWi+yi)>=0)
                                    {
                                        midPs[midWi+yi].setX(midPointXY.x[yi]);
                                        midPs[midWi+yi].setY(midPointXY.y[yi]);
                                    }
                                }
                            }
                        }
                    }
                    //从高速缓存里面读取最后面的数
                    for(int zi=0;zi<midpoint.StartNb;zi++)
                    {
                        midPs[midCache_ReadSize+zi].setX(midpoint.point.x[zi]);
                        midPs[midCache_ReadSize+zi].setY(midpoint.point.y[zi]);
                    }
                }
            }
        }
        if(HengZhouCanBeShow==1&&HengZhouValueGet==1)
        {
            for(int zi=0;zi<midPs.size();zi++)
            {
                if(zi<midHeng.size())
                {
                    midPs[zi].setX(midHeng[zi].y());
                }
                else
                {
                    int midHengNb=midHeng.size();
                    midPs[zi].setX(midHeng[midHengNb-1].y());
                }
            }
        }
        bool if_X_Max_Ref=0;
        bool if_X_Min_Ref=0;
        bool if_Y_Max_Ref=0;
        bool if_Y_Min_Ref=0;

        for(int zi=0;zi<midPs.size();zi++)
        {
            if(midPs[zi].x()>AXIS_MAX_X)
            {
                AXIS_MAX_X=midPs[zi].x();
                if_X_Max_Ref=1;
            }
            if(midPs[zi].x()<AXIS_Min_X)
            {
                AXIS_Min_X=midPs[zi].x();
                if_X_Min_Ref=1;
            }
            if(AXIS_MAX_Y<midPs[zi].y()+10)
            {
                AXIS_MAX_Y=midPs[zi].y()+10;
                if_Y_Max_Ref=1;
            }
            if(AXIS_Min_Y>midPs[zi].y()-10)
            {
                AXIS_Min_Y=midPs[zi].y()-10;
                if_Y_Min_Ref=1;
            }
        }
        if(if_X_Max_Ref)
        {
            m_axisX->setMax(AXIS_MAX_X);
        }
        if(if_X_Min_Ref)
        {
            m_axisX->setMin(AXIS_Min_X);
        }
        if(if_Y_Max_Ref)
        {
            m_axisY->setMax(AXIS_MAX_Y);
        }
        if(if_Y_Min_Ref)
        {
            m_axisY->setMin(AXIS_Min_Y);
        }
        if(LintType==0)
        {
            if(LIN[midlinenb].CanBeShow==1)
            {
                int midcount=LI[midlinenb].m_Series0->count();
                LI[midlinenb].m_Series0->removePoints(0, midcount);
                LI[midlinenb].m_Series0->replace(midPs);
            }
        }
        if(LintType==1)
        {
            if(LIN[midlinenb].CanBeShow==1)
            {
                int midcount=LI[midlinenb].m_Series1->count();
                LI[midlinenb].m_Series1->removePoints(0, midcount);
                LI[midlinenb].m_Series1->replace(midPs);
            }
        }
        if(LintType==2)
        {
            if(LIN[midlinenb].CanBeShow==1)
            {
                int midcount=LI[midlinenb].m_Series2->count();
                LI[midlinenb].m_Series2->removePoints(0, midcount);
                LI[midlinenb].m_Series2->replace(midPs);
            }
        }
    }
    if(LintType==3)//若为饼图，则只获取一个变量
    {
        if(midlinenb>=LIN.size())
        {
            return;
        }
        if(LIN[midlinenb].BarPieNb>=0)
        {
            double mid_value;
            if(midpoint.StartSize<99990)
            {
                mid_value=midpoint.point.y[midpoint.StartSize-1];
            }
            else
            {
                if(midpoint.StartNb>=1)
                {
                    mid_value=midpoint.point.y[midpoint.StartNb-1];
                }
                else
                {
                    mid_value=midpoint.point.y[maxPointNb-1];
                }
            }
            if(LIN[midlinenb].CanBeShow==1)
            {
                LI[0].m_Series3->slices()[LIN[midlinenb].BarPieNb]->setLabel(QString::number(mid_value));
                if(mid_value<0)
                {
                    mid_value=-mid_value;
                }
                LI[0].m_Series3->slices()[LIN[midlinenb].BarPieNb]->setValue(mid_value);
            }
        }
    }
}
void BaseIcon::HengzhouValue(int pjtnb,int midviewnb,Chart_PointCache midpoint,Chart_CacheSx midCacheSx,int AllSize)
{
    if(LintType<3)
    {
    HengZhouValueGet=0;//每一次都要先归零，后面若成功读取，则再赋值为1
    if(HengZhouCanBeShow)
    {
        HengZhouValueGet=1;
        if(AllSize<=maxPointNb)//当要求显示的数量小于高速缓存时，直接按照最简单逻辑读取高速缓存
        {
            if(midpoint.StartSize<99990)
            {
                if(AllSize>=midpoint.StartSize)
                {
                    if(midHeng.size()!=midpoint.StartSize)
                    {
                        midHeng.resize(midpoint.StartSize);
                    }
                    for(int zi=0;zi<midpoint.StartSize;zi++)
                    {
                        midHeng[zi].setX(midpoint.point.x[zi]);
                        midHeng[zi].setY(midpoint.point.y[zi]);
                    }
                }
                else
                {
                    if(midHeng.size()!=AllSize)
                    {
                        midHeng.resize(AllSize);
                    }
                    for(int zi=midpoint.StartSize-AllSize;zi<midpoint.StartSize;zi++)
                    {
                        midHeng[zi-midpoint.StartSize+AllSize].setX(midpoint.point.x[zi]);
                        midHeng[zi-midpoint.StartSize+AllSize].setY(midpoint.point.y[zi]);
                    }
                }
            }
            else
            {
                if(midHeng.size()!=AllSize)
                {
                    midHeng.resize(AllSize);
                }
                if(midpoint.StartNb>=AllSize)
                {
                    for(int zi=midpoint.StartNb-AllSize;zi<midpoint.StartNb;zi++)
                    {
                        midHeng[zi-midpoint.StartNb+AllSize].setX(midpoint.point.x[zi]);
                        midHeng[zi-midpoint.StartNb+AllSize].setY(midpoint.point.y[zi]);
                    }
                }
                else
                {
                    int end_chackNb=AllSize-midpoint.StartNb;
                    for(int zi=maxPointNb-end_chackNb;zi<maxPointNb;zi++)
                    {
                        midHeng[zi-maxPointNb+end_chackNb].setX(midpoint.point.x[zi]);
                        midHeng[zi-maxPointNb+end_chackNb].setY(midpoint.point.y[zi]);
                    }
                    for(int zi=0;zi<midpoint.StartNb;zi++)
                    {
                        midHeng[zi+end_chackNb].setX(midpoint.point.x[zi]);
                        midHeng[zi+end_chackNb].setY(midpoint.point.y[zi]);
                    }
                }
            }
        }
        else//当要求的数量高于高速缓存的maxPointNb时，要分具体情况进行
        {
            if(midpoint.StartSize<99990)//如果此时连point的start都没有填满，其他的都不满
            {
                //直接按照高速缓存来
                if(midHeng.size()!=midpoint.StartSize)
                {
                    midHeng.resize(midpoint.StartSize);
                }
                for(int zi=0;zi<midpoint.StartSize;zi++)
                {
                    midHeng[zi].setX(midpoint.point.x[zi]);
                    midHeng[zi].setY(midpoint.point.y[zi]);
                }
            }
            else//若point的start已填满，则cache至少size==1,判断Cache+point总数的值能不能满足显示数量
            {
                Chart_XY midPointXY={{0},{0}};
                int midCache_AllSize=midCacheSx.CanBeRead+midpoint.StartNb;
                if(AllSize>=midCache_AllSize)//此时Cache肯定未填满
                {
                    if(midHeng.size()!=midCache_AllSize)
                    {
                        midHeng.resize(midCache_AllSize);
                    }
                    int midWi=0;
                    for(int zi=0;zi<midCacheSx.StartSize;zi++)
                    {
                        midWi=zi*maxPointNb;
                        Chart_CacheGet(pjtnb,midviewnb,6,zi,midPointXY);
                        for(int yi=0;yi<maxPointNb;yi++)
                        {
                            midHeng[midWi+yi].setX(midPointXY.x[yi]);
                            midHeng[midWi+yi].setY(midPointXY.y[yi]);
                        }
                    }
                    midWi=midCacheSx.StartSize*maxPointNb;
                    for(int zi=0;zi<midpoint.StartNb;zi++)
                    {
                        midHeng[midWi+zi].setX(midpoint.point.x[zi]);
                        midHeng[midWi+zi].setY(midpoint.point.y[zi]);
                    }
                }
                else//当总数量大于要求数量，则size按照要求数量来
                {
                    if(midHeng.size()!=AllSize)
                    {
                        midHeng.resize(AllSize);
                    }
                    int midCache_ReadSize=AllSize-midpoint.StartNb;
                    //从Cache里面读取midCache_ReadSize个数
                    int midWi=0;
                    int midCache_RdNb = (midCache_ReadSize-1)/maxPointNb+1;//涉及到的缓存块数量
                    int midCache_YuShu = midCache_RdNb*maxPointNb-midCache_ReadSize;
                    if(midCacheSx.StartSize<99990)
                    {
                        for(int zi=midCacheSx.StartSize-midCache_RdNb;zi<midCacheSx.StartSize;zi++)
                        {
                            midWi=(zi-midCacheSx.StartSize+midCache_RdNb)*maxPointNb-midCache_YuShu;
                            Chart_CacheGet(pjtnb,midviewnb,6,zi,midPointXY);
                            for(int yi=0;yi<maxPointNb;yi++)
                            {
                                if((midWi+yi)>=0)
                                {
                                    midHeng[midWi+yi].setX(midPointXY.x[yi]);
                                    midHeng[midWi+yi].setY(midPointXY.y[yi]);
                                }
                            }
                        }
                    }
                    else
                    {
                        if(midCacheSx.StartNb>=midCache_RdNb)
                        {
                            for(int zi=midCacheSx.StartNb-midCache_RdNb;zi<midCacheSx.StartNb;zi++)
                            {
                                midWi=(zi-midCacheSx.StartNb+midCache_RdNb)*maxPointNb-midCache_YuShu;
                                Chart_CacheGet(pjtnb,midviewnb,6,zi,midPointXY);
                                for(int yi=0;yi<maxPointNb;yi++)
                                {
                                    if((midWi+yi)>=0)
                                    {
                                        midHeng[midWi+yi].setX(midPointXY.x[yi]);
                                        midHeng[midWi+yi].setY(midPointXY.y[yi]);
                                    }
                                }
                            }
                        }
                        else
                        {
                            int end_chackNb=midCache_RdNb-midCacheSx.StartNb;
                            for(int zi=60-end_chackNb;zi<60;zi++)
                            {
                                midWi=(zi-60+end_chackNb)*maxPointNb-midCache_YuShu;
                                Chart_CacheGet(pjtnb,midviewnb,6,zi,midPointXY);
                                for(int yi=0;yi<maxPointNb;yi++)
                                {
                                    if((midWi+yi)>=0)
                                    {
                                        midHeng[midWi+yi].setX(midPointXY.x[yi]);
                                        midHeng[midWi+yi].setY(midPointXY.y[yi]);
                                    }
                                }
                            }
                            for(int zi=0;zi<midCacheSx.StartNb;zi++)
                            {
                                midWi=(zi+end_chackNb)*maxPointNb-midCache_YuShu;
                                Chart_CacheGet(pjtnb,midviewnb,6,zi,midPointXY);
                                for(int yi=0;yi<maxPointNb;yi++)
                                {
                                    if((midWi+yi)>=0)
                                    {
                                        midHeng[midWi+yi].setX(midPointXY.x[yi]);
                                        midHeng[midWi+yi].setY(midPointXY.y[yi]);
                                    }
                                }
                            }
                        }
                    }
                    //从高速缓存里面读取最后面的数
                    for(int zi=0;zi<midpoint.StartNb;zi++)
                    {
                        midHeng[midCache_ReadSize+zi].setX(midpoint.point.x[zi]);
                        midHeng[midCache_ReadSize+zi].setY(midpoint.point.y[zi]);
                    }
                }
            }
        }
    }}
}
bool BaseIcon::event(QEvent *ev)
{
    if(ev->type() == QEvent::Resize)
    {
        QResizeEvent *re = static_cast<QResizeEvent*> (ev);
        int geometry_w=re->size().width();
        int geometry_h=re->size().height();
        for(int zi=0;zi<LIN.size();zi++)
        {
            LIN[zi].VarName->setGeometry(zi*100+10,4,96,20);
        }
        SeriesAdd.setGeometry(LIN.size()*100+10,4,25,20);
        SeriesClose.setGeometry(geometry_w-24-10,4,25,20);
        SaveToPng.setGeometry(geometry_w-52-10,4,25,20);
        View->setGeometry(0,24,geometry_w,geometry_h-24);
        if(LintType<3)
        {
            midOffOn.setGeometry(geometry_w-146,geometry_h-30,40,20);
            midOffOn.setShow();
            X_VarName.setGeometry(geometry_w-106,geometry_h-30,94,18);
        }
    }
    return QWidget::event(ev);
}
void BaseIcon::closeEvent ( QCloseEvent * )
{
    LIN.clear();
    LI.clear();
    LI.resize(0);
    LIN.resize(0);
    m_chart->removeAllSeries();
    delete(m_axisX);
    delete(m_axisY);
    delete(m_chart);
    View->close();
    delete(View);
}

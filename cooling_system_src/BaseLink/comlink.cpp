#include "comlink.h"
ComLink::ComLink(QWidget *parent)
    : QWidget{parent}
{
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QPalette::Window,QColor(247, 247, 247)));

    AnNiuFont.setFamily("宋体");
    AnNiuFont.setBold(false);//加粗
    AnNiuFont.setPixelSize(12);

    QPalette midControl;
    midControl.setColor(QPalette::WindowText, QColor(255, 255, 255));
    QPalette midControl_Plt;
    midControl_Plt.setColor(QPalette::WindowText, QColor(0, 119, 170));
    midPlt.setColor(QPalette::Text, QColor(127, 127, 127));
    midPlt_H.setColor(QPalette::Text, QColor(40, 40, 40));//字体颜色

    QPixmap midAdd_Pix[3];
    midAdd_Pix[0].load(":/image/jisuan/CreateProject.png");
    midAdd_Pix[1].load(":/image/jisuan/CreateProjectXf.png");
    midAdd_Pix[2].load(":/image/jisuan/CreateProjectFb.png");
    QPixmap midSave_Pix[3];
    midSave_Pix[0].load(":/image/jisuan/Save.png");
    midSave_Pix[1].load(":/image/jisuan/SaveXf.png");
    midSave_Pix[2].load(":/image/jisuan/SaveFb.png");
    QPixmap midClose_Pix[3];
    midClose_Pix[0].load(":/image/jisuan/AnNiu_GuanBi.png");
    midClose_Pix[1].load(":/image/jisuan/AnNiu_GuanBiXF.png");
    midClose_Pix[2].load(":/image/jisuan/AnNiu_GuanBiFb.png");

    QPixmap AnNiu_FbPix(":/image/jisuan/AnNiu_Fb.png");
    QPixmap midControl_Pix[4];
    midControl_Pix[0].load(":/image/jisuan/AnNiu_Baocun.png");
    midControl_Pix[1].load(":/image/jisuan/AnNiu_YunXing.png");
    midControl_Pix[2].load(":/image/jisuan/AnNiu_ZanTing.png");
    //标签按钮设置
    QPixmap AnNiu_HuaBuPix;
    QPixmap AnNiu_HuaBuFbPix;
    AnNiu_HuaBuPix.load(":/image/jisuan/AnNiu_FanYe.png");
    AnNiu_HuaBuFbPix.load(":/image/jisuan/AnNiu_FanYeFb.png");
    QPixmap midOnOffPix[2];
    midOnOffPix[0].load(":/image/jisuan/ICON_ON.png");
    midOnOffPix[1].load(":/image/jisuan/ICON_OFF.png");

    TxtBiaoTi.setParent(this);
    TxtBiaoTi.set_QText("接收消息输出 / 发送消息输出");
    TxtBiaoTi.set_QFont(AnNiuFont);
    TxtBiaoTi.set_QPlt(GetUpTextPalette());

    TextGl.setParent(this);
    TextGl.setAutoFillBackground(true);
    TextGl.setPalette(GetDownWindowsPalette());

    //第1页初始化
    SentCode=new QsciScintilla(this);
    textLexerSent = new QsciLexerLua;//创建一个词法分析器
    SentCode->setLexer(textLexerSent);//给QsciScintilla设置词法分析器
    apisSent = new QsciAPIs(textLexerSent);
    CodeEditStart(SentCode,apisSent);

    SentCode->installEventFilter(this);

    QPalette midHeiZi;
    midHeiZi.setColor(QPalette::Text, QColor(40, 40, 40));

    PageButton.setParent(this);
    PageButton.set_QType(1);
    PageButton.setpix(AnNiu_HuaBuPix);
    PageButton.setpixDj(AnNiu_HuaBuFbPix);
    PageButton.set_QFont(AnNiuFont);
    PageButton.set_QPlt(midHeiZi);
    PageButton.set_QPltDj(GetUpTextPalette());
    PageButton.setAnNiuWH(60,24);
    PageButton.set_QText("发送处理");
    PageButton.setUpDown(1);

    LUA_TiShi.setParent(this);
    LUA_TiShi.setFrame(QFrame::NoFrame);
    LUA_TiShi.setFont(AnNiuFont);
    LUA_TiShi.setPalette(midPlt);
    LUA_TiShi.setText("CTHSRtn=\"要发送的消息\"");
    LUA_TiShi.setReadOnly(true);
    connect(&PageButton, &AnNiuZiSuo::AnNiuClicked,this,[=](){PageButton.setUpDown(1);});

    QPalette DingXian_Plt;
    DingXian_Plt.setColor(QPalette::Window, QColor(223, 223, 223));

    DingXian.setParent(this);
    DingXian.setAutoFillBackground(true);
    DingXian.setPalette(DingXian_Plt);

    DingXian1.setParent(this);
    DingXian1.setAutoFillBackground(true);
    DingXian1.setPalette(DingXian_Plt);

    //设置窗口标题和大小
    comboBox.setParent(this);

    textRcv.setParent(this);
    textRcv.setStyleSheet("QPlainTextEdit{background:transparent;}");
    textRcv.setFrameShape(QFrame::NoFrame);
    textRcv.setMaximumBlockCount(1000);

    textSent.setParent(this);
    textSent.setStyleSheet("QPlainTextEdit{background:transparent;}");
    textSent.setFrameShape(QFrame::NoFrame);
    textSent.setMaximumBlockCount(1000);

    lineEdit.setParent(this);

    open_serialport.setParent(this);
    open_serialport.setpix(midControl_Pix[2]);
    open_serialport.setpixDj(midControl_Pix[1]);
    open_serialport.set_QText("打开");
    open_serialport.set_QFont(AnNiuFont);
    open_serialport.set_QPlt(midControl);
    open_serialport.set_QPltDj(midControl);
    open_serialport.setAnNiuWH(45,24);

    send_data.setParent(this);
    send_data.setpix(midControl_Pix[0]);
    send_data.setpixDj(AnNiu_FbPix);
    send_data.set_QText("发送");
    send_data.set_QFont(AnNiuFont);
    send_data.set_QPlt(midControl);
    send_data.set_QPltDj(midControl_Plt);
    send_data.setAnNiuWH(45,24);

    Info_Edit.setParent(this);
    Info_Edit.setpix(midControl_Pix[0]);
    Info_Edit.setpixDj(AnNiu_FbPix);
    Info_Edit.set_QText("设置");
    Info_Edit.set_QFont(AnNiuFont);
    Info_Edit.set_QPlt(midControl);
    Info_Edit.set_QPltDj(midControl_Plt);
    Info_Edit.setAnNiuWH(45,24);

    Sent_OnOff.setParent(this);
    Sent_OnOff.setpix(midOnOffPix[1]);
    Sent_OnOff.setpixDj(midOnOffPix[0]);
    Sent_OnOff.set_QFont(AnNiuFont);
    Sent_OnOff.set_QPlt(midControl);
    Sent_OnOff.set_QPltDj(midControl);
    Sent_OnOff.setAnNiuWH(32,16);

    connect(&Sent_OnOff, &AnNiuZiSuo::AnNiuClicked,this,[=](){if(if_Sent==0){if_Sent=1;}else{if_Sent=0;}});
    comboBox.addItem("请选择串口");
    //获取所有可用端口列表
    QList<QSerialPortInfo> serialPortList=QSerialPortInfo::availablePorts();
    //如果没有可用串口，则在状态栏提示相应信息
    if(!serialPortList.isEmpty())//若有串口可用，isEmpty是指不可用所以不能少了！
    {
        //创建遍历迭代器，把串口遍历显示到下拉框中
        QList<QSerialPortInfo>::Iterator nextSerialPort=serialPortList.begin();
        while (nextSerialPort != serialPortList.end())
        {
            comboBox.addItem(nextSerialPort->portName());
            nextSerialPort++;
        }
    }
    midCom_Thread=new Com_Thread(this);
    midCom_Thread->start();
    connect(midCom_Thread,&Com_Thread::ReturnMingling,this,[=](QString midString){
        textRcv.moveCursor(QTextCursor::End);
        textRcv.insertPlainText(midString+"\r\n");
        textRcv.moveCursor(QTextCursor::End);

        char misSen_Data[192]="";
        ChuanKouServerThread(midString.toUtf8().data(),misSen_Data);
        QString misSenData="#";
        misSenData=misSenData+misSen_Data;
        misSenData=misSenData+"\r\n";
        if(misSenData.length()>0)//将返回值发送回去
        {
            midCom_Thread->Com_Sent(misSenData);
            textSent.moveCursor(QTextCursor::End);
            textSent.insertPlainText(misSenData);
            textSent.moveCursor(QTextCursor::End);
        }
    });

    //绑定信号和槽
    connect(&send_data,&AnniuDiandong::AnNiuClicked,this,[=](){
        //获取需要发送的文本
        QString senData=lineEdit.text().trimmed();
        //使用串口发送字节数组
        midCom_Thread->Com_Sent(senData);
        textSent.appendPlainText(senData);//把数据依次显示到文本控件上面去
    });
    connect(&open_serialport,&AnNiuZiSuo::AnNiuClicked,this,[=](){
        if(midCom_Thread->Com_isOpen())
        {
            SentLuaError=2;//这个需要写在前面
            midCom_Thread->Com_Clear();
            Lua_CloseSent();

            comboBox.setEnabled(true);
            open_serialport.set_QText("打开");
            open_serialport.setUpDown(0);
        }
        else
        {
            if(comboBox.currentText()!="请选择串口")
            {
                Lua_StartSent(SentCode->text(),SentLuaError);
                if(SentLuaError<=0)
                {
                    midCom_Thread->Com_Start(comboBox.currentText());
                    if(midCom_Thread->Com_isOpen())
                    {
                        comboBox.setEnabled(false);
                        open_serialport.set_QText("关闭");
                        open_serialport.setUpDown(1);
                    }
                    else
                    {
                        open_serialport.setUpDown(0);
                    }
                }
                else
                {
                    open_serialport.setUpDown(0);
                    textSent.appendPlainText("--LUA ERROR--");
                    textSent.appendPlainText(RunLuaSentRtn);
                    Lua_CloseSent();
                }
            }
            else
            {
                open_serialport.setUpDown(0);
            }
        }
    });
    ComClose.setParent(this);
    ComClose.setpix(midClose_Pix[0]);
    ComClose.setpixXf(midClose_Pix[1]);
    ComClose.setpixDj(midClose_Pix[2]);
    ComClose.set_QFont(AnNiuFont);
    ComClose.setAnNiuWH(25,20);
    connect(&ComClose, &AnniuDiandong::AnNiuClicked, this, [=](){emit CloseView();});
    //
    m_timer = new QTimer(this);m_timer->setSingleShot(false);
    connect(m_timer, &QTimer::timeout, this, [=](){
        SetSent();
    });
    m_timer->start(10);
    //
    m_timer2 = new QTimer(this);
    m_timer2->setSingleShot(false);
    connect(m_timer2, &QTimer::timeout, this, [=](){
        QString midData_Rcv="";
        midCom_Thread->Com_String(midData_Rcv);
        if(midData_Rcv.length()>0)
        {
            textRcv.moveCursor(QTextCursor::End);
            textRcv.insertPlainText(midData_Rcv);
            textRcv.moveCursor(QTextCursor::End);
        }
    });
    m_timer2->start(30);
}
void ComLink::PjtNameSet(QString midPjtName)
{
    PjtName=midPjtName;
}
QString ComLink::GetComName()
{
    if(comboBox.currentText()!="请选择串口")
    {
        return comboBox.currentText();
    }
    return "";
}
QString ComLink::GetLuaString()
{
    return SentCode->text();
}
bool ComLink::GetIfSent()
{
    return if_Sent;
}
void ComLink::SetComName(QString midComName)
{
    if(midComName.length()>0)
    {
        for(int zi=0;zi<comboBox.count();zi++)
        {
            if(midComName==comboBox.itemText(zi))
            {
                comboBox.setCurrentIndex(zi);
            }
        }
    }
}
void ComLink::SetLuaString(QString midLuaString)
{
    SentCode->setText(midLuaString);
}
void ComLink::SetIfSent(bool midIfSent)
{
    if_Sent=midIfSent;
    if(if_Sent)
    {
        Sent_OnOff.setUpDown(1);
    }
    else
    {
        Sent_OnOff.setUpDown(0);
    }
}

void ComLink::Lua_StartSent(QString LuaString, int& miderror)
{
    QString SentLuaRtn = XieYiLuaAnalysis(PjtName.toUtf8().data(), LuaString.toUtf8().data());//进行变量名解析
    QString midOutChar = "";
    if(SentLuaRtn.length()>=8)//将解析lua的消息分开，前面是提示消息，后面是可执行文件，中间用##Line##隔开
    {
        for(int zi=0;zi<SentLuaRtn.length();zi++)
        {
            if(SentLuaRtn[zi]=='#'&&
                SentLuaRtn[zi+1]=='#'&&
                SentLuaRtn[zi+2]=='L'&&
                SentLuaRtn[zi+3]=='i'&&
                SentLuaRtn[zi+4]=='n'&&
                SentLuaRtn[zi+5]=='e'&&
                SentLuaRtn[zi+6]=='#'&&
                SentLuaRtn[zi+7]=='#'
                )
            {
                midOutChar=SentLuaRtn.left(zi);
                SentLuaRtn=SentLuaRtn.right(SentLuaRtn.length()-zi-8);
                break;
            }
        }
    }
    else
    {
        SentLuaRtn="";
    }
    textSent.setPlainText(midOutChar);
    LSent = luaL_newstate();
    luaL_openlibs(LSent);//开启此计算池
    luaL_loadstring(LSent, SentLuaRtn.toUtf8().data());//加载lua文件
    lua_pushvalue(LSent, -1);//压入栈
    miderror = lua_pcall(LSent, 0, LUA_MULTRET, 0);//执行0没有参数，LUA_MULTRET标识任意数量的结果
    if (miderror)
    {
        RunLuaSentRtn = lua_tostring(LSent, -1);// 获取错误信息
        lua_pop(LSent, 1);  // 弹出错误信息
    }
    else
    {
        RunLuaSentRtn = lua_tostring(LSent, -1);// 获取错误信息
        lua_pop(LSent, 1);  // 弹出错误信息
    }
}
void ComLink::Lua_RunSent(int& miderror)
{
    lua_pushvalue(LSent, -1);//压入栈
    miderror = lua_pcall(LSent, 0, LUA_MULTRET, 0);//执行
    if (miderror)
    {
        RunLuaSentRtn = lua_tostring(LSent, -1);// 获取错误信息
        lua_pop(LSent, 1);  // 弹出错误信息
    }
    else
    {
        RunLuaSentRtn = lua_tostring(LSent, -1);// 获取错误信息
        lua_pop(LSent, 1);  // 弹出错误信息
    }
}
void ComLink::Lua_CloseSent()
{
    if(LSent!= nullptr)
    {
        lua_close(LSent);//关闭
    }
}
void ComLink::SetSent()
{
    if(SentLuaError==0&&if_Sent==1)
    {
        //不能和上面的合并在一起，因为这里是外部计时器激发，会出现还没有初始化就来了的情况，所以必须
        if(midCom_Thread->Com_isOpen()==1)
        {
            Lua_RunSent(SentLuaError);
            if(SentLuaError==0)
            {
                if(RunLuaSentRtn.length()>0)//长度大于零时才发送
                {
                    midCom_Thread->Com_Sent(RunLuaSentRtn.toUtf8().data());
                }
            }
            textSent.appendPlainText(RunLuaSentRtn);//把数据依次显示到文本控件上面去
        }
    }
}
bool ComLink::event(QEvent *ev)
{
    if(ev->type() == QEvent::Resize)
    {
        QResizeEvent *re = static_cast<QResizeEvent*> (ev);
        int geometry_w=re->size().width();
        int geometry_h=re->size().height();

        comboBox.setGeometry(10,10,90,24);
        open_serialport.setGeometry(110,10,45,24);
        lineEdit.setGeometry(165+45,10,(geometry_w)/2-165-65-45,24);
        send_data.setGeometry((geometry_w)/2-55,10,45,24);
        Info_Edit.setGeometry(110+45,10,45,24);

        TxtBiaoTi.SetBianW(5);
        TxtBiaoTi.SetWH((geometry_w)/2-10,24);
        TxtBiaoTi.setGeometry(5,44,(geometry_w)/2-10,24);

        textRcv.setGeometry(0,70,(geometry_w)/4-1,geometry_h-80);
        TextGl.setGeometry((geometry_w)/4-1,70,1,geometry_h-80);
        textSent.setGeometry((geometry_w)/4,70,(geometry_w)/4,geometry_h-80);
        PageButton.setGeometry((geometry_w)/2,    10,60,24);
        Sent_OnOff.setGeometry((geometry_w)/2+60+4,14,32,16);
        LUA_TiShi.setGeometry((geometry_w)/2+100,10,(geometry_w)/2-100-44,24);
        DingXian.setGeometry((geometry_w)/2,34,(geometry_w)/2-5,1);
        DingXian1.setGeometry((geometry_w)/2,34,1,geometry_h-44);
        SentCode->setGeometry((geometry_w)/2,34,(geometry_w)/2-5,geometry_h-44);
        ComClose.setGeometry(geometry_w-24-10,4,25,20);
    }
    return QWidget::event(ev);
}
void ComLink::closeEvent(QCloseEvent *)
{
    if(midCom_Thread->Com_isOpen())//若原本正在打开
    {
        SentLuaError=2;//这个需要写在前面
        midCom_Thread->Com_Clear();
        Lua_CloseSent();
    }
    midCom_Thread->quit();
    comboBox.setEnabled(true);
}
void Com_Thread::Com_String(QString &midRcv)
{
    while(1)
    {
        if(if_Data_Read==0)
        {
            if_Cache_Read=1;
            midRcv=midRcvAll;
            midRcvAll.clear();
            if_Cache_Read=0;
            break;
        }
    }
}
void Com_Thread::Com_Sent(QString midDate)
{
    serialPort.write(midDate.toUtf8().data());
    serialPort.waitForBytesWritten(2);
}
void Com_Thread::receiveData()
{
    serialPort.waitForReadyRead(2);
    QByteArray serialData(serialPort.readAll());
    serialPort.clear();
    QString midserialData=serialData.data();
    midData=midData+midserialData;
    int WhileNb=10;
    while(WhileNb)
    {
        if(if_CacheStart==0)//若还未开始记录
        {
            int StartPosNb=midData.indexOf("#");
            if(StartPosNb>=0)//开始标识符#
            {
                midData=midData.remove(0,StartPosNb+1);
                if_CacheStart=1;//开始读取
            }
            else
            {
                if(if_Cache_Read==0)
                {
                    if_Data_Read=1;
                    midRcvAll=midRcvAll+midRcvBackUp;
                    midRcvBackUp="";
                    midRcvAll=midRcvAll+midData;
                    if_Data_Read=0;
                }
                else
                {
                    midRcvBackUp=midRcvBackUp+midData;
                }
                midData.clear();
                break;
            }
        }
        else//若之前的解析还未结束
        {
            int EndPosNb=midData.indexOf("\n");//识别为结束符
            if(EndPosNb>=0)
            {
                midCache.clear();
                midCache=midData.left(EndPosNb);
                midCache.remove('\r');
                midData.remove(0,EndPosNb+1);
                emit ReturnMingling(midCache);
                if_CacheStart=0;
            }
            else
            {
                EndPosNb=midData.indexOf("#");
                if(EndPosNb>=0)
                {
                    if(if_Cache_Read==0)
                    {
                        if_Data_Read=1;
                        midRcvAll=midRcvAll+midRcvBackUp;
                        midRcvBackUp="";
                        midRcvAll=midRcvAll+midData.left(EndPosNb);
                        if_Data_Read=0;
                    }
                    else
                    {
                        midRcvBackUp=midRcvBackUp+midData.left(EndPosNb);
                    }
                    midData.remove(0,EndPosNb);//这里是要保留#的
                    if_CacheStart=0;
                }
                else
                {
                    break;
                }
            }
        }
        if(midData.length()==0)//不可删除
        {
            break;
        }
        WhileNb=WhileNb-1;
    }
    if_Cache_Read=0;
}
void Com_Thread::Com_Start(QString ComName)
{
    if(!serialPort.isOpen())
    {
        //设置参数
        serialPort.setBaudRate(QSerialPort::Baud115200);
        serialPort.setReadBufferSize(256);
        serialPort.setDataBits(QSerialPort::Data8);
        serialPort.setParity(QSerialPort::NoParity);
        serialPort.setStopBits(QSerialPort::OneStop);
        serialPort.setFlowControl(QSerialPort::NoFlowControl);
        serialPort.setPortName(ComName);
        if(serialPort.open(QIODevice::ReadWrite))
        {
            serialPort.clear();
            isOpen=1;
        }
    }
}
void Com_Thread::Com_Clear()
{
    if(serialPort.isOpen())
    {
        serialPort.clear();
        serialPort.close();
        isOpen=0;
    }
}
bool Com_Thread::Com_isOpen()
{
    return isOpen;
}

void ComLink::CodeEditStart(QsciScintilla *midCode,QsciAPIs *midapis)
{    //字体设置
    QFont font0("Arial",36,QFont::Normal);
    QFont font1("Arial",8,QFont::Normal);
    //字体设置
    midCode->setFont(font0);
    //行号区域设置
    midCode->setMarginType(0,QsciScintilla::NumberMargin);//设置编号为0的页边显示行号。
    midCode->setMarginLineNumbers(0,true);//对该页边启用行号
    midCode->setMarginWidth(0,32);//设置页边宽度
    midCode->setMarginsBackgroundColor(QColor(223,223,223));
    midCode->setMarginsFont(font1);
    //自动折叠区域
    midCode->setMarginType(1, QsciScintilla::SymbolMargin);
    midCode->setMarginLineNumbers(1, false);
    midCode->setMarginWidth(1, 16);
    midCode->setMarginSensitivity(1, true);
    midCode->setMarkerBackgroundColor(QColor(234,245,147), 1);
    // 折叠式
    midCode->setFolding(QsciScintilla::BoxedTreeFoldStyle,1);
    // 折叠颜色
    midCode->resetFoldMarginColors();//先设置一下，启动“重新设置颜色”，没有这一句，后面的不行
    midCode->setFoldMarginColors(QColor(239,239,239),QColor(239,239,239));
    //括号匹配
    midCode->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    //开启自动缩进
    midCode->setAutoIndent(true);
    midCode->setIndentationGuides((bool)QsciScintilla::SC_IV_LOOKBOTH);//设置缩进的显示方式
    // 设置自动补齐
    midCode->setCaretLineVisible(true);
    midCode->setCaretLineBackgroundColor(QColor(239,239,239));// 设置光标所在行的背景色

    midapis->add(QString("import"));
    midapis->prepare();

    midCode->setAutoCompletionSource(QsciScintilla::AcsAll);   //设置源，自动补全所有地方出现的
    midCode->setAutoCompletionCaseSensitivity(true);   //设置自动补全大小写敏感
    midCode->setAutoCompletionThreshold(1);    //设置每输入一个字符就会出现自动补全的提示
    midCode->SendScintilla(QsciScintilla::SCI_SETCODEPAGE,QsciScintilla::SC_CP_UTF8);//设置编码为UTF-8
}
bool ComLink::eventFilter(QObject *watched, QEvent *event) {
    if (watched == SentCode) {
        if (event->type() == QEvent::KeyPress)
        {	// 键盘按下
            QKeyEvent *key = static_cast<QKeyEvent *>(event);
            if (key->key() == Qt::Key_Control)
            {
                Keyctrl=1;
            }
            if(key->key() == Qt::Key_S)
            {
                if(Keyctrl==1)
                {
                    emit SaveComLUA();
                }
            }
        }
        if (event->type() == QEvent::KeyRelease) {	// 键盘释放
            QKeyEvent *key = static_cast<QKeyEvent *>(event);
            if (key->key() == Qt::Key_Control)
            {
                Keyctrl=0;
            }
        }
    }
    // 事件交给上层对话框进行处理
    return QObject::eventFilter(watched, event);
}

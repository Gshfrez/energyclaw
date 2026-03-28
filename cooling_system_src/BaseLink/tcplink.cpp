#include "tcplink.h"

TcpLink::TcpLink(QWidget *parent)
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
    PageButton.set_QText("接收处理");
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
    PortEdit.setParent(this);
    PortEdit.setText("请填写端口");

    StartTag.setParent(this);
    StartTag.setFont(AnNiuFont);
    StartTag.setText("起始符:       开启反馈:");

    StartStringEdit.setParent(this);
    StartStringEdit.setText(StartString);

    textRcv.setParent(this);
    textRcv.setStyleSheet("QPlainTextEdit{background:transparent;}");
    textRcv.setFrameShape(QFrame::NoFrame);
    textRcv.setMaximumBlockCount(1000);

    textSent.setParent(this);
    textSent.setStyleSheet("QPlainTextEdit{background:transparent;}");
    textSent.setFrameShape(QFrame::NoFrame);
    textSent.setMaximumBlockCount(1000);

    open_serialport.setParent(this);
    open_serialport.setpix(midControl_Pix[2]);
    open_serialport.setpixDj(midControl_Pix[1]);
    open_serialport.set_QText("打开");
    open_serialport.set_QFont(AnNiuFont);
    open_serialport.set_QPlt(midControl);
    open_serialport.set_QPltDj(midControl);
    open_serialport.setAnNiuWH(45,24);

    Sent_OnOff.setParent(this);
    Sent_OnOff.setpix(midOnOffPix[1]);
    Sent_OnOff.setpixDj(midOnOffPix[0]);
    Sent_OnOff.set_QFont(AnNiuFont);
    Sent_OnOff.set_QPlt(midControl);
    Sent_OnOff.set_QPltDj(midControl);
    Sent_OnOff.setAnNiuWH(32,16);

    connect(&Sent_OnOff, &AnNiuZiSuo::AnNiuClicked,this,[=](){if(if_Sent==0){if_Sent=1;}else{if_Sent=0;}});

    connect(&Tcp_Server, &QTcpServer::newConnection, this, [=](){newConnection_slot();});
    this->thread()->wait();
    connect(&open_serialport,&AnNiuZiSuo::AnNiuClicked,this,[=](){
        if(Tcp_Server.isListening())//若已经打开了
        {
            SentLuaError=2;//这个需要写在前面
            Tcp_Clear();
            Lua_CloseSent();

            PortEdit.setEnabled(true);
            StartStringEdit.setEnabled(true);
            open_serialport.set_QText("监听");
            open_serialport.setUpDown(0);
        }
        else
        {
            if(PortEdit.text()!="请填写端口"&&StartStringEdit.text().length()>0)
            {
                StartString = StartStringEdit.text().left(1);
                Lua_StartSent(SentCode->text(),SentLuaError);
                if(SentLuaError<=0)//若没有错误
                {
                    Tcp_Start(PortEdit.text());
                    if(Tcp_Server.isListening())
                    {
                        PortEdit.setEnabled(false);
                        StartStringEdit.setEnabled(false);
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
                textSent.appendPlainText("打开失败：未填写端口、起始符");
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
}
void TcpLink::PjtNameSet(QString midPjtName)
{
    PjtName=midPjtName;
}
QString TcpLink::GetPort()
{
    if(PortEdit.text()!="请填写端口")
    {
        return PortEdit.text();
    }
    return "";
}
QString TcpLink::GetLuaString()
{
    return SentCode->text();
}
bool TcpLink::GetIfSent()
{
    return if_Sent;
}
void TcpLink::SetPort(QString midPortName)
{
    PortEdit.setText(midPortName);
}
void TcpLink::SetLuaString(QString midLuaString)
{
    SentCode->setText(midLuaString);
}
void TcpLink::SetIfSent(bool midIfSent)
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

void TcpLink::Lua_StartSent(QString LuaString, int& miderror)
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
void TcpLink::Lua_RunSent(int& miderror)
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
void TcpLink::Lua_CloseSent()
{
    if(LSent!= nullptr)
    {
        lua_close(LSent);//关闭
    }
}
bool TcpLink::event(QEvent *ev)
{
    if(ev->type() == QEvent::Resize)
    {
        QResizeEvent *re = static_cast<QResizeEvent*> (ev);
        int geometry_w=re->size().width();
        int geometry_h=re->size().height();

        PortEdit.setGeometry(10,10,90,24);
        open_serialport.setGeometry(110,10,45,24);
        StartTag.setGeometry(165,10,180,24);
        StartStringEdit.setGeometry(205,10,40,24);
        Sent_OnOff.setGeometry(305,14,32,16);

        TxtBiaoTi.SetBianW(5);
        TxtBiaoTi.SetWH((geometry_w)/2-10,24);
        TxtBiaoTi.setGeometry(5,44,(geometry_w)/2-10,24);
        textRcv.setGeometry(0,70,(geometry_w)/4-1,geometry_h-80);
        TextGl.setGeometry((geometry_w)/4-1,70,1,geometry_h-80);
        textSent.setGeometry((geometry_w)/4,70,(geometry_w)/4,geometry_h-80);
        PageButton.setGeometry((geometry_w)/2,    10,60,24);

        LUA_TiShi.setGeometry((geometry_w)/2+100,10,(geometry_w)/2-100-44,24);
        DingXian.setGeometry((geometry_w)/2,34,(geometry_w)/2-5,1);
        DingXian1.setGeometry((geometry_w)/2,34,1,geometry_h-44);
        SentCode->setGeometry((geometry_w)/2,34,(geometry_w)/2-5,geometry_h-44);
        ComClose.setGeometry(geometry_w-24-10,4,25,20);
    }
    return QWidget::event(ev);
}
void TcpLink::closeEvent(QCloseEvent *)
{
    if(Tcp_Server.isListening())//若原本正在打开
    {
        SentLuaError=2;//这个需要写在前面
        Tcp_Clear();
        Lua_CloseSent();
    }
    PortEdit.setEnabled(true);
    StartStringEdit.setEnabled(true);
}
void TcpLink::Tcp_Start(QString ComName)
{
    if(!Tcp_Server.isListening())
    {
        midData.clear();
        midCache.clear();
        //转化为端口号
        quint16 port = ComName.toUInt();
        //将服务器设置为被动监听状态
        Tcp_Server.listen(QHostAddress::Any,port);
        //执行到这表明服务器启动成功，并对客户端连接进行监听，如果有客户端向服务器发来连接请求，那么该服务器就会自动发射一个newConnection信号
        if(!Tcp_Server.isListening())
        {
            textRcv.appendPlainText("端口可能被占用");
        }
    }
}
void TcpLink::newConnection_slot()
{
    //获取最新连接的客户端套接字
    QTcpSocket *s = Tcp_Server.nextPendingConnection();
    //将获取的套接字存放到客户端容器中
    clientList.push_back(s);
    midData.push_back("");
    midCache.push_back("");
    //此时，客户端就和服务器建立起来联系了
    connect(s, &QTcpSocket::readyRead, this, &TcpLink::readyRead_slot);
}
//关于readyRead信号对应槽函数的实现
void TcpLink::readyRead_slot()
{
    //删除客户端链表中的无效客户端套接字
    for(int i=0; i<clientList.count(); i++)//必须放在这里，不要另开线程、time去管理涉及到QVector的管理，一定要在一个线程内。
    {
        //返回值：客户端状态，如果是0，表示无连接
        if(clientList[i]->state() == 0)
        {
            disconnect(clientList[i], &QTcpSocket::readyRead, 0, 0);
            clientList.removeAt(i);//将下标为i的客户端移除
            midData.removeAt(i);
        }
    }
    for(int clientNb=0; clientNb<clientList.count(); clientNb++)
    {
        //返回值：当前客户端待读的字节数，如果该数据0，表示无待读数据
        if(clientList[clientNb]->bytesAvailable() > 0)
        {
            QByteArray serialData(clientList[clientNb]->readAll());
            QString midserialData=serialData.data();
            textRcv.moveCursor(QTextCursor::End);
            textRcv.insertPlainText(midserialData);
            textRcv.moveCursor(QTextCursor::End);
            midData[clientNb]=midData[clientNb]+midserialData;
            int WhileNb=10;
            while(WhileNb)
            {
                if(if_CacheStart==0)//若还未开始记录
                {
                    int StartPosNb=midData[clientNb].indexOf(StartString);//"#"
                    if(StartPosNb>=0)
                    {
                        midData[clientNb].remove(0,StartPosNb+1);
                        if_CacheStart=1;//开始读取
                    }
                    else
                    {
                        midData[clientNb]="";
                        break;
                    }
                }
                else//若之前的解析还未结束
                {
                    int EndPosNb=midData[clientNb].indexOf('\n');
                    if(EndPosNb>=0)
                    {
                        midCache=midData[clientNb].left(EndPosNb);
                        midCache.remove('\r');
                        midData[clientNb].remove(0,EndPosNb+1);

                        char misSen_Data[192]="";
                        ChuanKouServerThread(midCache.toUtf8().data(),misSen_Data);
                        QString misSenData=StartString;
                        misSenData=misSenData+misSen_Data;
                        misSenData=misSenData+"\r\n";
                        if(misSenData.length()>0)//将返回值发送回去
                        {
                            if(if_Sent)
                            {
                                clientList[clientNb]->write(misSenData.toUtf8().data());
                                clientList[clientNb]->flush();
                                clientList[clientNb]->waitForReadyRead(2);
                            }
                            textSent.moveCursor(QTextCursor::End);
                            textSent.insertPlainText(misSenData);
                            textSent.moveCursor(QTextCursor::End);
                        }
                        if_CacheStart=0;
                    }
                    else
                    {
                        EndPosNb=midData[clientNb].indexOf(StartString);
                        if(EndPosNb>=0)
                        {
                            midData[clientNb].remove(0,EndPosNb);
                            if_CacheStart=0;//一定要等于0，等于是结束了这个无意义的筛选。下一个循环去冲头筛选。
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                if(midData[clientNb].length()==0)//不可删除
                {
                    break;
                }
                WhileNb=WhileNb-1;
            }
        }
    }
}
void TcpLink::Tcp_Clear()
{
    if(Tcp_Server.isListening())
    {
        for(int i=0; i<clientList.count(); i++)
        {
            clientList[i]->close();     //将下标为i的客户端移除
        }
        clientList.clear();
        midData.clear();
        Tcp_Server.close();
    }
}
void TcpLink::CodeEditStart(QsciScintilla *midCode,QsciAPIs *midapis)
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
bool TcpLink::eventFilter(QObject *watched, QEvent *event) {
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
                    emit SaveTcpLUA();
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

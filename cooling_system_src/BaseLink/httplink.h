#ifndef HTTPLINK_H
#define HTTPLINK_H

#include <QWidget>
#include <QTimer>
#include <QThread>
#include <QPlainTextEdit>
#include <QTcpSocket>
#include <QTcpServer>
#include <QLineEdit>
#include <QLabel>
#include <AnniuDiandong.h>
#include <AnNiuZiSuo.h>
#include <BaseKuang.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <BaseCore.h>
#include <BaseServer.h>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerlua.h>
#include <Qsci/qsciapis.h>
QT_END_NAMESPACE
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
class Http_Thread;
class HttpLink : public QWidget
{
    Q_OBJECT
public:
    explicit HttpLink(QWidget *parent = nullptr);

    void PjtNameSet(QString midPjtName);
    void SetSent();

    QString GetPort();
    QString GetLuaString();
    bool    GetIfSent();

    void SetPort(QString midComName);
    void SetLuaString(QString midLuaString);
    void SetIfSent(bool midIfSent);
private slots:
    void CodeEditStart(QsciScintilla *midCode,QsciAPIs *midapis);
    bool eventFilter(QObject *watched, QEvent *event);
    void Lua_StartSent(QString LuaString, int& miderror);
    void Lua_RunSent(int& miderror);
    void Lua_CloseSent();
    void TcpLuaRun();
    void closeEvent(QCloseEvent *event);
    bool event(QEvent *ev);
signals:
    void CloseView();
    void SaveTcpLUA();
private:
    QTimer* m_timer;
    BaseKuang TxtBiaoTi;

    QLabel *TextGl;
    QPlainTextEdit*textRcv;
    QPlainTextEdit*textSent;

    QLineEdit *PortEdit;
    AnNiuZiSuo open_serialport;
    AnNiuZiSuo *PageButton;
    QLineEdit LUA_TiShi;
    AnNiuZiSuo Sent_OnOff;
    QLabel DingXian;
    QLabel DingXian1;
    Http_Thread*midHttp_Thread;
    QFont AnNiuFont;
    AnniuDiandong ComClose;
    QPalette midPlt;
    QPalette midPlt_H;
    QString PjtName="";

    QsciScintilla *SentCode;
    QsciLexerLua *textLexerSent;
    QsciAPIs *apisSent;

    bool Keyctrl=0;
    bool if_Sent=0;
    int SentLuaError=1;
    QString RunLuaSentRtn;
    lua_State* LSent=nullptr;
};
class Http_Thread : public QThread
{
    Q_OBJECT
public:
    Http_Thread(QWidget *parent = nullptr) {
        Q_UNUSED(parent);
    }
    void Http_Start(QString PortName);
    void Http_Sent(QString midData,int clientNb);
    void Http_Clear();
    bool Http_isOpen();
    void Http_String(QString &midRcv,QString &midSent);
    void receiveData(QByteArray mid_Data,int clientNb);
    void newConnection_slot();
    void readyRead_slot();
    void run() override {
        connect(&Tcp_Server, &QTcpServer::newConnection, this, [=](){newConnection_slot();});
        this->thread()->wait();
    }
private:
    bool if_AT=0;
    bool isOpen=0;
    bool if_Cache_Read=0;
    bool if_CacheStart=0;
    QString midError;
    QList<QString> midData;
    QList<QString> midCache;
    QList<QString> midRcvAll;
    QList<QString> midSentAll;
    //定义服务器指针
    QTcpServer Tcp_Server;
    //定义客户端指针链表容器
    QList<QTcpSocket *> clientList;
};
#endif // HTTPLINK_H

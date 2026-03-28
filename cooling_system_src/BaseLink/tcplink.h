#ifndef TCPLINK_H
#define TCPLINK_H

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
class TcpLink : public QWidget
{
    Q_OBJECT
public:
    explicit TcpLink(QWidget *parent = nullptr);

    void PjtNameSet(QString midPjtName);

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
    void closeEvent(QCloseEvent *event);
    bool event(QEvent *ev);

    void Tcp_Start(QString PortName);
    void Tcp_Clear();
    void newConnection_slot();
    void readyRead_slot();
signals:
    void CloseView();
    void SaveTcpLUA();
private:
    BaseKuang TxtBiaoTi;

    QLabel TextGl;
    QPlainTextEdit textRcv;
    QPlainTextEdit textSent;

    QLineEdit  PortEdit;
    QLineEdit  StartStringEdit;
    QString StartString="#";
    QLabel StartTag;

    AnNiuZiSuo open_serialport;
    AnNiuZiSuo PageButton;
    QLineEdit LUA_TiShi;
    AnNiuZiSuo Sent_OnOff;
    QLabel DingXian;
    QLabel DingXian1;
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

    bool if_CacheStart=0;
    QList<QString> midData;
    QString midCache;
    //定义服务器
    QTcpServer Tcp_Server;
    //定义客户端指针链表容器
    QList<QTcpSocket *> clientList;
};
#endif // COMLINK_H

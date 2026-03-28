#ifndef COMLINK_H
#define COMLINK_H

#include <QWidget>
#include <QTimer>
#include <QThread>
#include <QPlainTextEdit>
#include <QSerialPort>
#include <QComboBox>
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
class Com_Thread;
class ComLink : public QWidget
{
    Q_OBJECT
public:
    explicit ComLink(QWidget *parent = nullptr);
    void PjtNameSet(QString midPjtName);

    QString GetComName();
    QString GetLuaString();
    bool    GetIfSent();

    void SetComName(QString midComName);
    void SetLuaString(QString midLuaString);
    void SetIfSent(bool midIfSent);
private slots:
    void CodeEditStart(QsciScintilla *midCode,QsciAPIs *midapis);
    bool eventFilter(QObject *watched, QEvent *event);
    void Lua_StartSent(QString LuaString, int& miderror);
    void Lua_RunSent(int& miderror);
    void Lua_CloseSent();
    void SetSent();

    void closeEvent(QCloseEvent *event);
    bool event(QEvent *ev);
signals:
    void CloseView();
    void SaveComLUA();
private:
    QTimer* m_timer;
    QTimer* m_timer2;
    BaseKuang TxtBiaoTi;

    QLabel TextGl;
    QPlainTextEdit textRcv;
    QPlainTextEdit textSent;

    QComboBox  comboBox;
    QLineEdit  lineEdit;
    AnniuDiandong Info_Edit;
    AnniuDiandong send_data;
    AnNiuZiSuo open_serialport;
    AnNiuZiSuo PageButton;
    QLineEdit LUA_TiShi;
    AnNiuZiSuo Sent_OnOff;
    QLabel DingXian;
    QLabel DingXian1;
    Com_Thread*midCom_Thread;
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
class Com_Thread : public QThread
{
    Q_OBJECT
public:
    Com_Thread(QWidget *parent = nullptr) {
        Q_UNUSED(parent);
    }
    void Com_Start(QString ComName);
    void Com_Sent(QString midData);
    void Com_Clear();
    bool Com_isOpen();
    void Com_String(QString &midRcv);
    void receiveData();
    void run() override {
        connect(&serialPort,&QSerialPort::readyRead,this,[=](){
            receiveData();
        });
        this->thread()->wait();
    }
signals:
    void ReturnMingling(QString);
private:
    bool isOpen=0;
    bool if_Cache_Read=0;
    bool if_Data_Read=0;
    bool if_CacheStart=0;
    QSerialPort serialPort;
    QString midData="";
    QString midCache="";
    QString midRcvAll="";
    QString midRcvBackUp="";
};
#endif // COMLINK_H

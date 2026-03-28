#ifndef COMASCII_H
#define COMASCII_H

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
class ChuankouThread2;
class ComASCII : public QWidget
{
    Q_OBJECT
public:
    explicit ComASCII(QWidget *parent = nullptr);

    void PjtNameSet(QString midPjtName);
    void SetSent();

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

    void closeEvent(QCloseEvent *event);
    bool event(QEvent *ev);
signals:
    void CloseView();
    void SaveComLUA();
private:
    QTimer* m_timer;
    BaseKuang TxtBiaoTi;

    QLabel *TextGl;
    QPlainTextEdit*textRcv;
    QPlainTextEdit*textSent;

    QComboBox *comboBox;
    QLineEdit *lineEdit;
    AnniuDiandong send_data;
    AnNiuZiSuo open_serialport;
    AnNiuZiSuo *PageButton;
    QLineEdit LUA_TiShi;
    AnNiuZiSuo Sent_OnOff;
    QLabel DingXian;
    QLabel DingXian1;
    ChuankouThread2*midChuankouThread;
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
class ChuankouThread2 : public QThread
{
    Q_OBJECT
public:
    ChuankouThread2(QWidget *parent = nullptr) {
        Q_UNUSED(parent);
    }
    void ChuankouStart(QString ComName);
    void ChuankouSent(QString midData);
    void ChuankouClear();
    bool Get_isOpen();
    void Get_String(QString &midRcv,QString &midSent);
    void receiveData();
    void run() override {
        serialPort.setBaudRate(QSerialPort::Baud115200);
        serialPort.setReadBufferSize(256);
        serialPort.setDataBits(QSerialPort::Data8);
        serialPort.setParity(QSerialPort::NoParity);
        serialPort.setStopBits(QSerialPort::OneStop);
        serialPort.setFlowControl(QSerialPort::NoFlowControl);
        connect(&serialPort,&QSerialPort::readyRead,this,[=](){
            receiveData();
        });
        this->thread()->wait();
    }
private:
    bool if_AT=0;
    bool isOpen=0;
    bool if_Cache_Read=0;
    bool if_CacheStart=0;
    QSerialPort serialPort;
    QString midData="";
    QString midCache="";
    QString midRcvAll="";
    QString midSentAll="";
};
#endif // COMASCII_H

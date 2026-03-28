#include "basecache.h"
static BasePixCache BaseKuangPix;
QPalette UpTextPalette;

void BaseKuangPixSet(QString midPjtName,ComSave midComSaveInfo[])
{
    //if(midPjtName.length()>0)
    //{
        QJsonArray midType;
        QJsonArray midComName;
        QJsonArray midLuaString;
        QJsonArray midIf_Sent;

        for(int zi=0;zi<24;zi++)
        {
            if(midComSaveInfo[zi].ComName.length()>0||
                midComSaveInfo[zi].Lua.length()>0||
                midComSaveInfo[zi].If_Sent==1||
                midComSaveInfo[zi].Type>0)
            {
                midComName.append(midComSaveInfo[zi].ComName);
                midLuaString.append(midComSaveInfo[zi].Lua);
                midIf_Sent.append(midComSaveInfo[zi].If_Sent);
                midType.append(midComSaveInfo[zi].Type);
            }
        }

        QJsonObject json;
        json.insert("ComName", midComName);
        json.insert("LuaString", midLuaString);
        json.insert("If_Sent", midIf_Sent);
        json.insert("Type", midType);

        // 构建JSON文档
        QJsonDocument document;
        document.setObject(json);
        QByteArray byteArray = document.toJson(QJsonDocument::Compact);//Compact
        QString strJson(byteArray);
        QString midpath=QT_FldAddress();
        midpath=midpath+"AlgProject\\"+midPjtName+"\\ComTcpInfo.json";
        QFile fw(midpath);
        if(fw.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream txtOutput(&fw);
            txtOutput << strJson;
        }
        fw.close();
    //}
}
void BaseKuangPixGet(QString midPjtName,ComSave midComSaveInfo[],int &midSize)
{
    //if(midPjtName.length()>0)
    //{
        QString midpath=QT_FldAddress();
        midpath=midpath+"AlgProject\\"+midPjtName+"\\ComTcpInfo.json";

        QString midJson="";
        QFile fw(midpath);
        if(fw.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream txtInput(&fw);
            while(!txtInput.atEnd())
            {
                midJson=txtInput.readLine();
            }
        }
        fw.close();
        //解析json
        if(midJson.length()>0)
        {
            QByteArray byteArray=midJson.toLocal8Bit();QJsonParseError jsonerror;
            QJsonDocument document = QJsonDocument::fromJson(byteArray, &jsonerror);
            if (!document.isNull() && (jsonerror.error == QJsonParseError::NoError))
            {
                if (document.isObject())
                {
                    if (document.object().contains("ComName"))
                    {
                        if (document.object().value("ComName").isArray())
                        {
                            QJsonArray midComName=document.object().value("ComName").toArray();
                            midSize=midComName.size();if(midSize>24){midSize=24;}
                            for(int zi=0;zi<midSize;zi++)
                            {
                                midComSaveInfo[zi].ComName=midComName[zi].toString();
                            }
                        }
                    }
                    if (document.object().contains("LuaString"))
                    {
                        if (document.object().value("LuaString").isArray())
                        {
                            QJsonArray midLuaString = document.object().value("LuaString").toArray();
                            for(int zi=0;zi<midLuaString.size();zi++)
                            {
                                midComSaveInfo[zi].Lua=midLuaString[zi].toString();
                            }
                        }
                    }
                    if (document.object().contains("If_Sent"))
                    {
                        if (document.object().value("If_Sent").isArray())
                        {
                            QJsonArray midIf_Sent = document.object().value("If_Sent").toArray();
                            for(int zi=0;zi<midIf_Sent.size();zi++)
                            {
                                midComSaveInfo[zi].If_Sent=midIf_Sent[zi].toBool();
                            }
                        }
                    }
                    if (document.object().contains("Type"))
                    {
                        if (document.object().value("Type").isArray())
                        {
                            QJsonArray midType = document.object().value("Type").toArray();
                            for(int zi=0;zi<midType.size();zi++)
                            {
                                midComSaveInfo[zi].Type=midType[zi].toInt();
                            }
                        }
                    }
                    else
                    {
                        for(int zi=0;zi<midSize;zi++)
                        {
                            midComSaveInfo[zi].Type=1;
                        }
                    }
                }
            }
        }
    //}
}

QPalette GetUpTextPalette()
{
    UpTextPalette.setColor(QPalette::WindowText, QColor(255, 153, 34));
    return UpTextPalette;
}
QPalette DownTextPalette;
QPalette GetDownTextPalette()
{
    DownTextPalette.setColor(QPalette::WindowText, QColor(40,40,40));
    return DownTextPalette;
}
QPalette DownLogTextPalette;
QPalette GetDownLogTextPalette()
{
    DownLogTextPalette.setColor(QPalette::WindowText, QColor(160,160,160));
    return DownLogTextPalette;
}
QPalette UpWindowsPalette;
QPalette GetUpWindowsPalette()
{
    UpWindowsPalette.setColor(QPalette::Window, QColor(255, 153, 34));
    return UpWindowsPalette;
}
QPalette DownWindowsPalette;
QPalette GetDownWindowsPalette()
{
    DownWindowsPalette.setColor(QPalette::Window, QColor(223,223,223));
    return DownWindowsPalette;
}
QPalette UpLineTextPalette;
QPalette GetUpLineTextPalette()
{
    UpLineTextPalette.setColor(QPalette::Text, QColor(255, 153, 34));
    return UpLineTextPalette;
}
QPalette DownLineTextPalette;
QPalette GetDownLineTextPalette()
{
    DownLineTextPalette.setColor(QPalette::Text, QColor(40, 40, 40));
    return DownLineTextPalette;
}
QPalette DownLineLogTextPalette;
QPalette GetDownLineLogTextPalette()
{
    DownLineLogTextPalette.setColor(QPalette::Text, QColor(160,160,160));
    return DownLineLogTextPalette;
}
void BaseKuangPixSet(BasePixCache midModuBasePix)
{
    BaseKuangPix=midModuBasePix;
}
BasePixCache BaseKuangPixGet()
{
    return BaseKuangPix;
}
BaseCache::BaseCache(QWidget *parent)
    : QWidget{parent}
{}
// 写入CSV文件


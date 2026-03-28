#include "basecache.h"

void BaseChartInfoSet(QString midPjtName,ChartSave midChartInfo)
{
    QJsonArray midViewName;
    QJsonArray midViewType;
    QJsonArray midHengZhouName;
    for(int zi=0;zi<24;zi++)
    {
        bool if_Push=0;
        QJsonArray midLineName;
        for(int yi=0;yi<6;yi++)
        {
            if(midChartInfo.LineName[zi][yi].length()>0)
            {
                midLineName.append(midChartInfo.LineName[zi][yi]);
                if_Push=1;
            }
        }
        if(if_Push)
        {
            midViewName.append(midLineName);
            midViewType.append(midChartInfo.Type[zi]);
            midHengZhouName.append(midChartInfo.HengZhouName[zi]);
        }
    }

    QJsonObject json;
    json.insert("LineName", midViewName);
    json.insert("Type", midViewType);
    json.insert("HengZhouName", midHengZhouName);

    // 构建JSON文档
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);//Compact
    QString strJson(byteArray);
    QString midpath=QT_FldAddress();
    midpath=midpath+"AlgProject\\"+midPjtName+"\\ChartInfo.json";
    QFile fw(midpath);
    if(fw.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream txtOutput(&fw);
        txtOutput << strJson;
    }
    fw.close();
}
void BaseChartInfoGet(QString midPjtName,ChartSave &midChartInfo,int &midViewSize)
{
    QString midpath=QT_FldAddress();
    midpath=midpath+"AlgProject\\"+midPjtName+"\\ChartInfo.json";

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
                if (document.object().contains("LineName"))
                {
                    if (document.object().value("LineName").isArray())
                    {
                        QJsonArray midViewName=document.object().value("LineName").toArray();
                        midViewSize=midViewName.size();
                        if(midViewSize>24){midViewSize=24;}
                        for(int zi=0;zi<midViewSize;zi++)
                        {
                            if (midViewName[zi].isArray())
                            {
                                QJsonArray midLineName=midViewName[zi].toArray();
                                for(int yi=0;yi<midLineName.size();yi++)
                                {
                                    midChartInfo.LineName[zi][yi]=midLineName[yi].toString();
                                }
                            }
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
                            midChartInfo.Type[zi]=midType[zi].toInt();
                        }
                    }
                }
                if (document.object().contains("HengZhouName"))
                {
                    if (document.object().value("HengZhouName").isArray())
                    {
                        QJsonArray midHengZhouName = document.object().value("HengZhouName").toArray();
                        for(int zi=0;zi<midHengZhouName.size();zi++)
                        {
                            midChartInfo.HengZhouName[zi]=midHengZhouName[zi].toString();
                        }
                    }
                }
            }
        }
    }
}
BaseCache::BaseCache(QWidget *parent)
    : QWidget{parent}
{}


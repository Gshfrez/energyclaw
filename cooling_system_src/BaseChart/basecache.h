#ifndef BASECACHE_H
#define BASECACHE_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "FOLDEREDIT.h"
struct ChartSave{
    QString LineName[24][6];
    int Type[24];
    QString HengZhouName[24];
};
void BaseChartInfoSet(QString midPjtName,ChartSave midComSaveInfo);
void BaseChartInfoGet(QString midPjtName,ChartSave &midComSaveInfo,int &midSize);
class BaseCache : public QWidget
{
    Q_OBJECT
public:
    explicit BaseCache(QWidget *parent = nullptr);

signals:
};

#endif // BASECACHE_H

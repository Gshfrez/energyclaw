#ifndef BASECACHE_H
#define BASECACHE_H

#include <QWidget>
#include <QPixmap>
#include <QPalette>
#include <QFile>
#include <QTextStream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "FOLDEREDIT.h"
struct ComSave{
    QString ComName;
    QString Lua;
    bool If_Sent;
    int Type;
};
struct BasePixCache{
    QPixmap *BasePix[9];
};

void BaseKuangPixSet(QString midPjtName,ComSave midComSaveInfo[]);
void BaseKuangPixGet(QString midPjtName,ComSave midComSaveInfo[],int &midSize);

QPalette GetUpTextPalette();
QPalette GetDownTextPalette();

QPalette GetUpWindowsPalette();
QPalette GetDownWindowsPalette();
QPalette GetDownLogTextPalette();
QPalette GetUpLineTextPalette();
QPalette GetDownLineTextPalette();
QPalette GetDownLineLogTextPalette();

class BaseCache : public QWidget
{
    Q_OBJECT
public:
    explicit BaseCache(QWidget *parent = nullptr);

signals:
};

#endif // BASECACHE_H

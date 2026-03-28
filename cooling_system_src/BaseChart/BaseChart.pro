QT += core gui
QT += core gui charts
msvc {
QMAKE_CFLAGS += /utf-8
QMAKE_CXXFLAGS += /utf-8
}
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
RC_ICONS=BaseChart.ico
CONFIG += c++17
DESTDIR=../../BaseDesigner/CommonLib
CONFIG(debug, debug|release) {

    INCLUDEPATH += ../../BaseDesigner/LibP/debug/
    INCLUDEPATH += ../../BaseDesigner/CommonLib/
    greaterThan(QT_MAJOR_VERSION, 5){
        TARGET = BaseChart
        LIBS += ../../BaseDesigner/LibP/debug/FOLDEREDIT_MDD.lib
    }
    else{
        TARGET = BaseChart_7
        LIBS += ../../BaseDesigner/LibP/debug/FOLDEREDIT.lib
    }
    LIBS += ../../BaseDesigner/CommonLib/BaseChartCache.lib
    #LIBS += ../../BaseDesigner/CommonLib/BaseNeiCunClient.lib
}else{
QMAKE_CXXFLAGS_RELEASE += /Od

    INCLUDEPATH += ../../BaseDesigner/LibP/
    INCLUDEPATH += ../../BaseDesigner/CommonLib/
    greaterThan(QT_MAJOR_VERSION, 5){
        TARGET = BaseChart_R
        LIBS += ../../BaseDesigner/LibP/FOLDEREDIT_MD.lib
        }
    else{
        TARGET = BaseChart_R_7
        LIBS += ../../BaseDesigner/LibP/FOLDEREDIT.lib
        }
    LIBS += ../../BaseDesigner/CommonLib/BaseChartCache_R.lib
    #LIBS += ../../BaseDesigner/CommonLib/BaseNeiCunClient_R.lib
}

SOURCES += \
    anniudiandong.cpp \
    anniuzisuo.cpp \
    basecache.cpp \
    baseicon.cpp \
    firtcurvechartview.cpp \
    gdwheel.cpp \
    icon_onoff.cpp \
    linezhexian.cpp \
    main.cpp \
    basechart.cpp

HEADERS += \
    anniudiandong.h \
    anniuzisuo.h \
    basecache.h \
    basechart.h \
    baseicon.h \
    firtcurvechartview.h \
    gdwheel.h \
    icon_onoff.h \
    linezhexian.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ziyuan.qrc

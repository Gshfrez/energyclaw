QT       += core gui
QT       += serialport
QT       += core gui network

msvc {
QMAKE_CFLAGS += /utf-8Q
QMAKE_CXXFLAGS += /utf-8
}
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
RC_ICONS=BaseLink.ico
CONFIG += c++17
DESTDIR=../../BaseDesigner/CommonLib
INCLUDEPATH=../lua-5.4.6/src
CONFIG(debug, debug|release) {
    INCLUDEPATH += ../../BaseDesigner/LibP/debug/
    INCLUDEPATH += ../../BaseDesigner/CommonLib/
    greaterThan(QT_MAJOR_VERSION, 5){
        TARGET = BaseLink
        LIBS += ../../BaseDesigner/LibP/debug/FOLDEREDIT_MDD.lib
        LIBS += ../../BaseDesigner/LibP/debug/LUA546_MDD.lib
        LIBS += ../../BaseDesigner/CommonLib/qscintilla2_qt6d.lib
    }
    else{
        TARGET = BaseLink_7
        LIBS += ../../BaseDesigner/LibP/debug/FOLDEREDIT.lib
        LIBS += ../../BaseDesigner/LibP/debug/LUA546.lib
        LIBS += ../../BaseDesigner/CommonLib/qscintilla2_qt5d.lib
    }
    LIBS += ../../BaseDesigner/CommonLib/BaseCore.lib
    LIBS += ../../BaseDesigner/CommonLib/BaseServer.lib
}else{
    QMAKE_CXXFLAGS_RELEASE += /Od
    INCLUDEPATH += ../../BaseDesigner/LibP/
    INCLUDEPATH += ../../BaseDesigner/CommonLib/
    greaterThan(QT_MAJOR_VERSION, 5){
        TARGET = BaseLink_R
        LIBS += ../../BaseDesigner/LibP/FOLDEREDIT_MD.lib
        LIBS += ../../BaseDesigner/LibP/LUA546_MD.lib
        LIBS += ../../BaseDesigner/CommonLib/qscintilla2_qt6.lib
        }
    else{
        TARGET = BaseLink_R_7
        LIBS += ../../BaseDesigner/LibP/FOLDEREDIT.lib
        LIBS += ../../BaseDesigner/LibP/LUA546.lib
        LIBS += ../../BaseDesigner/CommonLib/qscintilla2_qt5.lib
        }
    LIBS += ../../BaseDesigner/CommonLib/BaseCore_R.lib
    LIBS += ../../BaseDesigner/CommonLib/BaseServer_R.lib
}
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    anniudiandong.cpp \
    anniuzisuo.cpp \
    basecache.cpp \
    basekuang.cpp \
    comlink.cpp \
    main.cpp \
    baselink.cpp \
    tcplink.cpp

HEADERS += \
    anniudiandong.h \
    anniuzisuo.h \
    basecache.h \
    basekuang.h \
    baselink.h \
    comlink.h \
    tcplink.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ziyuan.qrc

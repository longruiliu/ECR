#-------------------------------------------------
#
# Project created by QtCreator 2013-03-01T17:00:17
#
#-------------------------------------------------

QT       += core gui network
QT       += webkit

TARGET = USay
TEMPLATE = app

DEFINES += JSON_IS_AMALGAMATION

SOURCES += main.cpp \
    chatroom.cpp \
    chatroompanel.cpp \
    friendlist.cpp \
    grouplist.cpp \
    logindialog.cpp \
    loginconfig.cpp \
    groupchatdialog.cpp \
    fadeinout.cpp \
    registerdialog.cpp \
    shakewindow.cpp \
    messagelistener.cpp \
    networkqueue.cpp \
    network1.cpp \
    protocol/jsoncpp.cpp \
    protocol/protocol.cpp \
    ../src-srv/msgRecord.cpp

HEADERS  += \
    chatroom.h \
    chatroompanel.h \
    friendlist.h \
    grouplist.h \
    logindialog.h \
    loginconfig.h \
    groupchatdialog.h \
    fadeinout.h\
    registerdialog.h \
    shakewindow.h \
    messagelistener.h \
    fadeinout.h \
    networkqueue.h \
    network1.h

FORMS    += \
    chatroom.ui \
    chatroompanel.ui \
    friendlist.ui \
    grouplist.ui \
    logindialog.ui \
    loginconfig.ui \
    groupchatdialog.ui \
    registerdialog.ui

RESOURCES += \
    USay.qrc

INCLUDEPATH += ./protocol
INCLUDEPATH += ../src-srv/include
INCLUDEPATH += ../include
RC_FILE = icon.rc

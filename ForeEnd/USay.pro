#-------------------------------------------------
#
# Project created by QtCreator 2013-03-01T17:00:17
#
#-------------------------------------------------

QT       += core gui
QT       += webkit

TARGET = USay
TEMPLATE = app


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
    shakewindow.cpp

HEADERS  += \
    chatroom.h \
    chatroompanel.h \
    friendlist.h \
    grouplist.h \
    logindialog.h \
    loginconfig.h \
    groupchatdialog.h \
    fadeinout.h \
    registerdialog.h \
    shakewindow.h

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

RC_FILE = icon.rc

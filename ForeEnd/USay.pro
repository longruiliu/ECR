#-------------------------------------------------
#
# Project created by QtCreator 2013-03-01T17:00:17
#
#-------------------------------------------------

QT       += core gui network
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
    shakewindow.cpp \
    messagelistener.cpp \
    networkqueue.cpp \
    network1.cpp

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

LIBS += D:\\ECR\\USay\\ForeEnd\\protocol\\json_vc71_libmt.lib
INCLUDEPATH += C:\\Users\\guzhouyiye\\Downloads\\jsoncpp-src-0.5.0\\include
INCLUDEPATH += D:\\tmp\\ECR\\src_srv\\include
INCLUDEPATH += D:\\tmp\\ECR\\src_srv\\user
RC_FILE = icon.rc

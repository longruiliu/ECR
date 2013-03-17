#-------------------------------------------------
#
# Project created by QtCreator 2013-03-17T09:58:01
#
#-------------------------------------------------

QT       += core gui

TARGET = Manager
TEMPLATE = app


SOURCES += main.cpp\
    managerwindow.cpp \
    sqlite3.c \
    Database.cpp \
    group.cpp \
    user.cpp

HEADERS  += \
    managerwindow.h \
    sqlite3.h \
    Database.h \
    user.h \
    group.h \
    user.h

FORMS += \
    managerwindow.ui

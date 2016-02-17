#-------------------------------------------------
#
# Project created by QtCreator 2016-02-14T12:39:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Circle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controlpanel.cpp \
    controlsgroup.cpp \
    circle.cpp \
    connector.cpp \
    drawpanel.cpp \
    params.cpp

HEADERS  += mainwindow.h \
    controlpanel.h \
    controlsgroup.h \
    circle.h \
    connector.h \
    drawpanel.h \
    params.h

FORMS    += mainwindow.ui \
    controlpanel.ui \
    controlsgroup.ui \
    drawpanel.ui \

CONFIG += c++11

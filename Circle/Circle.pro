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
    circle.cpp \
    drawpanel.cpp \
    params.cpp \
    controlgroup.cpp

HEADERS  += mainwindow.h \
    controlpanel.h \
    ControlGroup.h \
    circle.h \
    drawpanel.h \
    params.h \
    controlgroup.h

FORMS    += mainwindow.ui \
    controlpanel.ui \
    ControlGroup.ui \
    drawpanel.ui \
    controlgroup.ui

CONFIG += c++11

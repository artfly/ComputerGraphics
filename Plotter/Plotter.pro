#-------------------------------------------------
#
# Project created by QtCreator 2016-02-14T12:39:24
#
#-------------------------------------------------

QT       += core gui
QT       += widgets

TARGET = Plotter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controlpanel.cpp \
    lemniscate.cpp \
    drawpanel.cpp \
    params.cpp \
    controlgroup.cpp \
    jsonhandler.cpp

HEADERS  += mainwindow.h \
    controlpanel.h \
    ControlGroup.h \
    lemniscate.h \
    drawpanel.h \
    params.h \
    controlgroup.h \
    jsonhandler.h

CONFIG += c++11

FORMS += \
    mainwindow.ui \
    drawpanel.ui \
    controlpanel.ui \
    controlgroup.ui

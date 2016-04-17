QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Font
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
    controlcheckbox.cpp \
    controlgroup.cpp \
    controlpanel.cpp \
    drawpanel.cpp \
    jsonhandler.cpp \
    params.cpp \
    font.cpp

HEADERS  += mainwindow.h \
    controlcheckbox.h \
    controlgroup.h \
    controlinterface.h \
    controlpanel.h \
    drawpanel.h \
    jsonhandler.h \
    params.h \
    glyphpoint.h \
    font.h

FORMS    += mainwindow.ui \
    controlcheckbox.ui \
    controlgroup.ui \
    controlpanel.ui \
    drawpanel.ui

CONFIG += c++11

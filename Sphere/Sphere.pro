QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sphere
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
        controlgroup.cpp \
        controlpanel.cpp \
        drawpanel.cpp \
        params.cpp \
    controlcombobox.cpp \
    sphere.cpp

HEADERS  += mainwindow.h \
        controlgroup.h \
        controlinterface.h \
        controlpanel.h \
        drawpanel.h \
        params.h \
    controlcombobox.h \
    sphere.h

FORMS    += mainwindow.ui \
        controlgroup.ui \
        controlpanel.ui \
        drawpanel.ui \
    controlcombobox.ui

CONFIG += c++11

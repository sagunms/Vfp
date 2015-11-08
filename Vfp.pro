#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T11:58:11
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Vfp
TEMPLATE = app


SOURCES += main.cpp\
        View/mainview.cpp \
    View/setuptab.cpp \
    startup.cpp \
    utils.cpp \
    Model/settings.cpp

HEADERS  += View/mainview.h \
    View/setuptab.h \
    startup.h \
    utils.h \
    Model/settings.h

FORMS    += View/mainview.ui \
    View/setuptab.ui

CONFIG += c++11

RESOURCES += \
    vfpresources.qrc

DISTFILES +=

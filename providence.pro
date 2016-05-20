#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T12:17:10
#
#-------------------------------------------------

QT       += core gui sql

TARGET = providence
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cuisine.cpp \
    dish.cpp \
    ingrform.cpp \
    graphform.cpp \
    orderform.cpp

HEADERS  += mainwindow.h \
    cuisine.h \
    dish.h \
    ingrform.h \
    graphform.h \
    orderform.h

FORMS    += mainwindow.ui \
    graphform.ui \
    ingrform.ui \
    orderform.ui

include(qcustomplot/qcustomplot.pri)


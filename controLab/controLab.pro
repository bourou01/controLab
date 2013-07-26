#-------------------------------------------------
#
# Project created by QtCreator 2013-06-22T20:00:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = controLab
TEMPLATE = app

include(qextserialport/src/qextserialport.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    hled.cpp \
    QCustomPlot/qcustomplot.cpp \
    buffered2dsamples.cpp \
    frdmjsonparser.cpp \
    customgraph.cpp \
    MessageWindow.cpp \
    serialmanagerview.cpp \
    customplotview.cpp \
    serialconfigurationview.cpp \
    frdmcontrolview.cpp \
    managedobjectstore.cpp

HEADERS  += mainwindow.h \
    hled.h \
    QCustomPlot/qcustomplot.h \
    buffered2dsamples.h \
    frdmjsonparser.h \
    customgraph.h \
    MessageWindow.h \
    serialmanagerview.h \
    customplotview.h \
    serialconfigurationview.h \
    frdmcontrolview.h \
    managedobjectstore.h

FORMS    += mainwindow.ui \
    customplotview.ui \
    serialconfigurationview.ui \
    frdmcontrolview.ui

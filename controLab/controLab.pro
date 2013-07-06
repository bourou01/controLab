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
    serialcomdialog.cpp \
    hled.cpp \
    QCustomPlot/qcustomplot.cpp \
    buffered2dsamples.cpp \
    frdmjsonparser.cpp \
    customplotdialog.cpp \
    customgraph.cpp \
    QespTest.cpp \
    MessageWindow.cpp \
    frdmrequestmanager.cpp \
    serialmanagerview.cpp \
    customplotview.cpp \
    serialconfigurationview.cpp \
    frdmcontrolview.cpp

HEADERS  += mainwindow.h \
    serialcomdialog.h \
    hled.h \
    QCustomPlot/qcustomplot.h \
    buffered2dsamples.h \
    frdmjsonparser.h \
    customplotdialog.h \
    customgraph.h \
    QespTest.h \
    MessageWindow.h \
    frdmrequestmanager.h \
    serialmanagerview.h \
    customplotview.h \
    serialconfigurationview.h \
    frdmcontrolview.h

FORMS    += mainwindow.ui \
    serialcomdialog.ui \
    customplotdialog.ui \
    customplotview.ui \
    serialconfigurationview.ui \
    frdmcontrolview.ui

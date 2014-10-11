#-------------------------------------------------
#
# Project created by QtCreator 2014-04-16T17:08:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = IonogramProcessing
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    ionogram.cpp \
    componentlabeling.cpp \
    csv.cpp \
    disjointset.cpp \
    point.cpp \
    labeling_dialog.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    ionogram.h \
    componentlabeling.h \
    csv.h \
    disjointset.h \
    point.h \
    labeling_dialog.h

FORMS    += mainwindow.ui \
    labeling_dialog.ui

RESOURCES +=

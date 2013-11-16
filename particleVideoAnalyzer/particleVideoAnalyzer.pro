#-------------------------------------------------
#
# Project created by QtCreator 2013-11-13T17:21:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = particleVideoAnalyzer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    textprocessing.cpp \
    analyzer.cpp

HEADERS  += mainwindow.h \
    textprocessing.h \
    analyzer.h

FORMS    += mainwindow.ui

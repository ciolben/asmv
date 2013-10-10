#-------------------------------------------------
#
# Project created by QtCreator 2013-09-16T12:10:57
#
#-------------------------------------------------

QT       +=  core gui widgets
#QT       +=  multimedia multimediawidgets core gui
#QT       += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

FFMPEG_INCLUDES = ffmpeg/include/
FFMPEG_LIBS32 = ffmpeg/lib/
OPTICALFLOW_INCLUDES = opticalflow/include

win32:INCLUDEPATH += $$FFMPEG_INCLUDES
INCLUDEPATH += $$OPTICALFLOW_INCLUDES

#SUBDIRS += $$OPTICALFLOW_INCLUDES

LIBS += -L$$FFMPEG_LIBS32 -lavformat\
            -lavcodec \
            -lavdevice \
            -lavutil \
            -lavfilter \
            -lpostproc \
            -lswresample \
            -lswscale \

TARGET = test1
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    customctrl.cpp \
    #videoplayer.cpp \
    videotools.cpp \
    workerthread.cpp \
    opticalflowtools.cpp \
    opticalflow/include/Stochastic.cpp \
    opticalflow/include/OpticalFlow.cpp \
    opticalflow/include/GaussianPyramid.cpp

HEADERS  += mainwindow.h \
    customctrl.h \
    #videoplayer.h \
    videotools.h \
    workerthread.h \
    opticalflowtools.h \
    opticalflow/include/Vector.h \
    opticalflow/include/Stochastic.h \
    opticalflow/include/project.h \
    opticalflow/include/OpticalFlow.h \
    opticalflow/include/NoiseModel.h \
    opticalflow/include/Matrix.h \
    opticalflow/include/ImageProcessing.h \
    opticalflow/include/ImageIO.h \
    opticalflow/include/Image.h \
    opticalflow/include/GaussianPyramid.h

FORMS    += mainwindow.ui \
    customctrl.ui

#win32:QMAKE_LFLAGS += -shared

DEFINES += __STDC_CONSTANT_MACROS

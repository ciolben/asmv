#-------------------------------------------------
#
# Project created by QtCreator 2013-09-16T12:10:57
#
#-------------------------------------------------

QT       +=  core gui
#QT       +=  multimedia multimediawidgets core gui
#QT       += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quick qml

BOOST_PATH = "C:\Program Files\boost\boost_1_55_0"

GEOMETRICTOOLS_PATH = "D:/Programs/wildmagic5p10/SDK"

FFMPEG_INCLUDES = ffmpeg/include/
FFMPEG_LIBS32 = ffmpeg/lib/
OPTICALFLOW_INCLUDES = opticalflow/include

#FFMPEG flag
QMAKE_LFLAGS += /OPT:NOREF

INCLUDEPATH += $$FFMPEG_INCLUDES
INCLUDEPATH += $$OPTICALFLOW_INCLUDES \
                $$BOOST_PATH \
                $$GEOMETRICTOOLS_PATH/Include

SUBDIRS += timelineQML

LIBS += -L$$GEOMETRICTOOLS_PATH/Library -lWm5Core \
            -lWm5Imagics \
            -lWm5Mathematics \
            -lWm5Physics \
            -lWm5WglApplications \
            -lWm5WglGraphics

LIBS += -L$$FFMPEG_LIBS32 -lavformat\
            -lavcodec \
            -lavdevice \
            -lavutil \
            -lavfilter \
            -lpostproc \
            -lswresample \
            -lswscale

TARGET = ASMV
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
    opticalflow/include/GaussianPyramid.cpp \
    timeline.cpp \
    timelineQML/bspline.cpp \
    timelineQML/splinedrawer.cpp \
    qmlregister.cpp \
    addsequencedialog.cpp \
    imageeaterthread.cpp \
    opticalflowui.cpp \
    opticalflowthread.cpp \
    interpolateui.cpp \
    motionui.cpp \
    motionthread.cpp

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
    opticalflow/include/GaussianPyramid.h \
    timeline.h \
    timelineQML/bspline.h \
    timelineQML/splinedrawer.h \
    mathlib/spline.hpp \
    qmlregister.h \
    addsequencedialog.h \
    imageeaterthread.h \
    timelineQML/Sequence.hpp \
    opticalflowui.h \
    opticalflowthread.h \
    interpolateui.h \
    motionui.h \
    utils/iocompression.h \
    motionthread.h \
    mathlib/filtering.h \
    mathlib/bsplinefitter.h \
    utils/filesutils.h


FORMS    += mainwindow.ui \
    customctrl.ui \
    timeline.ui \
    addsequencedialog.ui \
    opticalflowui.ui \
    interpolateui.ui \
    motionui.ui

#win32:QMAKE_LFLAGS += -shared

LIBS += -lQt5Concurrent

DEFINES += __STDC_CONSTANT_MACROS

OTHER_FILES += \
    timelineQML/timeline.qmlproject \
    timelineQML/timeline.qml \
    timelineQML/Line.qml \
    opticalflowUI.qml

RESOURCES += \
    icons.qrc \
    qmls.qrc

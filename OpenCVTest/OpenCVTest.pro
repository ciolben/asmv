#-------------------------------------------------
#
# Project created by QtCreator 2013-10-30T21:21:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCVTest
TEMPLATE = app

OPENCV_PATH = "D:\Programs\opencv"
OPENCV_INCLUDE = $$OPENCV_PATH\build\include
OPENCV_INCLUDE2 = $$OPENCV_PATH\include\opencv2   #for opencv.hpp v2
OPENCV_MODULE = $$OPENCV_PATH\modules
OPENCV_MODULE_INCLUDES += $$OPENCV_MODULE\gpu\include #gpu support

OPENCV_LIBS = $$OPENCV_PATH\build\x86\vc10\lib #32 bit (| x86,x64), vc10 (| mingw,vc9,vc10,vc11), dynamic libs (| lib,staticlib)

INCLUDEPATH += $$OPENCV_INCLUDE \
                $$OPENCV_INLCUDE2 \
                $$OPENCV_MODULE_INLUDES

#QMAKE_LFLAGS_DEBUG   = /NODEFAULTLIB:msvcrtd
#QMAKE_LFLAGS_DEBUG   = /NODEFAULTLIB:msvcp100d
#QMAKE_LFLAGS_DEBUG   = /NODEFAULTLIB:libcmt

CONFIG(release,debug|release){
    LIBS += $$OPENCV_LIBS\opencv_calib3d246.lib \
            $$OPENCV_LIBS\opencv_contrib246.lib \
            $$OPENCV_LIBS\opencv_core246.lib \
            $$OPENCV_LIBS\opencv_features2d246.lib \
            $$OPENCV_LIBS\opencv_flann246.lib \
            $$OPENCV_LIBS\opencv_gpu246.lib \
$$OPENCV_LIBS\opencv_haartraining_engine.lib \
            $$OPENCV_LIBS\opencv_highgui246.lib \
            $$OPENCV_LIBS\opencv_imgproc246.lib \
            $$OPENCV_LIBS\opencv_legacy246.lib \
            $$OPENCV_LIBS\opencv_ml246.lib \
$$OPENCV_LIBS\opencv_nonfree246.lib \
            $$OPENCV_LIBS\opencv_objdetect246.lib \
$$OPENCV_LIBS\opencv_ocl246.lib \
$$OPENCV_LIBS\opencv_photo246.lib \
$$OPENCV_LIBS\opencv_stitching246.lib \
$$OPENCV_LIBS\opencv_superres246.lib \
            $$OPENCV_LIBS\opencv_ts246.lib \
            $$OPENCV_LIBS\opencv_video246.lib \
$$OPENCV_LIBS\opencv_videostab246.lib
}

CONFIG(debug,debug|release){
    LIBS += $$OPENCV_LIBS\opencv_calib3d246d.lib \
            $$OPENCV_LIBS\opencv_contrib246d.lib \
            $$OPENCV_LIBS\opencv_core246d.lib \
            $$OPENCV_LIBS\opencv_features2d246d.lib \
            $$OPENCV_LIBS\opencv_flann246d.lib \
            $$OPENCV_LIBS\opencv_gpu246d.lib \
$$OPENCV_LIBS\opencv_haartraining_engined.lib \
            $$OPENCV_LIBS\opencv_highgui246d.lib \
            $$OPENCV_LIBS\opencv_imgproc246d.lib \
            $$OPENCV_LIBS\opencv_legacy246d.lib \
            $$OPENCV_LIBS\opencv_ml246d.lib \
$$OPENCV_LIBS\opencv_nonfree246d.lib \
            $$OPENCV_LIBS\opencv_objdetect246d.lib \
$$OPENCV_LIBS\opencv_ocl246d.lib \
$$OPENCV_LIBS\opencv_photo246d.lib \
$$OPENCV_LIBS\opencv_stitching246d.lib \
$$OPENCV_LIBS\opencv_superres246d.lib \
            $$OPENCV_LIBS\opencv_ts246.lib \
            $$OPENCV_LIBS\opencv_video246d.lib \
$$OPENCV_LIBS\opencv_videostab246d.lib
}

SOURCES += main.cpp\
        mainwindow.cpp \
    contours2.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

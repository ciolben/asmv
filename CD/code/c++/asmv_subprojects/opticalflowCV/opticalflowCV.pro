#-------------------------------------------------
#
# Project created by QtCreator 2013-11-01T17:29:46
#
#-------------------------------------------------

TARGET = opticalflowCV

#CONFIG += lib_conf
#CONFIG += console

lib_conf {
    DEFINES += OPTICALFLOWCV_LIBRARY
    TEMPLATE = lib
} else {
    TEMPLATE = app
}

SOURCES += opticalflowcv.cpp

HEADERS += opticalflowcv.h\
        opticalflowcv_global.h \
    broxflow.hpp

#--OPENCV stuff--

OPENCV_PATH = "D:\Programs\opencvbuild\install"
OPENCV_INCLUDE = $$OPENCV_PATH\include

OPENCV_LIBS = $$OPENCV_PATH\lib

INCLUDEPATH += $$OPENCV_INCLUDE

CONFIG(release,debug|release){
    LIBS += $$OPENCV_LIBS\opencv_calib3d246.lib \
            $$OPENCV_LIBS\opencv_contrib246.lib \
            $$OPENCV_LIBS\opencv_core246.lib \
            $$OPENCV_LIBS\opencv_features2d246.lib \
            $$OPENCV_LIBS\opencv_flann246.lib \
            $$OPENCV_LIBS\opencv_gpu246.lib \
            #$$OPENCV_LIBS\opencv_haartraining_engine.lib \
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
           #$$OPENCV_LIBS\opencv_haartraining_engined.lib \
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

#----------------

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

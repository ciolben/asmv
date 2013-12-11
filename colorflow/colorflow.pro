TARGET = colorflow

TEMPLATE = app

#--OPENCV stuff--

OPENCV_PATH = "D:\opencv246"
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

SOURCES += \
    main.cpp

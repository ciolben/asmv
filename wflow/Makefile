# set the binaries that have to be built
TARGETS := DenseTrack Video

# set the build configuration set 
BUILD := release
#BUILD := debug

# set bin and build dirs
BUILDDIR := .build_$(BUILD)
BINDIR := $(BUILD)

#CXX=cl

#paths
BOOSTPATH="/cygdrive/c/Program Files/boost/boost_1_54_0
OPENCVPATH="/cygdrive/d/opencv246
FFMPEGPATH="/cygdrive/c/Users/Loic/Coding_Main/ADM/ffmpeg

# libraries 
LIBBOOST=${BOOSTPATH}/stage/lib"
LIBOPENCV=${OPENCVPATH}/lib"
LIBFFMPEG=${FFMPEGPATH}/lib"
#LDLIBS = $(addprefix -l, $(LIBS) $(LIBS_$(notdir $*)))
LIBDIRS = \
 	-L${LIBBOOST} \
	-L${LIBOPENCV} \
	-L${LIBFFMPEG}
LIBS := \
	 -llibboost_program_options-vc100-mt-1_54 -llibboost_regex-vc100-mt-1_54 -llibboost_system-vc100-mt-1_54 -llibboost_filesystem-vc100-mt-1_54 \
	 -lopencv_core246 -lopencv_highgui246 -lopencv_video246 -lopencv_imgproc246 \
-lopencv_calib3d246 \
-lopencv_contrib246 \
-lopencv_features2d246 \
-lopencv_flann246 \
-lopencv_gpu246 \
-lopencv_legacy246 \
-lopencv_ml246 \
-lopencv_nonfree246 \
-lopencv_objdetect246 \
-lopencv_ocl246 \
-lopencv_photo246 \
-lopencv_stitching246 \
-lopencv_superres246 \
-lopencv_ts246 \
-lopencv_videostab246 \
	 -lavformat -lavdevice -lavutil -lavcodec -lswscale
	#lapack cblas atlas blas \

LDLIBS = ${LIBDIRS} ${LIBS}
#includes
INCDIRS := \
	-I${OPENCVPATH}/include" \
	-I${BOOSTPATH}" \
	-I${FFMPEGPATH}/include"}

# set some flags and compiler/linker specific commands
CXXFLAGS = -pipe -D __STDC_CONSTANT_MACROS -D STD=std -Wall $(CXXFLAGS_$(BUILD)) -I. -I/opt/include ${INCDIRS}
CXXFLAGS_debug := -ggdb
CXXFLAGS_release := -O3 -DNDEBUG -ggdb
LDFLAGS = -L/opt/lib -pipe -Wall $(LDFLAGS_$(BUILD))
LDFLAGS_debug := -ggdb
LDFLAGS_release := -O3 -ggdb

include make/generic.mk

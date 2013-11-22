#############################################################################
# Automatically generated from M
#############################################################################

OS			= CYGWIN_NT-6.1-WOW64

MOTION2D_HOME		= /cygdrive/c/Users/Loic/Coding_Main/ADM/Motion2D-1.3.11.1
MOTION2D_DIR_SRC	= $(MOTION2D_HOME)/src


MOTION2D_DIR_COMPENSE         = $(MOTION2D_DIR_SRC)/compense
MOTION2D_DIR_CPRIM            = $(MOTION2D_DIR_SRC)/cprim
MOTION2D_DIR_ESTIMATION       = $(MOTION2D_DIR_SRC)/estimation
MOTION2D_DIR_IMAGE            = $(MOTION2D_DIR_SRC)/image
MOTION2D_DIR_INC              = $(MOTION2D_DIR_SRC)/inc
MOTION2D_DIR_INTERFACE        = $(MOTION2D_DIR_SRC)/interface
MOTION2D_DIR_MATSYM           = $(MOTION2D_DIR_SRC)/mat_sym
MOTION2D_DIR_MEMOIRE          = $(MOTION2D_DIR_SRC)/memoire
MOTION2D_DIR_PYRAMIDE         = $(MOTION2D_DIR_SRC)/pyramide
MOTION2D_DIR_CONTRIB          = $(MOTION2D_DIR_SRC)/contrib
MOTION2D_DIR_CONTRIB_MPEG2DEC = $(MOTION2D_DIR_CONTRIB)/mpeg2dec
MOTION2D_DIR_CONTRIB_LOCALPNG = $(MOTION2D_DIR_CONTRIB)/localpng

# Compiling
CONF_CXX		= g++
CONF_CXX_VERSION	= $(shell $(CONF_CXX) -dumpversion)
CONF_CXXFLAGS		= -Wall -O2 -pipe -funroll-loops -finline-functions

# Linking
RANLIB		= ranlib
AR		= ar r

CXXFLAGS_OPT		= 
LDFLAGS_OPT		= 
SUFFIX                  = 

MOTION2D_DIR_INCLUDE	= $(MOTION2D_HOME)/include
MOTION2D_DIR_LIB	= $(MOTION2D_HOME)/lib
MOTION2D_DIR_BIN	= $(MOTION2D_HOME)/bin

MOTION2D_BINPATH	= $(MOTION2D_DIR_BIN)/$(OS)
MOTION2D_LIBPATH	= $(MOTION2D_DIR_LIB)/$(OS)/$(CONF_CXX_VERSION)

MOTION2D_LIBNAME	= libMotion2D$(SUFFIX).a
MPEG2DEC_LIBNAME	= libmpeg2dec$(SUFFIX).a
LOCALPNG_LIBNAME	= liblocalpng$(SUFFIX).a
MOTION2D_LIBS           = -llocalpng$(SUFFIX) -lpng -lz

IFLAGS		=\
		-I$(MOTION2D_DIR_INCLUDE) -I$(MOTION2D_DIR_INC) \
		-I$(MOTION2D_DIR_MATSYM) -I$(MOTION2D_DIR_CPRIM) \
		-I$(MOTION2D_DIR_PYRAMIDE) -I$(MOTION2D_DIR_MEMOIRE) \
		-I$(MOTION2D_DIR_COMPENSE) -I$(MOTION2D_DIR_CONTRIB_LOCALPNG) \
		-I$(MOTION2D_DIR_CONTRIB_MPEG2DEC)

CXX		= $(CONF_CXX)
CXXFLAGS	= $(CONF_CXXFLAGS) $(CXXFLAGS_OPT) $(IFLAGS)


INC		= \
		$(MOTION2D_DIR_INC)/type.h	\
		$(MOTION2D_DIR_INC)/macro.h	\
		$(MOTION2D_DIR_INC)/constant.h	\
		$(MOTION2D_DIR_INC)/interplt.h \
		$(MOTION2D_DIR_INCLUDE)/Motion2D.h

MOTION2D_LIB	= $(MOTION2D_LIBPATH)/$(MOTION2D_LIBNAME)

.KEEP_STATE	:
.PRECIOUS	: $(MOTION2D_LIBNAME)

all install	: directory $(MOTION2D_LIBNAME)
	@echo
	@echo "The Motion2D library is now built in $(MOTION2D_LIBPATH)"
	@echo

directory:
	@if [ ! -d $(MOTION2D_DIR_LIB)/$(OS) ] ;\
	then \
		echo "*" ; \
		echo "* Creation of the $(MOTION2D_DIR_LIB)/$(OS) directory..." ; \
		echo "*" ; \
		mkdir $(MOTION2D_DIR_LIB)/$(OS) ; \
	fi ;
	@if [ ! -d $(MOTION2D_LIBPATH) ] ;\
	then \
		echo "*" ; \
		echo "* Creation of the $(MOTION2D_LIBPATH) directory..." ; \
		echo "*" ; \
		mkdir $(MOTION2D_LIBPATH) ; \
	fi ;

checkup:
	@if [ ! -d $(MOTION2D_LIBPATH) ] ;\
	then \
		echo "*" ; \
		echo "* Error lib: make install before" ; \
		echo "*" ; \
		exit 1; \
	fi ;

MOTION2D_OBJ	=\
		$(MOTION2D_DIR_INTERFACE)/CMotion2D.o	\
		$(MOTION2D_DIR_INTERFACE)/CMotion2DPyramid.o	\
		$(MOTION2D_DIR_INTERFACE)/CMotion2DModel.o	\
		$(MOTION2D_DIR_INTERFACE)/CMotion2DEstimator.o	\
		$(MOTION2D_DIR_INTERFACE)/CMotion2DWarping.o	\
		$(MOTION2D_DIR_ESTIMATION)/RMRmod.o		\
		$(MOTION2D_DIR_ESTIMATION)/irls.o		\
		$(MOTION2D_DIR_ESTIMATION)/weights.o		\
		$(MOTION2D_DIR_ESTIMATION)/estimate.o		\
		$(MOTION2D_DIR_ESTIMATION)/estimate_const.o	\
		$(MOTION2D_DIR_ESTIMATION)/estimate_aff.o	\
		$(MOTION2D_DIR_ESTIMATION)/estimate_quad.o	\
		$(MOTION2D_DIR_ESTIMATION)/para_mvt.o		\
		$(MOTION2D_DIR_ESTIMATION)/variance.o		\
		$(MOTION2D_DIR_ESTIMATION)/covariance.o		\
		$(MOTION2D_DIR_ESTIMATION)/im_spat_temp.o	\
		$(MOTION2D_DIR_ESTIMATION)/mem_est.o		\
		$(MOTION2D_DIR_ESTIMATION)/cog.o		\
		$(MOTION2D_DIR_MEMOIRE)/memoire.o		\
		$(MOTION2D_DIR_PYRAMIDE)/pyramide.o		\
		$(MOTION2D_DIR_PYRAMIDE)/filt_gauss.o		\
		$(MOTION2D_DIR_PYRAMIDE)/multigr.o		\
		$(MOTION2D_DIR_PYRAMIDE)/gradient.o		\
		$(MOTION2D_DIR_MATSYM)/inverse_mat_sym.o	\
		$(MOTION2D_DIR_MATSYM)/resoud_mat_sym.o		\
		$(MOTION2D_DIR_MATSYM)/invert.o			\
		$(MOTION2D_DIR_MATSYM)/mtx_tool.o		\
		$(MOTION2D_DIR_MATSYM)/arithm.o			\
		$(MOTION2D_DIR_COMPENSE)/compense.o		\
		$(MOTION2D_DIR_CPRIM)/acast.o			\
		$(MOTION2D_DIR_CPRIM)/daarith.o			\
		$(MOTION2D_DIR_CPRIM)/damem.o			\
		$(MOTION2D_DIR_CPRIM)/faarith.o			\
		$(MOTION2D_DIR_CPRIM)/fafirf.o			\
		$(MOTION2D_DIR_CPRIM)/fafirf3.o			\
		$(MOTION2D_DIR_CPRIM)/fafirf5.o			\
		$(MOTION2D_DIR_CPRIM)/fafirf7.o			\
		$(MOTION2D_DIR_CPRIM)/famem.o			\
		$(MOTION2D_DIR_CPRIM)/saarith.o			\
		$(MOTION2D_DIR_CPRIM)/ucamem.o			\
		$(MOTION2D_DIR_CPRIM)/uiamem.o			\
		$(MOTION2D_DIR_IMAGE)/Motion2DImage_PNM.o	\
		$(MOTION2D_DIR_IMAGE)/Motion2DImage_PNG.o	\
		$(MOTION2D_DIR_IMAGE)/Motion2DImage_RAW.o	\
		$(MOTION2D_DIR_IMAGE)/CMotion2DVideo_Mpeg2.o	\
		$(MOTION2D_DIR_IMAGE)/CImageReader.o		\
		$(MOTION2D_DIR_IMAGE)/CMpeg2Reader.o		\
		$(MOTION2D_DIR_IMAGE)/CReader.o			\
		$(MOTION2D_DIR_IMAGE)/CImageWriter.o		\
		$(MOTION2D_DIR_IMAGE)/CWriter.o			\
		$(MOTION2D_DIR_IMAGE)/FieldVector.o



$(MOTION2D_LIBNAME) :\
	$(MOTION2D_LIB)($(MOTION2D_OBJ))
	$(RANLIB) $(MOTION2D_LIB)

$(MOTION2D_LIB)(%.o): %.c
	@echo "*"
	@echo "* Add $*.c in library $@ "
	@echo "*"
	$(CXX) $(CXXFLAGS) -c $*.c -o $*.o
	($(AR) $@ $%; rm $%)

$(MOTION2D_LIB)(%.o): %.cpp
	@echo "*"
	@echo "* Add $*.cpp in library $@ "
	@echo "*"
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $*.o
	($(AR) $@ $%; rm $%)

clean:
	rm -f *~ */*~
	rm -f *% */*%
	rm -f *.o */*.o
	rm -f -r ../*/SunWS_cache ../*/*/SunWS_cache
	rm -f -r ../*/ii_files ../*/*/ii_files
	rm -f -r ../*/ti_files ../*/*/ti_files


uninstall:
	rm -f $(MOTION2D_LIB)
	rm -f -r ../*/SunWS_cache ../*/*/SunWS_cache
	rm -f -r ../*/ii_files ../*/*/ii_files
	rm -f -r ../*/ti_files ../*/*/ti_files


# Update the dependencies
$(MOTION2D_LIB)($(MOTION2D_DIR_ESTIMATION)/RMRmod.o): $(INC) \
	$(MOTION2D_DIR_ESTIMATION)/RMRmod.c \
	$(MOTION2D_DIR_ESTIMATION)/RMRmod.h \
	$(MOTION2D_DIR_ESTIMATION)/irls.h \
	$(MOTION2D_DIR_ESTIMATION)/para_mvt.h \
	$(MOTION2D_DIR_ESTIMATION)/weights.h \
	$(MOTION2D_DIR_ESTIMATION)/im_spat_temp.h \
	$(MOTION2D_DIR_ESTIMATION)/variance.h \
	$(MOTION2D_DIR_ESTIMATION)/mem_est.h \
	$(MOTION2D_DIR_PYRAMIDE)/multigr.h
$(MOTION2D_LIB)($(MOTION2D_DIR_ESTIMATION)/irls.o): $(INC) \
	$(MOTION2D_DIR_ESTIMATION)/irls.c \
	$(MOTION2D_DIR_ESTIMATION)/irls.h \
	$(MOTION2D_DIR_ESTIMATION)/para_mvt.h \
	$(MOTION2D_DIR_ESTIMATION)/weights.h \
	$(MOTION2D_DIR_ESTIMATION)/estimate.h
$(MOTION2D_LIB)($(MOTION2D_DIR_ESTIMATION)/weights.o): $(INC) \
	$(MOTION2D_DIR_ESTIMATION)/weights.c \
	$(MOTION2D_DIR_ESTIMATION)/weights.h
$(MOTION2D_LIB)($(MOTION2D_DIR_ESTIMATION)/estimate.o): $(INC) \
	$(MOTION2D_DIR_ESTIMATION)/estimate.c \
	$(MOTION2D_DIR_ESTIMATION)/estimate.h \
	$(MOTION2D_DIR_ESTIMATION)/estimate_const.h \
	$(MOTION2D_DIR_ESTIMATION)/estimate_aff.h \
	$(MOTION2D_DIR_ESTIMATION)/estimate_quad.h \
	$(MOTION2D_DIR_MATSYM)/inverse_mat_sym.h \
	$(MOTION2D_DIR_MATSYM)/resoud_mat_sym.h
$(MOTION2D_LIB)($(MOTION2D_DIR_ESTIMATION)/estimate_const.o): $(INC) \
	$(MOTION2D_DIR_ESTIMATION)/estimate_const.c \
	$(MOTION2D_DIR_ESTIMATION)/estimate_const.h \
	$(MOTION2D_DIR_ESTIMATION)/covariance.h \
	$(MOTION2D_DIR_MATSYM)/inverse_mat_sym.h \
	$(MOTION2D_DIR_MATSYM)/resoud_mat_sym.h
$(MOTION2D_LIB)($(MOTION2D_DIR_ESTIMATION)/estimate_aff.o): $(INC) \
	$(MOTION2D_DIR_ESTIMATION)/estimate_aff.c \
	$(MOTION2D_DIR_ESTIMATION)/estimate_aff.h \
	$(MOTION2D_DIR_ESTIMATION)/covariance.h \
	$(MOTION2D_DIR_MATSYM)/inverse_mat_sym.h \
	$(MOTION2D_DIR_MATSYM)/resoud_mat_sym.h
$(MOTION2D_LIB)($(MOTION2D_DIR_ESTIMATION)/estimate_quad.o): $(INC) \
	$(MOTION2D_DIR_ESTIMATION)/estimate_quad.c \
	$(MOTION2D_DIR_ESTIMATION)/estimate_quad.h \
	$(MOTION2D_DIR_ESTIMATION)/covariance.h \
	$(MOTION2D_DIR_MATSYM)/inverse_mat_sym.h \
	$(MOTION2D_DIR_MATSYM)/resoud_mat_sym.h
$(MOTION2D_LIB)($(MOTION2D_DIR_ESTIMATION)/para_mvt.o): $(INC) \
	$(MOTION2D_DIR_ESTIMATION)/para_mvt.c \
	$(MOTION2D_DIR_ESTIMATION)/para_mvt.h
$(MOTION2D_LIB)($(MOTION2D_DIR_ESTIMATION)/variance.o):$(INC) \
	$(MOTION2D_DIR_ESTIMATION)/variance.c \
	$(MOTION2D_DIR_ESTIMATION)/variance.h
$(MOTION2D_LIB)($(MOTION2D_DIR_ESTIMATION)/covariance.o):$(INC) \
	$(MOTION2D_DIR_ESTIMATION)/covariance.c \
	$(MOTION2D_DIR_ESTIMATION)/covariance.h
$(MOTION2D_LIB)($(MOTION2D_DIR_ESTIMATION)/im_spat_temp.o): $(INC) \
	$(MOTION2D_DIR_ESTIMATION)/im_spat_temp.c \
	$(MOTION2D_DIR_ESTIMATION)/im_spat_temp.h \
	$(MOTION2D_DIR_ESTIMATION)/para_mvt.h
$(MOTION2D_LIB)($(MOTION2D_DIR_ESTIMATION)/mem_est.o): $(INC) \
	$(MOTION2D_DIR_ESTIMATION)/mem_est.c \
	$(MOTION2D_DIR_ESTIMATION)/mem_est.h \
	$(MOTION2D_DIR_MEMOIRE)/memoire.h
$(MOTION2D_LIB)($(MOTION2D_DIR_ESTIMATION)/cog.o): $(INC) \
	$(MOTION2D_DIR_ESTIMATION)/cog.c \
	$(MOTION2D_DIR_ESTIMATION)/cog.h
$(MOTION2D_LIB)($(MOTION2D_DIR_MEMOIRE)/memoire.o): $(INC) \
	$(MOTION2D_DIR_MEMOIRE)/memoire.c \
	$(MOTION2D_DIR_MEMOIRE)/memoire.h
$(MOTION2D_LIB)($(MOTION2D_DIR_PYRAMIDE)/pyramide.o): $(INC) \
	$(MOTION2D_DIR_PYRAMIDE)/pyramide.c \
	$(MOTION2D_DIR_PYRAMIDE)/pyramide.h \
	$(MOTION2D_DIR_PYRAMIDE)/filt_gauss.h \
	$(MOTION2D_DIR_PYRAMIDE)/multigr.h \
	$(MOTION2D_DIR_PYRAMIDE)/gradient.h \
	$(MOTION2D_DIR_MEMOIRE)/memoire.h
$(MOTION2D_LIB)($(MOTION2D_DIR_PYRAMIDE)/filt_gauss.o): $(INC) \
	$(MOTION2D_DIR_PYRAMIDE)/filt_gauss.c \
	$(MOTION2D_DIR_PYRAMIDE)/filt_gauss.h
$(MOTION2D_LIB)($(MOTION2D_DIR_PYRAMIDE)/multigr.o): $(INC) \
	$(MOTION2D_DIR_PYRAMIDE)/multigr.c \
	$(MOTION2D_DIR_PYRAMIDE)/multigr.h\
	$(MOTION2D_DIR_MEMOIRE)/memoire.h
$(MOTION2D_LIB)($(MOTION2D_DIR_PYRAMIDE)/gradient.o): $(INC) \
	$(MOTION2D_DIR_PYRAMIDE)/gradient.c \
	$(MOTION2D_DIR_PYRAMIDE)/gradient.h
$(MOTION2D_LIB)($(MOTION2D_DIR_MATSYM)/inverse_mat_sym.o): $(INC) \
	$(MOTION2D_DIR_MATSYM)/inverse_mat_sym.c \
	$(MOTION2D_DIR_MATSYM)/inverse_mat_sym.h \
	$(MOTION2D_DIR_MATSYM)/invert.h
$(MOTION2D_LIB)($(MOTION2D_DIR_MATSYM)/resoud_mat_sym.o): $(INC) \
	$(MOTION2D_DIR_MATSYM)/resoud_mat_sym.c \
	$(MOTION2D_DIR_MATSYM)/resoud_mat_sym.h\
	$(MOTION2D_DIR_MATSYM)/invert.h
$(MOTION2D_LIB)($(MOTION2D_DIR_MATSYM)/invert.o): \
	$(MOTION2D_DIR_MATSYM)/invert.c \
	$(MOTION2D_DIR_MATSYM)/invert.h
$(MOTION2D_LIB)($(MOTION2D_DIR_MATSYM)/mtx_tool.o): \
	$(MOTION2D_DIR_MATSYM)/mtx_tool.c \
	$(MOTION2D_DIR_MATSYM)/mtx_tool.h
$(MOTION2D_LIB)($(MOTION2D_DIR_MATSYM)/arithm.o): \
	$(MOTION2D_DIR_MATSYM)/arithm.c \
	$(MOTION2D_DIR_MATSYM)/arithm.h

$(MOTION2D_LIB)($(MOTION2D_DIR_INTERFACE)/CMotion2D.o): \
	$(MOTION2D_DIR_INTERFACE)/CMotion2D.cpp \
	$(MOTION2D_DIR_INCLUDE)/CMotion2D.h \
	$(MOTION2D_DIR_INCLUDE)/CImageReader.h \
	$(MOTION2D_DIR_INCLUDE)/CMpeg2Reader.h \
	$(MOTION2D_DIR_INCLUDE)/CImageWriter.h

$(MOTION2D_LIB)($(MOTION2D_DIR_INTERFACE)/CMotion2DEstimator.o): $(INC) \
	$(MOTION2D_DIR_INTERFACE)/CMotion2DEstimator.cpp \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DEstimator.h \
	$(MOTION2D_DIR_INTERFACE)/CMotion2DModel.cpp \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DPyramid.h \
	$(MOTION2D_DIR_PYRAMIDE)/filt_gauss.h \
	$(MOTION2D_DIR_ESTIMATION)/RMRmod.h \
	$(MOTION2D_DIR_ESTIMATION)/cog.h \
	$(MOTION2D_DIR_MEMOIRE)/memoire.h \
	$(MOTION2D_DIR_ESTIMATION)/para_mvt.h \
	$(MOTION2D_DIR_ESTIMATION)/mem_est.h

$(MOTION2D_LIB)($(MOTION2D_DIR_INTERFACE)/CMotion2DModel.o): $(INC) \
	$(MOTION2D_DIR_INTERFACE)/CMotion2DModel.cpp \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DModel.h \
	$(MOTION2D_DIR_COMPENSE)/compense.h \
	$(MOTION2D_DIR_ESTIMATION)/para_mvt.h

$(MOTION2D_LIB)($(MOTION2D_DIR_INTERFACE)/CMotion2DPyramid.o): $(INC) \
	$(MOTION2D_DIR_INTERFACE)/CMotion2DPyramid.cpp \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DPyramid.h \
	$(MOTION2D_DIR_PYRAMIDE)/pyramide.h \
	$(MOTION2D_DIR_PYRAMIDE)/filt_gauss.h \
	$(MOTION2D_DIR_MEMOIRE)/memoire.h

$(MOTION2D_LIB)($(MOTION2D_DIR_INTERFACE)/CMotion2DWarping.o): $(INC) \
	$(MOTION2D_DIR_INTERFACE)/CMotion2DWarping.cpp \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DWarping.h \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DModel.h \
	$(MOTION2D_DIR_ESTIMATION)/para_mvt.h \
	$(MOTION2D_DIR_COMPENSE)/compense.h

$(MOTION2D_LIB)($(MOTION2D_DIR_IMAGE)/Motion2DImage_PNM.o):  \
	$(MOTION2D_DIR_IMAGE)/Motion2DImage_PNM.cpp \
	$(MOTION2D_DIR_INCLUDE)/Motion2DImage_PNM.h
$(MOTION2D_LIB)($(MOTION2D_DIR_IMAGE)/Motion2DImage_RAW.o):  \
	$(MOTION2D_DIR_IMAGE)/Motion2DImage_RAW.cpp \
	$(MOTION2D_DIR_INCLUDE)/Motion2DImage_RAW.h
$(MOTION2D_LIB)($(MOTION2D_DIR_IMAGE)/Motion2DImage_PNG.o):  \
	$(MOTION2D_DIR_IMAGE)/Motion2DImage_PNG.cpp \
	$(MOTION2D_DIR_INCLUDE)/Motion2DImage_PNG.h
$(MOTION2D_LIB)($(MOTION2D_DIR_IMAGE)/FieldVector.o):  \
	$(MOTION2D_DIR_IMAGE)/FieldVector.cpp \
	$(MOTION2D_DIR_INCLUDE)/FieldVector.h \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DModel.h
$(MOTION2D_LIB)($(MOTION2D_DIR_IMAGE)/CMotion2DVideo_Mpeg2.o): \
	$(MOTION2D_DIR_IMAGE)/CMotion2DVideo_Mpeg2.cpp \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DVideo_Mpeg2.h \
	$(MOTION2D_DIR_CONTRIB_MPEG2DEC)/config.h \
	$(MOTION2D_DIR_CONTRIB_MPEG2DEC)/global.h \
	$(MOTION2D_DIR_CONTRIB_MPEG2DEC)/mpeg2dec.h
$(MOTION2D_LIB)($(MOTION2D_DIR_IMAGE)/CReader.o):  \
	$(MOTION2D_DIR_IMAGE)/CReader.cpp \
	$(MOTION2D_DIR_INCLUDE)/CReader.h \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DImage.h \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DImage_base.cpp
$(MOTION2D_LIB)($(MOTION2D_DIR_IMAGE)/CImageReader.o):  \
	$(MOTION2D_DIR_IMAGE)/CImageReader.cpp \
	$(MOTION2D_DIR_INCLUDE)/CImageReader.h \
	$(MOTION2D_DIR_INCLUDE)/CReader.h \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DImage.h \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DImage_base.cpp
$(MOTION2D_LIB)($(MOTION2D_DIR_IMAGE)/CMpeg2Reader.o):  \
	$(MOTION2D_DIR_IMAGE)/CMpeg2Reader.cpp \
	$(MOTION2D_DIR_INCLUDE)/CMpeg2Reader.h \
	$(MOTION2D_DIR_INCLUDE)/CReader.h \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DVideo_Mpeg2.h \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DImage.h \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DImage_base.cpp
$(MOTION2D_LIB)($(MOTION2D_DIR_IMAGE)/CWriter.o):  \
	$(MOTION2D_DIR_IMAGE)/CWriter.cpp \
	$(MOTION2D_DIR_INCLUDE)/CWriter.h \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DImage.h \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DImage_base.cpp
$(MOTION2D_LIB)($(MOTION2D_DIR_IMAGE)/CImageWriter.o):  \
	$(MOTION2D_DIR_IMAGE)/CImageWriter.cpp \
	$(MOTION2D_DIR_INCLUDE)/CImageWriter.h \
	$(MOTION2D_DIR_INCLUDE)/CWriter.h \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DImage.h \
	$(MOTION2D_DIR_INCLUDE)/CMotion2DImage_base.cpp

$(MOTION2D_LIB)($(MOTION2D_DIR_COMPENSE)/compense.o): $(INC) \
	$(MOTION2D_DIR_COMPENSE)/compense.c \
	$(MOTION2D_DIR_COMPENSE)/compense.h
$(MOTION2D_LIB)($(MOTION2D_DIR_CPRIM)/acast.o): \
	$(MOTION2D_DIR_CPRIM)/acast.c $(MOTION2D_DIR_CPRIM)/acast.h
$(MOTION2D_LIB)($(MOTION2D_DIR_CPRIM)/daarith.o): \
	$(MOTION2D_DIR_CPRIM)/daarith.c $(MOTION2D_DIR_CPRIM)/daarith.h
$(MOTION2D_LIB)($(MOTION2D_DIR_CPRIM)/damem.o): \
	$(MOTION2D_DIR_CPRIM)/damem.c $(MOTION2D_DIR_CPRIM)/damem.h
$(MOTION2D_LIB)($(MOTION2D_DIR_CPRIM)/faarith.o): \
	$(MOTION2D_DIR_CPRIM)/faarith.c $(MOTION2D_DIR_CPRIM)/faarith.h
$(MOTION2D_LIB)($(MOTION2D_DIR_CPRIM)/fafirf.o): \
	$(MOTION2D_DIR_CPRIM)/fafirf.c $(MOTION2D_DIR_CPRIM)/fafirf.h
$(MOTION2D_LIB)($(MOTION2D_DIR_CPRIM)/fafirf3.o): \
	$(MOTION2D_DIR_CPRIM)/fafirf3.c $(MOTION2D_DIR_CPRIM)/fafirf3.h
$(MOTION2D_LIB)($(MOTION2D_DIR_CPRIM)/fafirf5.o): \
	$(MOTION2D_DIR_CPRIM)/fafirf5.c $(MOTION2D_DIR_CPRIM)/fafirf5.h
$(MOTION2D_LIB)($(MOTION2D_DIR_CPRIM)/fafirf7.o): \
	$(MOTION2D_DIR_CPRIM)/fafirf7.c $(MOTION2D_DIR_CPRIM)/fafirf7.h
$(MOTION2D_LIB)($(MOTION2D_DIR_CPRIM)/famem.o): \
	$(MOTION2D_DIR_CPRIM)/famem.c $(MOTION2D_DIR_CPRIM)/famem.h
$(MOTION2D_LIB)($(MOTION2D_DIR_CPRIM)/saarith.o): \
	$(MOTION2D_DIR_CPRIM)/saarith.c $(MOTION2D_DIR_CPRIM)/saarith.h
$(MOTION2D_LIB)($(MOTION2D_DIR_CPRIM)/ucamem.o): \
	$(MOTION2D_DIR_CPRIM)/ucamem.c $(MOTION2D_DIR_CPRIM)/ucamem.h
$(MOTION2D_LIB)($(MOTION2D_DIR_CPRIM)/uiamem.o): \
	$(MOTION2D_DIR_CPRIM)/uiamem.c $(MOTION2D_DIR_CPRIM)/uiamem.h


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

IFLAGS		=

CXX		= $(CONF_CXX)
CXXFLAGS	= $(CONF_CXXFLAGS) $(CXXFLAGS_OPT) $(IFLAGS)


INC		=

LOCALPNG_LIB	= $(MOTION2D_LIBPATH)/$(LOCALPNG_LIBNAME)

.KEEP_STATE	:
.PRECIOUS	: $(LOCALPNG_LIBNAME)

all install	: directory $(LOCALPNG_LIBNAME)
	@echo
	@echo "The png library is now built in $(MOTION2D_LIBPATH)"
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


LOCALPNG_OBJ	= readpng.o writepng.o


$(LOCALPNG_LIBNAME) :\
	$(LOCALPNG_LIB)($(LOCALPNG_OBJ))
	$(RANLIB) $(LOCALPNG_LIB)

$(LOCALPNG_LIB)(%.o): %.c
	@echo "*"
	@echo "* Add $*.c in library $@ "
	@echo "*"
	$(CXX) $(CXXFLAGS) -c $*.c -o $*.o
	($(AR) $@ $%; rm $%)

clean:
	rm -f *~
	rm -f *%
	rm -f *.o
	rm -f -r SunWS_cache
	rm -f -r ii_files
	rm -f -r ti_files

uninstall:
	rm -f $(LOCALPNG_LIB)
	rm -f -r ../*/SunWS_cache ../*/*/SunWS_cache
	rm -f -r ../*/ii_files ../*/*/ii_files
	rm -f -r ../*/ti_files ../*/*/ti_files


# Update the dependencies
$(LOCALPNG_LIB)(writepng.o): writepng.c writepng.h
$(LOCALPNG_LIB)(readpng.o): readpng.c readpng.h


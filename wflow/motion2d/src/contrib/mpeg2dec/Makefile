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


IFLAGS		+=  -I. -I./exttypes

CXX		= $(CONF_CXX)
CXXFLAGS	= $(CONF_CXXFLAGS) $(CXXFLAGS_OPT) $(IFLAGS)

MPEG2DEC_LIB	= $(MOTION2D_LIBPATH)/$(MPEG2DEC_LIBNAME)

.KEEP_STATE	:
.PRECIOUS	: $(MPEG2DEC_LIBNAME)


all install	: directory $(MPEG2DEC_LIBNAME)
	@echo
	@echo "The Mpeg2 library is now built in $(MOTION2D_LIBPATH)"
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


# Definition des objets à compiler
MPEG2DEC_OBJ	= motion.o getvlc.o gethdr.o getblk.o getbits.o store.o \
	  	  recon.o spatscal.o idct.o idctref.o display.o systems.o \
	  	  subspic.o verify.o getpic.o mpeg2dec.o \
		  exttypes/dct.o exttypes/mvectors.o

$(MPEG2DEC_LIBNAME) :\
	$(MPEG2DEC_LIB)($(MPEG2DEC_OBJ))
	$(RANLIB) $(MPEG2DEC_LIB)

$(MPEG2DEC_LIB)(%.o): %.cpp
	@echo "*"
	@echo "* Add $*.cpp in library $@ "
	@echo "*"
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $*.o
	($(AR) $@ $%; rm $%)


# Dependances
#$(MPEG2DEC_LIB)(Mpeg2Irisa.o) : Mpeg2Irisa.h mpeg2dec.h config.h global.h
$(MPEG2DEC_LIB)(display.o) : display.cpp config.h global.h mpeg2dec.h
$(MPEG2DEC_LIB)(getbits.o) : getbits.cpp config.h global.h mpeg2dec.h
$(MPEG2DEC_LIB)(getblk.o) : getblk.cpp config.h global.h mpeg2dec.h
$(MPEG2DEC_LIB)(gethdr.o) : gethdr.cpp config.h global.h mpeg2dec.h
$(MPEG2DEC_LIB)(getvlc.o) : getvlc.cpp config.h global.h mpeg2dec.h getvlc.h
$(MPEG2DEC_LIB)(idct.o) : idct.cpp config.h
$(MPEG2DEC_LIB)(idctref.o) : idctref.cpp config.h
$(MPEG2DEC_LIB)(motion.o) : motion.cpp config.h global.h mpeg2dec.h
$(MPEG2DEC_LIB)(recon.o) : recon.cpp config.h global.h mpeg2dec.h
$(MPEG2DEC_LIB)(spatscal.o) : spatscal.cpp config.h global.h mpeg2dec.h
$(MPEG2DEC_LIB)(store.o) : store.cpp config.h global.h mpeg2dec.h
$(MPEG2DEC_LIB)(exttypes/dct.o) : exttypes/dct.cpp
$(MPEG2DEC_LIB)(exttypes/mvectors.o) : exttypes/mvectors.cpp


# additions since July 4, 1994 edition
$(MPEG2DEC_LIB)(getpic.o) : getpic.cpp getpic.h config.h global.h mpeg2dec.h
$(MPEG2DEC_LIB)(mpeg2dec.o) : mpeg2dec.cpp config.h global.h mpeg2dec.h
$(MPEG2DEC_LIB)(systems.o) : systems.cpp config.h global.h mpeg2dec.h
$(MPEG2DEC_LIB)(subspic.o) : subspic.cpp config.h global.h mpeg2dec.h
$(MPEG2DEC_LIB)(verify.o):   verify.cpp config.h global.h mpeg2dec.h


Mpeg2Test : Mpeg2Test.cpp $(MPEG2DEC_LIBNAME)
	@echo "*"
	@echo "* Creation of $@..."
	@echo "*"
	$(CPP) $(CFLAGS) $(CPPFLAGS) -I$(DIR_IMAGE) -I$(DIR_INCLUDE)  \
	-o $(DIR_BIN)/mpegTest.$(OS) Mpeg2Test.cpp\
	-L$(DIR_LIB)  \
	-L$(LIB_PATH) \
	-l$(LIB_MPEG2DECIRISA) -l$(LIB_IMAGE) -l$(LIB_FPNG) -l$(LIB_UTIL)   -lpng -lz -lm


# Menage
clean :
	rm -f *~ *% *.o *.a
	rm -f */*~ */*% */*.o */*.a
	rm -f -r SunWS_cache
	rm -f -r ii_files ti_files

# Suppression de la librairie
uninstall:
	rm -f $(MPEG2DEC_LIB)

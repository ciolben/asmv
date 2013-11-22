# -*- makefile -*-
#
# Main Makefile for building the Motion2D library and examples.
# Read PORTING for instructions how to port Motion2D to a new platform.

RELEASE_DIR  = ../release
RELEASE_NAME  = Motion2D

all install: .buildpath .builddir .buildoutput lib-src lib-contrib bin-examples

lib-contrib:
	cd src/contrib/localpng; $(MAKE)
	cd src/contrib/mpeg2dec; $(MAKE)
	chmod o+rx lib/*
	chmod o+rx lib/*/*
	chmod o+r lib/*/*/*.a

lib-src:
	cd src; $(MAKE)
	chmod o+rx lib/*
	chmod o+rx lib/*/*
	chmod o+r lib/*/*/*.a

bin-examples:
	cd examples; $(MAKE)
	chmod o+rx bin/*
	chmod o+rx bin/*/*

clean:
	rm -f *% */*%
	rm -f *~ */*~
	rm -f .buildpath
	rm -f .builddir
	rm -f .buildoutput
	rm -f */*/*.ilk */*/*.exp
	rm -f -r */Debug */*/Debug
	rm -f -r */Release */*/Release
	rm -f `find -type f -name .nse_depinfo`;\
	rm -f `find -type f -name .make.state`;\
	cd src; $(MAKE) $@
	cd src/contrib/localpng; $(MAKE) $@
	cd src/contrib/mpeg2dec; $(MAKE) $@
	cd examples; $(MAKE) $@

uninstall:
	cd src; $(MAKE) $@
	cd src/contrib/localpng; $(MAKE) $@
	cd src/contrib/mpeg2dec; $(MAKE) $@
	cd examples; $(MAKE) $@

uninstallall:
	$(MAKE) clean;
	$(MAKE) uninstall;
	rm -f -r bin/*
	rm -f -r lib/*
	rm -f src/Makefile
	rm -f examples/Makefile
	rm -f src/contrib/localpng/Makefile
	rm -f src/contrib/mpeg2dec/Makefile

.buildpath: Makefile
	@echo
	@echo '  Motion2D must first be configured using the "configure" script.'
	@echo
	@echo '  The make process will now run this...'
	@echo
	@./configure

.builddir: Makefile
	@echo
	@echo '  Motion2D must first be configured using the "configure" script.'
	@echo
	@echo '  The make process will now run this...'
	@echo
	@./configure

.buildoutput: Makefile
	@echo
	@echo '  Motion2D must first be configured using the "configure" script.'
	@echo
	@echo '  The make process will now run this...'
	@echo
	@./configure


release:
	@echo ""
	@if [ ! -d $(RELEASE_DIR) ]; then \
	  echo "  A $(RELEASE_DIR) directory was created! "; \
	  mkdir $(RELEASE_DIR); \
	fi ;\
	echo -n "  Please enter release number to generate (e.g. 1.3.11): "; \
	read RELEASE_VERSION; \
	echo " ver: $$RELEASE_VERSION";\
	if [ -d $(RELEASE_DIR)/$(RELEASE_NAME)-$${RELEASE_VERSION} ]; then \
	  echo "";\
	  echo "  A release directory \"$(RELEASE_DIR)/$(RELEASE_NAME)-$${RELEASE_VERSION}\" exists! ";\
	  echo "  Before generating a new release you have to suppress it."; \
	  echo -n "  Do you want to suppress it (y|n) : "; \
	  read ANSWER; \
	  if [ $${ANSWER} = "y" ]; then \
	    echo "  Suppress in progress..."; \
	    rm -f -r $(RELEASE_DIR)/$(RELEASE_NAME)-$${RELEASE_VERSION} ;\
	  else \
	    echo -n "  The release was not build !"; \
	    echo "";\
	    exit; \
	  fi; \
	fi; \
	echo "";\
	echo "  A new release directory will be created! ";\
	mkdir $(RELEASE_DIR)/$(RELEASE_NAME)-$${RELEASE_VERSION};\
	mkdir $(RELEASE_DIR)/$(RELEASE_NAME)-$${RELEASE_VERSION}/test;\
	echo "  Copying Motion2D test files...";\
	cp -p -r ../test/sequence $(RELEASE_DIR)/$(RELEASE_NAME)-$${RELEASE_VERSION}/test/ ;\
	rm -f -r $(RELEASE_DIR)/$(RELEASE_NAME)-$${RELEASE_VERSION}/test/sequence/debug ;\
	rm -f -r $(RELEASE_DIR)/$(RELEASE_NAME)-$${RELEASE_VERSION}/test/sequence/raw* ;\
	rm -f -r $(RELEASE_DIR)/$(RELEASE_NAME)-$${RELEASE_VERSION}/test/sequence/pgm ;\
	rm -f -r $(RELEASE_DIR)/$(RELEASE_NAME)-$${RELEASE_VERSION}/test/sequence/ppm ;\
	rm -f -r $(RELEASE_DIR)/$(RELEASE_NAME)-$${RELEASE_VERSION}/test/sequence/png/*.pgm ;\
	cp -p -r ../test/motion   $(RELEASE_DIR)/$(RELEASE_NAME)-$${RELEASE_VERSION}/test/ ;\
	echo "  Copying current Motion2D files before creating tar archive...";\
	cp -p -r * $(RELEASE_DIR)/$(RELEASE_NAME)-$${RELEASE_VERSION};\
	cd $(RELEASE_DIR)/$(RELEASE_NAME)-$${RELEASE_VERSION};\
	./configure ;\
	echo "  Update the online documentation! " ;\
	$(MAKE) online-doc ;\
	echo "  Update the user manual! " ;\
	$(MAKE) usermanual ;\
	cp -p doc/latex/usermanual/usermanual.pdf doc/usermanual.pdf ;\
	$(MAKE) uninstallall ;\
	rm -f `find -type f -name site.cfg`;\
	rm -f `find -type f -name *doxygen* -maxdepth 2`;\
	rm -f `find -type f -name *~`;\
	rm -f `find -type f -name tca.map`;\
	rm -f `find -type f -name .inslog2`;\
	rm -f -r doc/latex ;\
	rm -f -r src/doc ;\
	rm -f -r windows ;\
	rm -f -r examples/Crop.cpp ;\
	rm -f -r examples/MakeDiff.cpp ;\
	rm -f -r examples/Motion2DTest.cpp ;\
	rm -f -r examples/Motion2DTestCropImages.cpp ;\
	rm -f -r examples/Motion2DFrancois.cpp ;\
	rm -f -r examples/Makefile.Exemple ;\
	rm -f -r examples/Makefile.Exemple.mk ;\
	rm -f -r TODO ;\
	rm -f -r TAGS ;\
	rm -f -r compile-computer.sh ;\
	rm -f -r compile-v-debug.sh ;\
	rm -f -r compile-v.sh ;\
	rm -f -r yes ;\
	echo "  Release number is $$RELEASE_VERSION, creating tar archive...";\
	cd .. ;\
	tar cfz $(RELEASE_NAME)-$${RELEASE_VERSION}.tar.gz $(RELEASE_NAME)-$${RELEASE_VERSION} ;\
	echo "" ;\
	echo "  The release is available in: " $(RELEASE_DIR)/$(RELEASE_NAME)-$${RELEASE_VERSION}.tar.gz

#rm -f -r $(RELEASE_NAME)-$${RELEASE_VERSION}

online-doc:
	@echo "Online documentation creation..."
	cd doc; doxygen config.html.doxygen
	cp -p -f src/doc/index.html doc/html/
	cp -p -f src/doc/fra.html doc/html/
	cp -p -f src/doc/index.html doc/html/eng.html
	cp -p -f src/doc/logo-vista3.gif doc/html/
	cp -p -f src/doc/new.gif doc/html/

refmanual:
	@echo "Reference manual creation..."
	cd doc; doxygen config.latex.doxygen ;\
	cd latex/refmanual ;\
	rm -f *.pdf *.dvi *.aux *.toc *.idx *.ind *.ilg *.log *.out ;\
	rm -f refman.ps ;\
	perl -p -i -e "s/clearemptydoublepage/cleardoublepage/" *.tex ;\
	make pdf

usermanual:
	@echo "User manual creation..."
	cd doc/latex/usermanual ;\
	make uninstall ;\
	make pdf

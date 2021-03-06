#
# Toplevel makefile for OS/161.
#
#
# Rules:
#    all (default):  depend, compile, and install system.
#    build:          depend, compile, and install system from scratch.
#    compile:        compile and install binaries.
#    includes:       install header files.
#    tags:           generate/regenerate "tags" files.
#    depend:         update make dependency information.
#    clean:          remove generated files.
#
# The "compile" rule subsumes both compilation and installation,
# because certain parts must be installed before subsequent parts
# can be built. Note that it does *not* install include files.
#
# The "includes" rule installs header files from the kernel and
# libraries into the include directory of the system tree.
#

asst = ASST2
pwd = $(shell pwd)

silent:
	$(MAKE) -s goldteam

goldteam:
	#echo "Running configure...\c"
	#cd os161-1.11 && ./configure --ostree=$(pwd)/root --toolprefix=os161-
	#echo "done."
	echo "Making includes...\c"
	-$(MAKE) includes > /dev/null && \
	echo "done."
	echo "Running assignment config...\c"
	cd os161-1.11/kern/conf && ./config $(asst) > /dev/null && \
	echo "done."
	echo "Making assignment depends...\c"
	cd os161-1.11/kern/compile/$(asst) && $(MAKE) depend > /dev/null && $(MAKE) > /dev/null && $(MAKE) install > /dev/null && \
	echo "done."
	echo "Building user-level utilities and test programs...\c"
	cd os161-1.11 && $(MAKE) > /dev/null
	echo "done."
	echo "Making tests...\c"
	cd os161-1.11/testbin && $(MAKE) > /dev/null && $(MAKE) install > /dev/null && \
	echo "done."
	echo "Making main executable...\c"
	cd os161-1.11 && $(MAKE) > /dev/null && \
	echo "done."

all:
	$(MAKE) includes
	$(MAKE) depend
	$(MAKE) compile

build:
	$(MAKE) clean
	$(MAKE) all

compile:
	(cd lib && $(MAKE))
	(cd lib && $(MAKE) install)
	(cd bin && $(MAKE))
	(cd sbin && $(MAKE))
	(cd testbin && $(MAKE))
	(cd uw-testbin && $(MAKE))
	(cd my-testbin && $(MAKE))
	(cd bin && $(MAKE) install)
	(cd sbin && $(MAKE) install)
	(cd testbin && $(MAKE) install)
	(cd uw-testbin && $(MAKE) install)
	(cd my-testbin && $(MAKE) install)
	(cd man && $(MAKE) install)
	(cd kern && $(MAKE))
	(cd kern && $(MAKE) install)

includes:
	(cd kern && $(MAKE) includes)
	(cd include && $(MAKE) includes)
	(cd lib/hostcompat && $(MAKE) includes)

tags depend clean:
	(cd include && $(MAKE) $@)
	(cd lib && $(MAKE) $@)
	(cd bin && $(MAKE) $@)
	(cd sbin && $(MAKE) $@)
	(cd testbin && $(MAKE) $@)
	(cd uw-testbin && $(MAKE) $@)
	(cd my-testbin && $(MAKE) $@)
	(cd man && $(MAKE) $@)
	(cd kern && $(MAKE) $@)

vclean:
	(cd uw-testbin && $(MAKE) $@)
	(cd my-testbin && $(MAKE) $@)

clean: cleanhere
cleanhere:
	rm -f *~ mk/*~


.PHONY: all build compile includes tags depend clean cleanhere

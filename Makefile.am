# Makefile.am - use automake to generate Makefile.in

AM_CXFLAGS = $(INIT_CFLAGS)

bin_PROGRAMS = compare_package
compare_package_SOURCES = compare_package.c

all:

clean-local:
	$(RM) Makefile
	$(RM) Makefile.in
	$(RM) aclocal.m4
	$(RM) ar-lib
	$(RM) compile
	$(RM) compare_package 
	$(RM) config.*
	$(RM) configure
	$(RM) configure~
	$(RM) depcomp
	$(RM) install-sh
	$(RM) ltmain.sh
	$(RM) libtool
	$(RM) missing 
	$(RM) *.o 
	rm -rf .deps 
	rm -rf .libs
	rm -rf autom4te.cache
	rm -rf m4 

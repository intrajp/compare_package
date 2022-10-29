# Makefile.am - use automake to generate Makefile.in
#
# Copyright (C) 2022 Shintaro Fujiwara 
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301 USA

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

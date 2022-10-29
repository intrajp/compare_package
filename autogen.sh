# autogen.sh - Use to create 'configure'. 
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

#!/bin/sh
# Run this to generate all the initial makefiles, etc.

test -n "$srcdir" || srcdir=`dirname "$0"`
test -n "$srcdir" || srcdir=.
#test -n "$srcdir" || srcdir=./src
test -n "$srcdir" || srcdir=./

olddir=`pwd`
cd $srcdir

AUTORECONF=`which autoconf`
if test -z $AUTORECONF; then
    echo "*** No autoconf found, please install autoconf package. ***"
        exit 1
else
    echo "autoconf is installed. I proceed."
fi

INTLTOOLIZE=`which intltoolize`
if test -z $INTLTOOLIZE; then
        echo "*** No intltoolize found, please install the intltool package. ***"
        exit 1
else
    echo "intltoolize is installed. I proceed."
fi

LIBTOOLIZE=`which libtoolize`
if test -z $LIBTOOLIZE; then
        echo "*** No libtoolize found, please install the libtool package. ***"
        exit 1
else
    echo "libtoolize is installed. I proceed."
fi

MAKE=`which make`
if test -z $MAKE; then
    echo "*** No make found, please install make package. ***"
        exit 1
else
    echo "make is installed. I proceed."
fi


AUTOPOINT='intltoolize --automake --copy' autoreconf --force --install --verbose

cd $olddir
test -n "$NOCONFIGURE" || "$srcdir/configure" "$@"
automake

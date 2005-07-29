#
# Copyright (C) 2004 Cedric Pinson
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#
# Authors:
#  Loic Dachary <loic@gnu.org>
#  Cedric Pinson <cpinson@freesheep.org>
#
# 

# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.54)
AC_INIT(libnoise, 0.9.0)
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE([dist-bzip2 dist-zip])
AM_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_MAKE_SET
AC_GNU_SOURCE
AC_LANG(C++)
AC_PROG_CPP
AC_PROG_CXX
AM_PATH_CCACHE
AC_PROG_LIBTOOL


AC_EXEEXT
AC_OBJEXT

AC_ISC_POSIX
AC_HEADER_STDC
AC_C_INLINE

AC_LANG_SAVE
AC_LANG_CPLUSPLUS
AC_LANG_RESTORE

# Check is STLport is needed
AC_CHECK_NATIVE_STL
if test "$native_stl" != "yes"
then
	AM_PATH_STLPORT
fi

CPPFLAGS="$CPPFLAGS -I/usr/local/include"' -I${top_srcdir}/include'

AC_CONFIG_FILES([Makefile
		 libnoise.pc
	         src/Makefile
		 doc/Makefile
	 ])
AC_OUTPUT

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
#  Cedric Pinson <cpinson@freesheep.org>
#
# 
MAINTAINERCLEANFILES = Makefile.in

lib_LTLIBRARIES = libnoise.la

noiseincludedir = $(includedir)/noise
noiseinclude_HEADERS = $(wildcard *.h)

noisemodelincludedir = $(includedir)/noise/model
noisemodelinclude_HEADERS = $(wildcard model/*.h)

noisemoduleincludedir =	$(includedir)/noise/module
noisemoduleinclude_HEADERS = $(wildcard module/*.h)



libnoise_la_SOURCES = \
	latlon.cpp \
	mathconsts.h \
	noisegen.cpp \
	model/cylinder.cpp \
	model/line.cpp \
	model/plane.cpp \
	model/sphere.cpp \
	module/abs.cpp \
	module/add.cpp \
	module/billow.cpp \
	module/blend.cpp \
	module/cache.cpp \
	module/checkerboard.cpp \
	module/clamp.cpp \
	module/const.cpp \
	module/curve.cpp \
	module/cylinders.cpp \
	module/displace.cpp \
	module/exponent.cpp \
	module/invert.cpp \
	module/max.cpp \
	module/min.cpp \
	module/modulebase.cpp \
	module/multiply.cpp \
	module/perlin.cpp \
	module/power.cpp \
	module/ridgedmulti.cpp \
	module/rotatepoint.cpp \
	module/scalebias.cpp \
	module/scalepoint.cpp \
	module/select.cpp \
	module/spheres.cpp \
	module/terrace.cpp \
	module/translatepoint.cpp \
	module/turbulence.cpp \
	module/voronoi.cpp

libnoise_la_LDFLAGS = -version-info 0:0:0

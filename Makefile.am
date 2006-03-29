#
# Copyright (C) 2004-2006 Mekensleep
#
# Mekensleep
# 24 rue vieille du temple
# 75004 Paris
#       licensing@mekensleep.com
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
#
# 
EXTRA_DIST = \
	config/ccache.m4 bootstrap \
	examples/Makefile.dos \
	include/Makefile.dos \
	lib/Makefile.dos \
	tests/Makefile.dos \
	mktab_astud.vcproj  mktab_evx.vcproj	mktab_lowball.vcproj  poker-eval.vcproj \
	mktab_basic.vcproj  mktab_joker.vcproj	mktab_packed.vcproj \
	poker-eval.sln \
	WHATS-HERE.Java \
	WHATS-HERE \
	$(wildcard gentoo/dev-games/poker-eval/*.ebuild)

SUBDIRS = \
	lib \
	include \
	tests \
	examples

MAINTAINERCLEANFILES = \
	INSTALL \
	Makefile.in \
	aclocal.m4 \
	compile \
	config.guess \
	config.rpath \
	include/stamp-h1 \
	config.sub \
	configure \
	depcomp \
	install-sh \
	ltmain.sh \
	missing \
	mkinstalldirs

DISTCLEANFILES = \
	config.log \
	config.status

pkgconfigdir = ${libdir}/pkgconfig
pkgconfig_DATA = poker-eval.pc

ACLOCAL_AMFLAGS = -I config

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
MAINTAINERCLEANFILES = Makefile.in

INCLUDES = -I$(top_srcdir)/include

EXTRA_DIST = run.in

TESTS = run

check_PROGRAMS = \
	joktest1 \
	enumtest1 \
	enumtest2 \
	enumtest3 \
	enumtest5 \
	enumtest7

joktest1_SOURCES = joktest1.c
joktest1_LDADD = $(top_builddir)/lib/libpoker-eval.la

enumtest1_SOURCES = enumtest1.c
enumtest1_LDADD = $(top_builddir)/lib/libpoker-eval.la

enumtest2_SOURCES = enumtest2.c
enumtest2_LDADD = $(top_builddir)/lib/libpoker-eval.la

enumtest3_SOURCES = enumtest3.c
enumtest3_LDADD = $(top_builddir)/lib/libpoker-eval.la

enumtest5_SOURCES = enumtest5.c
enumtest5_LDADD = $(top_builddir)/lib/libpoker-eval.la

enumtest7_SOURCES = enumtest7.c
enumtest7_LDADD = $(top_builddir)/lib/libpoker-eval.la

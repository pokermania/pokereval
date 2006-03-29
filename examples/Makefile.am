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

EXTRA_DIST = utest1

TESTS = utest1

noinst_PROGRAMS = \
	eval \
	fish \
	five_card_hands \
	hcmp2 \
	hcmpn \
	pokenum \
	seven_card_hands \
	usedecks

eval_SOURCES = eval.c
eval_LDADD = $(top_builddir)/lib/libpoker-eval.la

fish_SOURCES = fish.c
fish_LDADD = $(top_builddir)/lib/libpoker-eval.la

five_card_hands_SOURCES = five_card_hands.c
five_card_hands_LDADD = $(top_builddir)/lib/libpoker-eval.la

hcmp2_SOURCES = hcmp2.c
hcmp2_LDADD = $(top_builddir)/lib/libpoker-eval.la

hcmpn_SOURCES = hcmpn.c
hcmpn_LDADD = $(top_builddir)/lib/libpoker-eval.la

pokenum_SOURCES = pokenum.c
pokenum_LDADD = $(top_builddir)/lib/libpoker-eval.la

seven_card_hands_SOURCES = seven_card_hands.c
seven_card_hands_LDADD = $(top_builddir)/lib/libpoker-eval.la

usedecks_SOURCES = usedecks.c
usedecks_LDADD = $(top_builddir)/lib/libpoker-eval.la


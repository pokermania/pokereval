#
# Copyright (C) 2004 Mekensleep
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

lib_LTLIBRARIES = libpoker-eval.la

EXTRA_DIST = evx_preamble.cfrag

BASIC_TABLES = \
        t_nbits.c t_topbit.c t_topcard.c t_topfivecards.c t_topfivebits.c \
        t_toptwobits.c t_cardmasks.c t_maskrank.c t_straight.c 
JOKER_TABLES = t_jokercardmasks.c t_jokerstraight.c
PACKED_TABLES = \
        t_nbitsandstr.c
EVX_TABLES = \
        t_evx_pairval.c t_evx_strval.c t_evx_tripsval.c t_evx_flushcards.c
ASTUD_TABLES = t_astudcardmasks.c
LOWBALL_TABLES = t_botfivecards.c t_botcard.c t_botfivecardsj.c

libpoker_eval_la_SOURCES = \
	combinations.c \
	deck.c \
	deck_astud.c \
	deck_joker.c \
	deck_std.c \
	enumerate.c \
	enumord.c \
	evx.c \
	lowball.c \
	rules_astud.c \
	rules_joker.c \
	rules_std.c \
	$(BASIC_TABLES) \
	$(JOKER_TABLES) \
	$(PACKED_TABLES) \
	$(EVX_TABLES) \
	$(ASTUD_TABLES) \
	$(LOWBALL_TABLES)

noinst_HEADERS = \
	mktable.h

MKTABLE_HELPERS = mktable.c mktable_utils.c

noinst_PROGRAMS = \
	mktab_basic \
	mktab_joker \
	mktab_packed \
	mktab_evx \
	mktab_astud \
	mktab_lowball \
	evx_gen5 \
	evx_gen7

mktab_basic_SOURCES = mktab_basic.c $(MKTABLE_HELPERS)
mktab_joker_SOURCES = mktab_joker.c $(MKTABLE_HELPERS)
mktab_packed_SOURCES = mktab_packed.c $(MKTABLE_HELPERS)
mktab_evx_SOURCES = mktab_evx.c $(MKTABLE_HELPERS)
mktab_astud_SOURCES = mktab_astud.c $(MKTABLE_HELPERS)
mktab_lowball_SOURCES = mktab_lowball.c $(MKTABLE_HELPERS)
evx_gen5_SOURCES = evx_generate.c 
evx_gen5_CPPFLAGS = -DCARDS_DEALT=5
evx_gen7_SOURCES = evx_generate.c
evx_gen7_CPPFLAGS = -DCARDS_DEALT=7

build_tables: $(noinst_PROGRAMS) evx_preamble.cfrag
	./mktab_basic
	./mktab_joker
	./mktab_packed
	./mktab_evx
	./mktab_astud
	./mktab_lowball
	./evx_gen5 > $(top_srcdir)/include/inlines/evx5.h
	./evx_gen7 > $(top_srcdir)/include/inlines/evx7.h

libpoker_eval_la_LDFLAGS = -version-info 1:0:0

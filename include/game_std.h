/*
 * Copyright (C) 1999-2004 
 *           Brian Goetz <brian@quiotix.com>
 *           Loic Dachary <loic@gnu.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef GAME_STD_H
#define GAME_STD_H

#define DECK_STANDARD
#define RULES_STANDARD

#include "deck_std.h"
#include "rules_std.h"

#undef Hand_EVAL_N
#undef Hand_EVAL_LOW
#undef Hand_EVAL_LOW8

#define Hand_EVAL_N     StdDeck_StdRules_EVAL_N
#define Hand_EVAL_TYPE  StdDeck_StdRules_EVAL_TYPE
#define Hand_EVAL_X5    StdDeck_StdRules_EVAL_X5
#define Hand_EVAL_X7    StdDeck_StdRules_EVAL_X7

#define Hand_EVAL_LOW   StdDeck_Lowball_EVAL
#define Hand_EVAL_LOW8  StdDeck_Lowball8_EVAL

#undef  DECK_STANDARD
#undef  RULES_STANDARD

#endif /* GAME_STD_H */

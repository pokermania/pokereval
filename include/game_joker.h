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
#ifndef GAME_JOKER_H
#define GAME_JOKER_H

#define DECK_JOKER
#define RULES_JOKER

#include "deck_joker.h"
#include "rules_joker.h"

#undef Hand_EVAL_N
#undef Hand_EVAL_TYPE
#undef Hand_EVAL_LOW
#undef Hand_EVAL_LOW8

#define Hand_EVAL_N     JokerDeck_JokerRules_EVAL_N
#define Hand_EVAL_TYPE(m, n)  HandVal_HANDTYPE(Hand_EVAL_N((m), (n)))

#define Hand_EVAL_LOW   JokerDeck_Lowball_EVAL
#define Hand_EVAL_LOW8  JokerDeck_Low8_EVAL

#undef  DECK_JOKER
#undef  RULES_JOKER


#endif /* GAME_JOKER_H */

/*
 * Copyright (C) 2002 Michael Maurer <mjmaurer@yahoo.com>
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
#ifndef __EVAL_JOKER_LOW8_H__
#define __EVAL_JOKER_LOW8_H__

#include "handval_low.h"
#include "deck_joker.h"
#include "inlines/eval_joker_low.h"

static inline LowHandVal 
JokerDeck_Lowball8_EVAL(JokerDeck_CardMask cards, int n_cards) {
  LowHandVal loval;
  loval = JokerDeck_Lowball_EVAL(cards, n_cards);
  if (loval <= LowHandVal_WORST_EIGHT)
    return loval;
  else 
    return LowHandVal_NOTHING;
}

#endif

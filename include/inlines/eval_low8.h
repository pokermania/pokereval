/*
 * Copyright (C) 2002 Michael Maurer <mjmaurer@users.sourceforge.net>
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
#ifndef __EVAL_LOW8_H__
#define __EVAL_LOW8_H__

#include "handval_low.h"

static inline LowHandVal 
StdDeck_Lowball8_EVAL(StdDeck_CardMask cards, int n_cards) {
  uint32 ranks, retval;

  ranks = (StdDeck_CardMask_HEARTS(cards) |
           StdDeck_CardMask_DIAMONDS(cards) |
           StdDeck_CardMask_CLUBS(cards) |
           StdDeck_CardMask_SPADES(cards));
  ranks = Lowball_ROTATE_RANKS(ranks);
  retval = bottomFiveCardsTable[ranks];
  if (retval > 0 && retval <= LowHandVal_WORST_EIGHT)
    return LowHandVal_HANDTYPE_VALUE(StdRules_HandType_NOPAIR) + retval;
  else 
    return LowHandVal_NOTHING;
}

#endif

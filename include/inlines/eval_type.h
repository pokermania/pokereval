/*
 *  eval_type.h: a fast poker hand evaluator -- evaluates only the hand type
 *  Should be small enough to stay in the L1 cache, if we're lucky.  Uses only
 *  one 8K table.  
 *
 *  Copyright (C) 1999 Brian Goetz
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __EVAL_TYPEONLY_H__
#define __EVAL_TYPEONLY_H__

#include "poker_defs.h"

extern uint8 nBitsAndStrTable[StdDeck_N_RANKMASKS];


#define SC StdDeck_CardMask_CLUBS(cards)
#define SD StdDeck_CardMask_DIAMONDS(cards)
#define SH StdDeck_CardMask_HEARTS(cards)
#define SS StdDeck_CardMask_SPADES(cards)

static inline int 
StdDeck_StdRules_EVAL_TYPE( StdDeck_CardMask cards, int n_cards )
{
  uint32 ranks, four_mask=0, three_mask=0, two_mask=0, 
    n_dups, is_st_or_fl = 0;
  uint8 n_ranks;

  ranks = SC | SD | SH | SS;
  n_ranks = nBitsAndStrTable[ranks] & 0x0F;
  n_dups = n_cards - n_ranks;

  if (n_ranks >= 5) {
    if (nBitsAndStrTable[ranks] & 0xF0)
      is_st_or_fl = StdRules_HandType_STRAIGHT;

    if ((nBitsAndStrTable[cards.cards.spades] & 0x0F) >= 5) {
      if (nBitsAndStrTable[cards.cards.spades] & 0xF0) 
        return StdRules_HandType_STFLUSH;
      else
        is_st_or_fl = StdRules_HandType_FLUSH;
    } 
    else if ((nBitsAndStrTable[cards.cards.clubs] & 0x0F) >= 5) {
      if (nBitsAndStrTable[cards.cards.clubs] & 0xF0) 
        return StdRules_HandType_STFLUSH;
      else
        is_st_or_fl = StdRules_HandType_FLUSH;
    } 
    else if ((nBitsAndStrTable[cards.cards.diamonds] & 0x0F) >= 5) {
      if (nBitsAndStrTable[cards.cards.diamonds] & 0xF0) 
        return StdRules_HandType_STFLUSH;
      else
        is_st_or_fl = StdRules_HandType_FLUSH;
    } 
    else if ((nBitsAndStrTable[cards.cards.hearts] & 0x0F) >= 5) {
      if (nBitsAndStrTable[cards.cards.hearts] & 0xF0) 
        return StdRules_HandType_STFLUSH;
      else
        is_st_or_fl = StdRules_HandType_FLUSH;
    } 

    if (is_st_or_fl && n_dups < 3)
      return is_st_or_fl;
  };

  switch (n_dups) {
  case 0:
    return HandType_NOPAIR;
    break;

  case 1:
    return StdRules_HandType_ONEPAIR;
    break;

  case 2:
    two_mask   = ~(SC ^ SD ^ SH ^ SS) & ranks;
    if (!two_mask) 
      return HandType_TRIPS;
    else
      return HandType_TWOPAIR;
    break;

  default:
    four_mask  = (SC&SD) & (SH&SS);
    if (four_mask) 
      return HandType_QUADS;
    three_mask = (( SC&SD )|( SH&SS )) & (( SC&SH )|( SD&SS ));
    if (three_mask) 
      return HandType_FULLHOUSE;
    else if (is_st_or_fl)
      return is_st_or_fl;
    else 
      return HandType_TWOPAIR;

    break;
  };

}

#undef SC
#undef SH
#undef SD
#undef SS

#endif

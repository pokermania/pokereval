/*
 *  eval_type.h: a fast poker hand evaluator -- evaluates only the hand type
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


#define SC cards.cards.clubs
#define SD cards.cards.diamonds
#define SH cards.cards.hearts
#define SS cards.cards.spades

static inline int 
StdRules_EVAL_TYPEONLY( CardMask cards, int n_cards )
{
  uint32 ranks, four_mask=0, three_mask=0, two_mask=0, 
    n_dups, n_ranks, is_straight = 0, is_flush = 0;

  ranks = SC | SD | SH | SS;
  n_ranks = nBitsAndStrTable[ranks] & 0x0F;

  if (n_ranks >= 5) {
    is_straight = nBitsAndStrTable[ranks] & 0xF0;
    if ((nBitsAndStrTable[cards.cards.spades] & 0x0F) >= 5) {
      if (nBitsAndStrTable[cards.cards.spades] & 0xF0) 
        return StdRules_HandType_STFLUSH;
      else
        is_flush = 1;
    } 
    else if ((nBitsAndStrTable[cards.cards.clubs] & 0x0F) >= 5) {
      if (nBitsAndStrTable[cards.cards.clubs] & 0xF0) 
        return StdRules_HandType_STFLUSH;
      else
        is_flush = 1;
    } 
    else if ((nBitsAndStrTable[cards.cards.diamonds] & 0x0F) >= 5) {
      if (nBitsAndStrTable[cards.cards.diamonds] & 0xF0) 
        return StdRules_HandType_STFLUSH;
      else
        is_flush = 1;
    } 
    else if ((nBitsAndStrTable[cards.cards.hearts] & 0x0F) >= 5) {
      if (nBitsAndStrTable[cards.cards.hearts] & 0xF0) 
        return StdRules_HandType_STFLUSH;
      else
        is_flush = 1;
    } 
  };

  n_dups = n_cards - n_ranks;
  if (n_dups < 3) {
    if (is_flush)
      return StdRules_HandType_FLUSH;
    else if (is_straight)
      return StdRules_HandType_STRAIGHT;
  };

  switch (n_dups) {
  case 0:
    break;

  case 1:
    two_mask   = ~(SC ^ SD ^ SH ^ SS) & ranks;
    break;

  case 2:
    two_mask   = ~(SC ^ SD ^ SH ^ SS) & ranks;
    three_mask = (( SC&SD )|( SH&SS )) & (( SC&SH )|( SD&SS ));
    break;

  default:
    four_mask  = SH & SD & SC & SS;
    two_mask   = (~(SC ^ SD ^ SH ^ SS) & ranks) ^ four_mask;
    three_mask = (( SC&SD )|( SH&SS )) & (( SC&SH )|( SD&SS ));
    break;
  };

  if (four_mask) 
    return HandType_QUADS;
  else if (three_mask && (n_dups >= 3)) 
    return HandType_FULLHOUSE;
  else if (is_flush)
    return StdRules_HandType_FLUSH;
  else if (is_straight)
    return StdRules_HandType_STRAIGHT;
  else if (three_mask) 
    return HandType_TRIPS;
  else if (n_dups == 0) 
    return HandType_NOPAIR;
  else if (n_dups == 1) 
    return HandType_ONEPAIR;
  else 
    return HandType_TWOPAIR;
}
#endif

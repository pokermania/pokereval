/*
 *  eval.h: a fast poker hand evaluator
 *
 *  Copyright (C) 1993-99 Clifford T. Matthews, Keith Miyake, Brian Goetz
 *
 *  Cliff wrote the original code.
 *  Keith significantly sped up is_straight, is_three_of_a_kind and is_pair,
 *	made mask_rank_table a real table and added returns to eval.
 *  Brian sped up the whole thing a lot, and made it suitable for use on 
 *      machines without 64-bit support.  
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

#ifndef __EVAL_H__
#define __EVAL_H__

#include "poker_defs.h"

/*
 * When run over seven cards, here are the distribution of hands:
 *        high hand: 23294460
 *             pair: 58627800
 *         two pair: 31433400
 *  three of a kind: 6461620
 *         straight: 6180020
 *            flush: 4047644
 *       full house: 3473184
 *   four of a kind: 224848
 *   straight flush: 41584
 *
 */

static inline HandVal
en__is_flush(CardMask cards, uint32 *flushranks )
{
  if (nBitsTable[cards.cards.spades] >= 5) {
    *flushranks          = cards.cards.spades;
    return HandVal_HANDTYPE_VALUE(StdRules_HandType_FLUSH) 
      + topFiveCardsTable[cards.cards.spades];
  } 
  else if (nBitsTable[cards.cards.clubs] >= 5) {
    *flushranks          = cards.cards.clubs;
    return HandVal_HANDTYPE_VALUE(StdRules_HandType_FLUSH) 
      + topFiveCardsTable[cards.cards.clubs];
  } 
  else if (nBitsTable[cards.cards.diamonds] >= 5) {
    *flushranks          = cards.cards.diamonds;
    return HandVal_HANDTYPE_VALUE(StdRules_HandType_FLUSH) 
      + topFiveCardsTable[cards.cards.diamonds];
  } 
  else if (nBitsTable[cards.cards.hearts] >= 5) {
    *flushranks          = cards.cards.hearts;
    return HandVal_HANDTYPE_VALUE(StdRules_HandType_FLUSH) 
      + topFiveCardsTable[cards.cards.hearts];
  } 
  else 
    return 0;
}

/*
 * is_straight used to check for a straight by masking the ranks with four
 * copies of itself, each shifted one bit with respect to the
 * previous one.  So any sequence of five adjacent bits will still
 * be non-zero, but any gap will result in a zero value.  There's
 * a nice side-effect of leaving the top most bit set so we can use
 * it to set top_card.
 * Now it uses a precomputed lookup table.  
 *
 */

static inline HandVal 
en__is_straight( uint32 ranks )
{
  int st;

  st = straightTable[ranks];
  if (st) 
    return HandVal_HANDTYPE_VALUE(StdRules_HandType_STRAIGHT)
      + HandVal_TOP_CARD_VALUE(st);
  else 
    return 0;

#if 0
    /* Keith's way, which is still pretty good and uses one less table. */
    if ( (ranks2  = ranks & (ranks << 1)) &&
	 (ranks2 &=         (ranks << 2)) &&
	 (ranks2 &=         (ranks << 3)) &&
	 (ranks2 &=         (ranks << 4)) ) {
        retval.eval_t.hand     = StdRules_HandType_STRAIGHT;
        retval.eval_t.top_card = topCardTable[ranks2];
    } else if ((ranks & StdDeck_FIVE_STRAIGHT) ==  StdDeck_FIVE_STRAIGHT) {
        retval.eval_t.hand     = StdRules_HandType_STRAIGHT;
        retval.eval_t.top_card = StdDeck_Ranks_5;
    }
#endif
}


static inline HandVal 
StdDeck_StdRules_EVAL_N( CardMask cards, int n_cards )
{
  HandVal retval, tempeval, tempeval2;
  uint32 ranks, four_mask=0, three_mask=0, two_mask=0, 
    n_dups, n_ranks, flushranks;
    
#define SC cards.cards.clubs
#define SD cards.cards.diamonds
#define SH cards.cards.hearts
#define SS cards.cards.spades

  retval = 0;
  ranks = SC | SD | SH | SS;
  n_ranks = nBitsTable[ranks];
  n_dups = n_cards - n_ranks;
  switch (n_dups)
    {
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

  tempeval = 0;
  tempeval2 = 0;

  if (n_ranks >= 5) {
    retval = en__is_flush(cards, &flushranks);
    if (retval) {
      tempeval = en__is_straight(flushranks);
      if (tempeval) {
        retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_STFLUSH)
          + HandVal_CARDS(tempeval);
        return retval;
      }
    } else
      retval = en__is_straight(ranks);
  };

  if (four_mask) {
    int tc;

    tc = topCardTable[four_mask];
    retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_QUADS)
      + HandVal_TOP_CARD_VALUE(tc)
      + HandVal_SECOND_CARD_VALUE(topCardTable[ranks ^ (1 << tc)]);
    return retval;
  };

  if (three_mask && (n_dups >= 3)) {
    int tc, t;

    retval  = HandVal_HANDTYPE_VALUE(StdRules_HandType_FULLHOUSE);
    tc = topCardTable[three_mask];
    retval += HandVal_TOP_CARD_VALUE(tc);
    t = (two_mask | three_mask) ^ (1 << tc);
    retval += HandVal_SECOND_CARD_VALUE(topCardTable[t]);
    return retval;
  };

  if (retval) /* flush and straight */
    return retval;

  if (three_mask) {
    int t, second;
        
    retval  = HandVal_HANDTYPE_VALUE(StdRules_HandType_TRIPS);
    retval += HandVal_TOP_CARD_VALUE(topCardTable[three_mask]);

    t = ranks ^ three_mask; /* Only one bit set in three_mask */
    second = topCardTable[t];
    retval += HandVal_SECOND_CARD_VALUE(second);
    t ^= (1 << second);
    retval += HandVal_THIRD_CARD_VALUE(topCardTable[t]);
    return retval;
  };

  /* Now, all that's left is pairs, if even that.  */
  switch (n_dups) {
  case 0:
    retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_NOPAIR)
      + topFiveCardsTable[ranks];
    break;
    
  case 1: {
    int t;
    uint32 kickers;

    retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_ONEPAIR)
           + HandVal_TOP_CARD_VALUE(topCardTable[two_mask]);
    t = ranks ^ two_mask;      /* Only one bit set in two_mask */
    /* Get the top five cards in what is left, drop all but the top three 
     * cards, and shift them by one to get the three desired kickers */
    kickers = (topFiveCardsTable[t] >> HandVal_CARD_WIDTH)
            & ~HandVal_FIFTH_CARD_MASK;
    retval += kickers;
  }
  break;

  case 2: {
    int t;
          
    retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_TWOPAIR);
    tempeval = topFiveCardsTable[two_mask]
             & (HandVal_TOP_CARD_MASK 
                | HandVal_SECOND_CARD_MASK);
    retval += tempeval;
    t = ranks ^ two_mask; /* Exactly two bits set in two_mask */
    retval += HandVal_THIRD_CARD_VALUE(topCardTable[t]);
  }
  break;
  
  default: {
    int top, second;
          
    retval = HandVal_HANDTYPE_VALUE(StdRules_HandType_TWOPAIR);
    top = topCardTable[two_mask];
    retval += HandVal_TOP_CARD_VALUE(top);
    second = topCardTable[two_mask ^ (1 << top)];
    retval += HandVal_SECOND_CARD_VALUE(second);
    retval += HandVal_THIRD_CARD_VALUE(topCardTable[ranks ^ (1 << top) 
                                                ^ (1 << second)]);
  }
  break;

  }; /* switch */
  
  return retval;
}

#endif


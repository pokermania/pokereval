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

static inline uint32 
_is_flush(CardMask cards, uint32 *flushranks )
{
    HandVal retval;

    retval.handval_n = 0;

    if (nBitsTable[cards.cards.spades] >= 5) {
        *flushranks          = cards.cards.spades;
        retval.handval.htype = HandType_FLUSH;
        retval.handval_n    += topFiveCardsTable[cards.cards.spades];
    } else if (nBitsTable[cards.cards.clubs   ] >= 5) {
        *flushranks          = cards.cards.clubs;
        retval.handval.htype = HandType_FLUSH;
        retval.handval_n    += topFiveCardsTable[cards.cards.clubs];
    } else if (nBitsTable[cards.cards.diamonds] >= 5) {
        *flushranks          = cards.cards.diamonds;
        retval.handval.htype = HandType_FLUSH;
        retval.handval_n    += topFiveCardsTable[cards.cards.diamonds];
    } else if (nBitsTable[cards.cards.hearts  ] >= 5) {
        *flushranks          = cards.cards.hearts;
        retval.handval.htype = HandType_FLUSH;
        retval.handval_n    += topFiveCardsTable[cards.cards.hearts];
    }

    return retval.handval_n;
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

static inline uint32 
_is_straight( uint32 ranks )
{
    int st;

    st = straightTable[ranks];
    if (st) {
      HandVal retval;

      retval.handval_n        = 0;
      retval.handval.htype    = HandType_STRAIGHT;
      retval.handval.top_card = st;
      return retval.handval_n;
    }
    else 
      return 0;

#if 0
    /* Keith's way, which is still pretty good and uses one less table. */
    if ( (ranks2  = ranks & (ranks << 1)) &&
	 (ranks2 &=         (ranks << 2)) &&
	 (ranks2 &=         (ranks << 3)) &&
	 (ranks2 &=         (ranks << 4)) ) {
        retval.eval_t.hand     = HandType_STRAIGHT;
        retval.eval_t.top_card = topCardTable[ranks2];
    } else if ((ranks & StdDeck_FIVE_STRAIGHT) ==  StdDeck_FIVE_STRAIGHT) {
        retval.eval_t.hand     = HandType_STRAIGHT;
        retval.eval_t.top_card = StdDeck_Ranks_5;
    }
#endif
}


static inline HandVal 
PokerHand_EVAL( CardMask cards, int n_cards )
{
    HandVal retval, tempeval, tempeval2;
    uint32 ranks, four_mask=0, three_mask=0, two_mask=0, 
      n_dups, n_ranks, flushranks;
    
#define SC cards.cards.clubs
#define SD cards.cards.diamonds
#define SH cards.cards.hearts
#define SS cards.cards.spades

    retval.handval_n = 0;
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

    tempeval.handval_n = 0;
    tempeval2.handval_n = 0;

    if (n_ranks >= 5)
      {
        retval.handval_n = _is_flush(cards, &flushranks);
        if (retval.handval_n) {
          tempeval.handval_n = _is_straight(flushranks);
          if (tempeval.handval_n) {
            retval.handval_n = 0;
            retval.handval.htype = HandType_STFLUSH;
            retval.handval.top_card = tempeval.handval.top_card;
/*-->*/     return retval.handval_n;
          }
        } else
          retval.handval_n = _is_straight(ranks);
      };

    if (four_mask) 
      {
        retval.handval_n = 0;
        retval.handval.htype = HandType_QUADS;
        retval.handval.top_card = topCardTable[four_mask];
        retval.handval.second_card = 
          topCardTable[ranks ^ (1 << retval.handval.top_card)];
        return retval.handval_n;
      };

    if (three_mask && (n_dups >= 3)) 
      {
        int t;

        retval.handval_n = 0;
        retval.handval.htype = HandType_FULLHOUSE;
        retval.handval.top_card = topCardTable[three_mask];
        t = (two_mask | three_mask) ^ (1 << retval.handval.top_card);
        retval.handval.second_card = topCardTable[t];
        return retval.handval_n;
      };

    if (retval.handval_n) /* flush and straight */
      return retval.handval_n;

    if (three_mask) 
      {
        int t;
        
        retval.handval.htype = HandType_TRIPS;
        retval.handval.top_card = topCardTable[three_mask];

        t = ranks ^ three_mask; /* Only one bit set in three_mask */
        retval.handval.second_card = topCardTable[t];
        t ^= (1 << retval.handval.second_card);
        retval.handval.third_card = topCardTable[t];
        return retval.handval_n;
      };

    /* Now, all that's left is pairs, if even that.  */
    switch (n_dups)
      {
      case 0:
        retval.handval_n = topFiveCardsTable[ranks];
        retval.handval.htype = HandType_NOPAIR;
        break;
        
      case 1:
        {
          int t;

          retval.handval.htype     = HandType_ONEPAIR;
          retval.handval.top_card = topCardTable[two_mask];
          t = ranks ^ two_mask;      /* Only one bit set in two_mask */
          tempeval.handval_n = topFiveCardsTable[t];
          retval.handval.second_card = tempeval.handval.top_card;
          retval.handval.third_card  = tempeval.handval.second_card;
          retval.handval.fourth_card = tempeval.handval.third_card;
        }
        break;

      case 2:
        {
          int t;
          
          retval.handval.htype = HandType_TWOPAIR;
          tempeval.handval_n = topFiveCardsTable[two_mask];
          retval.handval.top_card    = tempeval.handval.top_card;
          retval.handval.second_card = tempeval.handval.second_card;
          t = ranks ^ two_mask; /* Exactly two bits set in two_mask */
          retval.handval.third_card = topCardTable[t];
        }
        break;

      default:
        {
          int t;
          
          retval.handval.htype = HandType_TWOPAIR;
          retval.handval.top_card = topCardTable[two_mask];
          retval.handval.second_card = 
            topCardTable[two_mask ^ (1 << retval.handval.top_card)];
          t = ranks ^ (1 << retval.handval.top_card)
                    ^ (1 << retval.handval.second_card);
          retval.handval.third_card = topCardTable[t];
        }
        break;
      };

    return retval.handval_n;
}

#endif

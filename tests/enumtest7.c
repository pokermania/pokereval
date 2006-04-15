/*
 * Copyright (C) 1999-2006 
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
/*
 *  test program for eval_n/eval_x5
 */

#include	<stdio.h>
#include	"poker_defs.h"
#include        "inlines/eval.h"
#include	"inlines/evx7.h"

int main( void )
{
  CardMask cards, cards1, peggedCards;
  HandVal handval1, handval2;
  EvxHandVal evxHandVal;

  StdDeck_CardMask_RESET(peggedCards);
  StdDeck_CardMask_SET(peggedCards, 
                       StdDeck_MAKE_CARD(StdDeck_Rank_ACE, 
                                         StdDeck_Suit_DIAMONDS));
  StdDeck_CardMask_SET(peggedCards, 
                       StdDeck_MAKE_CARD(StdDeck_Rank_ACE, 
                                         StdDeck_Suit_HEARTS));
  ENUMERATE_5_CARDS_D(cards, peggedCards, 
                    {
                      StdDeck_CardMask_OR(cards1, cards, peggedCards);
                      handval1 = Hand_EVAL_N(cards1, 7);
                      evxHandVal = Hand_EVAL_X7(CardMask_CLUBS(cards1), 
                                                CardMask_DIAMONDS(cards1),
                                                CardMask_HEARTS(cards1),
                                                CardMask_SPADES(cards1));
                      handval2 = EvxHandVal_toHandVal(evxHandVal);
                      if (handval1 != handval2)
                        {
                          fprintf(stderr, "eval_n() and eval_x7() disagree\n");
                          printf("0\n");
                          Deck_printMask(cards);                        
                          printf(": ");                                 
                          HandVal_print(handval1);                  
                          printf(", ");
                          HandVal_print(handval2);                  
                          printf("\n");                                 
                          exit(0);
                        }
		      printf("%d %d %d %d %d %d\n", 
			     HandVal_HANDTYPE(handval1),
			     HandVal_TOP_CARD(handval1),
			     HandVal_SECOND_CARD(handval1),
			     HandVal_THIRD_CARD(handval1),
			     HandVal_FOURTH_CARD(handval1),
			     HandVal_FIFTH_CARD(handval1));
                    });
  exit(0);
}



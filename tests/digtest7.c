/*
 *  digtest7: test program for eval_n/eval_x7; computes MD5 checksum
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


#include	<stdio.h>
#include	"poker_defs.h"
#include        "inlines/eval.h"
#include	"inlines/evx7.h"
#include        "md5c.h"


int main( void )
{
  CardMask cards, cards1, peggedCards;
  HandVal handval1, handval2;
  EvxHandVal evxHandVal;
  Md5Context ctx;
  Md5RawDigest raw;
  Md5CodedDigest coded;
  unsigned char hashvals[6];


  ctx = MD5Begin();
  StdDeck_stringToMask("Ad Ah", &peggedCards);
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
                      
                      hashvals[0] = HandVal_HANDTYPE(handval1);
                      hashvals[1] = HandVal_TOP_CARD(handval1);
                      hashvals[2] = HandVal_SECOND_CARD(handval1);
                      hashvals[3] = HandVal_THIRD_CARD(handval1);
                      hashvals[4] = HandVal_FOURTH_CARD(handval1);
                      hashvals[5] = HandVal_FIFTH_CARD(handval1);
                      MD5DigestBytes(ctx, hashvals, 6);
                    });
  MD5End(ctx, raw);
  MD5EncodeDigest(raw, coded);
  printf("%s\n", coded);
  exit(0);
}




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
  StdRules_HandVal handval1, handval2;
  EvxHandVal evxHandVal;
  Md5Context ctx;
  Md5RawDigest raw;
  Md5CodedDigest coded;
  unsigned char hashvals[6];


  ctx = MD5Begin();
  StdDeck_stringToMask("Ad Ah", &peggedCards);
  ENUMERATE_5_CARDS(cards, 
                    {
                      StdDeck_CardMask_OR(cards1, cards, peggedCards);
                      handval1 = StdRules_HANDEVAL(cards1, 7);
                      evxHandVal = StdRules_EVAL_X7(cards1.cards.clubs, 
                                                    cards1.cards.diamonds,
                                                    cards1.cards.hearts,
                                                    cards1.cards.spades);
                      handval2 = EvxHandVal_toHandVal(evxHandVal);
                      if (handval1.handval_n != handval2.handval_n)
                        {
                          fprintf(stderr, "eval_n() and eval_x7() disagree\n");
                          printf("0\n");
                          Deck_printMask(cards);                        
                          printf(": ");                                 
                          Rules_printHandval(handval1);                  
                          printf(", ");
                          Rules_printHandval(handval2);                  
                          printf("\n");                                 
                          exit(0);
                        }
                      
                      hashvals[0] = handval1.handval.htype;
                      hashvals[1] = handval1.handval.top_card;
                      hashvals[2] = handval1.handval.second_card;
                      hashvals[3] = handval1.handval.third_card;
                      hashvals[4] = handval1.handval.fourth_card;
                      hashvals[5] = handval1.handval.fifth_card;
                      MD5DigestBytes(ctx, hashvals, 6);
                    });
  MD5End(ctx, raw);
  MD5EncodeDigest(raw, coded);
  printf("%s\n", coded);
  exit(0);
}



/*
 *  digtest5: test program for eval_n/eval_x5; computes MD5 checksum
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
#include	"inlines/evx5.h"
#include        "md5c.h"


int main( void )
{
  CardMask cards;
  StdRules_HandVal handval1, handval2;
  EvxHandVal evxHandVal;
  Md5Context ctx;
  Md5RawDigest raw;
  Md5CodedDigest coded;
  unsigned char hashvals[6];

  ctx = MD5Begin();
  ENUMERATE_5_CARDS(cards, 
                    {
                      handval1 = StdRules_HANDEVAL(cards, 5);
                      evxHandVal = StdRules_EVAL_X5(cards.cards.clubs, 
                                                    cards.cards.diamonds,
                                                    cards.cards.hearts,
                                                    cards.cards.spades);
                      handval2 = EvxHandVal_toHandVal(evxHandVal);
                      if (handval1 != handval2)
                        {
                          fprintf(stderr, "eval_n() and eval_x5() disagree\n");
                          printf("0\n");
                          Deck_printMask(cards);                        
                          printf(": ");                                 
                          Rules_printHandval(handval1);                  
                          printf(", ");
                          Rules_printHandval(handval2);                  
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



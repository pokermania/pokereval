/*
 *  hcmp2.c: a program to compare two pairs of hold'em hole cards at any
 *           point of the game (pre-flop, on the flop, turn or river).
 *              
 *  Example:
 *
 *      hcmp2  tc ac  3h ah  8c 6h 7h
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

#include <stdio.h>
#include <stdlib.h>

#include "poker_defs.h"
#include "inlines/eval.h"

int gNCommon, gNDead;
CardMask gDeadCards, gCommonCards, gPlayerCards[2];


static void
parseArgs(int argc, char **argv) {
  int i, seenCards = 0, count = 0;
  StdDeck_CardMask c;

  for (i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if (seenCards) goto error;
      if (strcmp(argv[i], "-d") == 0) {
	if (++i == argc) goto error;
        if (StdDeck_stringToMask(argv[i], &c) != 1)
          goto error;
        ++gNDead;
        StdDeck_CardMask_OR(gDeadCards, gDeadCards, c);
      } 
      else 
        goto error;
    } else {
      if (StdDeck_stringToMask(argv[i], &c) != 1)
        goto error;
      if (count < 2) 
        StdDeck_CardMask_OR(gPlayerCards[0], gPlayerCards[0], c);
      else if (count < 4) 
        StdDeck_CardMask_OR(gPlayerCards[1], gPlayerCards[1], c);
      else {
        StdDeck_CardMask_OR(gCommonCards, gCommonCards, c);
        ++gNCommon;
      };
      ++count;
    }
  }
  if (count < 4) goto error;
  if (gNCommon > 5) goto error;

  return;

 error:
  fprintf(stderr, "Usage: hcmp2 [ -d dead-card ] p1-cards p2-cards [ common-cards ]\n");
  exit(0);
}


int main( int argc, char *argv[] )
{
  CardMask cards, p0, p1, c0, c1;
  HandVal h0, h1;
  int h0_count=0, h1_count=0, tie_count=0, count=0;

  CardMask_RESET(gDeadCards);
  CardMask_RESET(gCommonCards);
  CardMask_RESET(gPlayerCards[0]);
  CardMask_RESET(gPlayerCards[1]);
  parseArgs(argc, argv);

  CardMask_OR(p0, gPlayerCards[0], gCommonCards);
  CardMask_OR(p1, gPlayerCards[1], gCommonCards);

  ENUMERATE_N_CARDS_D(cards, 5-gNCommon, gDeadCards, 
                      {
                        ++count;
                        CardMask_OR(c0, p0, cards);
                        h0 = PokerHand_EVAL_N(c0, 7);
                        CardMask_OR(c1, p1, cards);
                        h1 = PokerHand_EVAL_N(c1, 7);

                        if (h0 > h1)
			  ++h0_count;
                        else if (h1 > h0)
			  ++h1_count;
                        else
			  ++tie_count;
                      }
                      );

  printf("%d boards", count);
  if (gNCommon > 0) {
    printf(" containing ");
    Deck_printMask(gCommonCards);
  };
  if (gNDead) {
    printf(" with ");
    Deck_printMask(gDeadCards);
    printf(" removed");
  };
  printf("\n");
  printf("  cards      win  %%win       loss  %%lose       tie  %%tie      EV\n");
  printf("  ");
  Deck_printMask(gPlayerCards[0]);
  printf("  %7d %6.2f   %7d %6.2f   %7d %6.2f     %5.3f\n", 
         h0_count, 100.0*h0_count/count, 
         h1_count, 100.0*h1_count/count, 
         tie_count, 100.0*tie_count/count, 
         (1.0*h0_count + (tie_count/2.0)) / count);

  printf("  ");
  Deck_printMask(gPlayerCards[1]);
  printf("  %7d %6.2f   %7d %6.2f   %7d %6.2f     %5.3f\n", 
         h1_count, 100.0*h1_count/count, 
         h0_count, 100.0*h0_count/count, 
         tie_count, 100.0*tie_count/count, 
         (1.0*h1_count + (tie_count/2.0)) / count);
  return 0;
}

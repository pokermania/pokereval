/*
 *  hcmp2.c: a program to compare n pairs of hold'em hole cards at any
 *           point of the game (pre-flop, on the flop, turn or river).
 *              
 *  Example:
 *
 *      hcmpn  tc ac  3h ah  2h 2d -- 8c 6h 7h
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

#define MAX_PLAYERS 22

int gNCommon, gNDead, gNPlayers;
CardMask gDeadCards, gCommonCards, gPlayerCards[MAX_PLAYERS];


static void
parseArgs(int argc, char **argv) {
  int i, seenCards = 0, seenSep = 0, cardCount = 0;
  StdDeck_CardMask c;

  for (i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if (strcmp(argv[i], "-d") == 0) {
        if (seenCards) goto error;
	if (++i == argc) goto error;
        if (StdDeck_stringToMask(argv[i], &c) != 1)
          goto error;
        ++gNDead;
        StdDeck_CardMask_OR(gDeadCards, gDeadCards, c);
      } 
      else if (!strcmp(argv[i], "--"))
        seenSep = 1;
      else
        goto error;
    } else {
      if (StdDeck_stringToMask(argv[i], &c) != 1)
        goto error;
      seenCards = 1;
      if (seenSep) {
        StdDeck_CardMask_OR(gCommonCards, gCommonCards, c);
        ++gNCommon;
      }
      else {
        int i = cardCount / 2;
        StdDeck_CardMask_OR(gPlayerCards[i], gPlayerCards[i], c);
        gNPlayers = i+1;
        ++cardCount;
      };
    }
  }
  if (gNPlayers < 2) goto error;
  if (gNCommon > 5) goto error;

  return;

 error:
  fprintf(stderr, "Usage: hcmp2 [ -d dead-card ] p1-cards .. pn-cards [ -- common-cards ]\n");
  exit(0);
}


int main( int argc, char *argv[] )
{
  CardMask deadCards, cards, playerCards[MAX_PLAYERS], pCards;
  HandVal handval[MAX_PLAYERS], maxHand;
  int i;
  unsigned long winCount[MAX_PLAYERS], loseCount[MAX_PLAYERS], 
    tieCount[MAX_PLAYERS], handCount=0, nWinners;
  float ev[MAX_PLAYERS];

  CardMask_RESET(gDeadCards);
  CardMask_RESET(gCommonCards);
  
  for (i=0; i<MAX_PLAYERS; i++) {
    CardMask_RESET(gPlayerCards[i]);
    winCount[i] = 0;
    tieCount[i] = 0;
    loseCount[i] = 0;
    ev[i] = 0;
  };
  parseArgs(argc, argv);
  
  deadCards = gDeadCards;
  for (i=0; i<gNPlayers; i++) {
    CardMask_OR(playerCards[i], gPlayerCards[i], gCommonCards);
    CardMask_OR(deadCards, deadCards, playerCards[i]);
  };

  ENUMERATE_N_CARDS_D(cards, 5-gNCommon, deadCards, 
                      {
                        ++handCount;
                        nWinners = 0;
                        maxHand = HandVal_NOTHING;
                        for (i=0; i<gNPlayers; i++) {
                          CardMask_OR(pCards, playerCards[i], cards);
                          handval[i] = Hand_EVAL_N(pCards, 7);
                          if (handval[i] > maxHand) {
                            nWinners = 1;
                            maxHand = handval[i];
                          }
                          else if (handval[i] == maxHand) 
                            ++nWinners;
                        };

                        for (i=0; i<gNPlayers; i++) {
                          if (handval[i] == maxHand) {
                            if (nWinners == 1) {
                              ++winCount[i];
                              ev[i] += 1.0;
                            }
                            else {
                              ++tieCount[i];
                              ev[i] += (1.0 / nWinners);
                            };
                          }
                          else
                            ++loseCount[i];
                        }
                      }
                      );

  printf("%ld boards", handCount);
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
  for (i=0; i<gNPlayers; i++) {
    printf("  ");
    Deck_printMask(gPlayerCards[i]);
    printf("  %7ld %6.2f   %7ld %6.2f   %7ld %6.2f     %5.3f\n", 
           winCount[i], 100.0*winCount[i]/handCount, 
           loseCount[i], 100.0*loseCount[i]/handCount, 
           tieCount[i], 100.0*tieCount[i]/handCount, 
           ev[i] / handCount);
  };

  return 0;
  }

/* 
 * fish.h
 * Copyright 1999 Brian Goetz
 * 
 * An example program for the poker hand evaluation library.
 * It is so named because it performs the same action as a program written 
 * by Roy Hashimoto a long time ago.  
 * 
 * Given a (possibly empty) set of input cards, a (possibly empty)
 * set of dead cards, and the number of cards in a hand, this program
 * computes the distribution of each type of possible hand type after
 * exhaustively enumerating the set of possible hands which include the input
 * cards and exclude the dead cards.  
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
 */

#include <stdio.h>
#include <stdlib.h>
#include "poker_defs.h"
#include "inlines/eval.h"

int gNCards, gNPegged;
CardMask gDeadCards, gPeggedCards;

static void
parseArgs(int argc, char **argv) {
  int i, seenCards = 0;
  CardMask c;

  for (i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if (seenCards) goto error;
      if (strcmp(argv[i], "-n") == 0) {
	if (++i == argc) goto error;
	gNCards = atoi(argv[i]);
      } 
      else if (strcmp(argv[i], "-d") == 0) {
	if (++i == argc) goto error;
        if (Deck_stringToMask(argv[i], &c) != 1)
          goto error;
        CardMask_OR(gDeadCards, gDeadCards, c);
      } 
      else 
        goto error;
    } else {
      if (Deck_stringToMask(argv[i], &c) != 1)
        goto error;
      CardMask_OR(gPeggedCards, gPeggedCards, c);
      ++gNPegged;
    }
  }

  return;

 error:
  fprintf(stderr, "Usage: fish [ -d dead-card ] [-n n_cards] [ cards ]\n");
  exit(0);
}


uint32 totals[HandType_COUNT];

static void dump_totals(void) {
  int i;
  
  for (i = HandType_FIRST; i < HandType_COUNT; i++)
    printf("%s:  %d\n", handTypeNamesPadded[i], totals[i]);
}

int 
main(int argc, char **argv) {
  CardMask hand, cards;
  HandVal handval;

  gNCards = 7;
  CardMask_RESET(gDeadCards);
  CardMask_RESET(gPeggedCards);
  parseArgs(argc, argv);

  Deck_printMask(gPeggedCards);

  ENUMERATE_N_CARDS_D(cards, (gNCards-gNPegged), gDeadCards, 
                      {
                        CardMask_OR(hand, cards, gPeggedCards);
                        handval = Hand_EVAL_N(hand, gNCards);
                        ++totals[HandVal_HANDTYPE(handval)];
                      });
  dump_totals();
  return 0;
}

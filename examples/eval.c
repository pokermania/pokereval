/* 
 * eval.c
 * Copyright 1999 Brian Goetz
 * 
 * An example program for the poker hand evaluation library.
 * All it does is evaluate the hand given on the command line
 * and print out the value. 
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

int gNCards;
CardMask gCards;

static void
parseArgs(int argc, char **argv) {
  int i;
  CardMask c;

  for (i = 1; i < argc; ++i) {
    if (Deck_stringToMask(argv[i], &c) != 1)
      goto error;
    CardMask_OR(gCards, gCards, c);
    ++gNCards;
  }
  
  return;

 error:
  fprintf(stderr, "Usage: eval cards \n");
  exit(0);
}


int 
main(int argc, char **argv) {
  HandVal handval;

  gNCards = 0;
  CardMask_RESET(gCards);
  parseArgs(argc, argv);

  handval = Hand_EVAL_N(gCards, gNCards);

  Deck_printMask(gCards);
  printf(": ");                                 
  HandVal_print(handval);                  
  printf("\n");                                 

  return 0;
}

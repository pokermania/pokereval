/*
 *  five_card_hands.c: Enumerate and tabulate five-card hands
 *
 *  Copyright (C) 1993-99 Clifford T. Matthews, Brian Goetz
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
#include	<signal.h>
#include	"poker_defs.h"
#include	"inlines/eval.h"

/* #define VERBOSE */

uint32 totals[HandType_COUNT];


void dump_totals(void) {
  int i;
  
  for (i = HandType_FIRST; i < HandType_COUNT; i++)
    printf("%s:  %d\n", handTypeNamesPadded[i], totals[i]);
}


#ifdef VERBOSE
#define DUMP_HAND do {                          \
  Deck_printMask(cards);                        \
  printf(": ");                                 \
  Rules_printHandval(handval);                  \
  printf("\n");                                 \
} while (0)
#else
#define DUMP_HAND do { } while (0)
#endif

int main( void )
{
  CardMask cards;
  HandVal  handval;

  ENUMERATE_5_CARDS(cards, 
                    {
                      handval = PokerHand_EVAL_N(cards, 5);
                      ++totals[handval.handval.htype];
                      DUMP_HAND;
                    });

  dump_totals();
  exit(0);
}

/* $Id$ */

#include <stdio.h>
#include <stdlib.h>
#include "poker_defs.h"
#include "enumerate.h"

int main() {
  StdDeck_CardMask set_var[2];
  int num_sets = 2;
  int set_sizes[2] = {2, 1};
  StdDeck_CardMask dead_cards;
  int i;
  
  StdDeck_CardMask_RESET(dead_cards);
  for (i=0; i<39; i++) /* remove three suits to reduce output */
    StdDeck_CardMask_SET(dead_cards, i);
  DECK_ENUMERATE_COMBINATIONS_D(StdDeck, set_var, num_sets,
                                set_sizes, dead_cards,
  { 
    for (i=0; i<num_sets; i++) { 
      printf("%s | ", DmaskString(StdDeck, set_var[i])); 
    } 
    printf("\n"); 
  } 
    );
  return 0;
}

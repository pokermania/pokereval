#include <stdio.h>
#include "poker_defs.h"


int
GenericDeck_maskToString(Deck *deck, void *cardMask, char *outString) {
  int cards[50], n, i;
  char *p;

  n = (*deck->maskToCards)(cardMask, cards);
  
  p = outString;
  for (i=0; i<n; i++) {
    if (i > 0) 
      *p++ = ' ';
    p += (*deck->cardToString)(cards[i], p);
  };
  *p = '\0';
  return (outString - p);
}


int 
GenericDeck_printMask(Deck *deck, void *cardMask) {
  char outString[150];
  int r;

  r = GenericDeck_maskToString(deck, cardMask, outString);
  printf("%s", outString);
  return r;
}


char *
GenericDeck_maskString(Deck *deck, void *cardMask) {
  static thread char outString[150];

  GenericDeck_maskToString(deck, cardMask, outString);
  return outString;
}


char *
GenericDeck_cardString(Deck *deck, int cardIndex) {
  static thread char outString[16];

  (*deck->cardToString)(cardIndex, outString);
  return outString;
}


int
GenericDeck_printCard(Deck *deck, int cardIndex) {
  char outString[16];
  int ret;

  ret = (*deck->cardToString)(cardIndex, outString);
  if (ret) 
    printf("%s", outString);
  return ret;
}



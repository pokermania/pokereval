#include <stdio.h>
#include "poker_defs.h"

const char StdDeck_rankChars[] = "23456789TJKQA";
const char StdDeck_suitChars[] = "hdcs";

int 
StdDeck_cardToString(int cardIndex, char *outString) {
  *outString++ = StdDeck_rankChars[StdDeck_RANK(cardIndex)];
  *outString++ = StdDeck_suitChars[StdDeck_SUIT(cardIndex)];
  *outString   = '\0';

  return 2;
}


int
StdDeck_maskToString(StdDeck_CardMask cardMask, char *outString) {
  int i;
  char *p = outString;

  for (i=StdDeck_N_CARDS-1; i >= 0; i--) {
    if (StdDeck_CardMask_CARD_IS_SET(cardMask, i)) {
      if (p > outString) *p++ = ' ';
      *p++ = StdDeck_rankChars[StdDeck_RANK(i)];
      *p++ = StdDeck_suitChars[StdDeck_SUIT(i)];
    };
  };

  *p = '\0';
  return p - outString;
}


int
StdDeck_printCard(int cardIndex) {
  char buffer[80];
  int n;

  n = StdDeck_cardToString(cardIndex, buffer);
  printf("%s", buffer);
  return n;
}

int 
StdDeck_printMask(StdDeck_CardMask cardMask) {
  char buffer[80];
  int n;

  n = StdDeck_maskToString(cardMask, buffer);
  printf("%s", buffer);
  return n;
}


#if 0
int 
StdDeck_stringToMask(char *inString, StdDeck_CardMask outMask) {
  return 0;
}

int 
StdDeck_CardMask_nBitsSet(StdDeck_CardMask cards) {
  return 0;
}
#endif

#include <stdio.h>
#include <ctype.h>
#include "poker_defs.h"

const char StdDeck_rankChars[] = "23456789TJQKA";
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


int 
StdDeck_stringToMask(char *inString, StdDeck_CardMask *outMask) {
  char *p;
  int n=0, rank, suit, card;

  StdDeck_CardMask_RESET(*outMask);
  for (p=inString; p < inString + strlen(inString); p++) {
    if (*p == ' ')
      continue;
    for (rank=0; rank < StdDeck_Rank_COUNT; rank++) 
      if (StdDeck_rankChars[rank] == toupper(*p))
        break;
    if (rank == StdDeck_Rank_COUNT)
      break;
    ++p;
    for (suit=0; suit < StdDeck_Suit_COUNT; suit++) 
      if (StdDeck_suitChars[suit] == tolower(*p))
        break;
    if (suit == StdDeck_Suit_COUNT)
      break;
    ++p;
    card = StdDeck_MAKE_CARD(rank, suit);
    StdDeck_CardMask_SET(*outMask, card);
    ++n;
  }
    
  return n;
}

#if 0
int 
StdDeck_CardMask_nBitsSet(StdDeck_CardMask cards) {
  return 0;
}
#endif

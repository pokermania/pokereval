#include <stdio.h>
#include <ctype.h>
#include "poker_defs.h"
#include "astuddeck.h"

const char AStudDeck_rankChars[] = "xxxxx789TJQKA";
const char AStudDeck_suitChars[] = "hdcs";

int 
AStudDeck_cardToString(int cardIndex, char *outString) {
  *outString++ = AStudDeck_rankChars[AStudDeck_RANK(cardIndex)];
  *outString++ = AStudDeck_suitChars[AStudDeck_SUIT(cardIndex)];
  *outString   = '\0';

  return 2;
}


int
AStudDeck_maskToString(AStudDeck_CardMask cardMask, char *outString) {
  int i;
  char *p = outString;

  for (i=AStudDeck_N_CARDS-1; i >= 0; i--) {
    if (AStudDeck_CardMask_CARD_IS_SET(cardMask, i)) {
      if (p > outString) *p++ = ' ';
      p += StdDeck_cardToString(i, p);
    };
  };

  *p = '\0';
  return p - outString;
}


int
AStudDeck_printCard(int cardIndex) {
  char buffer[80];
  int n;

  n = AStudDeck_cardToString(cardIndex, buffer);
  printf("%s", buffer);
  return n;
}

int 
AStudDeck_printMask(AStudDeck_CardMask cardMask) {
  char buffer[80];
  int n;

  n = AStudDeck_maskToString(cardMask, buffer);
  printf("%s", buffer);
  return n;
}


int 
AStudDeck_stringToMask(char *inString, AStudDeck_CardMask *outMask) {
  char *p;
  int n=0, rank, suit, card;

  AStudDeck_CardMask_RESET(*outMask);
  for (p=inString; p < inString + strlen(inString); p++) {
    if (*p == ' ')
      continue;
    for (rank=AStudDeck_Rank_FIRST; rank <= AStudDeck_Rank_LAST; rank++) 
      if (AStudDeck_rankChars[rank] == toupper(*p))
        break;
    if (rank > AStudDeck_Rank_LAST)
      break;
    ++p;
    for (suit=AStudDeck_Suit_FIRST; suit <= AStudDeck_Suit_LAST; suit++) 
      if (AStudDeck_suitChars[suit] == tolower(*p))
        break;
    if (suit > AStudDeck_Suit_LAST)
      break;
    ++p;
    card = AStudDeck_MAKE_CARD(rank, suit);
    AStudDeck_CardMask_SET(*outMask, card);
    ++n;
  }
    
  return n;
}




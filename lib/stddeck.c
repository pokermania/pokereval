#include <stdio.h>
#include "poker_defs.h"

static const char rankChars[] = "23456789TJKQA";
static const char suitChars[] = "hdcs";

int 
StdDeck_cardToString(int cardIndex, char *outString) {
  *outString++ = rankChars[StdDeck_RANK(cardIndex)];
  *outString++ = suitChars[StdDeck_SUIT(cardIndex)];

  return 2;
}


int
StdDeck_maskToString(CardMask cardMask, char *outString) {
  int c;
  char *p = outString;

  while (cardMask.cards.spades != 0) {
    c = topCardTable[cardMask.cards.spades];
    cardMask.cards.spades ^= (1 << c);
    if (p > outString) *p++ = ' ';
    *p++ = rankChars[c];
    *p++ = suitChars[StdDeck_Suit_SPADES];
  };

  while (cardMask.cards.hearts != 0) {
    c = topCardTable[cardMask.cards.hearts];
    cardMask.cards.diamonds ^= (1 << c);
    if (p > outString) *p++ = ' ';
    *p++ = rankChars[c];
    *p++ = suitChars[StdDeck_Suit_HEARTS];
  };

  while (cardMask.cards.diamonds != 0) {
    c = topCardTable[cardMask.cards.diamonds];
    cardMask.cards.diamonds ^= (1 << c);
    if (p > outString) *p++ = ' ';
    *p++ = rankChars[c];
    *p++ = suitChars[StdDeck_Suit_DIAMONDS];
  };

  while (cardMask.cards.clubs != 0) {
    c = topCardTable[cardMask.cards.clubs];
    cardMask.cards.clubs ^= (1 << c);
    if (p > outString) *p++ = ' ';
    *p++ = rankChars[c];
    *p++ = suitChars[StdDeck_Suit_CLUBS];
  };
 
  return p - outString;
}


int
StdDeck_printCard(int cardIndex) {
  char buffer[80];
  int n;

  n = StdDeck_cardToString(cardIndex, buffer);
  printf("%.*s", n, buffer);
  return n;
}

int 
StdDeck_printMask(CardMask cardMask) {
  char buffer[80];
  int n;

  n = StdDeck_maskToString(cardMask, buffer);
  printf("%.*s", n, buffer);
  return n;
}


int 
StdDeck_stringToMask(char *inString, CardMask outMask) {
  return 0;
}

int 
StdDeck_CardMask_nBitsSet(CardMask cards) {
  return 0;
}



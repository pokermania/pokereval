#include <stdio.h>
#include <ctype.h>
#include "poker_defs.h"
#include "jokerdeck.h"

const char JokerDeck_rankChars[] = "23456789TJQKA";
const char JokerDeck_suitChars[] = "hdcs";

int 
JokerDeck_cardToString(int cardIndex, char *outString) {
  if (JokerDeck_IS_JOKER(cardIndex)) {
    *outString++ = 'X';
    *outString++ = 'x';
  }
  else {
    *outString++ = JokerDeck_rankChars[JokerDeck_RANK(cardIndex)];
    *outString++ = JokerDeck_suitChars[JokerDeck_SUIT(cardIndex)];
  };

  *outString   = '\0';
  return 2;
}


int
JokerDeck_maskToString(JokerDeck_CardMask cardMask, char *outString) {
  int i;
  char *p = outString;

  for (i=JokerDeck_N_CARDS-1; i >= 0; i--) {
    if (JokerDeck_CardMask_CARD_IS_SET(cardMask, i)) {
      if (p > outString) *p++ = ' ';
      p += JokerDeck_cardToString(i, p);
    };
  };

  *p = '\0';
  return p - outString;
}


int
JokerDeck_printCard(int cardIndex) {
  char buffer[80];
  int n;

  n = JokerDeck_cardToString(cardIndex, buffer);
  printf("%s", buffer);
  return n;
}

int 
JokerDeck_printMask(JokerDeck_CardMask cardMask) {
  char buffer[80];
  int n;

  n = JokerDeck_maskToString(cardMask, buffer);
  printf("%s", buffer);
  return n;
}


int 
JokerDeck_stringToMask(char *inString, JokerDeck_CardMask *outMask) {
  char *p;
  int n=0, rank, suit, card;

  JokerDeck_CardMask_RESET(*outMask);
  for (p=inString; p < inString + strlen(inString); p++) {
    if (*p == ' ')
      continue;

    if ((toupper(p[0]) == 'X') && toupper(p[1]) == 'X') {
      card = JokerDeck_JOKER;
      JokerDeck_CardMask_SET(*outMask, card);
      ++n;
      ++p; ++p;
    }
    else {
      for (rank=JokerDeck_Rank_FIRST; rank <= JokerDeck_Rank_LAST; rank++) 
        if (JokerDeck_rankChars[rank] == toupper(*p))
          break;
      if (rank > JokerDeck_Rank_LAST)
        break;
      ++p;
      for (suit=JokerDeck_Suit_FIRST; suit <= JokerDeck_Suit_LAST; suit++) 
        if (JokerDeck_suitChars[suit] == tolower(*p))
          break;
      if (suit > JokerDeck_Suit_LAST)
        break;
      ++p;
      card = JokerDeck_MAKE_CARD(rank, suit);
      JokerDeck_CardMask_SET(*outMask, card);
      ++n;
    };
  }
    
  return n;
}




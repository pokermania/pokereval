#include <stdio.h>

#include "poker_defs.h"
#include "deck_joker.h"
#include "rules_joker.h"

const char *JokerRules_handTypeNames[JokerRules_HandType_LAST+1] = {
  "NoPair",
  "OnePair",
  "TwoPair",
  "Trips",
  "Straight",
  "Flush",
  "FlHouse",
  "Quads",
  "StFlush",
  "Quints"
};

const char *JokerRules_handTypeNamesPadded[JokerRules_HandType_LAST+1] = {
  "NoPair  ",
  "OnePair ",
  "TwoPair ",
  "Trips   ",
  "Straight",
  "Flush   ",
  "FlHouse ",
  "Quads   ",
  "StFlush ",
  "Quints  "
};

int JokerRules_nSigCards[JokerRules_HandType_LAST+1] = {
  5, 
  4, 
  3, 
  3, 
  1, 
  5, 
  2,
  2, 
  1,
  1
};


int 
JokerRules_HandVal_toString(HandVal handval, char *outString) {
  char *p = outString;
  int htype = HandVal_HANDTYPE(handval);

  p += sprintf(outString, "%s (", JokerRules_handTypeNames[htype]);
  if (JokerRules_nSigCards[htype] >= 1) 
    p += sprintf(p, "%c", 
                 StdDeck_rankChars[HandVal_TOP_CARD(handval)]);
  if (JokerRules_nSigCards[htype] >= 2) 
    p += sprintf(p, " %c", 
                 StdDeck_rankChars[HandVal_SECOND_CARD(handval)]);
  if (JokerRules_nSigCards[htype] >= 3) 
    p += sprintf(p, " %c", 
                 StdDeck_rankChars[HandVal_THIRD_CARD(handval)]);
  if (JokerRules_nSigCards[htype] >= 4) 
    p += sprintf(p, " %c", 
                 StdDeck_rankChars[HandVal_FOURTH_CARD(handval)]);
  if (JokerRules_nSigCards[htype] >= 5) 
    p += sprintf(p, " %c", 
                 StdDeck_rankChars[HandVal_FIFTH_CARD(handval)]);
  p += sprintf(p, ")");

  return p - outString;
}

int 
JokerRules_HandVal_print(HandVal handval) {
  char buf[80];
  int n;

  n = JokerRules_HandVal_toString(handval, buf);
  printf("%s", buf);
  return n;
}



#include <stdio.h>

#include "poker_defs.h"

#if defined(NONSTANDARD_DECK)
#error "Cannot define NONSTANDARD_DECK for stdrules.c"
#endif

const char *StdRules_handTypeNames[HandType_COUNT] = {
  "NoPair",
  "OnePair",
  "TwoPair",
  "Trips",
  "Straight",
  "Flush",
  "FlHouse",
  "Quads",
  "StFlush"
};

const char *StdRules_handTypeNamesPadded[HandType_COUNT] = {
  "NoPair  ",
  "OnePair ",
  "TwoPair ",
  "Trips   ",
  "Straight",
  "Flush   ",
  "FlHouse ",
  "Quads   ",
  "StFlush "
};

int StdRules_nSigCards[HandType_COUNT] = {
  5, 
  4, 
  3, 
  3, 
  1, 
  5, 
  2,
  2, 
  1
};

int 
HandVal_toString(HandVal handval, char *outString) {
  char *p = outString;
  int htype = HandVal_HANDTYPE(handval);

  p += sprintf(outString, "%s (", handTypeNames[htype]);
  if (StdRules_nSigCards[htype] >= 1) 
    p += sprintf(p, "%c", 
                 StdDeck_rankChars[HandVal_TOP_CARD(handval)]);
  if (StdRules_nSigCards[htype] >= 2) 
    p += sprintf(p, " %c", 
                 StdDeck_rankChars[HandVal_SECOND_CARD(handval)]);
  if (StdRules_nSigCards[htype] >= 3) 
    p += sprintf(p, " %c", 
                 StdDeck_rankChars[HandVal_THIRD_CARD(handval)]);
  if (StdRules_nSigCards[htype] >= 4) 
    p += sprintf(p, " %c", 
                 StdDeck_rankChars[HandVal_FOURTH_CARD(handval)]);
  if (StdRules_nSigCards[htype] >= 5) 
    p += sprintf(p, " %c", 
                 StdDeck_rankChars[HandVal_FIFTH_CARD(handval)]);
  p += sprintf(p, ")");

  return p - outString;
}

int 
HandVal_print(HandVal handval) {
  char buf[80];
  int n;

  n = HandVal_toString(handval, buf);
  printf("%s", buf);
  return n;
}


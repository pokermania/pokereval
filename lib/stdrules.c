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

StdRules_HandVal StdRules_handValues[HandType_COUNT] = {
  (HandType_NOPAIR    << HandVal_HANDTYPE_SHIFT), 
  (HandType_ONEPAIR   << HandVal_HANDTYPE_SHIFT), 
  (HandType_TWOPAIR   << HandVal_HANDTYPE_SHIFT), 
  (HandType_TRIPS     << HandVal_HANDTYPE_SHIFT), 
  (HandType_STRAIGHT  << HandVal_HANDTYPE_SHIFT), 
  (HandType_FLUSH     << HandVal_HANDTYPE_SHIFT), 
  (HandType_FULLHOUSE << HandVal_HANDTYPE_SHIFT), 
  (HandType_QUADS     << HandVal_HANDTYPE_SHIFT), 
  (HandType_STFLUSH   << HandVal_HANDTYPE_SHIFT), 
};
  

int 
StdRules_handvalToString(StdRules_HandVal handval, char *outString) {
  char *p = outString;
  int htype = HandVal_GET_HANDTYPE(handval);

  p += sprintf(outString, "%s (", handTypeNames[htype]);
  if (StdRules_nSigCards[htype] >= 1) 
    p += sprintf(p, "%c", 
                 StdDeck_rankChars[HandVal_GET_TOP_CARD(handval)]);
  if (StdRules_nSigCards[htype] >= 2) 
    p += sprintf(p, " %c", 
                 StdDeck_rankChars[HandVal_GET_SECOND_CARD(handval)]);
  if (StdRules_nSigCards[htype] >= 3) 
    p += sprintf(p, " %c", 
                 StdDeck_rankChars[HandVal_GET_THIRD_CARD(handval)]);
  if (StdRules_nSigCards[htype] >= 4) 
    p += sprintf(p, " %c", 
                 StdDeck_rankChars[HandVal_GET_FOURTH_CARD(handval)]);
  if (StdRules_nSigCards[htype] >= 5) 
    p += sprintf(p, " %c", 
                 StdDeck_rankChars[HandVal_GET_FIFTH_CARD(handval)]);
  p += sprintf(p, ")");

  return p - outString;
}

int 
StdRules_printHandval(StdRules_HandVal handval) {
  char buf[80];
  int n;

  n = StdRules_handvalToString(handval, buf);
  printf("%s", buf);
  return n;
}


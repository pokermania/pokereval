#include <stdio.h>

#include "poker_defs.h"

const char *StdRules_handTypeNames[StdRules_HandType_COUNT] = {
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

const char *StdRules_handTypeNamesPadded[StdRules_HandType_COUNT] = {
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

int StdRules_nSigCards[StdRules_HandType_COUNT] = {
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
StdRules_handvalToString(StdRules_HandVal handval, char *outString) {
  char *p = outString;

  p += sprintf(outString, "%s (", 
               StdRules_handTypeNames[handval.handval.htype]);
  if (StdRules_nSigCards[handval.handval.htype] >= 1) 
    p += sprintf(p, "%c", StdDeck_rankChars[handval.handval.top_card]);
  if (StdRules_nSigCards[handval.handval.htype] >= 2) 
    p += sprintf(p, " %c", StdDeck_rankChars[handval.handval.second_card]);
  if (StdRules_nSigCards[handval.handval.htype] >= 3) 
    p += sprintf(p, " %c", StdDeck_rankChars[handval.handval.third_card]);
  if (StdRules_nSigCards[handval.handval.htype] >= 4) 
    p += sprintf(p, " %c", StdDeck_rankChars[handval.handval.fourth_card]);
  if (StdRules_nSigCards[handval.handval.htype] >= 5) 
    p += sprintf(p, " %c", StdDeck_rankChars[handval.handval.fifth_card]);
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


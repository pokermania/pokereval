#include <stdio.h>

#include "poker_defs.h"
#include "astuddeck.h"
#include "astudrules.h"

const char *AStudRules_handTypeNames[AStudRules_HandType_LAST+1] = {
  "NoPair",
  "OnePair",
  "TwoPair",
  "Trips",
  "Straight",
  "FlHouse",
  "Flush",
  "Quads",
  "StFlush"
};

const char *AStudRules_handTypeNamesPadded[AStudRules_HandType_LAST+1] = {
  "NoPair  ",
  "OnePair ",
  "TwoPair ",
  "Trips   ",
  "Straight",
  "FlHouse ",
  "Flush   ",
  "Quads   ",
  "StFlush "
};

int AStudRules_nSigCards[AStudRules_HandType_LAST+1] = {
  5, 
  4, 
  3, 
  3, 
  1, 
  2,
  5, 
  2, 
  1
};


int 
AStudRules_HandVal_toString(HandVal handval, char *outString) {
  char *p = outString;
  int htype = HandVal_HANDTYPE(handval);

  p += sprintf(outString, "%s (", AStudRules_handTypeNames[htype]);
  if (AStudRules_nSigCards[htype] >= 1) 
    p += sprintf(p, "%c", 
                 AStudDeck_rankChars[HandVal_TOP_CARD(handval)]);
  if (AStudRules_nSigCards[htype] >= 2) 
    p += sprintf(p, " %c", 
                 AStudDeck_rankChars[HandVal_SECOND_CARD(handval)]);
  if (AStudRules_nSigCards[htype] >= 3) 
    p += sprintf(p, " %c", 
                 AStudDeck_rankChars[HandVal_THIRD_CARD(handval)]);
  if (AStudRules_nSigCards[htype] >= 4) 
    p += sprintf(p, " %c", 
                 AStudDeck_rankChars[HandVal_FOURTH_CARD(handval)]);
  if (AStudRules_nSigCards[htype] >= 5) 
    p += sprintf(p, " %c", 
                 AStudDeck_rankChars[HandVal_FIFTH_CARD(handval)]);
  p += sprintf(p, ")");

  return p - outString;
}

int 
AStudRules_HandVal_print(HandVal handval) {
  char buf[80];
  int n;

  n = AStudRules_HandVal_toString(handval, buf);
  printf("%s", buf);
  return n;
}


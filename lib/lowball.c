#include <stdio.h>

#include "poker_defs.h"
#include "handval_low.h"

#define CARD_TO_RANK(c) ((c) == StdDeck_Rank_2 ? StdDeck_Rank_ACE : (c-1))

int 
LowHandVal_toString(LowHandVal hv, char *outString) {
  char *p = outString;
  int htype = HandVal_HANDTYPE(hv);

  if (hv == LowHandVal_NOTHING) 
    p += sprintf(outString, "NoLow");
  else {
    p += sprintf(outString, "%s (", StdRules_handTypeNames[htype]);
    if (StdRules_nSigCards[htype] >= 1) 
      p += sprintf(p, "%c", 
                   StdDeck_rankChars[CARD_TO_RANK(HandVal_TOP_CARD(hv))]);
    if (StdRules_nSigCards[htype] >= 2) 
      p += sprintf(p, " %c", 
                   StdDeck_rankChars[CARD_TO_RANK(HandVal_SECOND_CARD(hv))]);
    if (StdRules_nSigCards[htype] >= 3) 
      p += sprintf(p, " %c", 
                   StdDeck_rankChars[CARD_TO_RANK(HandVal_THIRD_CARD(hv))]);
    if (StdRules_nSigCards[htype] >= 4) 
      p += sprintf(p, " %c", 
                   StdDeck_rankChars[CARD_TO_RANK(HandVal_FOURTH_CARD(hv))]);
    if (StdRules_nSigCards[htype] >= 5) 
      p += sprintf(p, " %c", 
                   StdDeck_rankChars[CARD_TO_RANK(HandVal_FIFTH_CARD(hv))]);
    p += sprintf(p, ")");
  };

  return p - outString;
}

int 
LowHandVal_print(LowHandVal handval) {
  char buf[80];
  int n;

  n = LowHandVal_toString(handval, buf);
  printf("%s", buf);
  return n;
}

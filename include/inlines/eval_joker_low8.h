#ifndef __EVAL_JOKER_LOW8_H__
#define __EVAL_JOKER_LOW8_H__

#include "handval_low.h"
#include "deck_joker.h"
#include "inlines/eval_joker_low.h"

static inline LowHandVal 
JokerDeck_Lowball8_EVAL(JokerDeck_CardMask cards, int n_cards) {
  LowHandVal loval;
  loval = JokerDeck_Lowball_EVAL(cards, n_cards);
  if (loval <= LowHandVal_WORST_EIGHT)
    return loval;
  else 
    return LowHandVal_NOTHING;
}

#endif

#include <assert.h>
#include "handval_low.h"

/*
 * Lowball evaluator.  Assumes that n_cards >= 5
 */

static inline uint32
_bottomNCards(uint32 cards, int howMany) {
  int i;
  uint32 retval, t;

  retval = 0;
  for (i=0; i<howMany; i++) {
    t = bottomCardTable[cards];
    retval += t << (i*LowHandVal_CARD_WIDTH);
    cards ^= (1 << t);
  }

  return retval;
}


static inline LowHandVal 
StdDeck_Lowball_EVAL(StdDeck_CardMask cards, int n_cards) {
  uint32 ranks, dups, trips, ss, sh, sd, sc, t, tt;

  ss = StdDeck_CardMask_SPADES(cards);
  sc = StdDeck_CardMask_CLUBS(cards);
  sd = StdDeck_CardMask_DIAMONDS(cards);
  sh = StdDeck_CardMask_HEARTS(cards);

  ranks = sc | ss | sd | sh;
  ranks = Lowball_ROTATE_RANKS(ranks);
  if (nBitsTable[ranks] >= 5) 
    return LowHandVal_HANDTYPE_VALUE(StdRules_HandType_NOPAIR) 
      + bottomFiveCardsTable[ranks];
  else {
    dups = (sc&sd) | (sh & (sc|sd)) | (ss & (sh|sc|sd));
    dups = Lowball_ROTATE_RANKS(dups);
    t = bottomCardTable[dups];

    switch (nBitsTable[ranks]) {
    case 4:
      return LowHandVal_HANDTYPE_VALUE(StdRules_HandType_ONEPAIR) 
        + LowHandVal_TOP_CARD_VALUE(t)
        + (_bottomNCards(ranks ^ (1 << t), 3) << LowHandVal_CARD_WIDTH);
      break;

    case 3:
      if (nBitsTable[dups] == 2) {
        tt = bottomCardTable[dups ^ (1 << t)];
        return LowHandVal_HANDTYPE_VALUE(StdRules_HandType_TWOPAIR)
          + LowHandVal_TOP_CARD_VALUE(tt) 
          + LowHandVal_SECOND_CARD_VALUE(t) 
          + ((_bottomNCards(ranks ^ (1 << t) ^ (1 << tt), 1)) 
             << (2*LowHandVal_CARD_WIDTH));
      }
      else {
        t = bottomCardTable[dups];
        return LowHandVal_HANDTYPE_VALUE(StdRules_HandType_TRIPS) 
          + LowHandVal_TOP_CARD_VALUE(t)
          + (_bottomNCards(ranks ^ (1 << t), 2) 
             << (2*LowHandVal_CARD_WIDTH));
      }
      break;

    case 2:
      if (nBitsTable[dups] == 2) {
        trips = sc ^ ss ^ sd ^ sh;
        trips = Lowball_ROTATE_RANKS(trips);
        t = bottomCardTable[trips];
        return LowHandVal_HANDTYPE_VALUE(StdRules_HandType_FULLHOUSE)
          + LowHandVal_TOP_CARD_VALUE(t) 
          + LowHandVal_SECOND_CARD_VALUE(bottomCardTable[ranks ^ (1 << t)]);
      }
      else {
        return LowHandVal_HANDTYPE_VALUE(StdRules_HandType_QUADS)
          + LowHandVal_TOP_CARD_VALUE(t) 
          + LowHandVal_SECOND_CARD_VALUE(bottomCardTable[ranks ^ (1 << t)]);
      };
      break;
    };
  };

  assert(!"Logic error in eval_low");
  return 0;
}


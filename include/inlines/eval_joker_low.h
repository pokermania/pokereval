#include <assert.h>
#include "handval_low.h"
#include "deck_joker.h"
#include "inlines/eval_low.h"

/*
 * Lowball evaluator with joker.  Assumes that n_cards >= 5.  
 * Performance could be improved by expanding the standard lowball evaluator,
 * rather than trying to manipulate the card mask so we can reuse the standard
 * lowball evaluator.  This would save a lot of bit extractions and redundant
 * bit operations (like computing ranks.)  
 */

static inline LowHandVal 
JokerDeck_Lowball_EVAL(JokerDeck_CardMask cards, int n_cards) {
  uint32 ranks, rank, ss, sh, sd, sc;
  StdDeck_CardMask sCards;

  JokerDeck_CardMask_toStd(cards, sCards);
  if (!JokerDeck_CardMask_JOKER(cards)) 
    return StdDeck_Lowball_EVAL(sCards, n_cards);

  ss = JokerDeck_CardMask_SPADES(cards);
  sc = JokerDeck_CardMask_CLUBS(cards);
  sd = JokerDeck_CardMask_DIAMONDS(cards);
  sh = JokerDeck_CardMask_HEARTS(cards);

  ranks = sc | ss | sd | sh;
  if (!(ranks & (1 << JokerDeck_Rank_ACE)))
    rank = JokerDeck_Rank_ACE;
  else 
    for (rank= (1 << JokerDeck_Rank_2); 
	 rank <= (1 << JokerDeck_Rank_KING); 
	 rank <<= 1) 
      if (!(ranks & rank))
	break;

  if (!(sc & rank)) 
    StdDeck_CardMask_SET_CLUBS(sCards, sc | rank);
  else if (!(sd & rank))
    StdDeck_CardMask_SET_DIAMONDS(sCards, sc | rank);
  else if (!(sh & rank))
    StdDeck_CardMask_SET_HEARTS(sCards, sh | rank);
  else if (!(ss & rank))
    StdDeck_CardMask_SET_SPADES(sCards, ss | rank);

  return StdDeck_Lowball_EVAL(sCards, n_cards);
}

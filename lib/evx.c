#include <assert.h>

#include "poker_defs.h"
#include "evx_defs.h"


static int8 find_and_clear(uint32 *cardsp) {
  int8 retval;
  uint32 mask;
  
  for (mask = 1 << StdDeck_Rank_ACE, retval = StdDeck_Rank_ACE; 
       mask && !(*cardsp & mask);
       --retval, mask >>= 1)
    ;
  if (mask)
    *cardsp &= ~mask;
  return retval;
}

static uint8 next_card(uint32 *ms_cardsp, uint32 *ls_cardsp)
{
  int8 retval;

  retval = find_and_clear(ms_cardsp);
  if (retval == -1)
    retval = find_and_clear(ls_cardsp);
  return retval == -1 ? 0 : retval;
}


HandVal 
EvxHandVal_toHandVal(EvxHandVal ehv) {
  uint32 ls_cards, ms_cards, cards;
  int i;

  ms_cards = (ehv >> EvxHandVal_SIGCARDS_SHIFT) & EvxHandVal_RANK_MASK;
  ls_cards =  ehv & EvxHandVal_RANK_MASK;
  cards = 0;

  for (i=0; i<5; i++) 
    cards = (cards << HandVal_CARD_WIDTH) 
      + next_card(&ms_cards, &ls_cards);

  return HandVal_HANDTYPE_VALUE(EvxHandVal_HANDTYPE(ehv)) + cards;
}

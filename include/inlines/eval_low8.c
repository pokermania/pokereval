static inline LowHandVal 
StdDeck_Lowball8_EVAL(StdDeck_CardMask cards, int n_cards) {
  uint32 ranks, retval;

  ranks = (StdDeck_CardMask_HEARTS(cards) |
           StdDeck_CardMask_DIAMONDS(cards) |
           StdDeck_CardMask_HEARTS(cards) |
           StdDeck_CardMask_SPADES(cards));
  ranks = Lowball_ROTATE_RANKS(ranks);
  retval = bottomFiveCardsTable[ranks];
  if (retval > 0 && retval <= LowHandVal_WORST_EIGHT)
    return LowHandVal_HANDTYPE_VALUE(StdRules_HandType_NOPAIR) + retval;
  else 
    return LowHandVal_NOTHING;
}


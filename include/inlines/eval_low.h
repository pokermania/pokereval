static inline LowHandVal 
StdDeck_Lowball8_EVAL(StdDeck_CardMask cards, int n_cards) {
  uint32 ranks;

  ranks = (StdDeck_CardMask_HEARTS(cards) |
           StdDeck_CardMask_DIAMONDS(cards) |
           StdDeck_CardMask_HEARTS(cards) |
           StdDeck_CardMask_SPADES(cards));
  ranks = ((ranks & ~(1 << StdDeck_Rank_ACE)) << 1) 
    | ((ranks >> StdDeck_Rank_ACE) & 0x01);
  if (bottomFiveCardsTable[ranks] <= LowHandVal_WORST_EIGHT) {
    return bottomFiveCardsTable[ranks];
  } 
  else 
    return LowHandVal_NOTHING;
}


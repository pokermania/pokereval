#ifndef __HANDVAL_LOW_H__
#define __HANDVAL_LOW_H__

typedef uint32 LowHandVal;

#define LowHandVal_HANDTYPE_SHIFT    HandVal_HANDTYPE_SHIFT    
#define LowHandVal_HANDTYPE_MASK     HandVal_HANDTYPE_MASK     
#define LowHandVal_CARDS_SHIFT       HandVal_CARDS_SHIFT       
#define LowHandVal_CARDS_MASK        HandVal_CARDS_MASK        
#define LowHandVal_TOP_CARD_SHIFT    HandVal_TOP_CARD_SHIFT    
#define LowHandVal_TOP_CARD_MASK     HandVal_TOP_CARD_MASK     
#define LowHandVal_SECOND_CARD_SHIFT HandVal_SECOND_CARD_SHIFT 
#define LowHandVal_SECOND_CARD_MASK  HandVal_SECOND_CARD_MASK  
#define LowHandVal_THIRD_CARD_SHIFT  HandVal_THIRD_CARD_SHIFT  
#define LowHandVal_THIRD_CARD_MASK   HandVal_THIRD_CARD_MASK   
#define LowHandVal_FOURTH_CARD_SHIFT HandVal_FOURTH_CARD_SHIFT 
#define LowHandVal_FOURTH_CARD_MASK  HandVal_FOURTH_CARD_MASK  
#define LowHandVal_FIFTH_CARD_SHIFT  HandVal_FIFTH_CARD_SHIFT  
#define LowHandVal_FIFTH_CARD_MASK   HandVal_FIFTH_CARD_MASK   
#define LowHandVal_CARD_WIDTH        HandVal_CARD_WIDTH        
#define LowHandVal_CARD_MASK         HandVal_CARD_MASK         

#define LowHandVal_HANDTYPE          HandVal_HANDTYPE
#define LowHandVal_CARDS             HandVal_CARDS
#define LowHandVal_TOP_CARD          HandVal_TOP_CARD
#define LowHandVal_SECOND_CARD       HandVal_SECOND_CARD
#define LowHandVal_THIRD_CARD        HandVal_THIRD_CARD
#define LowHandVal_FOURTH_CARD       HandVal_FOURTH_CARD
#define LowHandVal_FIFTH_CARD        HandVal_FIFTH_CARD

#define LowHandVal_HANDTYPE_VALUE    HandVal_HANDTYPE_VALUE
#define LowHandVal_TOP_CARD_VALUE    HandVal_TOP_CARD_VALUE
#define LowHandVal_SECOND_CARD_VALUE HandVal_SECOND_CARD_VALUE
#define LowHandVal_THIRD_CARD_VALUE  HandVal_THIRD_CARD_VALUE
#define LowHandVal_FOURTH_CARD_VALUE HandVal_FOURTH_CARD_VALUE
#define LowHandVal_FIFTH_CARD_VALUE  HandVal_FIFTH_CARD_VALUE

#define LowHandVal_NOTHING                              \
(LowHandVal_HANDTYPE_VALUE(StdRules_HandType_STFLUSH)   \
 + LowHandVal_TOP_CARD_VALUE(StdDeck_Rank_ACE) + 1)

#define LowHandVal_WORST_EIGHT \
(LowHandVal_HANDTYPE_VALUE(StdRules_HandType_NOPAIR)     \
 + LowHandVal_TOP_CARD_VALUE(StdDeck_Rank_8+1)           \
 + LowHandVal_SECOND_CARD_VALUE(StdDeck_Rank_7+1)        \
 + LowHandVal_THIRD_CARD_VALUE(StdDeck_Rank_6+1)         \
 + LowHandVal_FOURTH_CARD_VALUE(StdDeck_Rank_5+1)        \
 + LowHandVal_FIFTH_CARD_VALUE(StdDeck_Rank_4+1))         

extern uint32  bottomFiveCardsTable[StdDeck_N_RANKMASKS];
extern uint32  bottomFiveJokerTable[StdDeck_N_RANKMASKS];
extern uint8        bottomCardTable[StdDeck_N_RANKMASKS];

extern int LowHandVal_toString(LowHandVal hv, char *outString);
extern int LowHandVal_print(LowHandVal handval);

#define Lowball_ROTATE_RANKS(ranks) \
((((ranks) & ~(1 << StdDeck_Rank_ACE)) << 1) \
 | (((ranks) >> StdDeck_Rank_ACE) & 0x01))

#endif

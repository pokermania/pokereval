/* 
 * The HandVal type used to be defined as a union of a 32-bit integer with
 * a mess of bit fields for the hand type, top card, etc.  This had two major
 * problems: 
 * 1.  Unions seem to cripple the optimizing ability of even smart compilers;
 * 2.  C's support for bit fields suck, and it required us to know the 
 *     endian-ness of the system to define the union.
 *
 * We've replaced it with a 32-bit quantity, and defined symbolically the
 * various shifts and masks for the various fields.  The 32-bit value can
 * still be compared numerically against another hand value to see which wins;
 * the only difference is slightly more complexity in building the value.
 * Fortunately, this is most often hidden in the evaluator, so the driver
 * programs often don't need to know anything about it.
 */

typedef uint32 StdRules_HandVal;

#define StdRules_HandVal_HANDTYPE_SHIFT    24
#define StdRules_HandVal_HANDTYPE_MASK     0x0F000000
#define StdRules_HandVal_CARDS_SHIFT       0
#define StdRules_HandVal_CARDS_MASK        0x000FFFFF
#define StdRules_HandVal_TOP_CARD_SHIFT    16
#define StdRules_HandVal_TOP_CARD_MASK     0x000F0000
#define StdRules_HandVal_SECOND_CARD_SHIFT 12
#define StdRules_HandVal_SECOND_CARD_MASK  0x0000F000
#define StdRules_HandVal_THIRD_CARD_SHIFT  8
#define StdRules_HandVal_THIRD_CARD_MASK   0x00000F00
#define StdRules_HandVal_FOURTH_CARD_SHIFT 4
#define StdRules_HandVal_FOURTH_CARD_MASK  0x000000F0
#define StdRules_HandVal_FIFTH_CARD_SHIFT  0
#define StdRules_HandVal_FIFTH_CARD_MASK   0x0000000F
#define StdRules_HandVal_CARD_WIDTH        4
#define StdRules_HandVal_CARD_MASK         0x0F

#define StdRules_HandVal_HANDTYPE(hv) \
  ((hv) >> StdRules_HandVal_HANDTYPE_SHIFT)
#define StdRules_HandVal_CARDS(hv) \
  ((hv) & StdRules_HandVal_CARDS_MASK)
#define StdRules_HandVal_TOP_CARD(hv) \
  (((hv) >> StdRules_HandVal_TOP_CARD_SHIFT) & StdRules_HandVal_CARD_MASK)
#define StdRules_HandVal_SECOND_CARD(hv) \
  (((hv) >> StdRules_HandVal_SECOND_CARD_SHIFT) & StdRules_HandVal_CARD_MASK)
#define StdRules_HandVal_THIRD_CARD(hv) \
  (((hv) >> StdRules_HandVal_THIRD_CARD_SHIFT) & StdRules_HandVal_CARD_MASK)
#define StdRules_HandVal_FOURTH_CARD(hv) \
  (((hv) >> StdRules_HandVal_FOURTH_CARD_SHIFT) & StdRules_HandVal_CARD_MASK)
#define StdRules_HandVal_FIFTH_CARD(hv) \
  (((hv) >> StdRules_HandVal_FIFTH_CARD_SHIFT) & StdRules_HandVal_CARD_MASK)

#define StdRules_HandType_NOPAIR    0
#define StdRules_HandType_ONEPAIR   1
#define StdRules_HandType_TWOPAIR   2
#define StdRules_HandType_TRIPS     3
#define StdRules_HandType_STRAIGHT  4
#define StdRules_HandType_FLUSH     5
#define StdRules_HandType_FULLHOUSE 6
#define StdRules_HandType_QUADS     7
#define StdRules_HandType_STFLUSH   8
#define StdRules_HandType_FIRST     StdRules_HandType_NOPAIR
#define StdRules_HandType_COUNT     9

#define StdRules_FIVE_STRAIGHT \
 ((1 << StdDeck_Rank_ACE ) \
  | (1 << StdDeck_Rank_2 ) \
  | (1 << StdDeck_Rank_3 ) \
  | (1 << StdDeck_Rank_4 ) \
  | (1 << StdDeck_Rank_5 ))

extern const char *StdRules_handTypeNames[StdRules_HandType_COUNT];
extern const char *StdRules_handTypeNamesPadded[StdRules_HandType_COUNT];

extern StdRules_HandVal StdRules_handValues[StdRules_HandType_COUNT];
extern int StdRules_nSigCards[StdRules_HandType_COUNT];

extern int 
StdRules_handvalToString(StdRules_HandVal handval, char *outString); 
extern int 
StdRules_printHandval(StdRules_HandVal handval); 


#ifndef NONSTANDARD_RULES
#define HandVal            StdRules_HandVal

#define HandVal_HANDTYPE_SHIFT    StdRules_HandVal_HANDTYPE_SHIFT    
#define HandVal_HANDTYPE_MASK     StdRules_HandVal_HANDTYPE_MASK     
#define HandVal_CARDS_SHIFT       StdRules_HandVal_CARDS_SHIFT       
#define HandVal_CARDS_MASK        StdRules_HandVal_CARDS_MASK        
#define HandVal_TOP_CARD_SHIFT    StdRules_HandVal_TOP_CARD_SHIFT    
#define HandVal_TOP_CARD_MASK     StdRules_HandVal_TOP_CARD_MASK     
#define HandVal_SECOND_CARD_SHIFT StdRules_HandVal_SECOND_CARD_SHIFT 
#define HandVal_SECOND_CARD_MASK  StdRules_HandVal_SECOND_CARD_MASK  
#define HandVal_THIRD_CARD_SHIFT  StdRules_HandVal_THIRD_CARD_SHIFT  
#define HandVal_THIRD_CARD_MASK   StdRules_HandVal_THIRD_CARD_MASK   
#define HandVal_FOURTH_CARD_SHIFT StdRules_HandVal_FOURTH_CARD_SHIFT 
#define HandVal_FOURTH_CARD_MASK  StdRules_HandVal_FOURTH_CARD_MASK  
#define HandVal_FIFTH_CARD_SHIFT  StdRules_HandVal_FIFTH_CARD_SHIFT  
#define HandVal_FIFTH_CARD_MASK   StdRules_HandVal_FIFTH_CARD_MASK   
#define HandVal_CARD_WIDTH        StdRules_HandVal_CARD_WIDTH        
#define HandVal_CARD_MASK         StdRules_HandVal_CARD_MASK         

#define HandVal_HANDTYPE      StdRules_HandVal_HANDTYPE
#define HandVal_CARDS         StdRules_HandVal_CARDS
#define HandVal_TOP_CARD      StdRules_HandVal_TOP_CARD
#define HandVal_SECOND_CARD   StdRules_HandVal_SECOND_CARD
#define HandVal_THIRD_CARD    StdRules_HandVal_THIRD_CARD
#define HandVal_FOURTH_CARD   StdRules_HandVal_FOURTH_CARD
#define HandVal_FIFTH_CARD    StdRules_HandVal_FIFTH_CARD

#define HandType_NOPAIR    StdRules_HandType_NOPAIR    
#define HandType_ONEPAIR   StdRules_HandType_ONEPAIR   
#define HandType_TWOPAIR   StdRules_HandType_TWOPAIR   
#define HandType_TRIPS     StdRules_HandType_TRIPS     
#define HandType_STRAIGHT  StdRules_HandType_STRAIGHT  
#define HandType_FLUSH     StdRules_HandType_FLUSH     
#define HandType_FULLHOUSE StdRules_HandType_FULLHOUSE 
#define HandType_QUADS     StdRules_HandType_QUADS     
#define HandType_STFLUSH   StdRules_HandType_STFLUSH    
#define HandType_FIRST     StdRules_HandType_FIRST  
#define HandType_COUNT     StdRules_HandType_COUNT     

#define handTypeNames        StdRules_handTypeNames
#define handTypeNamesPadded  StdRules_handTypeNamesPadded
#define nSigCards            StdRules_nSigCards

#define Rules_handvalToString StdRules_handvalToString
#define Rules_printHandval    StdRules_printHandval

#define PokerHand_EVAL_N   StdRules_HANDEVAL
#endif


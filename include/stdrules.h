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
#define StdRules_HandType_LAST      StdRules_HandType_STFLUSH
#define StdRules_HandType_COUNT     9

#define StdRules_FIVE_STRAIGHT \
 ((1 << StdDeck_Rank_ACE ) \
  | (1 << StdDeck_Rank_2 ) \
  | (1 << StdDeck_Rank_3 ) \
  | (1 << StdDeck_Rank_4 ) \
  | (1 << StdDeck_Rank_5 ))

extern const char *StdRules_handTypeNames[StdRules_HandType_LAST+1];
extern const char *StdRules_handTypeNamesPadded[StdRules_HandType_LAST+1];

extern int StdRules_nSigCards[StdRules_HandType_LAST+1];

extern int StdRules_HandVal_toString(HandVal handval, char *outString); 
extern int StdRules_HandVal_print(HandVal handval);


#ifndef NONSTANDARD_RULES
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
#define HandType_LAST      StdRules_HandType_LAST

#define handTypeNames        StdRules_handTypeNames
#define handTypeNamesPadded  StdRules_handTypeNamesPadded
#define nSigCards            StdRules_nSigCards
#define HandVal_print        StdRules_HandVal_print
#define HandVal_toString     StdRules_HandVal_toString

#endif


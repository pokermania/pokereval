/*
   Note that this file has two #if .. #endif sections -- one for 
   StdDeck macros to prevent double-inclusion, and one to define the 
   generic Rules_ macros if RULES_ASTUD is defined 
*/

#ifndef __RULES_ASTUD_H__
#define __RULES_ASTUD_H__

#define AStudRules_HandType_NOPAIR    0
#define AStudRules_HandType_ONEPAIR   1
#define AStudRules_HandType_TWOPAIR   2
#define AStudRules_HandType_TRIPS     3
#define AStudRules_HandType_STRAIGHT  4
#define AStudRules_HandType_FULLHOUSE 5
#define AStudRules_HandType_FLUSH     6
#define AStudRules_HandType_QUADS     7
#define AStudRules_HandType_STFLUSH   8
#define AStudRules_HandType_FIRST     AStudRules_HandType_NOPAIR
#define AStudRules_HandType_LAST      AStudRules_HandType_STFLUSH
#define AStudRules_HandType_COUNT     9

#define AStudRules_TEN_STRAIGHT \
 ((1 << AStudDeck_Rank_ACE ) \
  | (1 << AStudDeck_Rank_7 ) \
  | (1 << AStudDeck_Rank_8 ) \
  | (1 << AStudDeck_Rank_9 ) \
  | (1 << AStudDeck_Rank_TEN ))

extern const char *AStudRules_handTypeNames[AStudRules_HandType_LAST+1];
extern const char *AStudRules_handTypeNamesPadded[AStudRules_HandType_LAST+1];

extern int AStudRules_nSigCards[AStudRules_HandType_LAST+1];
extern int AStudRules_HandVal_toString(HandVal handval, char *outString); 
extern int AStudRules_HandVal_print(HandVal handval);

#endif

#ifdef RULES_ASTUD

#if defined(HandType_COUNT)
#include "rules_undef.h"
#endif

#define HandType_NOPAIR    AStudRules_HandType_NOPAIR    
#define HandType_ONEPAIR   AStudRules_HandType_ONEPAIR   
#define HandType_TWOPAIR   AStudRules_HandType_TWOPAIR   
#define HandType_TRIPS     AStudRules_HandType_TRIPS     
#define HandType_STRAIGHT  AStudRules_HandType_STRAIGHT  
#define HandType_FLUSH     AStudRules_HandType_FLUSH     
#define HandType_FULLHOUSE AStudRules_HandType_FULLHOUSE 
#define HandType_QUADS     AStudRules_HandType_QUADS     
#define HandType_STFLUSH   AStudRules_HandType_STFLUSH    
#define HandType_FIRST     AStudRules_HandType_FIRST  
#define HandType_COUNT     AStudRules_HandType_COUNT     
#define HandType_LAST      AStudRules_HandType_LAST

#define handTypeNames        AStudRules_handTypeNames
#define handTypeNamesPadded  AStudRules_handTypeNamesPadded
#define nSigCards            AStudRules_nSigCards
#define HandVal_print        AStudRules_HandVal_print
#define HandVal_toString     AStudRules_HandVal_toString

#endif

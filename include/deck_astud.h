/*
   Note that this file has two #if .. #endif sections -- one for 
   StdDeck macros to prevent double-inclusion, and one to define the 
   generic Deck_ macros if DECK_ASTUD is defined 
*/

#ifndef __DECK_ASTUD_H__
#define __DECK_ASTUD_H__

#define AStudDeck_N_CARDS      32
#define AStudDeck_MASK(index)  (AStudDeck_cardMasksTable[index])

#define AStudDeck_Rank_7      StdDeck_Rank_7
#define AStudDeck_Rank_8      StdDeck_Rank_8
#define AStudDeck_Rank_9      StdDeck_Rank_9
#define AStudDeck_Rank_TEN    StdDeck_Rank_TEN
#define AStudDeck_Rank_JACK   StdDeck_Rank_JACK
#define AStudDeck_Rank_QUEEN  StdDeck_Rank_QUEEN
#define AStudDeck_Rank_KING   StdDeck_Rank_KING
#define AStudDeck_Rank_ACE    StdDeck_Rank_ACE
#define AStudDeck_Rank_FIRST  AStudDeck_Rank_7
#define AStudDeck_Rank_LAST   AStudDeck_Rank_ACE
#define AStudDeck_Rank_COUNT  8
#define AStudDeck_N_RANKMASKS (1 << AStudDeck_Rank_COUNT)

#define AStudDeck_RANK(index)  (AStudDeck_Rank_FIRST \
                                + ((index) % AStudDeck_Rank_COUNT))
#define AStudDeck_SUIT(index)  ((index) / AStudDeck_Rank_COUNT)
#define AStudDeck_MAKE_CARD(rank, suit) ((suit * AStudDeck_Rank_COUNT) \
                                         + ( rank - AStudDeck_Rank_FIRST ))

#define AStudDeck_Suit_HEARTS   StdDeck_Suit_HEARTS
#define AStudDeck_Suit_DIAMONDS StdDeck_Suit_DIAMONDS
#define AStudDeck_Suit_CLUBS    StdDeck_Suit_CLUBS
#define AStudDeck_Suit_SPADES   StdDeck_Suit_SPADES
#define AStudDeck_Suit_FIRST    AStudDeck_Suit_HEARTS
#define AStudDeck_Suit_LAST     AStudDeck_Suit_SPADES
#define AStudDeck_Suit_COUNT    4

typedef StdDeck_RankMask AStudDeck_RankMask;

#define AStudDeck_CardMask          StdDeck_CardMask
#define AStudDeck_CardMask_SPADES   StdDeck_CardMask_SPADES
#define AStudDeck_CardMask_CLUBS    StdDeck_CardMask_CLUBS
#define AStudDeck_CardMask_DIAMONDS StdDeck_CardMask_DIAMONDS
#define AStudDeck_CardMask_HEARTS   StdDeck_CardMask_HEARTS

#define AStudDeck_CardMask_OR          StdDeck_CardMask_OR
#define AStudDeck_CardMask_AND         StdDeck_CardMask_AND
#define AStudDeck_CardMask_ANY_SET     StdDeck_CardMask_ANY_SET
#define AStudDeck_CardMask_RESET       StdDeck_CardMask_RESET

#ifdef HAVE_INT64                                                          
#define AStudDeck_CardMask_CARD_IS_SET(mask, index)                       \
  (( (mask).cards_n & (AStudDeck_MASK(index).cards_n)) != 0 )                 
#else                                                                   
#define AStudDeck_CardMask_CARD_IS_SET(mask, index)                       \
  ((( (mask).cards_nn.n1 & (AStudDeck_MASK(index).cards_nn.n1)) != 0 )    \
   || (( (mask).cards_nn.n2 & (AStudDeck_MASK(index).cards_nn.n2)) != 0 ))   
#endif

#define AStudDeck_CardMask_SET(mask, index)     \
do {                                            \
  AStudDeck_CardMask _t1 = AStudDeck_MASK(index);         \
  AStudDeck_CardMask_OR((mask), (mask), _t1);             \
} while (0)

extern AStudDeck_CardMask AStudDeck_cardMasksTable[AStudDeck_N_CARDS];

extern const char AStudDeck_rankChars[AStudDeck_Rank_LAST+1];
extern const char AStudDeck_suitChars[AStudDeck_Suit_LAST+1];

extern int AStudDeck_cardToString(int cardIndex, char *outString);
extern int AStudDeck_stringToCard(char *inString, int *outCard);

#define AStudDeck_cardString(i) GenericDeck_cardString(AStudDeck, (i))
#define AStudDeck_printCard(i)  GenericDeck_printCard(AStudDeck, (i))
#define AStudDeck_printMask(m)  GenericDeck_printMask(AStudDeck, (m))
#define AStudDeck_maskString(m) GenericDeck_maskString(AStudDeck, (m))
#define AStudDeck_maskToString(m, s) GenericDeck_maskToString(AStudDeck, (m), (s))

extern Deck AStudDeck;

#endif



#ifdef DECK_ASTUD

#if defined(Deck_N_CARDS)
#include "deck_undef.h"
#endif

#define Deck_N_CARDS      AStudDeck_N_CARDS
#define Deck_MASK         AStudDeck_MASK
#define Deck_RANK         AStudDeck_RANK
#define Deck_SUIT         AStudDeck_SUIT

#define Rank_7            AStudDeck_Rank_7 
#define Rank_8            AStudDeck_Rank_8 
#define Rank_9            AStudDeck_Rank_9 
#define Rank_TEN          AStudDeck_Rank_TEN
#define Rank_JACK         AStudDeck_Rank_JACK
#define Rank_QUEEN        AStudDeck_Rank_QUEEN
#define Rank_KING         AStudDeck_Rank_KING
#define Rank_ACE          AStudDeck_Rank_ACE
#define Rank_FIRST        AStudDeck_Rank_FIRST 
#define Rank_COUNT        AStudDeck_Rank_COUNT

#define Suit_HEARTS       AStudDeck_Suit_HEARTS
#define Suit_DIAMONDS     AStudDeck_Suit_DIAMONDS
#define Suit_CLUBS        AStudDeck_Suit_CLUBS
#define Suit_SPADES       AStudDeck_Suit_SPADES
#define Suit_FIRST        AStudDeck_Suit_FIRST
#define Suit_COUNT        AStudDeck_Suit_COUNT

#define CardMask               AStudDeck_CardMask 
#define CardMask_OR            AStudDeck_CardMask_OR
#define CardMask_SET           AStudDeck_CardMask_SET
#define CardMask_CARD_IS_SET   AStudDeck_CardMask_CARD_IS_SET
#define CardMask_ANY_SET       AStudDeck_CardMask_ANY_SET
#define CardMask_RESET         AStudDeck_CardMask_RESET

#define CardMask_SPADES        AStudDeck_CardMask_SPADES
#define CardMask_HEARTS        AStudDeck_CardMask_HEARTS
#define CardMask_CLUBS         AStudDeck_CardMask_CLUBS
#define CardMask_DIAMONDS      AStudDeck_CardMask_DIAMONDS

#define CurDeck AStudDeck

#endif /* DECK_ASTUD */


#ifdef HAVE_INT64
#define LongLong_OP(result, op1, op2, operation) \
  do { result = (op1) operation (op2); } while (0)
#define LongLong_OR(result, op1, op2)  LongLong_OP(result, op1, op2, |)
#define LongLong_AND(result, op1, op2) LongLong_OP(result, op1, op2, &)
#endif

#define StdDeck_FIRST_CARD   0
#define StdDeck_N_CARDS      52
#define StdDeck_MASK(index)  (StdDeck_cardMasksTable[index])

#define StdDeck_RANK(index)  ((index) % 13)
#define StdDeck_SUIT(index)  ((index) / 13)

#define StdDeck_Rank_2      0
#define StdDeck_Rank_3      1
#define StdDeck_Rank_4      2
#define StdDeck_Rank_5      3
#define StdDeck_Rank_6      4
#define StdDeck_Rank_7      5
#define StdDeck_Rank_8      6
#define StdDeck_Rank_9      7
#define StdDeck_Rank_TEN    8
#define StdDeck_Rank_JACK   9
#define StdDeck_Rank_QUEEN  10
#define StdDeck_Rank_KING   11
#define StdDeck_Rank_ACE    12
#define StdDeck_Rank_COUNT  13
#define StdDeck_Rank_FIRST  StdDeck_Rank_2
#define StdDeck_N_RANKMASKS (1 << StdDeck_Rank_COUNT)

#define StdDeck_Suit_HEARTS   0
#define StdDeck_Suit_DIAMONDS 1
#define StdDeck_Suit_CLUBS    2
#define StdDeck_Suit_SPADES   3
#define StdDeck_Suit_FIRST    StdDeck_Suit_HEARTS
#define StdDeck_Suit_COUNT    4

typedef uint32 StdDeck_RankMask;

typedef union {
#ifdef HAVE_INT64
  uint64  cards_n;
#else
  struct {
    uint32 n1, n2;
  } cards_nn;
#endif
  struct {
    uint32         :(16 - StdDeck_Rank_COUNT);
    uint32 spades  :StdDeck_Rank_COUNT;
    uint32         :(16 - StdDeck_Rank_COUNT);
    uint32 clubs   :StdDeck_Rank_COUNT;
    uint32         :(16 - StdDeck_Rank_COUNT);
    uint32 diamonds:StdDeck_Rank_COUNT;
    uint32         :(16 - StdDeck_Rank_COUNT);
    uint32 hearts  :StdDeck_Rank_COUNT;
  } cards;
} StdDeck_CardMask;

#if HAVE_INT64
#define StdDeck_CardMask_OR(result, op1, op2) \
  LongLong_OR((result).cards_n, (op1).cards_n, (op2).cards_n) 
#else
#define StdDeck_CardMask_OR(result, op1, op2)                           \
  do {                                                                  \
    (result.cards_nn.n1) = (op1.cards_nn.n1) | (op2.cards_nn.n1);       \
    (result.cards_nn.n2) = (op1.cards_nn.n2) | (op2.cards_nn.n2);       \
} while (0)
#endif

#define StdDeck_CardMask_AND(result, op1, op2) \
  LongLong_AND((result).cards_n, (op1).cards_n, (op2).cards_n) 

#define StdDeck_CardMask_SET(mask, index)       \
do {                                            \
  CardMask _t1 = Deck_MASK(index);              \
  CardMask_OR((mask), (mask), _t1);             \
} while (0)

#ifdef HAVE_INT64                                                          
#define StdDeck_CardMask_CARD_IS_SET(mask, index)                       \
  (( (mask).cards_n & (Deck_MASK(index).cards_n)) != 0 )                 
#else                                                                   
#define StdDeck_CardMask_CARD_IS_SET(mask, index)                       \
  ((( (mask).cards_nn.n1 & (Deck_MASK(index).cards_nn.n1)) != 0 )       \
   || (( (mask).cards_nn.n2 & (Deck_MASK(index).cards_nn.n2)) != 0 ))   
#endif

#ifdef HAVE_INT64                                                          
#define StdDeck_CardMask_ANY_SET(mask1, mask2)                          \
  (( (mask1).cards_n & (mask2).cards_n) != 0 )                 
#else                                                                   
#define StdDeck_CardMask_ANY_SET(mask, index)                           \
  ((( (mask1).cards_nn.n1 & (mask2).cards_nn.n1) != 0 )                 \
   || (( (mask1).cards_nn.n2 & (mask2).cards_nn.n2) != 0 ))           
#endif

#ifdef HAVE_INT64
#define StdDeck_CardMask_RESET(mask) \
  do { (mask).cards_n = 0; } while (0)
#else
#define StdDeck_CardMask_RESET(mask) \
  do { (mask).cards_nn.n1 = (mask).cards_nn.n2 = 0; } while (0)
#endif

extern uint8          nBitsTable[StdDeck_N_RANKMASKS];
extern uint32  topFiveCardsTable[StdDeck_N_RANKMASKS];
extern uint32    topFiveBitTable[StdDeck_N_RANKMASKS];
extern uint8        topCardTable[StdDeck_N_RANKMASKS];
extern uint32        topBitTable[StdDeck_N_RANKMASKS];
extern uint32    topTwoBitsTable[StdDeck_N_RANKMASKS];
extern uint32   topFiveBitsTable[StdDeck_N_RANKMASKS];
extern uint8       straightTable[StdDeck_N_RANKMASKS];
extern StdDeck_CardMask StdDeck_cardMasksTable[StdDeck_N_CARDS];

extern const char StdDeck_rankChars[StdDeck_Rank_COUNT];
extern const char StdDeck_suitChars[StdDeck_Suit_COUNT];

extern int StdDeck_cardToString(int cardIndex, char *outString);
extern int StdDeck_maskToString(StdDeck_CardMask cardMask, char *outString);
extern int StdDeck_printCard(int cardIndex);
extern int StdDeck_printMask(StdDeck_CardMask cardMask);
extern int StdDeck_stringToMask(char *inString, StdDeck_CardMask outMask);


#ifndef NONSTANDARD_DECK
#define Deck_FIRST_CARD   StdDeck_FIRST_CARD
#define Deck_N_CARDS      StdDeck_N_CARDS
#define Deck_MASK         StdDeck_MASK
#define Deck_RANK         StdDeck_RANK
#define Deck_SUIT         StdDeck_SUIT

#define Deck_cardToString StdDeck_cardToString
#define Deck_maskToString StdDeck_maskToString
#define Deck_printCard    StdDeck_printCard
#define Deck_printMask    StdDeck_printMask
#define Deck_stringToMask StdDeck_stringToMask

#define Rank_2            StdDeck_Rank_2 
#define Rank_3            StdDeck_Rank_3
#define Rank_4            StdDeck_Rank_4 
#define Rank_5            StdDeck_Rank_5 
#define Rank_6            StdDeck_Rank_6 
#define Rank_7            StdDeck_Rank_7 
#define Rank_8            StdDeck_Rank_8 
#define Rank_9            StdDeck_Rank_9 
#define Rank_TEN          StdDeck_Rank_TEN
#define Rank_JACK         StdDeck_Rank_JACK
#define Rank_QUEEN        StdDeck_Rank_QUEEN
#define Rank_KING         StdDeck_Rank_KING
#define Rank_ACE          StdDeck_Rank_ACE
#define Rank_FIRST        StdDeck_Rank_FIRST 
#define Rank_COUNT        StdDeck_Rank_COUNT

#define Suit_HEARTS       StdDeck_Suit_HEARTS
#define Suit_DIAMONDS     StdDeck_Suit_DIAMONDS
#define Suit_CLUBS        StdDeck_Suit_CLUBS
#define Suit_SPADES       StdDeck_Suit_SPADES
#define Suit_FIRST        StdDeck_Suit_FIRST
#define Suit_COUNT        StdDeck_Suit_COUNT

#define CardMask               StdDeck_CardMask 
#define CardMask_OR            StdDeck_CardMask_OR
#define CardMask_SET           StdDeck_CardMask_SET
#define CardMask_CARD_IS_SET   StdDeck_CardMask_CARD_IS_SET
#define CardMask_ANY_SET       StdDeck_CardMask_ANY_SET
#define CardMask_RESET         StdDeck_CardMask_RESET

#endif


#ifndef __JOKERDECK_H__
#define __JOKERDECK_H__

#define JokerDeck_N_CARDS      53
#define JokerDeck_MASK(index)  (JokerDeck_cardMasksTable[index])

#define JokerDeck_Rank_2      StdDeck_Rank_2
#define JokerDeck_Rank_3      StdDeck_Rank_3
#define JokerDeck_Rank_4      StdDeck_Rank_4
#define JokerDeck_Rank_5      StdDeck_Rank_5
#define JokerDeck_Rank_6      StdDeck_Rank_6
#define JokerDeck_Rank_7      StdDeck_Rank_7
#define JokerDeck_Rank_8      StdDeck_Rank_8
#define JokerDeck_Rank_9      StdDeck_Rank_9
#define JokerDeck_Rank_TEN    StdDeck_Rank_TEN
#define JokerDeck_Rank_JACK   StdDeck_Rank_JACK
#define JokerDeck_Rank_QUEEN  StdDeck_Rank_QUEEN
#define JokerDeck_Rank_KING   StdDeck_Rank_KING
#define JokerDeck_Rank_ACE    StdDeck_Rank_ACE
#define JokerDeck_Rank_COUNT  StdDeck_Rank_COUNT
#define JokerDeck_Rank_FIRST  StdDeck_Rank_FIRST
#define JokerDeck_Rank_LAST   StdDeck_Rank_LAST
#define JokerDeck_N_RANKMASKS StdDeck_N_RANKMASKS

#define JokerDeck_RANK          StdDeck_RANK
#define JokerDeck_SUIT          StdDeck_SUIT
#define JokerDeck_IS_JOKER(index) (index == JokerDeck_JOKER)
#define JokerDeck_MAKE_CARD     StdDeck_MAKE_CARD
#define JokerDeck_JOKER        (JokerDeck_N_CARDS - 1)

#define JokerDeck_Suit_HEARTS   StdDeck_Suit_HEARTS
#define JokerDeck_Suit_DIAMONDS StdDeck_Suit_DIAMONDS
#define JokerDeck_Suit_CLUBS    StdDeck_Suit_CLUBS
#define JokerDeck_Suit_SPADES   StdDeck_Suit_SPADES
#define JokerDeck_Suit_FIRST    StdDeck_Suit_FIRST
#define JokerDeck_Suit_LAST     StdDeck_Suit_LAST
#define JokerDeck_Suit_COUNT    StdDeck_Suit_COUNT

typedef uint32 JokerDeck_RankMask;

typedef union {
#ifdef HAVE_INT64
  uint64  cards_n;
#else
  struct {
    uint32 n1, n2;
  } cards_nn;
#endif
  struct {
    uint32         : (16 - JokerDeck_Rank_COUNT - 1);
    uint32 joker   : 1;
    uint32 spades  : JokerDeck_Rank_COUNT;
    uint32         : (16 - JokerDeck_Rank_COUNT);
    uint32 clubs   : JokerDeck_Rank_COUNT;
    uint32         : (16 - JokerDeck_Rank_COUNT);
    uint32 diamonds: JokerDeck_Rank_COUNT;
    uint32         : (16 - JokerDeck_Rank_COUNT);
    uint32 hearts  : JokerDeck_Rank_COUNT;
  } cards;
} JokerDeck_CardMask;

#define JokerDeck_CardMask_SPADES(cm)   ((cm).cards.spades)
#define JokerDeck_CardMask_CLUBS(cm)    ((cm).cards.clubs)
#define JokerDeck_CardMask_DIAMONDS(cm) ((cm).cards.diamonds)
#define JokerDeck_CardMask_HEARTS(cm)   ((cm).cards.hearts)
#define JokerDeck_CardMask_JOKER(cm)    ((cm).cards.joker)

#define JokerDeck_CardMask_OR          StdDeck_CardMask_OR
#define JokerDeck_CardMask_AND         StdDeck_CardMask_AND
#define JokerDeck_CardMask_SET         StdDeck_CardMask_SET
#define JokerDeck_CardMask_ANY_SET     StdDeck_CardMask_ANY_SET
#define JokerDeck_CardMask_RESET       StdDeck_CardMask_RESET

#ifdef HAVE_INT64                                                          
#define JokerDeck_CardMask_CARD_IS_SET(mask, index)                       \
  (( (mask).cards_n & (JokerDeck_MASK(index).cards_n)) != 0 )                 
#else                                                                   
#define JokerDeck_CardMask_CARD_IS_SET(mask, index)                       \
  ((( (mask).cards_nn.n1 & (JokerDeck_MASK(index).cards_nn.n1)) != 0 )    \
   || (( (mask).cards_nn.n2 & (JokerDeck_MASK(index).cards_nn.n2)) != 0 ))   
#endif

extern JokerDeck_CardMask JokerDeck_cardMasksTable[JokerDeck_N_CARDS];

extern const char JokerDeck_rankChars[JokerDeck_Rank_LAST+1];
extern const char JokerDeck_suitChars[JokerDeck_Suit_LAST+1];

extern int JokerDeck_cardToString(int cardIndex, char *outString);
extern int JokerDeck_maskToString(JokerDeck_CardMask cardMask, char *outString);
extern int JokerDeck_printCard(int cardIndex);
extern int JokerDeck_printMask(JokerDeck_CardMask cardMask);
extern int JokerDeck_stringToMask(char *inString, JokerDeck_CardMask *outMask);


#ifdef USE_JOKER_DECK

#define Deck_N_CARDS      JokerDeck_N_CARDS
#define Deck_MASK         JokerDeck_MASK
#define Deck_RANK         JokerDeck_RANK
#define Deck_SUIT         JokerDeck_SUIT

#define Deck_cardToString JokerDeck_cardToString
#define Deck_maskToString JokerDeck_maskToString
#define Deck_printCard    JokerDeck_printCard
#define Deck_printMask    JokerDeck_printMask
#define Deck_stringToMask JokerDeck_stringToMask

#define Rank_2            JokerDeck_Rank_2 
#define Rank_3            JokerDeck_Rank_3
#define Rank_4            JokerDeck_Rank_4 
#define Rank_5            JokerDeck_Rank_5 
#define Rank_6            JokerDeck_Rank_6 
#define Rank_7            JokerDeck_Rank_7 
#define Rank_8            JokerDeck_Rank_8 
#define Rank_9            JokerDeck_Rank_9 
#define Rank_TEN          JokerDeck_Rank_TEN
#define Rank_JACK         JokerDeck_Rank_JACK
#define Rank_QUEEN        JokerDeck_Rank_QUEEN
#define Rank_KING         JokerDeck_Rank_KING
#define Rank_ACE          JokerDeck_Rank_ACE
#define Rank_FIRST        JokerDeck_Rank_FIRST 
#define Rank_COUNT        JokerDeck_Rank_COUNT

#define Suit_HEARTS       JokerDeck_Suit_HEARTS
#define Suit_DIAMONDS     JokerDeck_Suit_DIAMONDS
#define Suit_CLUBS        JokerDeck_Suit_CLUBS
#define Suit_SPADES       JokerDeck_Suit_SPADES
#define Suit_FIRST        JokerDeck_Suit_FIRST
#define Suit_COUNT        JokerDeck_Suit_COUNT

#define CardMask               JokerDeck_CardMask 
#define CardMask_OR            JokerDeck_CardMask_OR
#define CardMask_SET           JokerDeck_CardMask_SET
#define CardMask_CARD_IS_SET   JokerDeck_CardMask_CARD_IS_SET
#define CardMask_ANY_SET       JokerDeck_CardMask_ANY_SET
#define CardMask_RESET         JokerDeck_CardMask_RESET

#define CardMask_SPADES        JokerDeck_CardMask_SPADES
#define CardMask_HEARTS        JokerDeck_CardMask_HEARTS
#define CardMask_CLUBS         JokerDeck_CardMask_CLUBS
#define CardMask_DIAMONDS      JokerDeck_CardMask_DIAMONDS

#endif 

#endif

#ifndef __DECK_H__
#define __DECK_H__

typedef int     Deck_cardToStringFn(int cardIndex, char *outString);
typedef int     Deck_maskToCardsFn(void *cardMask, int cardIndices[]);
typedef int     Deck_stringToCardFn(char *inString, int *index);
typedef int     Deck_numCardsFn(void *cardMask);

typedef struct {
  int                  nCards;
  char *               name;
  Deck_cardToStringFn *cardToString;
  Deck_stringToCardFn *stringToCard;
  Deck_maskToCardsFn  *maskToCards;
  Deck_numCardsFn     *numCards;
} Deck;

#define Deck_cardToString       (CurDeck.cardToString)
#define Deck_stringToCard       (CurDeck.stringToCard)
#define Deck_cardString(i)      GenericDeck_cardString(CurDeck, (i))
#define Deck_printCard(i)       GenericDeck_printCard(CurDeck, (i))

#define Deck_printMask(m)       \
        GenericDeck_printMask(&CurDeck, ((void *) &(m)))

#define Deck_maskString(m)      \
        GenericDeck_maskString(&CurDeck, ((void *) &(m)))

#define Deck_numCards(m)      \
        GenericDeck_numCards(&CurDeck, ((void *) &(m)))

#define Deck_maskToString(m, s) \
        GenericDeck_maskToString(&CurDeck, ((void *) &(m)), (s))

/* As an alternative to the CurDeck approach, provide another set of macros
   that accept an object of type Deck as an argument. */
#define DcardToString(d, c, s) ((d).cardToString((c), (s)))
#define DstringToCard(d, s, i) ((d).stringToCard((s), (i)))
#define DcardString(d, i) (GenericDeck_cardString(&(d), (i)))
#define DprintCard(d, i) (GenericDeck_printCard(&(d), (i)))
#define DprintMask(d, m) (GenericDeck_printMask(&(d), ((void *) &(m))))
#define DmaskString(d, m) (GenericDeck_maskString(&(d), ((void *) &(m))))
#define DnumCards(d, m) (GenericDeck_numCards(&(d), ((void *) &(m))))
#define DmaskToString(d, m, s) (GenericDeck_maskString(&(d), ((void *) &(m)), (s)))

extern char *
GenericDeck_cardString(Deck *deck, int cardIndex);
extern int 
GenericDeck_printMask(Deck *deck, void *cardMask);
extern int
GenericDeck_maskToString(Deck *deck, void *cardMask, char *outString);
extern char *
GenericDeck_maskString(Deck *deck, void *cardMask);
extern int
GenericDeck_printCard(Deck *deck, int cardIndex);
extern int
GenericDeck_numCards(Deck *deck, void *cardMask);

/* These are required by the ENUMERATE_ macros */

#define Deck_CardMask              CardMask
#define Deck_CardMask_OR           CardMask_OR
#define Deck_CardMask_XOR          CardMask_XOR
#define Deck_CardMask_AND          CardMask_AND
#define Deck_CardMask_RESET        CardMask_RESET
#define Deck_CardMask_ANY_SET      CardMask_ANY_SET
#define Deck_CardMask_CARD_IS_SET  CardMask_CARD_IS_SET

#endif


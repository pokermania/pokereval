#include <stdio.h>

#include "poker_defs.h"
#include "jokerdeck.h"
#include "mktable.h"

#define JCM_COMMENT_STRING \
 "JokerDeck_cardMasks[].  Maps card indices (0..53) to CardMasks.  \n"       \
 "The output mask has only one bit set, the bit corresponding to the card\n" \
 "identified by the index." 
#define JCM_FILENAME "t_jokercardmasks"



static void 
doCardMaskTable(void) {
  JokerDeck_CardMask c;
  int i;

  MakeTable_begin("JokerDeck_cardMasksTable", 
                  JCM_FILENAME, 
                  "JokerDeck_CardMask", 
                  JokerDeck_N_CARDS);
  MakeTable_comment(JCM_COMMENT_STRING);
  MakeTable_extraCode("#include \"jokerdeck.h\"");
  for (i=0; i<JokerDeck_N_CARDS; i++) {
    JokerDeck_CardMask_RESET(c);
    if (JokerDeck_IS_JOKER(i))
      c.cards.joker = 1;
    else {
      int suit = JokerDeck_SUIT(i);
      int rank = JokerDeck_RANK(i);
      if (suit == JokerDeck_Suit_HEARTS)
        c.cards.hearts = (1 << rank);
      else if (suit == JokerDeck_Suit_DIAMONDS)
        c.cards.diamonds = (1 << rank);
      else if (suit == JokerDeck_Suit_CLUBS)
        c.cards.clubs = (1 << rank);
      else if (suit == JokerDeck_Suit_SPADES)
        c.cards.spades = (1 << rank);
    };

#ifdef HAVE_INT64
    MakeTable_outputUInt64(c.cards_n);
#else
    {
      char buf[80];
      sprintf(buf, " { { 0x%08x, 0x%08x } } ", c.cards_nn.n1, c.cards_nn.n2);
      MakeTable_outputString(buf);
    };
#endif
  };

  MakeTable_end();
}


int 
main(int argc, char **argv) {
  doCardMaskTable();

  return 0;
}


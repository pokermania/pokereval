#define ENUMERATE_1_CARDS(cards_var, action)    \
{                                               \
  int _i1;                                      \
  CardMask _card;                               \
                                                \
  for (_i1 = Deck_N_CARDS-1; _i1 >= 0; _i1--) { \
    _card = Deck_MASK(_i1);                     \
    cards_var = _card;                          \
    do { action } while (0);                    \
  };                                            \
}

#define ENUMERATE_2_CARDS(cards_var, action)    \
{                                               \
  int _i1, _i2;                                 \
  CardMask _card1, _card2,                      \
    _n2;                                        \
                                                \
  for (_i1 = Deck_N_CARDS-1; _i1 >= 0; _i1--) { \
    _card1 = Deck_MASK(_i1);                    \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {        \
      _card2 = Deck_MASK(_i2);                  \
      CardMask_OR(_n2, _card1, _card2);         \
      cards_var = _n2;                          \
      do { action } while (0);                  \
    };                                          \
  };                                            \
}                                               \

#define ENUMERATE_3_CARDS(cards_var, action)    \
{                                               \
  int _i1, _i2, _i3;                            \
  CardMask _card1, _card2, _card3,              \
    _n2, _n3;                                   \
                                                \
  for (_i1 = Deck_N_CARDS-1; _i1 >= 0; _i1--) { \
    _card1 = Deck_MASK(_i1);                    \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {        \
      _card2 = Deck_MASK(_i2);                  \
      CardMask_OR(_n2, _card1, _card2);         \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {      \
        _card3 = Deck_MASK(_i3);                \
	CardMask_OR(_n3, _n2, _card3);          \
        cards_var = _n3;                        \
        do { action } while (0);                \
      };                                        \
    };                                          \
  };                                            \
}

#define ENUMERATE_4_CARDS(cards_var, action)    \
{                                               \
  int _i1, _i2, _i3, _i4;                       \
  CardMask _card1, _card2, _card3, _card4,      \
    _n2, _n3, _n4;                              \
                                                \
  for (_i1 = Deck_N_CARDS-1; _i1 >= 0; _i1--) { \
    _card1 = Deck_MASK(_i1);                    \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {        \
      _card2 = Deck_MASK(_i2);                  \
      CardMask_OR(_n2, _card1, _card2);         \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {      \
        _card3 = Deck_MASK(_i3);                \
	CardMask_OR(_n3, _n2, _card3);          \
        for (_i4 = _i3-1; _i4 >= 0; _i4--) {    \
          _card4 = Deck_MASK(_i4);              \
	  CardMask_OR(_n4, _n3, _card4);        \
          cards_var = _n4;                      \
          do { action } while (0);              \
        };                                      \
      };                                        \
    };                                          \
  };                                            \
}

#define ENUMERATE_5_CARDS(cards_var, action)            \
{                                                       \
  int _i1, _i2, _i3, _i4, _i5;                          \
  CardMask _card1, _card2, _card3, _card4, _card5,      \
    _n2, _n3, _n4, _n5;                                 \
                                                        \
  for (_i1 = Deck_N_CARDS-1; _i1 >= 0; _i1--) {         \
    _card1 = Deck_MASK(_i1);                            \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                \
      _card2 = Deck_MASK(_i2);                          \
      CardMask_OR(_n2, _card1, _card2);                 \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {              \
        _card3 = Deck_MASK(_i3);                        \
	CardMask_OR(_n3, _n2, _card3);                  \
        for (_i4 = _i3-1; _i4 >= 0; _i4--) {            \
          _card4 = Deck_MASK(_i4);                      \
	  CardMask_OR(_n4, _n3, _card4);                \
          for (_i5 = _i4-1; _i5 >= 0; _i5--) {          \
            _card5 = Deck_MASK(_i5);                    \
            CardMask_OR(_n5, _n4, _card5);              \
            cards_var = _n5;                            \
            do { action } while (0);                    \
          };                                            \
        };                                              \
      };                                                \
    };                                                  \
  };                                                    \
}


#define ENUMERATE_1_CARDS_D(cards_var, dead_cards, action)      \
{                                                               \
  int _i1;                                                      \
  CardMask _card;                                               \
                                                                \
  for (_i1 = Deck_N_CARDS-1; _i1 >= 0; _i1--) {                 \
    _card = Deck_MASK(_i1);                                     \
    if (CardMask_ANY_SET(dead_cards, _card))                    \
      continue;                                                 \
    cards_var = _card;                                          \
    do { action } while (0);                                    \
  };                                                            \
}

#define ENUMERATE_2_CARDS_D(cards_var, dead_cards, action)      \
{                                                               \
  int _i1, _i2;                                                 \
  CardMask _card1, _card2,                                      \
    _n2;                                                        \
                                                                \
  for (_i1 = Deck_N_CARDS-1; _i1 >= 0; _i1--) {                 \
    _card1 = Deck_MASK(_i1);                                    \
    if (CardMask_ANY_SET(dead_cards, _card1))                   \
      continue;                                                 \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                        \
      _card2 = Deck_MASK(_i2);                                  \
      if (CardMask_ANY_SET(dead_cards, _card2))                 \
        continue;                                               \
      CardMask_OR(_n2, _card1, _card2);                         \
      cards_var = _n2;                                          \
      do { action } while (0);                                  \
    };                                                          \
  };                                                            \
}

#define ENUMERATE_3_CARDS_D(cards_var, dead_cards, action)      \
{                                                               \
  int _i1, _i2, _i3;                                            \
  CardMask _card1, _card2, _card3,                              \
    _n2, _n3;                                                   \
                                                                \
  for (_i1 = Deck_N_CARDS-1; _i1 >= 0; _i1--) {                 \
    _card1 = Deck_MASK(_i1);                                    \
    if (CardMask_ANY_SET(dead_cards, _card1))                   \
      continue;                                                 \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                        \
      _card2 = Deck_MASK(_i2);                                  \
      if (CardMask_ANY_SET(dead_cards, _card2))                 \
        continue;                                               \
      CardMask_OR(_n2, _card1, _card2);                         \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {                      \
        _card3 = Deck_MASK(_i3);                                \
        if (CardMask_ANY_SET(dead_cards, _card3))               \
          continue;                                             \
	CardMask_OR(_n3, _n2, _card3);                          \
        cards_var = _n3;                                        \
        do { action } while (0);                                \
      };                                                        \
    };                                                          \
  };                                                            \
}

#define ENUMERATE_4_CARDS_D(cards_var, dead_cards, action)      \
{                                                               \
  int _i1, _i2, _i3, _i4;                                       \
  CardMask _card1, _card2, _card3, _card4,                      \
    _n2, _n3, _n4;                                              \
                                                                \
  for (_i1 = Deck_N_CARDS-1; _i1 >= 0; _i1--) {                 \
    _card1 = Deck_MASK(_i1);                                    \
    if (CardMask_ANY_SET(dead_cards, _card1))                   \
      continue;                                                 \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                        \
      _card2 = Deck_MASK(_i2);                                  \
      if (CardMask_ANY_SET(dead_cards, _card2))                 \
        continue;                                               \
      CardMask_OR(_n2, _card1, _card2);                         \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {                      \
        _card3 = Deck_MASK(_i3);                                \
        if (CardMask_ANY_SET(dead_cards, _card3))               \
          continue;                                             \
	CardMask_OR(_n3, _n2, _card3);                          \
        for (_i4 = _i3-1; _i4 >= 0; _i4--) {                    \
          _card4 = Deck_MASK(_i4);                              \
          if (CardMask_ANY_SET(dead_cards, _card4))             \
            continue;                                           \
	  CardMask_OR(_n4, _n3, _card4);                        \
          cards_var = _n4;                                      \
          do { action } while (0);                              \
        };                                                      \
      };                                                        \
    };                                                          \
  };                                                            \
}

#define ENUMERATE_5_CARDS_D(cards_var, dead_cards, action)      \
{                                                               \
  int _i1, _i2, _i3, _i4, _i5;                                  \
  CardMask _card1, _card2, _card3, _card4, _card5,              \
    _n2, _n3, _n4, _n5;                                         \
                                                                \
  for (_i1 = Deck_N_CARDS-1; _i1 >= 0; _i1--) {                 \
    _card1 = Deck_MASK(_i1);                                    \
    if (CardMask_ANY_SET(dead_cards, _card1))                   \
      continue;                                                 \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                        \
      _card2 = Deck_MASK(_i2);                                  \
      if (CardMask_ANY_SET(dead_cards, _card2))                 \
        continue;                                               \
      CardMask_OR(_n2, _card1, _card2);                         \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {                      \
        _card3 = Deck_MASK(_i3);                                \
        if (CardMask_ANY_SET(dead_cards, _card3))               \
          continue;                                             \
	CardMask_OR(_n3, _n2, _card3);                          \
        for (_i4 = _i3-1; _i4 >= 0; _i4--) {                    \
          _card4 = Deck_MASK(_i4);                              \
          if (CardMask_ANY_SET(dead_cards, _card4))             \
            continue;                                           \
	  CardMask_OR(_n4, _n3, _card4);                        \
          for (_i5 = _i4-1; _i5 >= 0; _i5--) {                  \
            _card5 = Deck_MASK(_i5);                            \
            if (CardMask_ANY_SET(dead_cards, _card5))           \
              continue;                                         \
            CardMask_OR(_n5, _n4, _card5);                      \
            cards_var = _n5;                                    \
            do { action } while (0);                            \
          };                                                    \
        };                                                      \
      };                                                        \
    };                                                          \
  };                                                            \
}



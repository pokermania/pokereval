#define ENUMERATE_1_CARDS(cards_var, action)    \
{                                               \
  int _i1;                                      \
  CardMask _card;                               \
                                                \
  for (i1 = Deck_N_CARDS-1; _i1 >= 0; _i1--) {  \
    _card = Deck_MASK(_i1);                     \
    cards_var = _card;                          \
    do { action } while (0);                    \
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


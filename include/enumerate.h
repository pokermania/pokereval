#include <stdio.h>

#define DECK_ENUMERATE_1_CARDS(deck, cards_var, action) \
do {                                                    \
  int _i1;                                              \
  deck##_CardMask _card;                                \
                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {       \
    _card = deck##_MASK(_i1);                           \
    cards_var = _card;                                  \
    { action };                                         \
  };                                                    \
} while (0)

#define DECK_ENUMERATE_2_CARDS(deck, cards_var, action) \
do {                                                    \
  int _i1, _i2;                                         \
  deck##_CardMask _card1, _card2,                       \
    _n2;                                                \
                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {       \
    _card1 = deck##_MASK(_i1);                          \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                \
      _card2 = deck##_MASK(_i2);                        \
      deck##_CardMask_OR(_n2, _card1, _card2);          \
      cards_var = _n2;                                  \
      { action };                                       \
    };                                                  \
  };                                                    \
} while (0)

#define DECK_ENUMERATE_3_CARDS(deck, cards_var, action) \
do {                                                    \
  int _i1, _i2, _i3;                                    \
  deck##_CardMask _card1, _card2, _card3,               \
    _n2, _n3;                                           \
                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {       \
    _card1 = deck##_MASK(_i1);                          \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                \
      _card2 = deck##_MASK(_i2);                        \
      deck##_CardMask_OR(_n2, _card1, _card2);          \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {              \
        _card3 = deck##_MASK(_i3);                      \
	deck##_CardMask_OR(_n3, _n2, _card3);           \
        cards_var = _n3;                                \
        { action };                                     \
      };                                                \
    };                                                  \
  };                                                    \
} while (0)

#define DECK_ENUMERATE_4_CARDS(deck, cards_var, action) \
do {                                                    \
  int _i1, _i2, _i3, _i4;                               \
  deck##_CardMask _card1, _card2, _card3, _card4,       \
    _n2, _n3, _n4;                                      \
                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {       \
    _card1 = deck##_MASK(_i1);                          \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                \
      _card2 = deck##_MASK(_i2);                        \
      deck##_CardMask_OR(_n2, _card1, _card2);          \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {              \
        _card3 = deck##_MASK(_i3);                      \
	deck##_CardMask_OR(_n3, _n2, _card3);           \
        for (_i4 = _i3-1; _i4 >= 0; _i4--) {            \
          _card4 = deck##_MASK(_i4);                    \
	  deck##_CardMask_OR(_n4, _n3, _card4);         \
          cards_var = _n4;                              \
          { action };                                   \
        };                                              \
      };                                                \
    };                                                  \
  };                                                    \
} while (0)

#define DECK_ENUMERATE_5_CARDS(deck, cards_var, action)                   \
do {                                                                      \
  int _i1, _i2, _i3, _i4, _i5;                                            \
  deck##_CardMask _card1, _card2, _card3, _card4, _card5,                 \
    _n2, _n3, _n4, _n5;                                                   \
                                                                          \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                         \
    _card1 = deck##_MASK(_i1);                                            \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                  \
      _card2 = deck##_MASK(_i2);                                          \
      deck##_CardMask_OR(_n2, _card1, _card2);                            \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {                                \
        _card3 = deck##_MASK(_i3);                                        \
	deck##_CardMask_OR(_n3, _n2, _card3);                             \
        for (_i4 = _i3-1; _i4 >= 0; _i4--) {                              \
          _card4 = deck##_MASK(_i4);                                      \
	  deck##_CardMask_OR(_n4, _n3, _card4);                           \
          for (_i5 = _i4-1; _i5 >= 0; _i5--) {                            \
            _card5 = deck##_MASK(_i5);                                    \
            deck##_CardMask_OR(_n5, _n4, _card5);                         \
            cards_var = _n5;                                              \
            { action };                                                   \
          };                                                              \
        };                                                                \
      };                                                                  \
    };                                                                    \
  };                                                                      \
} while (0)                                                               
                                                                          
#define DECK_ENUMERATE_7_CARDS(deck, cards_var, action)                   \
do {                                                                      \
  int _i1, _i2, _i3, _i4, _i5, _i6, _i7;                                  \
  deck##_CardMask _card1, _card2, _card3, _card4, _card5, _card6, _card7, \
    _n2, _n3, _n4, _n5, _n6, _n7;                                         \
                                                                          \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                         \
    _card1 = deck##_MASK(_i1);                                            \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                  \
      _card2 = deck##_MASK(_i2);                                          \
      deck##_CardMask_OR(_n2, _card1, _card2);                            \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {                                \
        _card3 = deck##_MASK(_i3);                                        \
	deck##_CardMask_OR(_n3, _n2, _card3);                             \
        for (_i4 = _i3-1; _i4 >= 0; _i4--) {                              \
          _card4 = deck##_MASK(_i4);                                      \
	  deck##_CardMask_OR(_n4, _n3, _card4);                           \
          for (_i5 = _i4-1; _i5 >= 0; _i5--) {                            \
            _card5 = deck##_MASK(_i5);                                    \
            deck##_CardMask_OR(_n5, _n4, _card5);                         \
            for (_i6 = _i5-1; _i6 >= 0; _i6--) {                          \
              _card6 = deck##_MASK(_i6);                                  \
              deck##_CardMask_OR(_n6, _n5, _card6);                       \
              for (_i7 = _i6-1; _i7 >= 0; _i7--) {                        \
                _card7 = deck##_MASK(_i7);                                \
                deck##_CardMask_OR(_n7, _n6, _card7);                     \
                cards_var = _n7;                                          \
                { action };                                               \
              };                                                          \
            };                                                            \
          };                                                              \
        };                                                                \
      };                                                                  \
    };                                                                    \
  };                                                                      \
} while (0)


#define DECK_ENUMERATE_1_CARDS_D(deck, cards_var, dead_cards, action)   \
do {                                                                    \
  int _i1;                                                              \
  deck##_CardMask _card;                                                \
                                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                       \
    _card = deck##_MASK(_i1);                                           \
    if (deck##_CardMask_ANY_SET(dead_cards, _card))                     \
      continue;                                                         \
    cards_var = _card;                                                  \
    { action };                                                         \
  };                                                                    \
} while (0)

#define DECK_ENUMERATE_2_CARDS_D(deck, cards_var, dead_cards, action)   \
do {                                                                    \
  int _i1, _i2;                                                         \
  deck##_CardMask _card1, _card2,                                       \
    _n2;                                                                \
                                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                       \
    _card1 = deck##_MASK(_i1);                                          \
    if (deck##_CardMask_ANY_SET(dead_cards, _card1))                    \
      continue;                                                         \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                \
      _card2 = deck##_MASK(_i2);                                        \
      if (deck##_CardMask_ANY_SET(dead_cards, _card2))                  \
        continue;                                                       \
      deck##_CardMask_OR(_n2, _card1, _card2);                          \
      cards_var = _n2;                                                  \
      { action };                                                       \
    };                                                                  \
  };                                                                    \
} while (0)                                                             
                                                                        
#define DECK_ENUMERATE_3_CARDS_D(deck, cards_var, dead_cards, action)   \
do {                                                                    \
  int _i1, _i2, _i3;                                                    \
  deck##_CardMask _card1, _card2, _card3,                               \
    _n2, _n3;                                                           \
                                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                       \
    _card1 = deck##_MASK(_i1);                                          \
    if (deck##_CardMask_ANY_SET(dead_cards, _card1))                    \
      continue;                                                         \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                \
      _card2 = deck##_MASK(_i2);                                        \
      if (deck##_CardMask_ANY_SET(dead_cards, _card2))                  \
        continue;                                                       \
      deck##_CardMask_OR(_n2, _card1, _card2);                          \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {                              \
        _card3 = deck##_MASK(_i3);                                      \
        if (deck##_CardMask_ANY_SET(dead_cards, _card3))                \
          continue;                                                     \
	deck##_CardMask_OR(_n3, _n2, _card3);                           \
        cards_var = _n3;                                                \
        { action };                                                     \
      };                                                                \
    };                                                                  \
  };                                                                    \
} while (0)                                                             
                                                                        
#define DECK_ENUMERATE_4_CARDS_D(deck, cards_var, dead_cards, action)   \
do {                                                                    \
  int _i1, _i2, _i3, _i4;                                               \
  deck##_CardMask _card1, _card2, _card3, _card4,                       \
    _n2, _n3, _n4;                                                      \
                                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                       \
    _card1 = deck##_MASK(_i1);                                          \
    if (deck##_CardMask_ANY_SET(dead_cards, _card1))                    \
      continue;                                                         \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                \
      _card2 = deck##_MASK(_i2);                                        \
      if (deck##_CardMask_ANY_SET(dead_cards, _card2))                  \
        continue;                                                       \
      deck##_CardMask_OR(_n2, _card1, _card2);                          \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {                              \
        _card3 = deck##_MASK(_i3);                                      \
        if (deck##_CardMask_ANY_SET(dead_cards, _card3))                \
          continue;                                                     \
	deck##_CardMask_OR(_n3, _n2, _card3);                           \
        for (_i4 = _i3-1; _i4 >= 0; _i4--) {                            \
          _card4 = deck##_MASK(_i4);                                    \
          if (deck##_CardMask_ANY_SET(dead_cards, _card4))              \
            continue;                                                   \
	  deck##_CardMask_OR(_n4, _n3, _card4);                         \
          cards_var = _n4;                                              \
          { action };                                                   \
        };                                                              \
      };                                                                \
    };                                                                  \
  };                                                                    \
} while (0)                                                             
                                                                        
#define DECK_ENUMERATE_5_CARDS_D(deck, cards_var, dead_cards, action)   \
do {                                                                    \
  int _i1, _i2, _i3, _i4, _i5;                                          \
  deck##_CardMask _card1, _card2, _card3, _card4, _card5,               \
    _n2, _n3, _n4, _n5;                                                 \
                                                                        \
  for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                       \
    _card1 = deck##_MASK(_i1);                                          \
    if (deck##_CardMask_ANY_SET(dead_cards, _card1))                    \
      continue;                                                         \
    for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                \
      _card2 = deck##_MASK(_i2);                                        \
      if (deck##_CardMask_ANY_SET(dead_cards, _card2))                  \
        continue;                                                       \
      deck##_CardMask_OR(_n2, _card1, _card2);                          \
      for (_i3 = _i2-1; _i3 >= 0; _i3--) {                              \
        _card3 = deck##_MASK(_i3);                                      \
        if (deck##_CardMask_ANY_SET(dead_cards, _card3))                \
          continue;                                                     \
	deck##_CardMask_OR(_n3, _n2, _card3);                           \
        for (_i4 = _i3-1; _i4 >= 0; _i4--) {                            \
          _card4 = deck##_MASK(_i4);                                    \
          if (deck##_CardMask_ANY_SET(dead_cards, _card4))              \
            continue;                                                   \
	  deck##_CardMask_OR(_n4, _n3, _card4);                         \
          for (_i5 = _i4-1; _i5 >= 0; _i5--) {                          \
            _card5 = deck##_MASK(_i5);                                  \
            if (deck##_CardMask_ANY_SET(dead_cards, _card5))            \
              continue;                                                 \
            deck##_CardMask_OR(_n5, _n4, _card5);                       \
            cards_var = _n5;                                            \
            { action };                                                 \
          };                                                            \
        };                                                              \
      };                                                                \
    };                                                                  \
  };                                                                    \
} while (0)




#define DECK_ENUMERATE_N_CARDS_D(deck, cards_var, n_cards, dead_cards,     \
                                 action)                                   \
do {                                                                       \
  int _i1, _i2, _i3, _i4, _i5, _i6, _i7, _i8, _i9;                         \
  deck##_CardMask _card1, _card2, _card3, _card4, _card5,                  \
    _card6, _card7, _card8, _card9,                                        \
    _n1, _n2, _n3, _n4, _n5, _n6, _n7, _n8, _n9;                           \
                                                                           \
  _i1 = _i2 = _i3 = _i4 = _i5 = _i6 = _i7 = _i8 = _i9 = 0;                 \
  deck##_CardMask_RESET(_card9);                                           \
  _card1 = _card2 = _card3 = _card4 = _card5 = _card6                      \
    = _card7 = _card8 = _card9;                                            \
  deck##_CardMask_RESET(_n9);                                              \
  _n1 = _n2 = _n3 = _n4 = _n5 = _n6 = _n7 = _n8 = _n9;                     \
                                                                           \
  switch (n_cards) {                                                       \
  default:                                                                 \
  case 9:                                                                  \
  case 0:                                                                  \
    break;                                                                 \
  case 8:                                                                  \
    _i2 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 7:                                                                  \
    _i3 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 6:                                                                  \
    _i4 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 5:                                                                  \
    _i5 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 4:                                                                  \
    _i6 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 3:                                                                  \
    _i7 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 2:                                                                  \
    _i8 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 1:                                                                  \
    _i9 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  }                                                                        \
  switch (n_cards) {                                                       \
  default:                                                                 \
    fprintf(stderr, "ENUMERATE_N_CARDS: n-cards must be in range 0..9\n"); \
    break;                                                                 \
                                                                           \
  case 9:                                                                  \
    for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                        \
      _card1 = deck##_MASK(_i1);                                           \
      if (deck##_CardMask_ANY_SET(dead_cards, _card1))                     \
        continue;                                                          \
      _n1 = _card1;                                                        \
      for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                 \
  case 8:                                                                  \
        _card2 = deck##_MASK(_i2);                                         \
        if (deck##_CardMask_ANY_SET(dead_cards, _card2))                   \
          continue;                                                        \
        deck##_CardMask_OR(_n2, _n1, _card2);                              \
        for (_i3 = _i2-1; _i3 >= 0; _i3--) {                               \
  case 7:                                                                  \
          _card3 = deck##_MASK(_i3);                                       \
          if (deck##_CardMask_ANY_SET(dead_cards, _card3))                 \
            continue;                                                      \
          deck##_CardMask_OR(_n3, _n2, _card3);                            \
          for (_i4 = _i3-1; _i4 >= 0; _i4--) {                             \
  case 6:                                                                  \
            _card4 = deck##_MASK(_i4);                                     \
            if (deck##_CardMask_ANY_SET(dead_cards, _card4))               \
              continue;                                                    \
            deck##_CardMask_OR(_n4, _n3, _card4);                          \
            for (_i5 = _i4-1; _i5 >= 0; _i5--) {                           \
  case 5:                                                                  \
              _card5 = deck##_MASK(_i5);                                   \
              if (deck##_CardMask_ANY_SET(dead_cards, _card5))             \
                continue;                                                  \
              deck##_CardMask_OR(_n5, _n4, _card5);                        \
              for (_i6 = _i5-1; _i6 >= 0; _i6--) {                         \
  case 4:                                                                  \
                _card6 = deck##_MASK(_i6);                                 \
                if (deck##_CardMask_ANY_SET(dead_cards, _card6))           \
                  continue;                                                \
                deck##_CardMask_OR(_n6, _n5, _card6);                      \
                for (_i7 = _i6-1; _i7 >= 0; _i7--) {                       \
  case 3:                                                                  \
                  _card7 = deck##_MASK(_i7);                               \
                  if (deck##_CardMask_ANY_SET(dead_cards, _card7))         \
                    continue;                                              \
                  deck##_CardMask_OR(_n7, _n6, _card7);                    \
                  for (_i8 = _i7-1; _i8 >= 0; _i8--) {                     \
  case 2:                                                                  \
                    _card8 = deck##_MASK(_i8);                             \
                    if (deck##_CardMask_ANY_SET(dead_cards, _card8))       \
                      continue;                                            \
                    deck##_CardMask_OR(_n8, _n7, _card8);                  \
                    for (_i9 = _i8-1; _i9 >= 0; _i9--) {                   \
  case 1:                                                                  \
                      _card9 = deck##_MASK(_i9);                           \
                      if (deck##_CardMask_ANY_SET(dead_cards, _card9))     \
                        continue;                                          \
                      deck##_CardMask_OR(_n9, _n8, _card9);                \
  case 0:                                                                  \
                        cards_var = _n9;                                   \
                        { action };                                        \
		    }                                                      \
		  }                                                        \
		}                                                          \
	      }                                                            \
	    }                                                              \
	  }                                                                \
	}                                                                  \
      }                                                                    \
    }                                                                      \
  }                                                                        \
} while (0)                                                                
                                                                           
                                                                           
#define DECK_ENUMERATE_N_CARDS(deck, cards_var, n_cards, action)           \
do {                                                                       \
  int _i1, _i2, _i3, _i4, _i5, _i6, _i7, _i8, _i9;                         \
  deck##_CardMask _card1, _card2, _card3, _card4, _card5,                  \
    _card6, _card7, _card8, _card9,                                        \
    _n1, _n2, _n3, _n4, _n5, _n6, _n7, _n8, _n9;                           \
                                                                           \
  _i1 = _i2 = _i3 = _i4 = _i5 = _i6 = _i7 = _i8 = _i9 = 0;                 \
  deck##_CardMask_RESET(_card9);                                           \
  _card1 = _card2 = _card3 = _card4 = _card5 = _card6                      \
    = _card7 = _card8 = _card9;                                            \
  deck##_CardMask_RESET(_n9);                                              \
  _n1 = _n2 = _n3 = _n4 = _n5 = _n6 = _n7 = _n8 = _n9;                     \
                                                                           \
  switch (n_cards) {                                                       \
  default:                                                                 \
  case 9:                                                                  \
  case 0:                                                                  \
    break;                                                                 \
  case 8:                                                                  \
    _i2 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 7:                                                                  \
    _i3 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 6:                                                                  \
    _i4 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 5:                                                                  \
    _i5 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 4:                                                                  \
    _i6 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 3:                                                                  \
    _i7 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 2:                                                                  \
    _i8 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  case 1:                                                                  \
    _i9 = deck##_N_CARDS-1;                                                \
    break;                                                                 \
  }                                                                        \
  switch (n_cards) {                                                       \
  default:                                                                 \
    fprintf(stderr, "ENUMERATE_N_CARDS: n-cards must be in range 0..9\n"); \
    break;                                                                 \
                                                                           \
  case 9:                                                                  \
    for (_i1 = deck##_N_CARDS-1; _i1 >= 0; _i1--) {                        \
      _card1 = deck##_MASK(_i1);                                           \
      _n1 = _card1;                                                        \
      for (_i2 = _i1-1; _i2 >= 0; _i2--) {                                 \
  case 8:                                                                  \
        _card2 = deck##_MASK(_i2);                                         \
        deck##_CardMask_OR(_n2, _n1, _card2);                              \
        for (_i3 = _i2-1; _i3 >= 0; _i3--) {                               \
  case 7:                                                                  \
          _card3 = deck##_MASK(_i3);                                       \
          deck##_CardMask_OR(_n3, _n2, _card3);                            \
          for (_i4 = _i3-1; _i4 >= 0; _i4--) {                             \
  case 6:                                                                  \
            _card4 = deck##_MASK(_i4);                                     \
            deck##_CardMask_OR(_n4, _n3, _card4);                          \
            for (_i5 = _i4-1; _i5 >= 0; _i5--) {                           \
  case 5:                                                                  \
              _card5 = deck##_MASK(_i5);                                   \
              deck##_CardMask_OR(_n5, _n4, _card5);                        \
              for (_i6 = _i5-1; _i6 >= 0; _i6--) {                         \
  case 4:                                                                  \
                _card6 = deck##_MASK(_i6);                                 \
                deck##_CardMask_OR(_n6, _n5, _card6);                      \
                for (_i7 = _i6-1; _i7 >= 0; _i7--) {                       \
  case 3:                                                                  \
                  _card7 = deck##_MASK(_i7);                               \
                  deck##_CardMask_OR(_n7, _n6, _card7);                    \
                  for (_i8 = _i7-1; _i8 >= 0; _i8--) {                     \
  case 2:                                                                  \
                    _card8 = deck##_MASK(_i8);                             \
                    deck##_CardMask_OR(_n8, _n7, _card8);                  \
                    for (_i9 = _i8-1; _i9 >= 0; _i9--) {                   \
  case 1:                                                                  \
                      _card9 = deck##_MASK(_i9);                           \
                      deck##_CardMask_OR(_n9, _n8, _card9);                \
  case 0:                                                                  \
                        cards_var = _n9;                                   \
                        { action };                                        \
		    }                                                      \
		  }                                                        \
		}                                                          \
	      }                                                            \
	    }                                                              \
	  }                                                                \
	}                                                                  \
      }                                                                    \
    }                                                                      \
  }                                                                        \
} while (0)


#define ENUMERATE_1_CARDS(c,a) DECK_ENUMERATE_1_CARDS(Deck, c, a)
#define ENUMERATE_2_CARDS(c,a) DECK_ENUMERATE_2_CARDS(Deck, c, a)
#define ENUMERATE_3_CARDS(c,a) DECK_ENUMERATE_3_CARDS(Deck, c, a)
#define ENUMERATE_4_CARDS(c,a) DECK_ENUMERATE_4_CARDS(Deck, c, a)
#define ENUMERATE_5_CARDS(c,a) DECK_ENUMERATE_5_CARDS(Deck, c, a)
#define ENUMERATE_7_CARDS(c,a) DECK_ENUMERATE_7_CARDS(Deck, c, a)

#define ENUMERATE_1_CARDS_D(c,d,a) DECK_ENUMERATE_1_CARDS_D(Deck, c, d, a)
#define ENUMERATE_2_CARDS_D(c,d,a) DECK_ENUMERATE_2_CARDS_D(Deck, c, d, a)
#define ENUMERATE_3_CARDS_D(c,d,a) DECK_ENUMERATE_3_CARDS_D(Deck, c, d, a)
#define ENUMERATE_4_CARDS_D(c,d,a) DECK_ENUMERATE_4_CARDS_D(Deck, c, d, a)
#define ENUMERATE_5_CARDS_D(c,d,a) DECK_ENUMERATE_5_CARDS_D(Deck, c, d, a)
#define ENUMERATE_7_CARDS_D(c,d,a) DECK_ENUMERATE_7_CARDS_D(Deck, c, d, a)

#define ENUMERATE_N_CARDS(c,n,a) DECK_ENUMERATE_N_CARDS(Deck, c, n, a)
#define ENUMERATE_N_CARDS_D(c,n,d,a) DECK_ENUMERATE_N_CARDS_D(Deck, c, n, d, a)


#define DECK_ENUMERATE_PERMUTATIONS_D(deck, set_var, num_sets, set_sizes,   \
                                      dead_cards, action)                   \
{                                                                           \
  deck##_CardMask _orMask[deck##_N_CARDS+1];                                \
  int _i, _j, _t, _nLiveCards, _nCards, _liveCards[deck##_N_CARDS],         \
    _indices[deck##_N_CARDS+1];                                             \
                                                                            \
  _nCards = _nLiveCards = 0;                                                \
  for (_i=0; _i < (num_sets); _i++)                                         \
    _nCards += (set_sizes)[_i];                                             \
                                                                            \
  for (_i=0; _i < deck##_N_CARDS; _i++)                                     \
    if (!(deck##_CardMask_CARD_IS_SET(dead_cards, _i)))                     \
      _liveCards[_nLiveCards++] = _i;                                       \
                                                                            \
  if (_nLiveCards < _nCards)                                                \
    fprintf(stderr, "ENUMERATE_PERMUTATIONS: not enough cards\n");          \
  else {                                                                    \
    deck##_CardMask_RESET(_orMask[0]);                                      \
    for (_i=1; _i <= _nCards; _i++) {                                       \
      _indices[_i] = _i-1;                                                  \
      deck##_CardMask_OR(_orMask[_i], _orMask[_i-1],                        \
                         deck##_MASK(_liveCards[_indices[_i]]));            \
    };                                                                      \
                                                                            \
    for (;;) {                                                              \
      set_var[0] = _orMask[set_sizes[0]];                                   \
      _t = set_sizes[0];                                                    \
      for (_j=1; _j < num_sets; _j++) {                                     \
        deck##_CardMask_XOR(set_var[_j], _orMask[_t + set_sizes[_j]],       \
                            _orMask[_t]);                                   \
        _t += set_sizes[_j];                                                \
      };                                                                    \
      { action };                                                           \
                                                                            \
      if (_indices[_nCards] != _liveCards[_nLiveCards - 1]) {               \
        ++_indices[_nCards];                                                \
        deck##_CardMask_OR(_orMask[_nCards], _orMask[_nCards-1],            \
                           deck##_MASK(_liveCards[_indices[_nCards]]));     \
      }                                                                     \
      else {                                                                \
        for (_i=_nCards-1; _i > 0; _i--)                                    \
          if (_indices[_i] != _liveCards[_nLiveCards - (_nCards - _i) - 1]) \
            break;                                                          \
        if (_i == 0)                                                        \
          break;                                                            \
        ++_indices[_i];                                                     \
        deck##_CardMask_OR(_orMask[_i], _orMask[_i-1],                      \
                           deck##_MASK(_liveCards[_indices[_i]]));          \
        for (_j=_i+1; _j <= _nCards; _j++) {                                \
          _indices[_j] = 0;                                                 \
          while (deck##_CardMask_CARD_IS_SET(_orMask[_j-1],                 \
                                             _liveCards[_indices[_j]]))     \
            ++_indices[_j];                                                 \
          deck##_CardMask_OR(_orMask[_j], _orMask[_j-1],                    \
                             deck##_MASK(_liveCards[_indices[_j]]));        \
        };                                                                  \
      };                                                                    \
    };                                                                      \
  };                                                                        \
}


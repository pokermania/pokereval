#define DECK_JOKER
#define RULES_STANDARD

#include "deck_joker.h"
#include "rules_std.h"

#undef Hand_EVAL_N
#undef Hand_EVAL_TYPE
#undef Hand_EVAL_LOW
#undef Hand_EVAL_LOW8

#define Hand_EVAL_N     JokerDeck_StdRules_EVAL_N
#define Hand_EVAL_TYPE(m, n)  HandVal_HANDTYPE(Hand_EVAL_N((m), (n)))

#define Hand_EVAL_LOW   JokerDeck_Lowball_EVAL
#define Hand_EVAL_LOW8  JokerDeck_Low8_EVAL

#undef  DECK_JOKER
#undef  RULES_STANDARD


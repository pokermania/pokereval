#define DECK_ASTUD
#define RULES_ASTUD

#include "deck_astud.h"
#include "rules_astud.h"

#undef Hand_EVAL_N
#undef Hand_EVAL_TYPE

#define Hand_EVAL_N           AStudDeck_AStudRules_EVAL_N
#define Hand_EVAL_TYPE(m, n)  HandVal_HANDTYPE(Hand_EVAL_N((m), (n)))

#undef  DECK_ASTUD
#undef  RULES_ASTUD


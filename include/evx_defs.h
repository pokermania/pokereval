#ifndef __EVX_DEFS__
#define __EVX_DEFS__

typedef uint32 EvxHandVal;

#define EvxHandVal_TYPE_SHIFT     (2 * StdDeck_Rank_COUNT)
#define EvxHandVal_SIGCARDS_SHIFT StdDeck_Rank_COUNT
#define EvxHandVal_KICKERS_SHIFT  0
#define EvxHandVal_RANK_MASK      (0x1FFF)

#define EvxHandVal_HANDTYPE_VALUE(ht) ((ht) << EvxHandVal_TYPE_SHIFT)
#define EvxHandVal_HANDTYPE(ehv) ((ehv) >> EvxHandVal_TYPE_SHIFT)

enum {
  EvxHandVal_NOPAIR    = EvxHandVal_HANDTYPE_VALUE(StdRules_HandType_NOPAIR), 
  EvxHandVal_ONEPAIR   = EvxHandVal_HANDTYPE_VALUE(StdRules_HandType_ONEPAIR), 
  EvxHandVal_TWOPAIR   = EvxHandVal_HANDTYPE_VALUE(StdRules_HandType_TWOPAIR), 
  EvxHandVal_TRIPS     = EvxHandVal_HANDTYPE_VALUE(StdRules_HandType_TRIPS), 
  EvxHandVal_STRAIGHT  = EvxHandVal_HANDTYPE_VALUE(StdRules_HandType_STRAIGHT), 
  EvxHandVal_FLUSH     = EvxHandVal_HANDTYPE_VALUE(StdRules_HandType_FLUSH), 
  EvxHandVal_FULLHOUSE = EvxHandVal_HANDTYPE_VALUE(StdRules_HandType_FULLHOUSE), 
  EvxHandVal_QUADS     = EvxHandVal_HANDTYPE_VALUE(StdRules_HandType_QUADS), 
  EvxHandVal_STFLUSH   = EvxHandVal_HANDTYPE_VALUE(StdRules_HandType_STFLUSH),
};

extern uint32 evxPairValueTable[StdDeck_N_RANKMASKS];
extern uint32 evxTripsValueTable[StdDeck_N_RANKMASKS];
extern uint32 evxStrValueTable[StdDeck_N_RANKMASKS];
extern uint32 evxFlushCardsTable[StdDeck_N_RANKMASKS];

extern HandVal EvxHandVal_toHandVal(EvxHandVal ehv);

#endif

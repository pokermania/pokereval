#include <stdio.h>
#include <assert.h>

#include "poker_defs.h"
#include "evx_defs.h"
#include "mktable.h"

/* 
 * Generate tables used by the evalExactlyN functions.  These have the
 * hand values pre-built, with the hand-type already ORed in, so that
 * the return value can be returned quickly, at the cost of having many
 * large lookup tables.
 */

#define TV_COMMENT_STRING \
 "evxTripsValueTable[].  Maps 13-bit rank masks to a value identifying\n" \
 "the top two bits (kickers) of the input mask and the hand value for TRIPS."
#define TV_FILENAME "t_evx_tripsval"

#define PV_COMMENT_STRING \
 "evxPairValueTable[].  Maps 13-bit rank masks to a value identifying\n" \
 "the top three bits (kickers) of the input mask and the hand value for PAIR."
#define PV_FILENAME "t_evx_pairval"

#define SV_COMMENT_STRING \
 "evxStrValueTable[].  Maps 13-bit rank masks to a value identifying\n" \
 "the high bit of the straight and the hand value for STRAIGHT."
#define SV_FILENAME "t_evx_strval"

#define FC_COMMENT_STRING \
 "evxFlushCardsTable[].  Maps 13-bit rank masks to a value identifying\n" \
 "whether there are five or more bits set, and if so which bits. "
#define FC_FILENAME "t_evx_flushcards"


static void 
doTripsValueTable(void) {
  int i;

  MakeTable_begin("evxTripsValueTable", 
                  TV_FILENAME, 
                  "uint32", 
                  StdDeck_N_RANKMASKS);
  MakeTable_comment(TV_COMMENT_STRING);
  for (i=0; i < StdDeck_N_RANKMASKS; i++) {
    uint32 val, cards;

    cards = i;
    val = top_bit_func(cards);
    cards ^= val;
    val |= top_bit_func(cards);
    if (val)
      val |= (StdRules_HandType_TRIPS << EvxHandVal_TYPE_SHIFT);
    MakeTable_outputUInt32(val);
  };

  MakeTable_end();
}


static void 
doStraightValueTable(void) {
  int i;

  MakeTable_begin("evxStrValueTable", 
                  SV_FILENAME, 
                  "uint32", 
                  StdDeck_N_RANKMASKS);
  MakeTable_comment(SV_COMMENT_STRING);
  for (i=0; i < StdDeck_N_RANKMASKS; i++) {
    uint32 sv, val;

    sv = straight_func(i);
    val = sv ? 
      (1 << sv) | (StdRules_HandType_STRAIGHT << EvxHandVal_TYPE_SHIFT) : 0;
    MakeTable_outputUInt32(val);
  };

  MakeTable_end();
}


static void 
doPairValueTable(void) {
  int i;

  MakeTable_begin("evxPairValueTable", 
                  PV_FILENAME, 
                  "uint32", 
                  StdDeck_N_RANKMASKS);
  MakeTable_comment(PV_COMMENT_STRING);
  for (i=0; i < StdDeck_N_RANKMASKS; i++) {
    uint32 retval, cards, temp;

    cards = i;
    retval = top_bit_func(cards);
    cards ^= retval;
    temp = top_bit_func(cards);
    retval ^= temp;
    cards ^= temp;
    retval |= top_bit_func(cards) 
              | (StdRules_HandType_ONEPAIR << EvxHandVal_TYPE_SHIFT);

    MakeTable_outputUInt32(retval);
  };

  MakeTable_end();
}


static void 
doFlushCardsTable(void) {
  int i;

  MakeTable_begin("evxFlushCardsTable", 
                  FC_FILENAME, 
                  "uint32", 
                  StdDeck_N_RANKMASKS);
  MakeTable_comment(FC_COMMENT_STRING);
  for (i=0; i < StdDeck_N_RANKMASKS; i++) {
    uint32 val;

    val = (n_bits_func(i) >= 5) ? i : 0;
    MakeTable_outputUInt32(val);
  };

  MakeTable_end();
}


int 
main(int argc, char **argv) {
  doPairValueTable();
  doStraightValueTable();
  doTripsValueTable();
  doFlushCardsTable();

  return 0;
}


#include "poker_defs.h"
#include "mktable.h"

uint32
top_bit_func( uint32 n )
{
  uint32 retval;

  for (retval = 1 << StdDeck_Rank_ACE; !(retval & n) && retval; retval >>= 1)
    ;
  return retval;
}    


uint32
n_bits_func( uint32 n )
{
  int retval;

  retval = 0;
  while (n) {
    if (n & 1)
      ++retval;
    n >>= 1;
  }
  return retval;
}


uint32 
top_card_func( uint32 n )
{
  int retval, bit;

  if (n)
    for ( bit = (1 << StdDeck_Rank_ACE), retval = StdDeck_Rank_ACE; 
          !(n & bit); bit >>= 1, --retval)
      ;
  else
    return 0;
  return retval;
}


uint32
straight_func( uint32 n ) {
  uint32 ranks, ranks2;

  ranks = n;
  if ( (ranks2  = ranks & (ranks << 1)) &&
       (ranks2 &=         (ranks << 2)) &&
       (ranks2 &=         (ranks << 3)) &&
       (ranks2 &=         (ranks << 4)) ) {
    return top_card_func(ranks2);
  } 
  else if ((ranks & StdRules_FIVE_STRAIGHT) == StdRules_FIVE_STRAIGHT) 
    return StdDeck_Rank_5;

  return 0;
}

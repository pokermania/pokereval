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


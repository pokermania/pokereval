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
bottom_bit_func( uint32 n )
{
  /* BBF returns the bottom bit set, treating 2 as low bit and A as high 
     bit.  If you want to do A-5 low evaluation, you'll need to rotate
     the input mask one to make A the low bit before calling this. */
  uint32 retval;

  if (n == 0) 
    return 0;

  for (retval = 1; 
       !(retval & n) && retval <= 1 << StdDeck_Rank_ACE; 
       retval <<= 1)
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
bottom_card_func( uint32 n )
{
  /* BCF returns the index of the bottom set bit, treating 2 as low
     bit and A as high bit.  If you want to do A-5 low evaluation,
     you'll need to rotate the input mask one to make A the low bit
     before calling this.  Also, if no bits are set, then the results may
     not be valid.  
   */
  int retval, bit;

  if (n)
    for ( bit = (1 << StdDeck_Rank_2), retval = StdDeck_Rank_2; 
          !(n & bit) && retval <= StdDeck_Rank_ACE; 
          bit <<= 1, ++retval)
      ;
  else
    return -1;
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

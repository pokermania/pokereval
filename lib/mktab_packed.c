#include <stdio.h>
#include <assert.h>

#include "poker_defs.h"
#include "mktable.h"

#define NBS_COMMENT_STRING \
 "nBitsAndStrTable[].  Maps 13-bit rank masks onto an 8 bit quantity,\n"     \
 "packed with both the number of bits set in the mask (nBitsTable) and\n"    \
 "a value indicating if a straight is present (straightTable). \n"           \
 "It is possible, using just this table and bit masking operations, \n"      \
 "to determine the type of hand.  Since this table is only 8K it should\n"   \
 "in L1 cache on some processors.\n "                                        \
 "The layout of the result is as follows: \n"\
 "  Bit 0: (nBits >= 5)\n"\
 "  Bit 1: is-straight\n"\
 "  Bits 2-6: nBits\n"
#define NBS_FILENAME "t_nbitsandstr"


static void 
doNBitsAndStrTable(void) {
  int i;
  uint8 val, t;

  MakeTable_begin("nBitsAndStrTable", 
                  NBS_FILENAME, 
                  "uint8", 
                  StdDeck_N_RANKMASKS);
  MakeTable_comment(NBS_COMMENT_STRING);
  for (i=0; i < StdDeck_N_RANKMASKS; i++) {
    val = n_bits_func(i);
    assert((val & 0xF0) == 0);
    t = straight_func(i);

    MakeTable_outputUInt8((val << 2) 
                          | (((t != 0) & 0x01) << 1) 
                          | ((val >= 5) & 0x01) );
  };

  MakeTable_end();
}

int 
main(int argc, char **argv) {
  doNBitsAndStrTable();
  return 0;
}


/* $Id$ */

#include <stdio.h>
#include <stdlib.h>

#include "combinations.h"

int
main(int argc, char **argv)
{
  int nuniv;
  int nelem;
  int ncombo, *elems, cnum, i;
  Combinations vp;

  if (argc != 3) {
    printf("usage: %s nuniv nelem\n", argv[0]);
    return 1;
  }
  nuniv = atoi(argv[1]);
  nelem = atoi(argv[2]);
  vp = init_combinations(nuniv, nelem);
  if (vp == NULL) {
    printf("init_combinations failed\n");
    return 1;
  }
  ncombo = num_combinations(vp);
  elems = (int *) malloc(nelem * sizeof(int));
  for (cnum=0; cnum<ncombo; cnum++) {
    get_combination(vp, cnum, elems);
    for (i=0; i<nelem; i++)
      printf("%d ", elems[i] + 1);
    printf("\n");
  }
  free_combinations(vp);
  return 0;
}

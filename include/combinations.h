/* $Id$ */
/* Public declarations for combinations.c */
/* Michael Maurer, Jun 2002 */

#ifndef COMBINATIONS_H
#define COMBINATIONS_H

typedef void *Combinations;

void free_combinations(Combinations c);
Combinations init_combinations(int nuniv, int nelem);
int num_combinations(Combinations c);
void get_combination(Combinations c, int cnum, int *elems);

#endif

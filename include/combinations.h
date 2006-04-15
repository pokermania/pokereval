/*
 * Copyright (C) 2002-2006 
 *           Michael Maurer <mjmaurer@yahoo.com>
 *           Loic Dachary <loic@gnu.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/* Public declarations for combinations.c */
/* Michael Maurer, Jun 2002 */

#ifndef COMBINATIONS_H
#define COMBINATIONS_H

#include "pokereval_export.h"

typedef void *Combinations;

extern POKEREVAL_EXPORT void free_combinations(Combinations c);
extern POKEREVAL_EXPORT Combinations init_combinations(int nuniv, int nelem);
extern POKEREVAL_EXPORT int num_combinations(Combinations c);
extern POKEREVAL_EXPORT void get_combination(Combinations c, int cnum, int *elems);

#endif

/*
 * Copyright (C) 1999-2006 
 *           Brian Goetz <brian@quiotix.com>
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
#ifndef __EVX_DEFS__
#define __EVX_DEFS__

#include "pokereval_export.h"

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

extern POKEREVAL_EXPORT uint32 evxPairValueTable[StdDeck_N_RANKMASKS];
extern POKEREVAL_EXPORT uint32 evxTripsValueTable[StdDeck_N_RANKMASKS];
extern POKEREVAL_EXPORT uint32 evxStrValueTable[StdDeck_N_RANKMASKS];
extern POKEREVAL_EXPORT uint32 evxFlushCardsTable[StdDeck_N_RANKMASKS];

extern POKEREVAL_EXPORT HandVal EvxHandVal_toHandVal(EvxHandVal ehv);

#endif

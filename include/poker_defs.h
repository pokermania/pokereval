/*
 * Copyright (C) 1999-2004 
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
#ifndef __POKER_DEFS_H__
#define __POKER_DEFS_H__


/* Compiler-specific junk */

#if defined(_MSC_VER)
#define HAVE_INT64
#define UINT64_TYPE unsigned __int64
#define inline __inline
#define thread __declspec( thread )
#define HAVE_SYS_STAT_H
#else
#define thread 
#include "poker_config.h"
#endif

/* 64-bit integer junk */

#ifdef HAVE_INT64

#ifdef HAVE_LONG_LONG
typedef unsigned long long      uint64;
#elif SIZEOF_LONG == 8
typedef unsigned long           uint64;
#elif defined(UINT64_TYPE)
typedef UINT64_TYPE             uint64;
#else
#error "Don't know what 64-bit integers are called"
#endif

#define LongLong_OP(result, op1, op2, operation) \
  do { result = (op1) operation (op2); } while (0)
#define LongLong_OR(result, op1, op2)  LongLong_OP(result, op1, op2, |)
#define LongLong_AND(result, op1, op2) LongLong_OP(result, op1, op2, &)
#define LongLong_XOR(result, op1, op2) LongLong_OP(result, op1, op2, ^)

#endif


typedef unsigned char  uint8;
typedef   signed char   int8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

#include "deck.h"
#include "handval.h"
#include "handval_low.h"
#include "enumerate.h"

#include "game_std.h"

#endif


#ifndef __POKER_DEFS_H__
#define __POKER_DEFS_H__

#if defined(_MSC_VER)
#define HAVE_INT64
#define UINT64_TYPE unsigned __int64
#else
#include "config.h"
#endif

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
#endif

typedef unsigned char  uint8;
typedef   signed char   int8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

#include "stddeck.h"
#include "handval.h"
#include "stdrules.h"
#include "enumerate.h"

#if !defined(NONSTANDARD_DECK) && !defined(NONSTANDARD_RULES)
#define Hand_EVAL_N  StdDeck_StdRules_EVAL_N
#define Hand_EVAL_X5 StdDeck_StdRules_EVAL_X5
#define Hand_EVAL_X7 StdDeck_StdRules_EVAL_X7
#endif

#endif

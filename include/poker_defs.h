#ifndef __POKER_DEFS_H__
#define __POKER_DEFS_H__

#include "config.h"

#ifdef HAVE_INT64
#ifdef HAVE_LONG_LONG
typedef unsigned long long      uint64;
#elif SIZEOF_LONG == 8
typedef unsigned long           uint64;
#else
#error "Don't know what 64-bit integers are called"
#endif
#endif

typedef unsigned char  uint8;
typedef   signed char   int8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

#include "stddeck.h"
#include "stdrules.h"
#include "enumerate.h"

#endif

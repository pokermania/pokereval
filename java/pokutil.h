/* $Id$ */

#ifndef POKUTIL_H
#define POKUTIL_H
#include <jni.h>	/* for JNI types */
#include "poker_defs.h"	/* for *_CardMask types */
#include "deck_std.h"
#include "deck_joker.h"
#include "deck_astud.h"

extern int
parseStandardRanksSuits(JNIEnv *env, jintArray ranks, jintArray suits,
                        StdDeck_CardMask *mcards, int *ncards);

extern int
parseJokerRanksSuits(JNIEnv *env, jintArray ranks, jintArray suits,
                     JokerDeck_CardMask *mcards, int *ncards);

extern int
parseAsianStudRanksSuits(JNIEnv *env, jintArray ranks, jintArray suits,
                         AStudDeck_CardMask *mcards, int *ncards);

#endif

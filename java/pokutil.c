/* $Id$ */

#include <jni.h>
#include "jniutil.h"		/* JNI helpers: throw exceptions */
#include "poker_defs.h"		/* poker-eval basic definitions */
#include "pokutil.h"

/******************************************************************************
  Standard deck
******************************************************************************/
#include "deck_std.h"
#include "rules_std.h"

int
parseStandardRanksSuits(JNIEnv *env, jintArray ranks, jintArray suits,
                        StdDeck_CardMask *mcards, int *ncards)
{
  int i, status = 0;
  jsize nranks = (*env)->GetArrayLength(env, ranks);
  jsize nsuits = (*env)->GetArrayLength(env, suits);
  jint *jranks = (*env)->GetIntArrayElements(env, ranks, 0);
  jint *jsuits = (*env)->GetIntArrayElements(env, suits, 0);

  StdDeck_CardMask_RESET(*mcards);
  *ncards = 0;
  if (nranks != nsuits) {
    status = 1;
    goto release1;
  }
  for (i=0; i<nranks; i++) {
    int card = StdDeck_MAKE_CARD(jranks[i], jsuits[i]);
    if (StdDeck_CardMask_CARD_IS_SET(*mcards, card)) {
      status = 1;
      goto release1;
    }
    StdDeck_CardMask_SET(*mcards, card);
    (*ncards)++;
  }
#ifdef DEBUG
  printf("In C: Hand %s\n", DmaskString(StdDeck, *mcards));
#endif

 release1:
  (*env)->ReleaseIntArrayElements(env, ranks, jranks, JNI_ABORT);
  (*env)->ReleaseIntArrayElements(env, suits, jsuits, JNI_ABORT);
  return status;
}

/******************************************************************************
  Joker deck
******************************************************************************/
#include "deck_joker.h"
#include "rules_joker.h"

int
parseJokerRanksSuits(JNIEnv *env, jintArray ranks, jintArray suits,
                     JokerDeck_CardMask *mcards, int *ncards)
{
  int i, status = 0;
  jsize nranks = (*env)->GetArrayLength(env, ranks);
  jsize nsuits = (*env)->GetArrayLength(env, suits);
  jint *jranks = (*env)->GetIntArrayElements(env, ranks, 0);
  jint *jsuits = (*env)->GetIntArrayElements(env, suits, 0);

  JokerDeck_CardMask_RESET(*mcards);
  *ncards = 0;
  if (nranks != nsuits) {
    status = 1;
    goto release2;
  }
  for (i=0; i<nranks; i++) {
    int card;
    if (jranks[i] == JokerDeck_Rank_LAST + 1) {
      /* encode joker as any card with rank one higher than highest; this
         corresponds to rank 13 */
      card = JokerDeck_JOKER;
    } else {
      card = JokerDeck_MAKE_CARD(jranks[i], jsuits[i]);
    }
    if (JokerDeck_CardMask_CARD_IS_SET(*mcards, card)) {
      status = 1;
      goto release2;
    }
    JokerDeck_CardMask_SET(*mcards, card);
    (*ncards)++;
  }
#ifdef DEBUG
  printf("In C: Hand %s\n", DmaskString(JokerDeck, *mcards));
#endif

 release2:
  (*env)->ReleaseIntArrayElements(env, ranks, jranks, JNI_ABORT);
  (*env)->ReleaseIntArrayElements(env, suits, jsuits, JNI_ABORT);
  return status;
}


/******************************************************************************
  Asian Stud deck
******************************************************************************/
#include "deck_astud.h"
#include "rules_astud.h"

int
parseAsianStudRanksSuits(JNIEnv *env, jintArray ranks, jintArray suits,
                         AStudDeck_CardMask *mcards, int *ncards)
{
  int i, status = 0;
  jsize nranks = (*env)->GetArrayLength(env, ranks);
  jsize nsuits = (*env)->GetArrayLength(env, suits);
  jint *jranks = (*env)->GetIntArrayElements(env, ranks, 0);
  jint *jsuits = (*env)->GetIntArrayElements(env, suits, 0);

  AStudDeck_CardMask_RESET(*mcards);
  *ncards = 0;
  if (nranks != nsuits) {
    status = 1;
    goto release;
  }
  for (i=0; i<nranks; i++) {
    int card = AStudDeck_MAKE_CARD(jranks[i], jsuits[i]);
    if (AStudDeck_CardMask_CARD_IS_SET(*mcards, card)) {
      status = 1;
      goto release;
    }
    AStudDeck_CardMask_SET(*mcards, card);
    (*ncards)++;
  }
#ifdef DEBUG
  printf("In C: Hand %s\n", DmaskString(AStudDeck, *mcards));
#endif

 release:
  (*env)->ReleaseIntArrayElements(env, ranks, jranks, JNI_ABORT);
  (*env)->ReleaseIntArrayElements(env, suits, jsuits, JNI_ABORT);
  return status;
}


/* $Id$ */

#include <stdio.h>
#include <jni.h>
#include "pokerjni.h"
#include "jniutil.h"

#include "poker_defs.h"
#include "deck_astud.h"
#include "rules_astud.h"
#include "inlines/eval_astud.h"	/* must come after above!? */

static int
parseRanksSuits(JNIEnv *env, jintArray ranks, jintArray suits,
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

 release:
  (*env)->ReleaseIntArrayElements(env, ranks, jranks, 0);
  (*env)->ReleaseIntArrayElements(env, suits, jsuits, 0);
  return status;
}

JNIEXPORT jlong JNICALL Java_org_pokersource_eval_AsianStudEval_EvalHigh
   (JNIEnv *env, jclass class, jintArray ranks, jintArray suits)
{
  int ncards;
  AStudDeck_CardMask mcards;
  HandVal hival;
  
  if (parseRanksSuits(env, ranks, suits, &mcards, &ncards)) {
    jniThrow(env, class, "unable to parse input cards");
    return (jlong)0;
  }
  hival = AStudDeck_AStudRules_EVAL_N(mcards, ncards);
#ifdef DEBUG
  printf("In C: Hand [%s] => Eval: %d ",
         DmaskString(AStudDeck, mcards), hival);
  AStudRules_HandVal_print(hival);
  printf("\n");
#endif
  return (jlong)hival;
}

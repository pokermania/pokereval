/* $Id$ */

#include <stdio.h>
#include <jni.h>
#include "pokerjni.h"
#include "jniutil.h"

#include "poker_defs.h"
#include "inlines/eval.h"
#include "inlines/eval_low.h"
#include "inlines/eval_low8.h"

static int
parseRanksSuits(JNIEnv *env, jintArray ranks, jintArray suits,
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
    goto release;
  }
  for (i=0; i<nranks; i++) {
    int card = StdDeck_MAKE_CARD(jranks[i], jsuits[i]);
    if (StdDeck_CardMask_CARD_IS_SET(*mcards, card)) {
      status = 1;
      goto release;
    }
    StdDeck_CardMask_SET(*mcards, card);
    (*ncards)++;
  }

 release:
  (*env)->ReleaseIntArrayElements(env, ranks, jranks, 0);
  (*env)->ReleaseIntArrayElements(env, suits, jsuits, 0);
  return status;
}

JNIEXPORT jlong JNICALL Java_org_pokersource_eval_StandardEval_EvalHigh
   (JNIEnv *env, jclass class, jintArray ranks, jintArray suits)
{
  int ncards;
  StdDeck_CardMask mcards;
  HandVal hival;
  
  if (parseRanksSuits(env, ranks, suits, &mcards, &ncards)) {
    jniThrow(env, class, "unable to parse input cards");
    return (jlong)0;
  }
  hival = StdDeck_StdRules_EVAL_N(mcards, ncards);
#ifdef DEBUG
  printf("In C: Hand [%s] => Eval: %d ",
         DmaskString(StdDeck, mcards), hival);
  StdRules_HandVal_print(hival);
  printf("\n");
#endif
  return (jlong)hival;
}

JNIEXPORT jlong JNICALL Java_org_pokersource_eval_StandardEval_EvalLow
   (JNIEnv *env, jclass class, jintArray ranks, jintArray suits)
{
  int ncards;
  StdDeck_CardMask mcards;
  LowHandVal loval;
  
  if (parseRanksSuits(env, ranks, suits, &mcards, &ncards)) {
    jniThrow(env, class, "unable to parse input cards");
    return (jlong)0;
  }
  loval = StdDeck_Lowball_EVAL(mcards, ncards);
#ifdef DEBUG
  printf("In C: Hand [%s] => Eval: %d ",
         DmaskString(StdDeck, mcards), loval);
  LowHandVal_print(loval);
  printf("\n");
#endif
  return (jlong)loval;
}

JNIEXPORT jlong JNICALL Java_org_pokersource_eval_StandardEval_EvalLow8
   (JNIEnv *env, jclass class, jintArray ranks, jintArray suits)
{
  int ncards;
  StdDeck_CardMask mcards;
  LowHandVal lo8val;
  
  if (parseRanksSuits(env, ranks, suits, &mcards, &ncards)) {
    jniThrow(env, class, "unable to parse input cards");
    return (jlong)0;
  }
  lo8val = StdDeck_Lowball8_EVAL(mcards, ncards);
#ifdef DEBUG
  printf("In C: Hand [%s] => Eval: %d ",
         DmaskString(StdDeck, mcards), lo8val);
  LowHandVal_print(lo8val);
  printf("\n");
#endif
  return (jlong)lo8val;
}


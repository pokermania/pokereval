/* $Id$ */

#include <stdio.h>
#include <jni.h>
#include "pokerjni.h"
#include "jniutil.h"

#include "poker_defs.h"
#include "inlines/eval_joker.h"
#include "inlines/eval_joker_low.h"
#include "inlines/eval_joker_low8.h"
/*#include "deck_joker.h"*/
/*#include "rules_joker.h"*/

static int
parseRanksSuits(JNIEnv *env, jintArray ranks, jintArray suits,
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
    goto release;
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
      goto release;
    }
    JokerDeck_CardMask_SET(*mcards, card);
    (*ncards)++;
  }

 release:
  (*env)->ReleaseIntArrayElements(env, ranks, jranks, 0);
  (*env)->ReleaseIntArrayElements(env, suits, jsuits, 0);
  return status;
}

JNIEXPORT jlong JNICALL Java_org_pokersource_eval_JokerEval_EvalHigh
   (JNIEnv *env, jclass class, jintArray ranks, jintArray suits)
{
  int ncards;
  JokerDeck_CardMask mcards;
  HandVal hival;
  
  if (parseRanksSuits(env, ranks, suits, &mcards, &ncards)) {
    jniThrow(env, class, "unable to parse input cards");
    return (jlong)0;
  }
  hival = JokerDeck_JokerRules_EVAL_N(mcards, ncards);
#ifdef DEBUG
  printf("In C: Hand [%s] => Eval: %d ",
         DmaskString(JokerDeck, mcards), hival);
  JokerRules_HandVal_print(hival);
  printf("\n");
#endif
  return (jlong)hival;
}

JNIEXPORT jlong JNICALL Java_org_pokersource_eval_JokerEval_EvalLow
   (JNIEnv *env, jclass class, jintArray ranks, jintArray suits)
{
  int ncards;
  JokerDeck_CardMask mcards;
  LowHandVal loval;
  
  if (parseRanksSuits(env, ranks, suits, &mcards, &ncards)) {
    jniThrow(env, class, "unable to parse input cards");
    return (jlong)0;
  }
  loval = JokerDeck_Lowball_EVAL(mcards, ncards);
#ifdef DEBUG
  printf("In C: Hand [%s] => Eval: %d ",
         DmaskString(JokerDeck, mcards), loval);
  LowHandVal_print(loval);
  printf("\n");
#endif
  return (jlong)loval;
}

JNIEXPORT jlong JNICALL Java_org_pokersource_eval_JokerEval_EvalLow8
   (JNIEnv *env, jclass class, jintArray ranks, jintArray suits)
{
  int ncards;
  JokerDeck_CardMask mcards;
  LowHandVal lo8val;
  
  if (parseRanksSuits(env, ranks, suits, &mcards, &ncards)) {
    jniThrow(env, class, "unable to parse input cards");
    return (jlong)0;
  }
  lo8val = JokerDeck_Lowball8_EVAL(mcards, ncards);
#ifdef DEBUG
  printf("In C: Hand [%s] => Eval: %d ",
         DmaskString(JokerDeck, mcards), lo8val);
  LowHandVal_print(lo8val);
  printf("\n");
#endif
  return (jlong)lo8val;
}


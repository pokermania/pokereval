// $Id$

package org.pokersource.eval;

public class AsianStudEval {
  // must match values in deck_astud.h
  public static int SUIT_HEARTS		= 0;
  public static int SUIT_DIAMONDS	= 1;
  public static int SUIT_CLUBS		= 2;
  public static int SUIT_SPADES		= 3;

  // must match values in deck_astud.h
  public static int RANK_7	= 5;
  public static int RANK_8	= 6;
  public static int RANK_9	= 7;
  public static int RANK_TEN	= 8;
  public static int RANK_JACK	= 9;
  public static int RANK_QUEEN	= 10;
  public static int RANK_KING	= 11;
  public static int RANK_ACE	= 12;

  static {
    System.loadLibrary("poker");
    System.loadLibrary("pokerjni");
  }

  /** Evaluate an asian stud deck poker hand for high.
      @param ranks ranks[i] is rank of ith card
      @param suits suits[i] is suit of ith card
      @return integer code denoting hand value (higher beats lower)
  */
  public static native long EvalHigh(int[] ranks, int[] suits);
  
  /** A simple demonstration of AsianStudEval methods. */
  public static void main(String[] args) {
    int[] ranks = new int[5];
    int[] suits = new int[5];
    ranks[0] = RANK_ACE;	suits[0] = SUIT_HEARTS;
    ranks[1] = RANK_7;		suits[1] = SUIT_HEARTS;
    ranks[2] = RANK_8;		suits[2] = SUIT_HEARTS;
    ranks[3] = RANK_9;		suits[3] = SUIT_SPADES;
    ranks[4] = RANK_TEN;	suits[4] = SUIT_SPADES;
    System.out.println("In Java: cards=[" +
                       " " + ranks[0] + ":" + suits[0] +
                       " " + ranks[1] + ":" + suits[1] +
                       " " + ranks[2] + ":" + suits[2] +
                       " " + ranks[3] + ":" + suits[3] +
                       " " + ranks[4] + ":" + suits[4] +
                       "]");
    try {
      long hival = EvalHigh(ranks, suits);
      System.out.println("In Java: hival=" + hival + "\n");
    } catch (Exception e) {
      System.out.println("In Java: caught exception: " + e);
    }
  }
}

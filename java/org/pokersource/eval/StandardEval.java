// $Id$

package org.pokersource.eval;

public class StandardEval {
  // must match values in deck_std.h
  public static int SUIT_HEARTS		= 0;
  public static int SUIT_DIAMONDS	= 1;
  public static int SUIT_CLUBS		= 2;
  public static int SUIT_SPADES		= 3;

  // must match values in deck_std.h
  public static int RANK_2	= 0;
  public static int RANK_3	= 1;
  public static int RANK_4	= 2;
  public static int RANK_5	= 3;
  public static int RANK_6	= 4;
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
  public static native long EvalHigh(int[] ranks, int[] suits);
  public static native long EvalLow(int[] ranks, int[] suits);
  public static native long EvalLow8(int[] ranks, int[] suits);
  
  // a simple test
  public static void main(String[] args) {
    int[] ranks = new int[5];
    int[] suits = new int[5];
    ranks[0] = RANK_3; suits[0] = SUIT_HEARTS;
    ranks[1] = RANK_4; suits[1] = SUIT_HEARTS;
    ranks[2] = RANK_5; suits[2] = SUIT_HEARTS;
    ranks[3] = RANK_6; suits[3] = SUIT_HEARTS;
    ranks[4] = RANK_7; suits[4] = SUIT_HEARTS;
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
      long loval = EvalLow(ranks, suits);
      System.out.println("In Java: loval=" + loval + "\n");
      long lo8val = EvalLow8(ranks, suits);
      System.out.println("In Java: lo8val=" + lo8val + "\n");
    } catch (Exception e) {
      System.out.println("In Java: caught exception: " + e);
    }
  }
}

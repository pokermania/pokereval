// $Id$

package org.pokersource.enum;
import org.pokersource.eval.*;

public class Enumerate {
  // must match enum_game_t definitions in enumdefs.h
  public static int GAME_HOLDEM		= 0;
  public static int GAME_HOLDEM8	= 1;
  public static int GAME_OMAHA		= 2;
  public static int GAME_OMAHA8		= 3;
  public static int GAME_7STUD		= 4;
  public static int GAME_7STUD8		= 5;
  public static int GAME_7STUDNSQ	= 6;
  public static int GAME_RAZZ		= 7;
  public static int GAME_5DRAW		= 8;
  public static int GAME_5DRAW8		= 9;
  public static int GAME_5DRAWNSQ	= 10;
  public static int GAME_LOWBALL	= 11;
  public static int GAME_LOWBALL27	= 12;

  static {
    System.loadLibrary("poker");
    System.loadLibrary("pokerjni");
  }
  /**
     Compute all-in pot equity of each player's hand, either by complete
     enumeration of outcomes or by monte carlo sampling.
     @param gameType specifies game (holdem, omaha, etc)
     @param nsamples number of monte carlo samples; if 0, full enumeration
     @param pocketRanks pocketRanks[i][j] is rank of player i's jth card
     @param pocketSuits pocketSuits[i][j] is suit of player i's jth card
     @param boardRanks boardRanks[j] is rank of jth board card
     @param boardSuits boardSuits[j] is suit of jth board card
     @param deadRanks deadRanks[j] is rank of jth dead card
     @param deadSuits deadSuits[j] is suit of jth dead card
     @param ev output: ev[i] is pot equity of player i
   */
  public static native void PotEquity(int gameType,
                                      int nsamples,
                                      int[][] pocketRanks,
                                      int[][] pocketSuits,
                                      int[] boardRanks,
                                      int[] boardSuits,
                                      int[] deadRanks,
                                      int[] deadSuits,
                                      double[] ev);
  
  /**
     A simple test of Enumerate methods.
     Compare to "pokenum -h ks kh ad td 9c 8c -- kd jd th / As 2h.
  */
  public static void main(String[] args) {
    int[][] pocketRanks = new int[3][2];
    int[][] pocketSuits = new int[3][2];
    int[] boardRanks = new int[3];
    int[] boardSuits = new int[3];
    int[] deadRanks = new int[2];
    int[] deadSuits = new int[2];
    // player 0 has Ks Kh
    pocketRanks[0][0] = StandardEval.RANK_KING;
    pocketSuits[0][0] = StandardEval.SUIT_SPADES;
    pocketRanks[0][1] = StandardEval.RANK_KING;
    pocketSuits[0][1] = StandardEval.SUIT_HEARTS;

    // player 1 has Ad Td
    pocketRanks[1][0] = StandardEval.RANK_ACE;
    pocketSuits[1][0] = StandardEval.SUIT_DIAMONDS;
    pocketRanks[1][1] = StandardEval.RANK_TEN;
    pocketSuits[1][1] = StandardEval.SUIT_DIAMONDS;

    // player 2 has 9c 8c
    pocketRanks[2][0] = StandardEval.RANK_9;
    pocketSuits[2][0] = StandardEval.SUIT_CLUBS;
    pocketRanks[2][1] = StandardEval.RANK_8;
    pocketSuits[2][1] = StandardEval.SUIT_CLUBS;

    // the board is Kd Jd Th
    boardRanks[0] = StandardEval.RANK_KING;
    boardSuits[0] = StandardEval.SUIT_DIAMONDS;
    boardRanks[1] = StandardEval.RANK_JACK;
    boardSuits[1] = StandardEval.SUIT_DIAMONDS;
    boardRanks[2] = StandardEval.RANK_TEN;
    boardSuits[2] = StandardEval.SUIT_HEARTS;

    // another player folded As 2h
    deadRanks[0] = StandardEval.RANK_ACE;
    deadSuits[0] = StandardEval.SUIT_SPADES;
    deadRanks[1] = StandardEval.RANK_2;
    deadSuits[1] = StandardEval.SUIT_HEARTS;

    double[] ev = new double[pocketRanks.length];
    try {
      PotEquity(GAME_HOLDEM, 0, pocketRanks, pocketSuits,
                boardRanks, boardSuits, deadRanks, deadSuits, ev);
      for (int i=0; i<ev.length; i++) {
        System.out.println("In Java: Player " + i + " ev=" + ev[i]);
      }
    } catch (Exception e) {
      System.out.println("In Java: caught exception: " + e);
    }
  }
}

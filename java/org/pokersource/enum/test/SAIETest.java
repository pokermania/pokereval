// $Id$

package org.pokersource.enum.test;
import org.pokersource.enum.*;
import org.pokersource.game.Deck;
import java.util.HashSet;
import java.util.Iterator;

import junit.framework.*;

public class SAIETest extends TestCase {
  private HoldemBeliefVector bv1;
  private HoldemBeliefVector bv2;
  private HoldemBeliefVector bv3;
  private HoldemBeliefVector bv4;
  private long mask5h4h3d;
  
  public SAIETest(String name) {
    super(name);
  }
  public static void main(String args[]) {
    junit.textui.TestRunner.run(SAIETest.class);
  }

  protected void setUp() {
    bv1 = new HoldemBeliefVector("KhQc");
    bv2 = new HoldemBeliefVector("SM1 SM2 SM3");
    bv3 = new HoldemBeliefVector("SM1 SM2 SM3 SM4 SM5");
    bv4 = new HoldemBeliefVector("TdTc");
    mask5h4h3d = Deck.parseCardMask("5h 4h 3d");
  }

  public void testFlopGameSAIE() {
    double[] ev = new double[2];
    // KhQc vs "SM1 SM2 SM3" with board of 5h4h3d
    SAIE.FlopGameSAIE(Enumerate.GAME_HOLDEM, new BeliefVector[] {bv1, bv2},
                      mask5h4h3d, 0, ev);
    assertEquals(0.279634179634, ev[0], 1e-10);
    assertEquals(0.720365820366, ev[1], 1e-10);

    // KhQc vs "SM1 SM2 SM3 SM4 SM5" with board of 5h4h3d
    SAIE.FlopGameSAIE(Enumerate.GAME_HOLDEM, new BeliefVector[] {bv1, bv3},
                      mask5h4h3d, 0, ev);
    assertEquals(0.416602297485, ev[0], 1e-10);
    assertEquals(0.583397702515, ev[1], 1e-10);
  }

  public void checkEV(double ev[], HashSet matchups) {
    double[] evm = new double[ev.length];
    double totalprob = 0.0;
    for (Iterator iter=matchups.iterator(); iter.hasNext(); ) {
      HandMatchup hm = (HandMatchup) iter.next();
      for (int i=0; i<ev.length; i++) {
        evm[i] += hm.matchEV[i] * hm.matchProb;
      }
      totalprob += hm.matchProb;
    }
    for (int i=0; i<ev.length; i++) {
      evm[i] /= totalprob;
      assertEquals(evm[i], ev[i], 1e-10);
    }
  }

  public void testFlopGameSAIE_Matchup() {
    double[] ev = new double[2];
    HashSet matchups = new HashSet();
    // KhQc vs TdTc with board of 5h4h3d
    SAIE.FlopGameSAIE(Enumerate.GAME_HOLDEM, new BeliefVector[] {bv1, bv4},
                      mask5h4h3d, 0, ev, matchups);
    assertEquals(0.298484848485, ev[0], 1e-10);
    assertEquals(0.701515151515, ev[1], 1e-10);
    assertEquals(1, matchups.size());
    checkEV(ev, matchups);

    // KhQc vs "SM1 SM2 SM3" with board of 5h4h3d
    SAIE.FlopGameSAIE(Enumerate.GAME_HOLDEM, new BeliefVector[] {bv1, bv2},
                      mask5h4h3d, 0, ev, matchups);
    assertEquals(0.279634179634, ev[0], 1e-10);
    assertEquals(0.720365820366, ev[1], 1e-10);
    assertEquals((6+3+3+6+3) + (6+3+4+2+9) + (6+4+3+3+4+9),
                 matchups.size());
    checkEV(ev, matchups);
  }

}


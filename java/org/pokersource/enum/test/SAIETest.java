// $Id$

package org.pokersource.enum.test;
import org.pokersource.enum.*;
import org.pokersource.game.Deck;

import junit.framework.*;

public class SAIETest extends TestCase {
  private HoldemBeliefVector bv1;
  private HoldemBeliefVector bv2;
  private HoldemBeliefVector bv3;
  private long mask5h4h3d;
  
  public SAIETest(String name) {
    super(name);
  }
  public static void main(String args[]) {
    junit.textui.TestRunner.run(HoldemCanonGroupTest.class);
  }

  protected void setUp() {
    bv1 = new HoldemBeliefVector("KhQc");
    bv2 = new HoldemBeliefVector("SM1 SM2 SM3");
    bv3 = new HoldemBeliefVector("SM1 SM2 SM3 SM4 SM5");
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

}

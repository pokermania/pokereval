// $Id$

package org.pokersource.enum.test;
import org.pokersource.enum.*;
import org.pokersource.game.Deck;

import junit.framework.*;

/**
   @author Michael Maurer <mjmaurer@yahoo.com>
*/

public class HoldemHandGroupFactoryTest extends TestCase {
  public HoldemHandGroupFactoryTest(String name) {
    super(name);
  }
  public static void main(String args[]) {
    junit.textui.TestRunner.run(HoldemHandGroupFactoryTest.class);
  }

  protected void setUp() {
  }

  public void testCache() {
    HoldemHandGroup g1 = HoldemHandGroupFactory.getInstance("AK");
    HoldemHandGroup g2 = HoldemHandGroupFactory.getInstance("Q9s+");
    HoldemHandGroup g3 = HoldemHandGroupFactory.getInstance("AK");
    assertTrue(g1 != g2);
    assertTrue(!g1.equals(g2));
    assertTrue(g1 == g3);
    assertTrue(g1.equals(g3));
  }

  public void testException() {
    try {
      HoldemHandGroup g1 = HoldemHandGroupFactory.getInstance("JUNK");
      fail("Should raise IllegalArgumentException");
    } catch (IllegalArgumentException e) {
    } catch (RuntimeException e) {
      fail("Should raise IllegalArgumentException");
    }
  }

  public void testThreshold() {
    try {
      HoldemHandOrdering hho = new HoldemHandOrdering("sample1.hho");
      ThresholdHandGroup.registerHandValuation("SAMPLE1", hho);
      HoldemHandGroup gt = HoldemHandGroupFactory.getInstance("SAMPLE1>0.95");
      // SAMPLE1>0.95 is [AJs AQ TT AQs AK JJ AKs QQ KK AA]
      assertEquals(4+12+6+4+12+6+4+6+6+6, gt.numHands());
      assertTrue(!gt.isHandInGroup(Deck.parseCardMask("9h9d")));
      assertTrue(!gt.isHandInGroup(Deck.parseCardMask("AhJd")));
      assertTrue(!gt.isHandInGroup(Deck.parseCardMask("KcQc")));
      assertTrue(gt.isHandInGroup(Deck.parseCardMask("AhJh")));
      assertTrue(gt.isHandInGroup(Deck.parseCardMask("AhQd")));
      assertTrue(gt.isHandInGroup(Deck.parseCardMask("TsTd")));
      assertTrue(gt.isHandInGroup(Deck.parseCardMask("AsQs")));
      assertTrue(gt.isHandInGroup(Deck.parseCardMask("AsKh")));
      assertTrue(gt.isHandInGroup(Deck.parseCardMask("JhJd")));
      assertTrue(gt.isHandInGroup(Deck.parseCardMask("AdKd")));
      assertTrue(gt.isHandInGroup(Deck.parseCardMask("QhQs")));
      assertTrue(gt.isHandInGroup(Deck.parseCardMask("AhKs")));
      assertTrue(gt.isHandInGroup(Deck.parseCardMask("AhAs")));
    } catch (Exception e) {
      fail("exception " + e);
    }
  }
}

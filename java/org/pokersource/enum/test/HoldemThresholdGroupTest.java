// $Id$

package org.pokersource.enum.test;
import org.pokersource.enum.*;
import org.pokersource.game.Deck;

import junit.framework.*;

/**
   @author Michael Maurer <mjmaurer@yahoo.com>
*/

public class HoldemThresholdGroupTest extends TestCase {
  HoldemHandGroup ht1;

  public HoldemThresholdGroupTest(String name) {
    super(name);
  }
  public static void main(String args[]) {
    junit.textui.TestRunner.run(HoldemThresholdGroupTest.class);
  }

  protected void setUp() {
    try {
      HoldemHandOrdering hho = new HoldemHandOrdering("sample1.hho");
      ThresholdHandGroup.registerHandValuation("SAMPLE1", hho);
      ht1 = HoldemHandGroupFactory.getInstance("SAMPLE1>0.95");
    } catch (Exception e) {
      fail("exception " + e);
    }
  }

  public void testToString() {
    assertEquals("SAMPLE1>0.95", ht1.toString());
  }
  
  public void testIsHandInGroup() {
    // SAMPLE1>0.95 is [AJs AQ TT AQs AK JJ AKs QQ KK AA]
    assertTrue(!ht1.isHandInGroup(Deck.parseCardMask("9h9d")));
    assertTrue(!ht1.isHandInGroup(Deck.parseCardMask("AhJd")));
    assertTrue(!ht1.isHandInGroup(Deck.parseCardMask("KcQc")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("AhJh")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("AhQd")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("TsTd")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("AsQs")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("AsKh")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("JhJd")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("AdKd")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("QhQs")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("AhKs")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("AhAs")));
  }
  
  public void testGetHands() {
    assertEquals(4+12+6+4+12+6+4+6+6+6, ht1.numHands());
    assertEquals(4+12+6+4+12+6+4+6+6+6, ht1.getHands().length);
  }
}

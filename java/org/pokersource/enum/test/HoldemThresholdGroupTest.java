// $Id$

package org.pokersource.enum.test;

import junit.framework.TestCase;
import org.pokersource.enum.HoldemHandGroup;
import org.pokersource.enum.HoldemHandGroupFactory;
import org.pokersource.enum.HoldemHandOrdering;
import org.pokersource.enum.ThresholdHandGroup;
import org.pokersource.game.Deck;

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
    // SAMPLE1>0.95 is [AJs AQs 77 AKs 88 99 TT JJ QQ KK AA]
    assertTrue(!ht1.isHandInGroup(Deck.parseCardMask("6h6d")));
    assertTrue(!ht1.isHandInGroup(Deck.parseCardMask("AhKd")));
    assertTrue(!ht1.isHandInGroup(Deck.parseCardMask("KcQc")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("AhJh")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("AhQh")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("7s7d")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("AsKs")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("8s8d")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("9s9d")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("TsTd")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("JhJd")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("QhQs")));
    assertTrue(ht1.isHandInGroup(Deck.parseCardMask("AhAs")));
  }

  public void testGetHands() {
    assertEquals(4 + 4 + 6 + 4 + 6 + 6 + 6 + 6 + 6 + 6 + 6, ht1.numHands());
    assertEquals(4 + 4 + 6 + 4 + 6 + 6 + 6 + 6 + 6 + 6 + 6, ht1.getHands().length);
  }
}

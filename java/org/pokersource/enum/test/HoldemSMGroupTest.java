// $Id$

package org.pokersource.enum.test;
import org.pokersource.enum.*;
import org.pokersource.game.Deck;

import junit.framework.*;

public class HoldemSMGroupTest extends TestCase {
  private HoldemSMGroup gSM1;
  private HoldemSMGroup gSM2;
  private HoldemSMGroup gSM9;
  private long AhAd;
  private long KhQh;
  private long KhQs;
  private long Td9d;
  private long Td9c;
  private long _7d3c;

  
  public HoldemSMGroupTest(String name) {
    super(name);
  }
  public static void main(String args[]) {
    junit.textui.TestRunner.run(HoldemSMGroupTest.class);
  }

  protected void setUp() {
    gSM1 = new HoldemSMGroup("SM1");
    gSM2 = new HoldemSMGroup("SM2");
    gSM9 = new HoldemSMGroup("SM9");
    AhAd = Deck.parseCardMask("AhAd");
    KhQh = Deck.parseCardMask("KhQh");
    KhQs = Deck.parseCardMask("KhQs");
    Td9d = Deck.parseCardMask("Td9d");
    Td9c = Deck.parseCardMask("Td9c");
    _7d3c = Deck.parseCardMask("7d3c");
  }

  public void testToString() {
    assertEquals("SM1", gSM1.toString());
    assertEquals("SM2", gSM2.toString());
    assertEquals("SM9", gSM9.toString());
  }
  
  public void testIsHandInGroup() {
    assertTrue(gSM1.isHandInGroup(AhAd));
    assertTrue(!gSM1.isHandInGroup(KhQh));
    assertTrue(!gSM1.isHandInGroup(KhQs));
    assertTrue(!gSM1.isHandInGroup(Td9d));
    assertTrue(!gSM1.isHandInGroup(Td9c));
    assertTrue(!gSM1.isHandInGroup(_7d3c));

    assertTrue(!gSM2.isHandInGroup(AhAd));
    assertTrue(gSM2.isHandInGroup(KhQh));
    assertTrue(!gSM2.isHandInGroup(KhQs));
    assertTrue(!gSM2.isHandInGroup(Td9d));
    assertTrue(!gSM2.isHandInGroup(Td9c));
    assertTrue(!gSM2.isHandInGroup(_7d3c));

    assertTrue(!gSM9.isHandInGroup(AhAd));
    assertTrue(!gSM9.isHandInGroup(KhQh));
    assertTrue(!gSM9.isHandInGroup(KhQs));
    assertTrue(!gSM9.isHandInGroup(Td9d));
    assertTrue(!gSM9.isHandInGroup(Td9c));
    assertTrue(gSM9.isHandInGroup(_7d3c));
  }
  
  public void testGetHands() {
    assertEquals(6+6+6+6+4, gSM1.getHands().length);
    assertEquals(6+4+4+4+12, gSM2.getHands().length);
    assertEquals(784, gSM9.getHands().length);
  }

}

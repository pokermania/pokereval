// $Id$

package org.pokersource.game.test;

import junit.framework.*;

/**
   @author Michael Maurer <mjmaurer@yahoo.com>
*/

public class AllTests {
  public static void main (String[] args) {
    junit.textui.TestRunner.run(suite());
  }
  public static Test suite() {
    TestSuite suite = new TestSuite("All org.pokersource.game tests");
    suite.addTest(new TestSuite(DeckTest.class));
    return suite;
  }
}

// $Id$

package org.pokersource.util.test;

import junit.framework.*;

/**
   @author Michael Maurer <mjmaurer@yahoo.com>
*/

public class AllTests {
  public static void main (String[] args) {
    junit.textui.TestRunner.run(suite());
  }
  public static Test suite() {
    TestSuite suite = new TestSuite("All org.pokersource.util tests");
    suite.addTest(new TestSuite(IntArrayTest.class));
    suite.addTest(new TestSuite(LongArrayTest.class));
    suite.addTest(new TestSuite(NestedLoopEnumerationTest.class));
    suite.addTest(new TestSuite(ValueSortedMapTest.class));
    return suite;
  }
}

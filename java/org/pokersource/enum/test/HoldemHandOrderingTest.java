// $Id$

package org.pokersource.enum.test;
import org.pokersource.enum.*;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.InputStream;

import junit.framework.*;

/**
   @author Michael Maurer <mjmaurer@yahoo.com>
*/

public class HoldemHandOrderingTest extends TestCase {
  private static final String SAMPLE_PATH = "sample1.hho";
  private HoldemHandOrdering hho1;
  
  public HoldemHandOrderingTest(String name) {
    super(name);
  }
  public static void main(String args[]) {
    junit.textui.TestRunner.run(HoldemHandOrderingTest.class);
  }

  protected void setUp() {
    try {
      ClassLoader cl = ClassLoader.getSystemClassLoader();
      InputStream stream = cl.getResourceAsStream(SAMPLE_PATH);
      if (stream == null)
        throw new FileNotFoundException(SAMPLE_PATH);
      hho1 = new HoldemHandOrdering(stream);
    } catch (IOException e) {
      throw new RuntimeException("caught " + e);
    }
  }

  public void testToString() {
    assertTrue(hho1.toString().startsWith("72:0.0 82:0.00904977"));
  }

  public void testGreaterEqual() {
    HandGroup[] groups = hho1.greaterEqual(0.95);
    assertEquals(10, groups.length);
    assertEquals("AJs", groups[0].toString());
    assertEquals("AQ", groups[1].toString());
    assertEquals("TT", groups[2].toString());
    assertEquals("AQs", groups[3].toString());
    assertEquals("AK", groups[4].toString());
    assertEquals("JJ", groups[5].toString());
    assertEquals("AKs", groups[6].toString());
    assertEquals("QQ", groups[7].toString());
    assertEquals("KK", groups[8].toString());
    assertEquals("AA", groups[9].toString());
  }
}

// $Id$

package org.pokersource.enum;

/** Creates instances of HoldemHandGroup objects from their string
    representations.  Use of this factory is preferred to directly calling the
    constructors of the HoldemHandGroup subclasses.
*/

public class HoldemHandGroupFactory {
  private static Class[] groupClasses = {
    HoldemAtomicGroup.class,
    HoldemCanonGroup.class,
    HoldemSMGroup.class,
    HoldemAbdulGroup.class,
    HoldemUniversalGroup.class,
  };
  public static HoldemHandGroup getInstance(String groupSpec) {
    HoldemHandGroup group = null;
    // Loop through the known classes that can parse holdem hand groups and
    // try each in turn.  If one throws an exception, try another until we
    // run out.
    for (int i=0; i<groupClasses.length && group == null; i++) {
      try {
        java.lang.reflect.Constructor ctor =
          groupClasses[i].getConstructor(new Class[] {String.class});
        group = (HoldemHandGroup) ctor.newInstance(new Object[] {groupSpec});
      } catch (java.lang.reflect.InvocationTargetException e) {
        Throwable te = e.getTargetException();
        if (te instanceof java.lang.IllegalArgumentException) {
          // This is the exception we throw when unable to parse the
          // group specification.  So ignore it and try another class.
        } else {
          // Something unexpected
          throw new RuntimeException("BUG1: " + te);
        }
      } catch (Exception e) {
        // Something else unexpected
        throw new RuntimeException("BUG2: " + e);
      }
    }
    if (group == null)
      throw new java.lang.IllegalArgumentException("cannot parse spec: " +
                                                   groupSpec);
    return group;
  }
}

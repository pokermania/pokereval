// $Id$

package org.pokersource.enum;
import java.util.Set;

/** A HandGroup represents a set of poker hands that can be referred to by
    name.  The specific way that hands are assigned to named groups is
    specific to each poker game.  For example, in Holdem, named groups
    include specific holdings like "AhAd", "Kh2h"; canonical starting
    hands like "AKs", "TT"; or abdulian groups like "Q8s+".  Subclasses
    like HoldemHandGroup define these groups for specific games.
    @see BaseHandGroup
    @see HoldemHandGroup
    @author Michael Maurer <mjmaurer@yahoo.com>
*/

public interface HandGroup {
  String getGroupSpec();
  int numHands();
  long[] getHands();
  Set getHandSet();
  boolean isHandInGroup(long hand);
  String toString();
  String toStringAtomic();
}

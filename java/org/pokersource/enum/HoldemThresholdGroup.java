// $Id$

package org.pokersource.enum;

/**
 A holdem-specific implementation of ThresholdHandGroup.
 @see ThresholdHandGroup
 @author Michael Maurer <mjmaurer@yahoo.com>
 */

public class HoldemThresholdGroup extends ThresholdHandGroup
        implements HoldemHandGroup {
  public HoldemThresholdGroup(String groupSpec) {
    super(groupSpec);
  }
}

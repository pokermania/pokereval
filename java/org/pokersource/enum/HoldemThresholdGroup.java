// $Id$

package org.pokersource.enum;

/**
 A holdem-specific implementation of ThresholdHandGroup.
 @see ThresholdHandGroup
 @author Michael Maurer &lt;<a href="mailto:mjmaurer@yahoo.com">mjmaurer@yahoo.com</a>&gt;
 */

public class HoldemThresholdGroup extends ThresholdHandGroup
        implements HoldemHandGroup {
  public HoldemThresholdGroup(String groupSpec) {
    super(groupSpec);
  }
}

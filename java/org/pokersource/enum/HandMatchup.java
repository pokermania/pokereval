// $Id$

package org.pokersource.enum;

import org.pokersource.util.LongArray;

/**
 Represents one poker confrontation in which each player holds one specific
 hand.
 @see MatchupOutcome
 @author Michael Maurer &lt;<a href="mailto:mjmaurer@yahoo.com">mjmaurer@yahoo.com</a>&gt;
 */

public class HandMatchup extends LongArray {
  public HandMatchup(long values[]) {
    super(values);
  }
}

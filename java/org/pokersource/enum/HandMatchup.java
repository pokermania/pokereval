// $Id$

package org.pokersource.enum;

public class HandMatchup {
  public double matchProb;           // probability of this matchup
  public long matchHands[];          // matchHands[i] is player i's hand
  public double matchEV[];           // matchEV[i] is player i's all-in equity
  HandMatchup(double matchProb,
              long matchHands[],
              double matchEV[]) {
    if (matchHands.length != matchEV.length)
      throw new IllegalArgumentException("inconsistent array sizes");
    this.matchProb = matchProb;
    this.matchHands = (long[]) matchHands.clone();
    this.matchEV = (double[]) matchEV.clone();
  }
}

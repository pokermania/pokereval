// $Id$

package org.pokersource.enum;
import org.pokersource.game.Deck;
import java.util.HashSet;
import java.util.HashMap;
import java.util.Iterator;

/** Represents subjective beliefs about the possible hands held by a
    player.  Maintains a mapping from each hand to its probability of
    occurrence.
*/

public abstract class BeliefVector {
  /** Our string representation, from the constructor. */
  private String myspec;

  /** The universe of all possible hands.  Should be set in the subclass'
      constructor.  Used by addRemaining() to know which hands haven't
      yet been added. */
  HandGroup universalGroup;

  /** The belief probability (unconditioned by dead cards) of each hand group.
      Hash key is HoldemHandGroup, value is Double.  Positive value is the
      relative probability compared to uniform Bayesian prior (so, a value of
      +2 means hand from this group are twice as likely as would be expected
      from a uniform distribution over all possible hands); a negative value
      indicates an absolute probability (so -0.40 means that hands in this
      group account for 40% of the total probability).  Values must be either
      all positive or all negative. */
  private HashMap groupProb;

  /** The bitmask of dead cards.  This conditions the probabilities returned
      by getBeliefProb(). */
  private long deadCards;

  /** The belief probability (conditioned by dead cards) for each atomic
      starting hand.  Updated as needed by recomputeHandProb().  */
  private HashMap handProb;

  private boolean hasRelative = false;
  private boolean hasAbsolute = false;

  /** Instantiate self from string respresentation.  Meant to be called from
      subclass's constructor.  The subclass constructor should then parse the
      string spec and populate groupProb and deadCards. */
  public BeliefVector(String spec) {
    myspec = spec;
    groupProb = new HashMap();
    deadCards = 0;
    handProb = null;
  }

  /** Instantiate self from string respresentation.  This method must be
      implemented by all subclasses.  Also, subclass constructors should call
      super(spec) and then fromString(spec). */
  public abstract void fromString(String spec);

  /** Generate string representation of self; the inverse of fromString(). */
  public String toString() {
    StringBuffer buf = new StringBuffer();
    for (Iterator iter = groupProb.keySet().iterator(); iter.hasNext(); ) {
      HandGroup group = (HandGroup) iter.next();
      if (buf.length() > 0)
        buf.append(" ");
      buf.append(group.toString());
      double prob = ((Double) groupProb.get(group)).doubleValue();
      String delim = (prob < 0) ? "=" : ":";
      int percent = (int) Math.round(100 * Math.abs(prob));
      buf.append(delim + percent);
    }
    if (deadCards != 0)
      buf.append(" / " + Deck.cardMaskString(deadCards));
    return buf.toString();
  }

  /** Generate a string representation of self that gives probability
      details for all atomic hands, conditioned on the dead cards. */
  public String toStringAtomic() {
    StringBuffer buf = new StringBuffer();
    for (Iterator iter = handProb.keySet().iterator(); iter.hasNext(); ) {
      Long lhand = (Long) iter.next();
      long hand = lhand.longValue();
      double prob = ((Double) handProb.get(lhand)).doubleValue();
      if (buf.length() > 1)
        buf.append(" ");
      buf.append(Deck.cardMaskString(hand, ""));
      int percent = (int) Math.round(100 * Math.abs(prob));
      buf.append(":" + percent);
    }
    return buf.toString();
  }


  /** Return an array of bitmasks representing hands with nonzero probability
      of occurring (conditioned on the dead cards). */
  public long[] getHands() {
    long[] hands = new long[handProb.size()];
    int nhands = 0;
    for (Iterator iter = handProb.keySet().iterator(); iter.hasNext(); )
      hands[nhands++] = ((Long) iter.next()).longValue();
    return hands;
  }
  
  /** Return the absolute probability that hand will occur, conditioned on
      the dead cards. */
  public double getBeliefProb(long hand) {
    Double prob = (Double) handProb.get(new Long(hand));
    if (prob == null)
      return 0;
    else
      return prob.doubleValue();
  }

  private void recomputeHandProb() {
    int totalHands = 0;         // # of atomic hands in union of groups
    int totalLive = 0;          // # of these that aren't excluded by deadCards
    double totalRel = 0.0;      // sum over groups of each group's relative prob
    				// times the group's number of atomic hands
    for (Iterator iter = groupProb.keySet().iterator(); iter.hasNext(); ) {
      HandGroup group = (HandGroup) iter.next();
      long[] ghands = group.getHands();
      double gprob = ((Double) groupProb.get(group)).doubleValue();
      int numLive = 0;
      for (int i=0; i<ghands.length; i++)
        if ((ghands[i] & deadCards) == 0)
          numLive++;
      totalLive += numLive;
      totalHands += ghands.length;
      if (gprob > 0)
        totalRel += gprob * ghands.length;
    }
    handProb = new HashMap(totalHands);
    if (totalLive > 0) {
      System.out.println("recomputing: totalHands=" + totalHands +
                         ", totalLive=" + totalLive + ", totalRel=" + totalRel);
      for (Iterator iter = groupProb.keySet().iterator(); iter.hasNext(); ) {
        HandGroup group = (HandGroup) iter.next();
        long[] ghands = group.getHands();
        double gprob = ((Double) groupProb.get(group)).doubleValue();
        double hprob;
        if (gprob < 0) {           // absolute probability
          hprob = -gprob / ghands.length;
        } else if (gprob > 0) {    // relative probability
          hprob = gprob / totalRel;
        } else {
          hprob = 0;
        }
        hprob *= (double)totalHands / totalLive;
        System.out.println("recomputing: group=" + group.toString() +
                           ", gsize=" + ghands.length +
                           ", gprob=" + gprob +
                           ", hprob=" + hprob);
        if (hprob > 0)
          for (int i=0; i<ghands.length; i++)
            if ((ghands[i] & deadCards) == 0) {
              Long key = new Long(ghands[i]);
              Double value = new Double(hprob);
              if (handProb.containsKey(key))
                throw new IllegalArgumentException
                  ("duplicate hand: " + Deck.cardMaskString(ghands[i]));
              handProb.put(key, value);
            }
      }
    }
  }

 /** Set the "dead cards", cards that are known not to be available.  This
     sets the probability to zero of any hand including any of these cards
     increases the probabilities of the other hands in proportion. */
  public void setDeadCards(long cards) {
    deadCards = cards;
    recomputeHandProb();
  }

  private void addHandGroup(HandGroup group, double prob) {
    System.out.println("ADD group=" + group.toString() + ", prob=" + prob);
    groupProb.put(group, new Double(prob));
    recomputeHandProb();
  }

  /** During construction, add a new hand group with its probability of
      occurrence relative to the Bayesian probability.  Meant to be called by
      subclass's fromString() */
  void addHandGroupRelative(HandGroup group, double relativeProb) {
    if (hasAbsolute)
      throw new IllegalArgumentException("cannot mix relative and absolute probs");
    addHandGroup(group, relativeProb);
    hasRelative = true;
  }
  
  /** During construction, add a new hand group with its absolute probability
      of occurrence.  The sum of absolute probabilities over groups should be
      1.  Meant to be called by subclass's fromString(). */
  void addHandGroupAbsolute(HandGroup group, double absoluteProb) {
    if (hasRelative)
      throw new IllegalArgumentException("cannot mix relative and absolute probs");
    addHandGroup(group, -absoluteProb);
    hasAbsolute = true;
  }

  private void addRemaining(double prob) {
    System.out.println("ADD all remaining hands, prob=" + prob);
    // Form a special hand group whose set of hands is the difference between
    // the universe of possible hands and hands present in groups we have
    // already added.
    HandGroup others = new HandGroup();
    others.myspec = "<other>";
    others.myhands = new HashSet();
    others.myhands.addAll(universalGroup.myhands);
    for (Iterator iter = groupProb.keySet().iterator(); iter.hasNext(); ) {
      HandGroup group = (HandGroup) iter.next();
      others.myhands.removeAll(group.myhands);
    }
    groupProb.put(others, new Double(prob));
    recomputeHandProb();
  }

  /** During construction, add each hand not yet added with its probability of
      occurrence relative to its Bayesian probability.  Meant to be called by
      subclass's fromString() */
  void addRemainingRelative(double relativeProb) {
    if (hasAbsolute)
      throw new IllegalArgumentException("cannot mix relative and absolute probs");
    addRemaining(relativeProb);
    hasRelative = true;
  }
  
  /** During construction, add each hand not yet added with the given absolute
      probability of occurrence of the entire set of such hands.  The sum of
      absolute probabilities over groups should be 1.  Meant to be called by
      subclass's fromString(). */
  void addRemainingAbsolute(double absoluteProb) {
    if (hasRelative)
      throw new IllegalArgumentException("cannot mix relative and absolute probs");
    addRemaining(-absoluteProb);
    hasAbsolute = true;
  }
}

// $Id$

package org.pokersource.enum;
import org.pokersource.game.Deck;
import java.util.HashSet;
import java.util.StringTokenizer;

/** A concrete implementation of BeliefVector for the game of Holdem. */

public class HoldemBeliefVector extends BeliefVector {
  /** Instantiate from a string representation.  The syntax is one or more
      whitespace separated tokens, where each token takes the form GROUP
      [":" RELPROB | "=" ABSPROB].  Here GROUP is the string
      representation of a HoldemHandGroup, RELPROB indicates that hands in
      the group are RELPROB/100 times as likely as would be expected without
      any other information, and ABSPROB indicates that hands in the group
      occur precisely ABSPROB percent of the time.  If the probability is
      omitted then ":100" is the default.  Either all groups must use relative
      probability or all groups must use absolute probability.  The special
      value "<other>" may be used for the last GROUP; it denotes the set
      of hands not yet mentioned in any previous GROUP. */
  public HoldemBeliefVector(String spec) {
    super(spec);
    universalGroup = (HandGroup) HoldemHandGroupFactory.getInstance("<any>");
    fromString(spec);
  }

  public void fromString(String spec) {
    StringTokenizer st1 = new StringTokenizer(spec);
    while (st1.hasMoreTokens()) {
      String tok1 = st1.nextToken();
      StringTokenizer st2 = new StringTokenizer(tok1, ":=", true);
      String groupSpec = st2.nextToken();
      double prob;
      if (st2.hasMoreTokens()) {
        String delim = st2.nextToken();
        String sprob = st2.nextToken();
        prob = Double.valueOf(sprob).doubleValue() / 100;
        if (delim.equals("="))
          prob = -prob;
      } else {
        prob = 1.0;
      }
      if (groupSpec.equals("<other>")) {
        if (prob > 0) {
          addRemainingRelative(prob);
        } else if (prob < 0) {
          addRemainingAbsolute(-prob);
        }
      } else {
        HoldemHandGroup group = HoldemHandGroupFactory.getInstance(groupSpec);
        if (prob > 0) {
          addHandGroupRelative(group, prob);
        } else if (prob < 0) {
          addHandGroupAbsolute(group, -prob);
        }
      }
    }
  }

  public static void main(String[] args) {
    HoldemBeliefVector v1 = new HoldemBeliefVector("");
    v1.addHandGroupRelative(new HoldemCanonGroup("AKs"), 2.00);
    v1.addHandGroupRelative(new HoldemCanonGroup("T9"), 1.00);
    v1.addHandGroupRelative(new HoldemCanonGroup("52s"), 0.50);
    System.out.println("v1.toString = " + v1.toString());
    System.out.println("v1.toStringAtomic = " + v1.toStringAtomic());

    HoldemBeliefVector v2 = new HoldemBeliefVector("AKs:200 T9 52s:50");
    System.out.println("v2.toString = " + v2.toString());
    System.out.println("v2.toStringAtomic = " + v2.toStringAtomic());
    int[] dranks = {Deck.RANK_5, Deck.RANK_5};
    int[] dsuits = {Deck.SUIT_HEARTS, Deck.SUIT_SPADES};
    long dead = Deck.createCardMask(dranks, dsuits);
    v2.setDeadCards(dead);
    System.out.println("v2.toString = " + v2.toString());
    System.out.println("v2.toStringAtomic = " + v2.toStringAtomic());

    HoldemBeliefVector v3 = new HoldemBeliefVector("AA=50 SM2=50");
    System.out.println("v3.toString = " + v3.toString());
    System.out.println("v3.toStringAtomic = " + v3.toStringAtomic());
  }
}

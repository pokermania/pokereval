// $Id$

package org.pokersource.enum;

/** An iterator that steps through an abritrary number of nested loops, each
    starting at zero and ending at its own upper limit.  Useful when the
    number of nested loops is known only at runtime.  Example: if the
    limits are set to {2, 3, 2}, then the iterator will return the following
    values:
<pre>
	{0, 0, 0}
	{0, 0, 1}
	{0, 1, 0}
	{0, 1, 1}
	{0, 2, 0}
	{0, 2, 1}
	{1, 0, 0}
	{1, 0, 1}
	{1, 1, 0}
	{1, 1, 1}
	{1, 2, 0}
	{1, 2, 1}
</pre>
*/

public class NestedLoopEnumeration implements java.util.Enumeration {
  private int ndims;
  private int[] next;
  private int[] limits;

  /** Initializes a nested loop iterator with limits.length dimensions.
      @param limits limits[i] is the upper limit of the ith nested loop (the
      loop runs from 0 to limits[i]-1 inclusive)
  */
  public NestedLoopEnumeration(int[] limits) {
    this.limits = limits;
    ndims = limits.length;
    next = new int[ndims];
    for (int i=0; i<ndims; i++) {
      if (limits[i] <= 0)
        throw new IllegalArgumentException("limits must be positive");
      next[i] = 0;
    }
  }

  public boolean hasMoreElements() {
    return (next != null);
  }

  /** Return an integer array listing the next loop indices for each
      dimension.
      @return An object of int[] type; the ith value is the loop variable
      for the ith nested loop.
  */
  public Object nextElement() {
    if (next == null)
      return null;
    int[] elem = (int[]) next.clone();
    next[ndims-1]++;            // increment least-significant dimension
    for (int i=ndims-1; i>=0; i--) { // check for carries
      if (next[i] == limits[i]) { // need to carry
        next[i] = 0;            // rollover to zero
        if (i>0)
          next[i-1]++;          // carry to next higher dimension
        else
          next = null;          // no more elements
      }
    }
    return elem;
  }
}

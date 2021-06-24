/* Copyright (C) 2013-2021 Free Software Foundation, Inc.
   Author: Stefan Larsson

   This file is part of GNU Libidn.

   GNU Libidn is free software: you can redistribute it and/or
   modify it under the terms of either:

     * the GNU Lesser General Public License as published by the Free
       Software Foundation; either version 3 of the License, or (at
       your option) any later version.

   or

     * the GNU General Public License as published by the Free
       Software Foundation; either version 2 of the License, or (at
       your option) any later version.

   or both in parallel, as here.

   GNU Libidn is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received copies of the GNU General Public License and
   the GNU Lesser General Public License along with this program.  If
   not, see <http://www.gnu.org/licenses/>. */

package gnu.inet.encoding;

import com.google.common.collect.ImmutableList;
import org.junit.Assert;
import org.junit.Test;

import java.util.List;

/**
 * @author Stefan Larsson
 */
public class RangeSetTest
{
  @Test
  public void testEmptyRangeSet()
  {
    final RangeSet rangeSet;
    final RangeSet.Builder builder = RangeSet.builder();
    rangeSet = builder.build();

    Assert.assertFalse("range set misses any number",
	    rangeSet.contains(42));
  }


  @Test
  public void testSingleItemRange()
  {
    final RangeSet rangeSet;
    final RangeSet.Builder builder = RangeSet.builder();
    builder.addRange(new RangeSet.Range(42));
    rangeSet = builder.build();

    Assert.assertTrue("single-number range set contains number",
		      rangeSet.contains(42));
    Assert.assertFalse("single-number range set misses other number",
		       rangeSet.contains(17));
  }

  @Test
  public void testMultiItemRange()
  {
    final RangeSet rangeSet;
    final RangeSet.Builder builder = RangeSet.builder();
    builder.addRange(new RangeSet.Range(10, 15));
    rangeSet = builder.build();

    Assert.assertTrue("[10,15] contains 10", rangeSet.contains(10));
    Assert.assertTrue("[10,15] contains 13", rangeSet.contains(13));
    Assert.assertTrue("[10,15] contains 15", rangeSet.contains(15));
    Assert.assertFalse("[10,15] doesn't contain 9", rangeSet.contains(9));
    Assert.assertFalse("[10,15] doesn't contain 16", rangeSet.contains(16));
  }

  @Test
  public void testAdjacentMultiItemRanges()
  {
    final RangeSet rangeSet;
    final RangeSet.Builder builder = RangeSet.builder();
    builder.addRange(new RangeSet.Range(10, 12));
    builder.addRange(new RangeSet.Range(13, 15));
    rangeSet = builder.build();

    Assert.assertTrue("[10,15] contains 10", rangeSet.contains(10));
    Assert.assertTrue("[10,15] contains 13", rangeSet.contains(13));
    Assert.assertTrue("[10,15] contains 15", rangeSet.contains(15));
    Assert.assertFalse("[10,15] doesn't contain 9", rangeSet.contains(9));
    Assert.assertFalse("[10,15] doesn't contain 16", rangeSet.contains(16));
  }

  @Test
  public void testOverlappingMultiItemRanges()
  {
    final RangeSet rangeSet;
    final RangeSet.Builder builder = RangeSet.builder();
    builder.addRange(new RangeSet.Range(10, 13));
    builder.addRange(new RangeSet.Range(13, 15));
    rangeSet = builder.build();

    Assert.assertTrue("[10,15] contains 10", rangeSet.contains(10));
    Assert.assertTrue("[10,15] contains 13", rangeSet.contains(13));
    Assert.assertTrue("[10,15] contains 15", rangeSet.contains(15));
    Assert.assertFalse("[10,15] doesn't contain 9", rangeSet.contains(9));
    Assert.assertFalse("[10,15] doesn't contain 16", rangeSet.contains(16));
  }

  @Test
  public void testSeparatedMultiItemRanges()
  {
    final RangeSet rangeSet;
    final RangeSet.Builder builder = RangeSet.builder();
    builder.addRange(new RangeSet.Range(13, 15));
    builder.addRange(new RangeSet.Range(10, 11));
    rangeSet = builder.build();

    Assert.assertTrue("[10,11][13,15] contains 10", rangeSet.contains(10));
    Assert.assertTrue("[10,11][13,15] contains 11", rangeSet.contains(11));
    Assert.assertTrue("[10,11][13,15] contains 13", rangeSet.contains(13));
    Assert.assertTrue("[10,11][13,15] contains 15", rangeSet.contains(15));
    Assert.assertFalse("[10,11][13,15] doesn't contain 9", rangeSet.contains(9));
    Assert.assertFalse("[10,11][13,15] doesn't contain 12", rangeSet.contains(12));
    Assert.assertFalse("[10,11][13,15] doesn't contain 16", rangeSet.contains(16));
  }

  @Test
  public void testEmptyBuilder()
  {
    final List<RangeSet.Range> merged =
	    RangeSet.Builder.mergeRanges(ImmutableList.<RangeSet.Range>of());
    Assert.assertTrue("empty merged is empty", merged.isEmpty());
  }

  @Test
  public void testSingleRangeBuilder()
  {
    final RangeSet.Range range = new RangeSet.Range(1, 2);
    final List<RangeSet.Range> merged =
	    RangeSet.Builder.mergeRanges(ImmutableList.<RangeSet.Range>of(range));
    Assert.assertEquals("single range stays", ImmutableList.of(range), merged);
  }

  @Test
  public void testAdjacentRangesBuilder()
  {
    final RangeSet.Range range1 = new RangeSet.Range(1, 2);
    final RangeSet.Range range2 = new RangeSet.Range(3, 4);
    final List<RangeSet.Range> merged =
	    RangeSet.Builder.mergeRanges(
		    ImmutableList.<RangeSet.Range>of(range1, range2));
    Assert.assertEquals("adjacent merged ranges",
			ImmutableList.of(new RangeSet.Range(1, 4)), merged);
  }

  @Test
  public void testSeparatedRangesBuilder()
  {
    final RangeSet.Range range1 = new RangeSet.Range(1, 2);
    final RangeSet.Range range2 = new RangeSet.Range(4, 5);
    final List<RangeSet.Range> merged =
	    RangeSet.Builder.mergeRanges(
		    ImmutableList.<RangeSet.Range>of(range1, range2));
    Assert.assertEquals("adjacent merged ranges",
	    ImmutableList.of(range1, range2), merged);
  }

  @Test
  public void testMergeMultipleRangesBuilder()
  {
    final RangeSet.Range range1 = new RangeSet.Range(1, 2);
    final RangeSet.Range range2 = new RangeSet.Range(3, 5);
    final RangeSet.Range range3 = new RangeSet.Range(4, 8);
    final RangeSet.Range range4 = new RangeSet.Range(5, 7);
    final List<RangeSet.Range> merged =
	    RangeSet.Builder.mergeRanges(
		    ImmutableList.<RangeSet.Range>of(range1, range2,
						     range3, range4));
    Assert.assertEquals("multiple ranges merged to one",
	    ImmutableList.of(new RangeSet.Range(1, 8)), merged);
  }

}

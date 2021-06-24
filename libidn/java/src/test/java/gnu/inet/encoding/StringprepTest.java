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

import org.junit.Assert;
import org.junit.Test;

/**
 * Stringprep unit tests converted from C version.
 * @author Stefan Larsson
 */
public class StringprepTest
{
  private enum Profile {
    NODE_PREP
      {
	@Override
	String prep(String in, boolean allowUnassigned) throws StringprepException
	{
	  return Stringprep.nodeprep(in, allowUnassigned);
	}
      },
    NAME_PREP
      {
	@Override
	String prep(String in, boolean allowUnassigned) throws StringprepException
	{
	  return Stringprep.nameprep(in, allowUnassigned);
	}
      },
    RESOURCE_PREP
      {
	@Override
	String prep(String in, boolean allowUnassigned) throws StringprepException
	{
	  return Stringprep.resourceprep(in, allowUnassigned);
	}
      }
    ;

    abstract String prep(String in, boolean allowUnassigned) throws StringprepException;
  }

  private static class Check {
    private final String comment;
    private final String in;
    private final String out;
    private final Profile profile;
    private final boolean allowUnassigned;
    private final boolean expectException;

    private Check(final String comment,
		  final String in,
		  final String out,
		  final Profile profile,
		  final boolean allowUnassigned,
		  final boolean expectException)
    {
      this.comment = comment;
      this.in = in;
      this.out = out;
      this.profile = profile;
      this.allowUnassigned = allowUnassigned;
      this.expectException = expectException;
    }

    private Check(final String comment,
		  final String in, final String out)
    {
      this.comment = comment;
      this.in = in;
      this.out = out;
      this.profile = Profile.NAME_PREP;
      this.allowUnassigned = true; // C tests allow unassigned CPs by default
      this.expectException = false;
    }

    @Override
    public String toString()
    {
      return "Check{" +
	      "comment='" + comment + '\'' +
	      ", in='" + in + '\'' +
	      ", out='" + out + '\'' +
	      ", profile=" + profile +
	      ", allowUnassigned=" + allowUnassigned +
	      ", expectException=" + expectException +
	      '}';
    }
  }

  // test cases converted to Java from tst_stringprep.c
  private final Check[] checks = new Check[] {
	  new Check("Map to nothing", "foo\u00ad\u034f\u1806\u180bbar\u200b\u2060baz\ufe00\ufe08\ufe0f\ufeff", "foobarbaz"),
	  new Check("Case folding ASCII U+0043 U+0041 U+0046 U+0045", "CAFE", "cafe"),
	  new Check("Case folding 8bit U+00DF (german sharp s)", "\u00df", "ss"),
	  new Check("Case folding U+0130 (turkish capital I with dot)", "\u0130", "i\u0307"),
	  new Check("Case folding multibyte U+0143 U+037A", "\u0143\u037a", "\u0144 \u03b9"),
// Code points outside BMP not supported by Java impl yet
//	  new Check("Case folding U+2121 U+33C6 U+1D7BB", "\u2121\u33c6\ud835\udfbb", "telc\u2215kg\u03c3"),
	  new Check("Normalization of U+006a U+030c U+00A0 U+00AA", "j\u030c\u00a0\u00aa", "\u01f0 a"),
	  new Check("Case folding U+1FB7 and normalization", "\u1fb7", "\u1fb6\u03b9"),
	  new Check("Self-reverting case folding U+01F0 and normalization", "\u01f0", "\u01f0"),
	  new Check("Self-reverting case folding U+0390 and normalization", "\u0390", "\u0390"),
	  new Check("Self-reverting case folding U+03B0 and normalization", "\u03b0", "\u03b0"),
	  new Check("Self-reverting case folding U+1E96 and normalization", "\u1e96", "\u1e96"),
	  new Check("Self-reverting case folding U+1F56 and normalization", "\u1f56", "\u1f56"),
	  new Check("ASCII space character U+0020", " ", " "),
	  new Check("Non-ASCII 8bit space character U+00A0", "\u00a0", " "),
	  new Check("Non-ASCII multibyte space character U+1680", "\u1680", "", Profile.NAME_PREP, true, true),
	  new Check("Non-ASCII multibyte space character U+2000", "\u2000", " "),
	  new Check("Zero Width Space U+200b", "\u200b", ""),
	  new Check("Non-ASCII multibyte space character U+3000", "\u3000", " "),
	  new Check("ASCII control characters U+0010 U+007F", "\u0010\u007f", "\u0010\u007f"),
	  new Check("Non-ASCII 8bit control character U+0085", "\u0085", "", Profile.NAME_PREP, true, true),
	  new Check("Non-ASCII multibyte control character U+180E", "\u180e", "", Profile.NAME_PREP, true, true),
	  new Check("Zero Width No-Break Space U+FEFF", "\ufeff", ""),
	  new Check("Non-ASCII control character U+1D175", "\ud834\udd75", "", Profile.NAME_PREP, true, true),
	  new Check("Plane 0 private use character U+F123", "\uf123", "", Profile.NAME_PREP, true, true),
	  new Check("Plane 15 private use character U+F1234", "\udb84\ude34", "", Profile.NAME_PREP, true, true),
	  new Check("Plane 16 private use character U+10F234", "\udbfc\ude34", "", Profile.NAME_PREP, true, true),
	  new Check("Non-character code point U+8FFFE", "\ud9ff\udffe", "", Profile.NAME_PREP, true, true),
	  new Check("Non-character code point U+10FFFF", "\udbff\udfff", "", Profile.NAME_PREP, true, true),
	  new Check("Surrogate code U+DF42", "\ufffd", "", Profile.NAME_PREP, true, true),
	  new Check("Non-plain text character U+FFFD", "\ufffd", "", Profile.NAME_PREP, true, true),
	  new Check("Ideographic description character U+2FF5", "\u2ff5", "", Profile.NAME_PREP, true, true),
	  new Check("Display property character U+0341", "\u0341", "\u0301"),
	  new Check("Left-to-right mark U+200E", "\u200e", "\u0301", Profile.NAME_PREP, true, true),
	  new Check("Deprecated U+202A", "\u202a", "\u0301", Profile.NAME_PREP, true, true),
	  new Check("Language tagging character U+E0001", "\udb40\udc01", "\u0301", Profile.NAME_PREP, true, true),
	  new Check("Language tagging character U+E0042", "\udb40\udc42", "", Profile.NAME_PREP, true, true),
	  new Check("Bidi: RandALCat character U+05BE and LCat characters", "foo\u05bebar", "", Profile.NAME_PREP, true, true),
	  new Check("Bidi: RandALCat character U+FD50 and LCat characters", "foo\ufd50bar", "", Profile.NAME_PREP, true, true),
	  new Check("Bidi: RandALCat character U+FB38 and LCat characters", "foo\ufe76bar", "foo \u064ebar"),
	  new Check("Bidi: RandALCat without trailing RandALCat U+0627 U+0031", "\u06271", "", Profile.NAME_PREP, true, true),
	  new Check("Bidi: RandALCat character U+0627 U+0031 U+0628", "\u06271\u0628", "\u06271\u0628"),
	  new Check("Unassigned code point U+E0002", "\udb40\udc02", "", Profile.NAME_PREP, false, true),
	  new Check("Larger test (shrinking)", "X\u00ad\u00df\u0130\u2121j\u030c\u00a0\u00aa\u03b0\u2000", "xssi\u0307tel\u01f0 a\u03b0 "),
	  new Check("Larger test (expanding)", "X\u00df\u3316\u0130\u2121\u249f\u3300", "xss\u30ad\u30ed\u30e1\u30fc\u30c8\u30ebi\u0307tel(d)\u30a2\u30d1\u30fc\u30c8"),
	  new Check("Test of prohibited ASCII character U+0020", " ", "", Profile.NODE_PREP, true, true),
	  new Check("Test of NFKC U+00A0 and prohibited character U+0020", "\u00a0", "", Profile.NODE_PREP, true, true),
	  new Check("Case map + normalization", "\u00b5", "\u03bc"),
	  new Check("NFKC test", "\u00aa", "a"),
	  new Check("nameprep, exposed a bug in libstringprep 0.0.5", "\u00aa\n", "a\n"),
	  new Check("unassigned code point U+0221", "\u0221", "\u0221"),
	  new Check("Unassigned code point U+0221", "\u0221", "", Profile.NAME_PREP, false, true),
	  new Check("Unassigned code point U+0236", "\u0236", "\u0236"),
	  new Check("unassigned code point U+0236", "\u0236", "", Profile.NAME_PREP, false, true),
	  new Check("bidi both RandALCat and LCat  U+0627 U+00AA U+0628", "\u0627\u00aa\u0628", "", Profile.NAME_PREP, true, true),
	  new Check("XMPP node profile prohibited output", "foo@bar", "", Profile.NODE_PREP, true, true),
	  new Check("XMPP resource profile on same string should work though", "foo@bar", "foo@bar", Profile.RESOURCE_PREP, true, false)

  };

  @Test
  public void testStringprep() {
    int i = 0;
    for (final Check check : checks) {
      try {
	final String out = check.profile.prep(check.in, check.allowUnassigned);
	if (check.expectException) {
	  Assert.fail("Unexpectedly got no exception at idx=" + i + ", check: " + check);
	}
	Assert.assertEquals("Check output mismatch: " + check, check.out, out);
      } catch (StringprepException e) {
	if (!check.expectException) {
	  e.printStackTrace();
	  Assert.fail("Unexpectedly got exception at idx=" + i + ", check: " + check);
	}
      } catch (RuntimeException ex) {
	ex.printStackTrace();
	Assert.fail("Oops, RuntimeException at idx=" + i + " testing " + check);
      }
      i++;
    }
  }
}

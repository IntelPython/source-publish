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

package gnu.inet.encoding.caliper;

import com.google.caliper.Runner;
import com.google.caliper.SimpleBenchmark;
import com.google.common.collect.ObjectArrays;
import gnu.inet.encoding.Stringprep;
import gnu.inet.encoding.StringprepException;
import org.junit.Test;
import org.junit.experimental.categories.Category;

@SuppressWarnings("UnusedDeclaration")
public class CaliperStringprep extends SimpleBenchmark
{

  public CaliperStringprep()
  {
  }

  public static void main(final String... args) {
    // Caliper:
    CaliperStringprep benchmark = new CaliperStringprep();
    benchmark.runCaliper();

    // Plain run, use with profiling
    // 100K -> 10s normal run
    // 1K -> minute(s)? with hprof times
/*
    final int reps = 1000;
    try {
      benchmark.timeNodePrep3x(reps);
      benchmark.timeNamePrep3x(reps);
      benchmark.timeResourcePrep3x(reps);
      benchmark.timeXMPPStringpreps3x(reps);
    } catch (StringprepException ex) {
      throw new IllegalStateException(ex);
    }
*/
  }

  /**
   * This test case is just a means of allowing to start caliper tests
   * automatically from a build.
   *
   * In order to make nice graphs of performance changes over time,
   * you can use jenkins/hudson together with caliper-ci, see
   * Docs: https://code.google.com/p/caliper-ci/
   * Source: https://github.com/jenkinsci/caliper-ci-plugin
   *
   * Create a jenkins project using maven to build this software.
   * Use these as maven goals: "-P caliper -U clean verify".
   * Set "POM" (hidden behind Advanced button) to "java/pom.xml"
   * Add the "Publish Caliper microbenchmark results" post-build action.
   * In the caliper-ci post-build action, set
   * "JSON result files" to "java/*.caliper.json".
   */
  @Test
  @Category(CaliperStringprep.class)
  public void runCaliper() {
    new Runner().run(ObjectArrays.concat(
	    new String[] {"--saveResults", "CaliperStringprep.caliper.json",
			  "-JBiasedLocking=-XX:BiasedLockingStartupDelay=0",
			  "-JServer=-server",
			  "-JAggressiveOpts=-XX:+AggressiveOpts"},
	    CaliperStringprep.class.getName()));
  }

  public int timeNodePrep3x(final int reps) throws StringprepException
  {
    int dummy = 0;
    for (int i = 0; i < reps; i++) {
      final String out = Stringprep.nodeprep("XmPpUserName");
      final String out2 = Stringprep.nodeprep("xmppusername");
      final String out3 = Stringprep.nodeprep("xmppusername\u1fb7\u200b\u1f56\u00df");
      dummy += out.length() + out2.length() + out3.length();
    }
    return dummy;
  }

  public int timeNamePrep3x(final int reps) throws StringprepException
  {
    int dummy = 0;
    for (int i = 0; i < reps; i++) {
      final String out = Stringprep.nameprep("domainName.com");
      final String out2 = Stringprep.nameprep("domainname.com");
      final String out3 = Stringprep.nameprep("a" + "\u1fb7\u200b\u1f56\u00df.com");
      dummy += out.length() + out2.length() + out3.length();
    }
    return dummy;
  }
  public int timeResourcePrep3x(final int reps) throws StringprepException
  {
    int dummy = 0;
    for (int i = 0; i < reps; i++) {
      final String out = Stringprep.resourceprep("Client-12345");
      final String out2 = Stringprep.resourceprep("res");
      final String out3 = Stringprep.resourceprep("res\u1fb7\u200b\u1f56\u00df");
      dummy += out.length() + out2.length() + out3.length();
    }
    return dummy;
  }

  public int timeXMPPStringpreps3x(final int reps) throws StringprepException
  {
    int dummy = 0;
    for (int i = 0; i < reps; i++) {
      final String outA1 = Stringprep.nodeprep("XmPpUserName");
      final String outA2 = Stringprep.nameprep("domainName.com");
      final String outA3 = Stringprep.resourceprep("Client-12345");

      final String outB1 = Stringprep.nodeprep("xmppusername");
      final String outB2 = Stringprep.nameprep("domainname.com");
      final String outB3 = Stringprep.resourceprep("res");

      // difficult to optimize away unusual characters deep inside lookup-tables
      final String outC1 = Stringprep.nodeprep("xmppusername\u1fb7\u200b\u1f56\u00df");
      final String outC2 = Stringprep.nameprep("a" + "\u1fb7\u200b\u1f56\u00df.com");
      final String outC3 = Stringprep.resourceprep("res\u1fb7\u200b\u1f56\u00df");

      dummy += outA1.length() + outB2.length() + outC3.length();
    }
    return dummy;
  }

  /**
   * Easy to optimize input but still common for XMPP.
   */
  public int timeXMPPSimpleStringprep(final int reps) throws StringprepException
  {
    int dummy = 0;
    for (int i = 0; i < reps; i++) {
      final String out1 = Stringprep.nodeprep("myusername5");
      final String out2 = Stringprep.nameprep("domainname.com");
      final String out3 = Stringprep.resourceprep("Resource-1234");

      dummy += out1.length() + out2.length() + out3.length();
    }
    return dummy;
  }

}

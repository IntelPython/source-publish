/* tst_toascii64oob.c --- Regression tests for stack OOB in idna_to_ascii().
 * Copyright (C) 2002-2021 Simon Josefsson
 *
 * This file is part of GNU Libidn.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <idna.h>
#include <idn-free.h>

#include "utils.h"

/* Reported by Hanno Böck in
   https://lists.gnu.org/archive/html/help-libidn/2015-07/msg00016.html */

/* This test requires you to build with CFLAGS="-fsanitize=address"
   and disable valgrind since asan and valgrind conflict.  Thus
   normally a bit uneffective, but may be useful to have around.

   make
   make
   make clean
   make CFLAGS="-fsanitize=address"
   make CFLAGS="-fsanitize=address" check VALGRIND=

   Revert patch in URL above to trigger this self test.
 */

void
doit (void)
{
  const char *in = "00000000000000000000000000000000000000000000000000"
    "00000000000000";
  char *output;
  uint32_t *tmp;
  int rc;

  tmp = stringprep_utf8_to_ucs4 (in, -1, NULL);
  if (!tmp)
    fail ("stringprep_utf8_to_ucs4 failed");

  rc = idna_to_ascii_4z (tmp, &output, 0);
  free (tmp);
  if (rc != IDNA_INVALID_LENGTH)
    fail ("idna_to_ascii_4z: %d", rc);
}

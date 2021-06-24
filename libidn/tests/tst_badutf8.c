/* tst_badutf8.c --- Self tests for malformed UTF-8 regressions.
 * Copyright (C) 2015-2021 Simon Josefsson
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

void
doit (void)
{
  char *badutf8 = strdup ("\x7e\x64\x61\x72\x10\x2f\x2f\xf9\x2b\x71"
			  "\x60\x79\x7b\x2e\x63\x75\x2b\x61\x65\x72"
			  "\x75\x65\x56\x66\x7f\x62\xc5\x76\xe5\x00");
  char *s = NULL;
  int rc;

  rc = idna_to_ascii_8z (badutf8, &s, 0);
  free (badutf8);
  if (rc != IDNA_ICONV_ERROR)
    fail ("rc %d\n", rc);

  idn_free (s);
}

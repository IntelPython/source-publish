/* tst_utf8crash.c --- Self tests for malformed UTF-8 regressions.
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

/* Based on report from Adam Sampson:
   https://lists.gnu.org/archive/html/help-libidn/2015-07/msg00026.html */

void
doit (void)
{
  const char input[] = "\200bad.com";
  char *output;
  int rc;

  rc = idna_to_unicode_8z8z (input, &output, 0);
  if (rc != IDNA_ICONV_ERROR)
    fail ("rc %d\n", rc);
}

/* tst_badutf8nfkc.c --- Self tests for malformed UTF-8 NFKC input.
 * Copyright (C) 2016-2021 Simon Josefsson
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

#include <string.h>
#include <stdlib.h>

#include <stringprep.h>

#include "utils.h"

void
doit (void)
{
  char *badutf8 = strdup ("\xe4");
  char *s = NULL;

  s = stringprep_utf8_nfkc_normalize (badutf8, -1);
  free (s);
  free (badutf8);
}

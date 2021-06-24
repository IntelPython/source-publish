## Process this file with automake to produce Makefile.in
# Copyright (C) 2002-2021 Simon Josefsson
#
# This file is part of GNU Libidn.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

SUBDIRS = gl lib/gl lib po src
if ENABLE_DOC
SUBDIRS += doc
endif
SUBDIRS += tests fuzz examples
if JAVA
SUBDIRS += java
endif
if CSHARP
SUBDIRS += csharp
endif

EXTRA_DIST = cfg.mk maint.mk
EXTRA_DIST += COPYING.LESSERv2 COPYING.LESSERv3 COPYINGv2 COPYINGv3

ACLOCAL_AMFLAGS = -I lib/m4 -I gl/m4 -I lib/gl/m4 -I m4
DISTCHECK_CONFIGURE_FLAGS = --enable-doc --enable-gtk-doc --disable-valgrind-tests

EXTRA_DIST += FAQ libc/README libc/getaddrinfo-idn.txt libc/example.c	\
	contrib/README contrib/idn-python/README			\
	contrib/idn-python/Makefile contrib/idn-python/idn.c		\
	contrib/idn-python/test.py contrib/web/idn.php			\
	contrib/java/README contrib/java/autogen.sh			\
	contrib/java/configure.ac contrib/java/Makefile.am		\
	contrib/java/ExampleIDNA.java contrib/java/IDNA.java		\
	contrib/java/IDNA.c contrib/doxygen/Doxyfile.in			\
	contrib/doxygen/Doxyfile.orig contrib/doxygen/gdoc2doxygen

# Visual Studio project files.
EXTRA_DIST += windows/libidn.sln windows/libidn.vcproj			\
	windows/include/unistd.h windows/include/idn-int.h		\
	windows/include/stdbool.h windows/include/ac-stdint.h		\
	windows/include/config.h windows/libidn4win.mk

EXTRA_DIST += HACKING

# git-version-gen
EXTRA_DIST += $(top_srcdir)/.version
BUILT_SOURCES = $(top_srcdir)/.version
$(top_srcdir)/.version:
	echo $(VERSION) > $@-t && mv $@-t $@
dist-hook: gen-ChangeLog
	echo $(VERSION) > $(distdir)/.tarball-version

.PHONY: gen-ChangeLog
gen-ChangeLog:
	$(AM_V_GEN)if test -d .git; then				\
		$(top_srcdir)/build-aux/gitlog-to-changelog >		\
			$(distdir)/cl-t &&				\
		{ rm -f $(distdir)/ChangeLog &&				\
		  mv $(distdir)/cl-t $(distdir)/ChangeLog; }		\
	fi

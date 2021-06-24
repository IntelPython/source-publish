## Process this file with automake to produce Makefile.in
# Copyright (C) 2002-2021 Simon Josefsson.
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

SUBDIRS = specifications tld java cyclo
if ENABLE_GTK_DOC
SUBDIRS += . reference
endif

EXTRA_DIST = gdoc components.fig

info_TEXINFOS = libidn.texi
libidn_TEXINFOS = fdl-1.3.texi idn--help.texi
libidn_TEXINFOS += texinfo.css example.txt example2.txt example3.txt example4.txt example5.txt
libidn_TEXINFOS += $(gdoc_TEXINFOS)
libidn_TEXINFOS += libidn-components.eps libidn-components.png	\
			libidn-components.pdf

AM_MAKEINFOHTMLFLAGS = $(AM_MAKEINFOFLAGS) \
	--no-split --css-include=texinfo.css

imagesdir = $(infodir)
images_DATA = libidn-components.png

libidn-components.eps: components.fig
	fig2dev -L eps $< $@

libidn-components.png: components.fig
	fig2dev -L png $< $@

libidn-components.pdf: components.fig
	fig2dev -L pdf $< $@

idn--help.texi: $(top_srcdir)/src/idn.c
	$(top_builddir)/src/idn$(EXEEXT) --help | $(GREP) '^ \+-' > tmp
	mv tmp idn--help.texi

example.txt: $(top_srcdir)/examples/example.c
	sed -e '/* example/,/^$$/d' $< > $@.tmp && mv $@.tmp $@

example2.txt: $(top_srcdir)/examples/example2.c
	sed -e '/* example/,/^$$/d' $< > $@.tmp && mv $@.tmp $@

example3.txt: $(top_srcdir)/examples/example3.c
	sed -e '/* example/,/^$$/d' $< > $@.tmp && mv $@.tmp $@

example4.txt: $(top_srcdir)/examples/example4.c
	sed -e '/* example/,/^$$/d' $< > $@.tmp && mv $@.tmp $@

example5.txt: $(top_srcdir)/examples/example5.c
	sed -e '/* example/,/^$$/d' $< > $@.tmp && mv $@.tmp $@

# Man pages.

dist_man_MANS = idn.1 $(gdoc_MANS)
MAINTAINERCLEANFILES = $(dist_man_MANS)

idn.1: $(top_srcdir)/src/idn.c $(top_srcdir)/src/idn.ggo \
		$(top_srcdir)/configure.ac
	$(HELP2MAN) \
		--name="Internationalized Domain Names command line tool" \
		--output=$@ $(top_builddir)/src/idn$(EXEEXT)

# GDOC

GDOC_BIN = $(srcdir)/gdoc
GDOC_SRC = $(top_srcdir)/lib/idna.c $(top_srcdir)/lib/nfkc.c	\
	$(top_srcdir)/lib/pr29.c $(top_srcdir)/lib/punycode.c	\
	$(top_srcdir)/lib/stringprep.c $(top_srcdir)/lib/tld.c	\
	$(top_srcdir)/lib/toutf8.c $(top_srcdir)/lib/version.c \
	$(top_srcdir)/lib/idn-free.c \
	$(top_srcdir)/lib/strerror-idna.c $(top_srcdir)/lib/strerror-pr29.c \
	$(top_srcdir)/lib/strerror-punycode.c \
	$(top_srcdir)/lib/strerror-stringprep.c \
	$(top_srcdir)/lib/strerror-tld.c
GDOC_TEXI_PREFIX = texi/
GDOC_MAN_PREFIX = man/
GDOC_MAN_EXTRA_ARGS = -module $(PACKAGE) -sourceversion $(VERSION) \
	-bugsto $(PACKAGE_BUGREPORT) -pkg-name "$(PACKAGE_NAME)" \
	-includefuncprefix -seeinfo $(PACKAGE) \
	-copyright "2002-2021 Simon Josefsson" \
	-verbatimcopying
include $(srcdir)/gdoc.mk

BUILT_SOURCES += example.txt example2.txt example3.txt example4.txt example5.txt

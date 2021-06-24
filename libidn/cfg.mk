# Copyright (C) 2006-2021 Simon Josefsson
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

manual_title = Internationalized Domain Names Library

old_NEWS_hash = b9048a5d608511b0dc69c0799ce3c52b

bootstrap-tools = gnulib,autoconf,automake,libtoolize,make,makeinfo,help2man,gperf,gengetopt,gtkdocize,tar,gzip

local-checks-to-skip = sc_prohibit_strcmp sc_prohibit_have_config_h	\
	sc_require_config_h sc_require_config_h_first			\
	sc_prohibit_HAVE_MBRTOWC sc_program_name sc_trailing_blank	\
	sc_GPL_version sc_immutable_NEWS				\
	sc_prohibit_gnu_make_extensions sc_codespell
VC_LIST_ALWAYS_EXCLUDE_REGEX = \
	^(GNUmakefile|maint.mk|gtk-doc.make|m4/pkg.m4|m4/libtool.m4|doc/specifications|contrib/doxygen/Doxyfile|doc/fdl-1.3.texi|csharp/libidn.*suo|(lib/)?(gl|gltests|build-aux)/)

# Explicit syntax-check exceptions.
exclude_file_name_regexp--sc_bindtextdomain = ^examples/|libc/|tests/|fuzz/
exclude_file_name_regexp--sc_prohibit_atoi_atof = ^examples/example2.c$$
exclude_file_name_regexp--sc_copyright_check = ^doc/libidn.texi
exclude_file_name_regexp--sc_useless_cpp_parens = ^lib/nfkc.c$$
exclude_file_name_regexp--sc_prohibit_strncpy = ^src/idn.c$$
exclude_file_name_regexp--sc_prohibit_empty_lines_at_EOF = ^fuzz/libidn_.*fuzzer.(in|repro)/.*$$
exclude_file_name_regexp--sc_two_space_separator_in_usage = ^cfg.mk$$
exclude_file_name_regexp--sc_prohibit_always_true_header_tests = ^lib/toutf8.c$$

INDENT_SOURCES = -ppi 1 `find . -name '*.[ch]'|grep -v -e ^./gl/ -e ^./fuzz/ -e ^./gltests/ -e ^./lib/gl/ -e ^./lib/gltests/ -e '^./lib/\(gunibreak.h\|gunicomp.h\|gunidecomp.h\|rfc3454.c\|rfc3454.h\|tlds.c\)$$'`

aximport:
	for f in m4/ax_*.m4; do \
		wget -O $$f "https://git.savannah.gnu.org/gitweb/?p=autoconf-archive.git;a=blob_plain;f=$$f"; \
	done

review-diff:
	git diff `git describe --abbrev=0`.. \
	| grep -v -e ^index -e '^diff --git' \
	| filterdiff -p 1 -x 'build-aux/*' -x 'gl/*' -x 'gltests/*' -x 'lib/gl/*' -x 'lib/gltests/*' -x 'po/*' -x 'maint.mk' -x '.gitignore' -x '.x-sc*' -x ChangeLog -x GNUmakefile \
	| less

my-update-copyright:
	make update-copyright update-copyright-env='UPDATE_COPYRIGHT_USE_INTERVALS=1'
	make update-copyright update-copyright-env='UPDATE_COPYRIGHT_HOLDER="Simon Josefsson" UPDATE_COPYRIGHT_USE_INTERVALS=1'
	perl -pi -e "s/2002-20.. Simon Josefsson/2002-`(date +%Y)` Simon Josefsson/" doc/Makefile.am src/idn.c

sc_codespell:
	@if `which codespell > /dev/null`; then \
		codespell -L tim,ede,wich `git ls-files|egrep -v '^doc/specifications/.*|doc/gdoc|fuzz/libidn_(stringprep|toascii|tounicode)_fuzzer.in/.*$$'`; \
	fi

# Fuzz

COVERAGE_CCOPTS ?= "-g --coverage"
COVERAGE_OUT ?= doc/coverage

fuzz-coverage:
	$(MAKE) $(AM_MAKEFLAGS) clean
	lcov --directory . --zerocounters
	$(MAKE) $(AM_MAKEFLAGS) CFLAGS=$(COVERAGE_CCOPTS) CXXFLAGS=$(COVERAGE_CCOPTS)
	$(MAKE) -C fuzz $(AM_MAKEFLAGS) CFLAGS=$(COVERAGE_CCOPTS) CXXFLAGS=$(COVERAGE_CCOPTS) check
	mkdir -p $(COVERAGE_OUT)
	lcov --directory . --output-file $(COVERAGE_OUT)/$(PACKAGE).info --capture
	lcov --remove $(COVERAGE_OUT)/$(PACKAGE).info '*/lib/gl/*' -o $(COVERAGE_OUT)/$(PACKAGE).info
	genhtml --output-directory $(COVERAGE_OUT) \
                $(COVERAGE_OUT)/$(PACKAGE).info \
                --highlight --frames --legend \
                --title "$(PACKAGE_NAME)"
	@echo
	@echo "View fuzz coverage report with 'xdg-open $(COVERAGE_OUT)/index.html'"

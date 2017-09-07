bin_PROGRAMS = jff-a2c jff-algol
jff_a2c_SOURCES = frontend.c frontend.h
jff_algol_SOURCES = jff-algol.c frontend.h
lib_LIBRARIES = lib_jff.a
lib_jff_a_SOURCES = runtime.c jff_header.h
pkgdata_DATA = operator prelude
EXTRA_DIST = doc examples operator prelude jff_header.template
include_HEADERS = jff_header.h
noinst_PROGRAMS=gc
gc_SOURCES=gc.c
BUILT_SOURCES=jff_header.h

jff_header.h: jff_header.template 
	cat jff_header.template > jff_header.h
	./gc >> jff_header.h

OPERATOR	= $(datadir)/jff-a2c/operator
PRELUDE		= $(datadir)/jff-a2c/prelude
HEADER		= $(includedir)/jff_header.h
FRONTEND	= $(bindir)/jff-a2c
ALGOL		= $(bindir)/jff-algol
RUNTIME		= $(libdir)/lib_jff.a
INDENT		= /usr/bin/indent
AM_CFLAGS = -O3 -g -DOPERATOR=\"$(OPERATOR)\" -DPRELUDE=\"$(PRELUDE)\" -DRUNTIME=\"$(RUNTIME)\" -DHEADER=\"$(HEADER)\" -DINDENT=\"$(INDENT)\" -DCCOMPILER=\"$(CC)\" -DACOMPILER=\"$(FRONTEND)\"


bin_PROGRAMS = jff-a2c jff-algol
jff_a2c_SOURCES = frontend.c frontend.h
jff_algol_SOURCES = jff-algol.c frontend.h
lib_LIBRARIES = lib_jff.a
lib_jff_a_SOURCES = runtime.c jff_header.h
pkgdata_DATA = operator_e operator_f prelude_e prelude_f
EXTRA_DIST = doc examples operator_e operator_f prelude_e prelude_f jff_header.template
include_HEADERS = jff_header.h
#BUILT_SOURCES=jff_header.h

OPERATOR_E	= $(datadir)/jff-a2c/operator_e
OPERATOR_F	= $(datadir)/jff-a2c/operator_f
PRELUDE_E	= $(datadir)/jff-a2c/prelude_e
PRELUDE_F	= $(datadir)/jff-a2c/prelude_f
HEADER		= $(includedir)/jff_header.h
FRONTEND	= $(bindir)/jff-a2c
ALGOL		= $(bindir)/jff-algol
RUNTIME		= $(libdir)/lib_jff.a
INDENT		= /usr/bin/indent
AM_CFLAGS = -O3 -g -DOPERATOR_E=\"$(OPERATOR_E)\" -DOPERATOR_F=\"$(OPERATOR_F)\" -DPRELUDE_E=\"$(PRELUDE_E)\" -DPRELUDE_F=\"$(PRELUDE_F)\"  -DRUNTIME=\"$(RUNTIME)\" -DHEADER=\"$(HEADER)\" -DINDENT=\"$(INDENT)\" -DCCOMPILER=\"$(CC)\" -DACOMPILER=\"$(FRONTEND)\"


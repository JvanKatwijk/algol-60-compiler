
jff-algol: A simple ALGOL 60 to C translator

==============================================================

In 2002 and 2003 I wrote, as a hobby project, a simple Algol 60 to C
translator. The rationale was to show the semantics of (some of
the) Algol 60 constructs in terms of C expressions. 
The resulting compiler compiled Algol 60, using C as intermediate language
and - if the compilation succeeds - generates an executable. For those interested:
it had no problems with "man or boy".

Since it was a fun project, the compiler was named "jff-algol", i.e.
just for fun.

Recently, by cleaning up some old disks, I found the sources of the compiler
and - with a very few modifications - the software just ran.

The directory contains an automake/configure combination to create
two executables and a small library

================================================================

jff-algol
----------------------------------------------------------------

The program jff-algol is the driver program. The setup is that calling

	jff-algol filename.alg

will compile the Algol source to c code, generate a (more or less) structured
C file and compile and link the C file, resulting in an executable with the
same name as the source program without the extension. The documentation contains
a manual with a fairly detailed description of the resulting C code of a dozen
example programs.

Command line options to specify components used, build and operating
instructions are also described in the manual.

====================================================================

frontend.c
--------------------------------------------------------------------

The file frontend.c is the real Algol 60 to C translator. As mentioned
in the manual, the original idea was - whenever I would have some time -
to recode the frontend into Algol 60 itself but that (almost obviously)
never happened.
However, due to that (vague) intention, the implementation refrained from
using records. 
in the C implementation, all structures (treenodes etc)  are implemented as
segments of homogeneous arrays.

The file frontend.c is translated into an executable "jff-a2c".

======================================================================

runtime.c
----------------------------------------------------------------------

All runtime support is implemented in the file runtime.c. In the
make and installation process this file is compiled and converted
into a library lib-jff.a

=======================================================================

jff_header.h
-----------------------------------------------------------------------

The specification of the runtime support is given in jff_header.h

=======================================================================

operator
-----------------------------------------------------------------------

One of the objectives was to have a pretty loose coupling of the compile
with the definition of the operators. On the start of a compilation,
the compiler will read the file "operator". The file contains
for each operator a few lines, specifying the operator and presenting
a pattern for the compilation, e.g.

       [ ^ 9 ((integer integer integer "(__ipow(%L,%R))")
                 (real integer real " __npow (%L, %R)")
                 (integer real real "__fpow ((double)%L, %R)")
                 (real real real "__fpow (%L, %R)")) ]

========================================================================

prelude
------------------------------------------------------------------------

The prelude file contains the specifications of the predefined functions.
The file is readin at the start of the compilation. In the prelude
file it is allowed to specify a function as "c function", e.g.

	real procedure read_real (channel);
	value channel; integer channel; c_procedure;

	procedure outinteger (channel, v);
	value channel, v; integer channel, v; c_procedure;

=================================================================

Installation
------------------------------------------------------------------

The installation procedure, using auto tools, is a little shaky but
does run and was tested on a Linux environment and an MSYS-2/mingw64
environment.

I am using the gcc toolchain, both with Linux and MSYS-2/Mingw64 Windows.

The installation procedure will compile jff-algol.c, jff-a2c.c and run-time.c.
For compilation of run-time.c the include file jff_header.h is needed.

Furthermore, under Linux the installation process will (try to) install
the executables jff-algol and jff-a2c in the directory "/usr/local/bin",
create a library lib-jff.a from the compiled runtime.c file and install it
in the directory "/usr/local/lib" and the files jff\_header.h, operator
and prelude in the directory "/usr/local/share/jff-a2c".
Under MSYS-2/Mingw64, the installation process will (try to) install
the executables jff-algol and jff-a2c in the directory /mingw64/bin,
the library lib-jff.a in /mingw64/lib, and the files operator and prelude
in /mingw64/share/jff-a2c.

=========================================================================

Copyright
-------------------------------------------------------------------------
	Copyright (C)  2016, 2017
	Jan van Katwijk (J.vanKatwijk@gmail.com)
	Lazy Chair Programming
	
	

The Algol 60 software is made available under the GPL-2.0.
All SDR-J software, among which jff-algol is one - is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    GNU General Public License for more details.



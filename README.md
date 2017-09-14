
jff-algol: A simple ALGOL 60 to C translator

==============================================================

In the period 2002, 2003 I wrote in spare time, as a hobby project,
a simple Algol 60 to C translator. The rationale was to show the
semantics of (some of the) Algol 60 constructs in terms of C expressions. 

The objective was therefore to translate Algol 60 constructs into
C equivalents  rather than to some "intermediate stack machine".

As an example (see example 1 in the example directory), the function
	
	integer procedure fac (n); value n; integer n;
	   fac := if n < 1 then 1 else n * fac (n - 1);

is translated into


	int _fac_42 (int n) {
	int __res_val;
	   __res_val = ((n) < (1)) ? 1 : (n) * (_fac_42 ((n) - (1)));
	return __res_val;
	}

The resulting compiler compiled Algol 60, using C as intermediate language
and - if the mapping to C succeeded - is invoked a C compiler and
generated an executable. 
For those interested: it was certainly capable of handling things like the
"man or boy" example (although that takes more lines in C than the fac example
above).

Since it was a fun project, the compiler was named "jff-algol", i.e.
Just-For-Fun-Algol.

Recently, when cleaning up some old archives on disks, I found 
the sources of the compiler and - with a very few modifications -
the software compiled properly and just ran.

The directory contains an automake/configure combination to create
two executables and a small library

================================================================

jff-algol
----------------------------------------------------------------

The program jff-algol is the driver program. The setup is that calling

	jff-algol [options] filename.alg filename-2.alg ... filename-n.alg

will compile the Algol sources to C code by generating for each of the Algol 
sources a (more or less) structured C file and include file, and compile and
link the C file, resulting in an executable (with the same name as the source
program without the extension). The documentation contains
a manual with a fairly detailed description of the resulting C code of a dozen
example programs.

The file jff-algol.c contains the source for this program.

Command line options to specify components used, build and operating
instructions are also described in the manual.

====================================================================

frontend.c
--------------------------------------------------------------------

The file frontend.c contains the source of the real Algol 60 to C translator.
As mentioned in the manual, the original idea was - whenever I would 
have some more free time - to recode the frontend into Algol 60 code 
itself but that (almost obviously) never happened.
However, due to that (vague) intention, the implementation refrained from
using records. 
In the C implementation, all structures (treenodes etc)  are implemented as
segments of homogeneous arrays (arrays of char *).

The file frontend.c is translated into an executable "jff-a2c". The jff-a2c
program can be used as a program on its own.

======================================================================

runtime.c
----------------------------------------------------------------------

All runtime support is implemented in the file runtime.c.
It contains the implementation of the (from a user's point of view invisible)
support functions, e.g. setting up an array, leaving a scope etc, the
implementation of some of the operators, and the implementation of the 
functions in the prelude.
In the installation process this file is compiled and the result converted
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

shows that the power operator is on priority level 9, and, depending on the
type of the operands, implemented as a call to a C function in the runtime
support system.

The file is read in at the start of the compilation.

========================================================================

prelude
------------------------------------------------------------------------

The prelude file contains the specifications of the predefined functions.
The file is readin at the start of the compilation. In the prelude
file it is allowed to specify a function as "c function", i.e., a 
procedure with as body the keyword c_procedure (or c_proc)

	procedure outreal    (channel, v); value channel, v;
	                                   integer channel; real v; c_procedure;

	procedure ininteger (channel, v); value channel; 
		                          integer channel, v; c_procedure;
	procedure inreal (channel, v); value channel;
	                               integer channel; real v; c_procedure;


=================================================================

Installation
------------------------------------------------------------------

The installation procedure, using auto tools, is a little shaky but
does run and was tested both in a Linux environment and a Windows 10
environment with MSYS-2/mingw64 installed.
Note that for the compiler to be a real compiler, it needs helpp
from a C compiler to translate the C output of the jff-a2c translator
into an executable.

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



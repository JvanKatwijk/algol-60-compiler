#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: example26.alg		*/
/* Compiled at Wed Sep 13 13:03:25 2017		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	void newline (int); /* newline declared at line 24*/
extern	void outreal (int,double); /* outreal declared at line 43*/
extern	void _S_41 (char	*,double (*)(char *, double), double(*)(char *, int)); /* S declared at line 4*/
struct ___S_41_rec {
char *__l_field;
char	*Lx;
 double (*Ax)(char *, double);
double (*Vx)(char *, int);
};
extern	double _r_43 (); /* r declared at line 5*/
extern double D_r_43 (char *, int, ...);	 /* r declared at line 5*/
extern double _x_40; /* x declared at line 10*/

//	specification for thunk
extern double A_jff_0A (char *, double);
extern double _jff_0A (char *, int);

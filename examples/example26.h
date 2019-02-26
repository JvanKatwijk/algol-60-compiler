#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.2		*/
/* input file: example26.alg		*/
/* Compiled at Sun Jan 13 17:47:57 2019		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	double fabs (double); /* fabs declared at line 2*/
extern	void newline (int); /* newline declared at line 25*/
extern	void outreal (int,double); /* outreal declared at line 44*/
extern	void _S_44 (char	*,double (*)(char *, double), double(*)(char *, int)); /* S declared at line 4*/
struct ___S_44_rec {
char *__l_field;
char	*Lx;
 double (*Ax)(char *, double);
double (*Vx)(char *, int);
};
extern	double _r_46 (); /* r declared at line 5*/
extern double D_r_46 (char *, int, ...);	 /* r declared at line 5*/
extern double _x_43; /* x declared at line 10*/

//	specification for thunk
extern double A_jff_0A (char *, double);
extern double _jff_0A (char *, int);

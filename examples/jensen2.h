#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.4		*/
/* input file: jensen2.alg		*/
/* Compiled at Thu Apr 29 21:36:44 2021		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	double fabs (double); /* fabs declared at line 2*/
extern	void outstring (int,char	*); /* outstring declared at line 28*/
extern	void outreal (int,double); /* outreal declared at line 45*/
extern	void _outer_46 (); /* outer declared at line 2*/
struct ___outer_46_rec {
char *__l_field;
int __dv0 [2 * 1 + DOPE_BASE];
double	*_a_48; /* a declared at line 4*/
double _t_48; /* t declared at line 5*/
int _i_48; /* i declared at line 6*/
};
extern	double _jensen1_49 (char	*,int (*)(char *, int), int(*)(char *, int),char	*,double (*)(char *, double), double(*)(char *, int)); /* jensen1 declared at line 7*/
struct ___jensen1_49_rec {
char *__l_field;
double __res_val;
char	*Li_;
 int (*Ai_)(char *, int);
int (*Vi_)(char *, int);
char	*La_;
 double (*Aa_)(char *, double);
double (*Va_)(char *, int);
double _s_51; /* s declared at line 10*/
};

//	specification for thunk
extern int A_jff_0A (char *, int);
extern int _jff_0A (char *, int);

//	specification for thunk
extern double A_jff_1A (char *, double);
extern double _jff_1A (char *, int);

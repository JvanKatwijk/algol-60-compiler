#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.4		*/
/* input file: jensen1.alg		*/
/* Compiled at Mon Apr 26 18:31:52 2021		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	double fabs (double); /* fabs declared at line 2*/
extern	void outstring (int,char	*); /* outstring declared at line 28*/
extern	void outreal (int,double); /* outreal declared at line 45*/
extern double _a_45 []; // 
extern double _t_45; /* t declared at line 3*/
extern int _i_45; /* i declared at line 4*/
extern	double _jensen1_46 (char	*,int (*)(char *, int), int(*)(char *, int),char	*,double (*)(char *, double), double(*)(char *, int)); /* jensen1 declared at line 5*/
struct ___jensen1_46_rec {
char *__l_field;
double __res_val;
char	*Li_;
 int (*Ai_)(char *, int);
int (*Vi_)(char *, int);
char	*La_;
 double (*Aa_)(char *, double);
double (*Va_)(char *, int);
double _s_48; /* s declared at line 8*/
};

//	specification for thunk
extern int A_jff_0A (char *, int);
extern int _jff_0A (char *, int);

//	specification for thunk
extern double A_jff_1A (char *, double);
extern double _jff_1A (char *, int);

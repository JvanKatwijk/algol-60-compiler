#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.4		*/
/* input file: jensen3.alg		*/
/* Compiled at Mon Apr 26 18:07:23 2021		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	double fabs (double); /* fabs declared at line 2*/
extern	double random (); /* random declared at line 13*/
extern	void outstring (int,char	*); /* outstring declared at line 28*/
extern	void outreal (int,double); /* outreal declared at line 45*/
extern	void inreal (int,char	*,double (*)(char *, double), double(*)(char *, int)); /* inreal declared at line 48*/
extern	int r_lwb (int *, double	*,int); /* r_lwb declared at line 57*/
extern	int r_upb (int *, double	*,int); /* r_upb declared at line 60*/
extern	int _RAND_46 (); /* RAND declared at line 7*/
struct ___RAND_46_rec {
char *__l_field;
int __res_val;
};
extern	double _SUM_48 (int,int,char	*,int (*)(char *, int), int(*)(char *, int),char	*,double (*)(char *, double), double(*)(char *, int)); /* SUM declared at line 8*/
struct ___SUM_48_rec {
char *__l_field;
double __res_val;
int LO_;
int HI_;
char	*LINDEX_;
 int (*AINDEX_)(char *, int);
int (*VINDEX_)(char *, int);
char	*LEXPR_;
 double (*AEXPR_)(char *, double);
double (*VEXPR_)(char *, int);
double _ACCUM_50; /* ACCUM declared at line 12*/
};
extern int _I_52; /* I declared at line 25*/

//	specification for thunk
extern int A_jff_0A (char *, int);
extern int _jff_0A (char *, int);

//	specification for thunk
extern int A_jff_1A (char *, int);
extern int _jff_1A (char *, int);
extern int _I_53; /* I declared at line 32*/

//	specification for thunk
extern int A_jff_2A (char *, int);
extern int _jff_2A (char *, int);

//	specification for thunk
extern int A_jff_3A (char *, int);
extern int _jff_3A (char *, int);
extern	int __dv0 [];
extern double _DATA_54 []; // 
extern int _I_54; /* I declared at line 39*/
extern double _MEAN_54; /* MEAN declared at line 40*/
extern double _SUMD_54; /* SUMD declared at line 40*/
extern double _SUMSQ_54; /* SUMSQ declared at line 40*/

//	specification for thunk
extern double A_jff_4A (char *, double);
extern double _jff_4A (char *, int);

//	specification for thunk
extern int A_jff_5A (char *, int);
extern int _jff_5A (char *, int);

//	specification for thunk
extern double A_jff_6A (char *, double);
extern double _jff_6A (char *, int);

//	specification for thunk
extern int A_jff_7A (char *, int);
extern int _jff_7A (char *, int);

//	specification for thunk
extern double A_jff_8A (char *, double);
extern double _jff_8A (char *, int);

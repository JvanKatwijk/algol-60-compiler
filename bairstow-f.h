#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.4		*/
/* input file: bairstow-f.alg		*/
/* Compiled at Wed Sep 18 13:37:20 2019		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	double fabs (double); /* fabs declared at line 2*/
extern	double _ABS_4 (double); /* ABS declared at line 3*/
extern	int sign (double); /* sign declared at line 4*/
extern	int _SIGNE_7 (double); /* SIGNE declared at line 5*/
extern	double sqrt (double); /* sqrt declared at line 7*/
extern	double _RAC2_11 (double); /* RAC2 declared at line 8*/
extern	void outstring (int,char	*); /* outstring declared at line 30*/
extern	void outreal (int,double); /* outreal declared at line 47*/
extern	void _BAIRSTOW_42 (int,int *, double	*,char	*,double (*)(char *, double), double(*)(char *, int),char	*,double (*)(char *, double), double(*)(char *, int),char	*,double (*)(char *, double), double(*)(char *, int),char	*,double (*)(char *, double), double(*)(char *, int),char	*,int (*)(char *, int), int(*)(char *, int),int *, double	*,int *, double	*,char	*,jmp_buf * (*)(char *, jmp_buf *), jmp_buf *(*)(char *, int)); /* BAIRSTOW declared at line 2*/
struct ___BAIRSTOW_42_rec {
char *__l_field;
int N;
int	*DA ;
double	*A ;
char	*LS0;
 double (*AS0)(char *, double);
double (*VS0)(char *, int);
char	*LP0;
 double (*AP0)(char *, double);
double (*VP0)(char *, int);
char	*LEPS1;
 double (*AEPS1)(char *, double);
double (*VEPS1)(char *, int);
char	*LEPS2;
 double (*AEPS2)(char *, double);
double (*VEPS2)(char *, int);
char	*LMAXITER;
 int (*AMAXITER)(char *, int);
int (*VMAXITER)(char *, int);
int	*DX ;
double	*X ;
int	*DY ;
double	*Y ;
char	*LDIVERG;
 jmp_buf * (*ADIVERG)(char *, jmp_buf *);
jmp_buf * (*VDIVERG)(char *, int);
int __dv0 [2 * 1 + DOPE_BASE];
double	*_B_44; /* B declared at line 20*/
double	*_C_44; /* C declared at line 20*/
double _R_44; /* R declared at line 21*/
double _T1_44; /* T1 declared at line 21*/
double _Y1_44; /* Y1 declared at line 21*/
double _Y2_44; /* Y2 declared at line 21*/
double _S_44; /* S declared at line 21*/
double _P_44; /* P declared at line 21*/
double _S1_44; /* S1 declared at line 21*/
double _P1_44; /* P1 declared at line 21*/
double _DELTA_44; /* DELTA declared at line 21*/
double _DISCR_44; /* DISCR declared at line 21*/
double _S2_44; /* S2 declared at line 21*/
double _P2_44; /* P2 declared at line 21*/
double _X1_44; /* X1 declared at line 21*/
double _X2_44; /* X2 declared at line 21*/
int _I_44; /* I declared at line 23*/
int _K_44; /* K declared at line 23*/
int _NITER_44; /* NITER declared at line 23*/
};
extern int _I_48; /* I declared at line 101*/
extern int _N_48; /* N declared at line 101*/
extern int _MAXITER_48; /* MAXITER declared at line 101*/
extern double _S0_48; /* S0 declared at line 101*/
extern double _P0_48; /* P0 declared at line 101*/
extern double _EPS1_48; /* EPS1 declared at line 101*/
extern double _EPS2_48; /* EPS2 declared at line 101*/
extern	jmp_buf _DIVERG_49; /* DIVERG declared at line 123*/
extern	int __dv1 [];
extern double	*_X_49; /* X declared at line 107*/
extern double	*_Y_49; /* Y declared at line 107*/
extern	int __dv2 [];
extern double	*_A_49; /* A declared at line 107*/

//	specification for thunk
extern double A_jff_0A (char *, double);
extern double _jff_0A (char *, int);

//	specification for thunk
extern double A_jff_1A (char *, double);
extern double _jff_1A (char *, int);

//	specification for thunk
extern double A_jff_2A (char *, double);
extern double _jff_2A (char *, int);

//	specification for thunk
extern double A_jff_3A (char *, double);
extern double _jff_3A (char *, int);

//	specification for thunk
extern int A_jff_4A (char *, int);
extern int _jff_4A (char *, int);

//	specification for thunk
extern jmp_buf * A_jff_5A (char *, jmp_buf *);
extern jmp_buf * _jff_5A (char *, int);

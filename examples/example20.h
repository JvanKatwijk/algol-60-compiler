#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: example20.alg		*/
/* Compiled at Thu Sep  7 08:58:12 2017		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	double abs (double); /* abs declared at line 1*/
extern	double epsilon (); /* epsilon declared at line 11*/
extern	void fault (char	*,double); /* fault declared at line 15*/
extern	void space (int); /* space declared at line 22*/
extern	void newline (int); /* newline declared at line 24*/
extern	void outstring (int,char	*); /* outstring declared at line 26*/
extern	int outchar (int,char	*,int); /* outchar declared at line 34*/
extern	void outinteger (int,int); /* outinteger declared at line 40*/
extern	void outreal (int,double); /* outreal declared at line 43*/
extern	double _GPS_41 (char	*,double (*)(char *, double), double(*)(char *, int),char	*,double (*)(char *, double), double(*)(char *, int),char	*,double (*)(char *, double), double(*)(char *, int),char	*,double (*)(char *, double), double(*)(char *, int)); /* GPS declared at line 10*/
struct ___GPS_41_rec {
char *__l_field;
double __res_val;
char	*LI;
 double (*AI)(char *, double);
double (*VI)(char *, int);
char	*LN;
 double (*AN)(char *, double);
double (*VN)(char *, int);
char	*LZ;
 double (*AZ)(char *, double);
double (*VZ)(char *, int);
char	*LV;
 double (*AV)(char *, double);
double (*VV)(char *, int);
};
extern double _i_44; /* i declared at line 20*/
extern double _j_44; /* j declared at line 20*/
extern	int __dv0 [];
extern double	*_A_44; /* A declared at line 21*/

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
extern double A_jff_4A (char *, double);
extern double _jff_4A (char *, int);

//	specification for thunk
extern double A_jff_5A (char *, double);
extern double _jff_5A (char *, int);

//	specification for thunk
extern double A_jff_6A (char *, double);
extern double _jff_6A (char *, int);

//	specification for thunk
extern double A_jff_7A (char *, double);
extern double _jff_7A (char *, int);
extern	void _testmatr_46 (int,int *, double	*); /* testmatr declared at line 36*/
extern	void _invert_140_51 (int,double,char	*,jmp_buf * (*)(char *, jmp_buf *), jmp_buf *(*)(char *, int),int *, double	*); /* invert_140 declared at line 49*/
struct ___invert_140_51_rec {
char *__l_field;
int n;
double eps;
char	*Lout;
 jmp_buf * (*Aout)(char *, jmp_buf *);
jmp_buf * (*Vout)(char *, int);
int	*Da ;
double	*a ;
double _q_53; /* q declared at line 52*/
int _i_53; /* i declared at line 52*/
int _j_53; /* j declared at line 52*/
int _k_53; /* k declared at line 52*/
};
extern	void _print_matrix_58 (char	*,int,int *, double	*); /* print_matrix declared at line 82*/
extern int _n_45; /* n declared at line 101*/
extern	jmp_buf _sing_63; /* sing declared at line 115*/
extern	int __dv1 [];
extern double	*_A_63; /* A declared at line 106*/
extern double	*_B_63; /* B declared at line 106*/
extern double	*_C_63; /* C declared at line 106*/
extern int _i_63; /* i declared at line 106*/
extern int _j_63; /* j declared at line 106*/
extern int _k_63; /* k declared at line 106*/

//	specification for thunk
extern jmp_buf * A_jff_8A (char *, jmp_buf *);
extern jmp_buf * _jff_8A (char *, int);

//	specification for thunk
extern int A_jff_9A (char *, int);
extern int _jff_9A (char *, int);

//	specification for thunk
extern double A_jff_10A (char *, double);
extern double _jff_10A (char *, int);

//	specification for thunk
extern double A_jff_11A (char *, double);
extern double _jff_11A (char *, int);

//	specification for thunk
extern double A_jff_12A (char *, double);
extern double _jff_12A (char *, int);

//	specification for thunk
extern int A_jff_13A (char *, int);
extern int _jff_13A (char *, int);

//	specification for thunk
extern double A_jff_14A (char *, double);
extern double _jff_14A (char *, int);

//	specification for thunk
extern int A_jff_15A (char *, int);
extern int _jff_15A (char *, int);

//	specification for thunk
extern double A_jff_16A (char *, double);
extern double _jff_16A (char *, int);

//	specification for thunk
extern int A_jff_17A (char *, int);
extern int _jff_17A (char *, int);

//	specification for thunk
extern int A_jff_18A (char *, int);
extern int _jff_18A (char *, int);

//	specification for thunk
extern double A_jff_19A (char *, double);
extern double _jff_19A (char *, int);

//	specification for thunk
extern double A_jff_20A (char *, double);
extern double _jff_20A (char *, int);

//	specification for thunk
extern double A_jff_21A (char *, double);
extern double _jff_21A (char *, int);

//	specification for thunk
extern double A_jff_22A (char *, double);
extern double _jff_22A (char *, int);

//	specification for thunk
extern double A_jff_23A (char *, double);
extern double _jff_23A (char *, int);

//	specification for thunk
extern double A_jff_24A (char *, double);
extern double _jff_24A (char *, int);

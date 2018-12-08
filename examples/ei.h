#

/* jff_algol (Jan van Katwijk) */
/* Version 2.3		*/
/* input file: ei.alg		*/
/* Compiled at Sat Dec  8 10:06:11 2018		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	double fabs (double); /* fabs declared at line 1*/
extern	double ln (double); /* ln declared at line 9*/
extern	double exp (double); /* exp declared at line 10*/
extern	void outstring (int,char	*); /* outstring declared at line 26*/
extern	void outinteger (int,int); /* outinteger declared at line 40*/
extern	void outreal (int,double); /* outreal declared at line 43*/
extern	double _jfrac_42 (int,int *, double	*,int *, double	*); /* jfrac declared at line 3*/
extern	double _chepolsum_50 (int,double,int *, double	*); /* chepolsum declared at line 23*/
extern	double _pol_54 (int,double,int *, double	*); /* pol declared at line 37*/
extern	double _ei_58 (double); /* ei declared at line 46*/
struct ___ei_58_rec {
char *__l_field;
double __res_val;
double x;
int __dv0 [2 * 1 + DOPE_BASE];
double	*_p_60; /* p declared at line 48*/
int __dv1 [2 * 1 + DOPE_BASE];
double	*_q_60; /* q declared at line 49*/
double _t_61; /* t declared at line 82*/
double _r_61; /* r declared at line 82*/
double _x0_61; /* x0 declared at line 82*/
double _xmx0_61; /* xmx0 declared at line 82*/
double _z_62; /* z declared at line 96*/
double _z2_62; /* z2 declared at line 96*/
double _y_63; /* y declared at line 106*/
double _y_64; /* y declared at line 116*/
double _y_65; /* y declared at line 128*/
};
extern int _i_41; /* i declared at line 141*/
extern double _x_41; /* x declared at line 142*/

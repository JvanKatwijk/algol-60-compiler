#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: example18.alg		*/
/* Compiled at Thu Sep  7 12:30:13 2017		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	void newline (int); /* newline declared at line 24*/
extern	void outstring (int,char	*); /* outstring declared at line 26*/
extern	void outinteger (int,int); /* outinteger declared at line 40*/
extern int _i_40; /* i declared at line 2*/
extern int _count_40; /* count declared at line 3*/
extern	int _A_41 (int,char	*,int (*)(char *, int), int(*)(char *, int),char	*,int (*)(char *, int), int(*)(char *, int),char	*,int (*)(char *, int), int(*)(char *, int),char	*,int (*)(char *, int), int(*)(char *, int),char	*,int (*)(char *, int), int(*)(char *, int)); /* A declared at line 4*/
struct ___A_41_rec {
char *__l_field;
int __res_val;
int k;
char	*Lx1;
 int (*Ax1)(char *, int);
int (*Vx1)(char *, int);
char	*Lx2;
 int (*Ax2)(char *, int);
int (*Vx2)(char *, int);
char	*Lx3;
 int (*Ax3)(char *, int);
int (*Vx3)(char *, int);
char	*Lx4;
 int (*Ax4)(char *, int);
int (*Vx4)(char *, int);
char	*Lx5;
 int (*Ax5)(char *, int);
int (*Vx5)(char *, int);
};
extern	int _B_44 (struct ___A_41_rec	*); /* B declared at line 7*/
struct ___B_44_rec {
struct ___A_41_rec	*__l_field;
int __res_val;
};
extern int D_B_44 (char *, int, ...);	 /* B declared at line 7*/

//	specification for thunk
extern int A_jff_0A (char *, int);
extern int _jff_0A (char *, int);

//	specification for thunk
extern int A_jff_1A (char *, int);
extern int _jff_1A (char *, int);

//	specification for thunk
extern int A_jff_2A (char *, int);
extern int _jff_2A (char *, int);

//	specification for thunk
extern int A_jff_3A (char *, int);
extern int _jff_3A (char *, int);

//	specification for thunk
extern int A_jff_4A (char *, int);
extern int _jff_4A (char *, int);

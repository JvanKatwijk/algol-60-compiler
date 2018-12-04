#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: 321.alg		*/
/* Compiled at Sun Apr 22 18:17:51 2018		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	void outstring (int,char	*); /* outstring declared at line 26*/
extern	void outinteger (int,int); /* outinteger declared at line 40*/
extern	int _doit_42 (int); /* doit declared at line 16*/
struct ___doit_42_rec {
char *__l_field;
int __res_val;
int n;
int _count_44; /* count declared at line 24*/
};
extern	char _odd_45 (struct ___doit_42_rec	*,int); /* odd declared at line 20*/
struct ___odd_45_rec {
struct ___doit_42_rec	*__l_field;
char __res_val;
int x;
};
extern int _i_41; /* i declared at line 41*/
extern int _n_41; /* n declared at line 41*/
extern int _val_41; /* val declared at line 41*/
extern int _max_41; /* max declared at line 41*/
extern int _NN_41; /* NN declared at line 41*/

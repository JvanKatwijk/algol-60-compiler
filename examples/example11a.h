#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: example11a.alg		*/
/* Compiled at Thu Sep  7 08:58:58 2017		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	void outstring (int,char	*); /* outstring declared at line 26*/
extern	void _main_41 (); /* main declared at line 2*/
struct ___main_41_rec {
char *__l_field;
jmp_buf _L2_43;
jmp_buf _L1_43;
int _n_43; /* n declared at line 12*/
char _b_43; /* b declared at line 13*/
};
extern	void _go_to_44 (jmp_buf *); /* go_to declared at line 4*/
extern void D_go_to_44 (char *, int, ...);	 /* go_to declared at line 4*/
extern	void _dummy_46 (char *, void (*)(),char	*,jmp_buf * (*)(char *, jmp_buf *), jmp_buf *(*)(char *, int)); /* dummy declared at line 5*/
struct ___dummy_46_rec {
char *__l_field;
char	*Dp;
void (*p)();
char	*LL;
 jmp_buf * (*AL)(char *, jmp_buf *);
jmp_buf * (*VL)(char *, int);
};
extern	void _do_it_48 (struct ___main_41_rec	*); /* do_it declared at line 7*/
struct ___do_it_48_rec {
struct ___main_41_rec	*__l_field;
};
jmp_buf	*_L_50 (char *, int);	 /* L declared at line 9*/

//	specification for thunk
extern jmp_buf * A_jff_0A (char *, jmp_buf *);
extern jmp_buf * _jff_0A (char *, int);

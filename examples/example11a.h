#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.2		*/
/* input file: example11a.alg		*/
/* Compiled at Sun Jan 13 17:48:53 2019		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	double fabs (double); /* fabs declared at line 2*/
extern	void outstring (int,char	*); /* outstring declared at line 27*/
extern	void _main_44 (); /* main declared at line 2*/
struct ___main_44_rec {
char *__l_field;
jmp_buf _L2_46;
jmp_buf _L1_46;
int _n_46; /* n declared at line 12*/
char _b_46; /* b declared at line 13*/
};
extern	void _go_to_47 (jmp_buf *); /* go_to declared at line 4*/
extern void D_go_to_47 (char *, int, ...);	 /* go_to declared at line 4*/
extern	void _dummy_49 (char *, void (*)(),char	*,jmp_buf * (*)(char *, jmp_buf *), jmp_buf *(*)(char *, int)); /* dummy declared at line 5*/
struct ___dummy_49_rec {
char *__l_field;
char	*Dp;
void (*p)();
char	*LL;
 jmp_buf * (*AL)(char *, jmp_buf *);
jmp_buf * (*VL)(char *, int);
};
extern	void _do_it_51 (struct ___main_44_rec	*); /* do_it declared at line 7*/
struct ___do_it_51_rec {
struct ___main_44_rec	*__l_field;
};
jmp_buf	*_L_53 (char *, int);	 /* L declared at line 9*/

//	specification for thunk
extern jmp_buf * A_jff_0A (char *, jmp_buf *);
extern jmp_buf * _jff_0A (char *, int);

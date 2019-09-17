#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.2		*/
/* input file: example11.alg		*/
/* Compiled at Mon Mar  4 12:13:27 2019		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	double fabs (double); /* fabs declared at line 2*/
extern	void outstring (int,char	*); /* outstring declared at line 28*/
extern	jmp_buf _L2_44; /* L2 declared at line 17*/
extern	jmp_buf _L1_44; /* L1 declared at line 15*/
extern	void _go_to_45 (jmp_buf *); /* go_to declared at line 2*/
extern void D_go_to_45 (char *, int, ...);	 /* go_to declared at line 2*/
extern	void _dummy_47 (char *, void (*)(),char	*,jmp_buf * (*)(char *, jmp_buf *), jmp_buf *(*)(char *, int)); /* dummy declared at line 3*/
struct ___dummy_47_rec {
char *__l_field;
char	*Dp;
void (*p)();
char	*LL;
 jmp_buf * (*AL)(char *, jmp_buf *);
jmp_buf * (*VL)(char *, int);
};
extern	void _do_it_49 (); /* do_it declared at line 5*/
struct ___do_it_49_rec {
char *__l_field;
};
jmp_buf	*_L_51 (char *, int);	 /* L declared at line 7*/

//	specification for thunk
extern jmp_buf * A_jff_0A (char *, jmp_buf *);
extern jmp_buf * _jff_0A (char *, int);
extern int _n_44; /* n declared at line 10*/
extern char _b_44; /* b declared at line 11*/

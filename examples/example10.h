#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: example10.alg		*/
/* Compiled at Thu Sep  7 08:57:10 2017		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	void outstring (int,char	*); /* outstring declared at line 26*/
extern	jmp_buf _L2_40; /* L2 declared at line 17*/
extern	void _do_it_41 (); /* do_it declared at line 2*/
struct ___do_it_41_rec {
char *__l_field;
};
extern	void _go_to_44 (char	*,jmp_buf * (*)(char *, jmp_buf *), jmp_buf *(*)(char *, int)); /* go_to declared at line 4*/
struct ___go_to_44_rec {
char *__l_field;
char	*LL;
 jmp_buf * (*AL)(char *, jmp_buf *);
jmp_buf * (*VL)(char *, int);
};
extern void D_go_to_44 (char *, int, ...);	 /* go_to declared at line 4*/
extern	void _X_46 (char *, void (*)(),char	*,jmp_buf * (*)(char *, jmp_buf *), jmp_buf *(*)(char *, int)); /* X declared at line 5*/
struct ___X_46_rec {
char *__l_field;
char	*Dp;
void (*p)();
char	*LL;
 jmp_buf * (*AL)(char *, jmp_buf *);
jmp_buf * (*VL)(char *, int);
};
extern	void _dummy_48 (struct ___do_it_41_rec	*,int,char *, void (*)(),char	*,jmp_buf * (*)(char *, jmp_buf *), jmp_buf *(*)(char *, int)); /* dummy declared at line 6*/
struct ___dummy_48_rec {
struct ___do_it_41_rec	*__l_field;
int n;
char	*Dp;
void (*p)();
char	*LL;
 jmp_buf * (*AL)(char *, jmp_buf *);
jmp_buf * (*VL)(char *, int);
};

//	specification for thunk
extern jmp_buf * A_jff_0A (char *, jmp_buf *);
extern jmp_buf * _jff_0A (char *, int);

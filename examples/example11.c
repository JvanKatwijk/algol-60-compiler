#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.2		*/
/* input file: example11.alg		*/
/* Compiled at Mon Mar  4 12:13:27 2019		*/


#include	<stdio.h>
#include "example11.h"

//	Code for the global declarations

jmp_buf _L2_44;
jmp_buf _L1_44;
void D_go_to_45 (char *link, int n, ...) {
 int i;
  char *p1 [4];
 va_list vl;
 if (n != 1)
 fault ("wrong number of parameters for go_to", (double)2);
  va_start (vl, 4);
 for (i = 0; i < 4; i ++) p1 [i] = va_arg (vl, char *);
 va_end (vl);
_go_to_45(*(jmp_buf * *)(__eval_value_thunk (&p1, 1, 'j')));
}
 /* go_to declared at line 2*/
void _go_to_45 (jmp_buf * L){ 
 __jff_longjmp (L);

}
 /* dummy declared at line 3*/
void _dummy_47 (char	*Dp, void (*p)(),char	*LL, jmp_buf * (*AL)( char *, jmp_buf *), jmp_buf * (*VL)(char *, int)){ 
 struct ___dummy_47_rec local_data_dummy;
struct ___dummy_47_rec *LP = & local_data_dummy;
LP -> Dp = Dp;
LP -> p = p;
LP -> LL = LL;
LP -> AL = AL;
LP -> VL = VL;
((LP) ->  p)((LP) -> Dp ,1 ,(char *)(('j' << 8) + 'T'), (LP) -> LL, (LP) -> AL, (LP) -> VL);

}
 /* do_it declared at line 5*/
void _do_it_49 (){ 
 struct ___do_it_49_rec local_data_do_it;
struct ___do_it_49_rec *LP = & local_data_do_it;

{ // code for block at line 7
_dummy_47 (NULL, D_go_to_45, LP, A_jff_0A, _jff_0A);
; // null statement 
}

}
 /* L declared at line 7*/
jmp_buf *_L_51 (char *LP, int n) {
 switch (n) {
default:
case 1: return _L1_44;
case 2: return  ( _b_44 )? _L2_44 : _L1_44;

}; // end of switch list 
} 
jmp_buf *  A_jff_0A (char *LP, jmp_buf * V){
fault (" no assignable object",8);
}
jmp_buf *  _jff_0A (char *LP, int d){
return _L_51 (((struct ___do_it_49_rec *)(LP)), _n_44);
}
int _n_44; /* n declared at line 10*/
char _b_44; /* b declared at line 11*/


// The main program
int	main () {
 char	*LP = (char *)NULL;

{ // code for block at line 2
if (setjmp (_L2_44)) goto L_L2_44;
if (setjmp (_L1_44)) goto L_L1_44;
outstring (1, "Example 11: use of switches\n");
_n_44=2;
_b_44=true;
_do_it_49 ();
L_L1_44:outstring (1, "Incorrect\n");
goto L_L_end_44;
L_L2_44:outstring (1, "Correct\n");
L_L_end_44:; // null statement 
}
}

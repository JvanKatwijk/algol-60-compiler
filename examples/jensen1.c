#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.4		*/
/* input file: jensen1.alg		*/
/* Compiled at Mon Apr 26 18:31:52 2021		*/


#include	<stdio.h>
#include "jensen1.h"

//	Code for the global declarations

double _a_45[4 - 1 +1]; /* a declared at line 2*/
double _t_45; /* t declared at line 3*/
int _i_45; /* i declared at line 4*/
 /* jensen1 declared at line 5*/
double _jensen1_46 (char	*Li_, int (*Ai_)( char *, int), int (*Vi_)(char *, int),char	*La_, double (*Aa_)( char *, double), double (*Va_)(char *, int)){ 
 struct ___jensen1_46_rec local_data_jensen1;
struct ___jensen1_46_rec *LP = & local_data_jensen1;
LP -> Li_ = Li_;
LP -> Ai_ = Ai_;
LP -> Vi_ = Vi_;
LP -> La_ = La_;
LP -> Aa_ = Aa_;
LP -> Va_ = Va_;

{ // code for block at line 8
for (((LP) -> Ai_) ((LP) -> Li_, 1); ( ((LP) -> Vi_)(((LP) -> Li_), 0)- (4)) * sign ((double)1 )<= 0;((LP) -> Ai_)((LP) -> Li_, ((LP) -> Vi_)(((LP) -> Li_), 0)+1))(LP) ->  _s_48=((LP) ->  _s_48) + (((LP) -> Va_)(((LP) -> La_), 0));
 (LP ) -> __res_val = (LP) ->  _s_48;
; // null statement 
}
return LP -> __res_val;

}
int  A_jff_0A (char *LP, int V){
return _i_45 = V;
}
int  _jff_0A (char *LP, int d){
return _i_45;
}
double  A_jff_1A (char *LP, double V){
return _a_45 [_i_45-1] = V;
}
double  _jff_1A (char *LP, int d){
return _a_45 [_i_45-1];
}


// The main program
int	main () {
 char	*LP = (char *)NULL;

{ // code for block at line 2
for (_i_45=1; ( _i_45- (4)) * sign ((double)1 )<= 0;_i_45 +=1)_a_45 [_i_45-1]=(double)((_i_45) + (1));
_t_45=_jensen1_46 (LP, A_jff_0A, _jff_0A, LP, A_jff_1A, _jff_1A);
outstring (1, "D\n");
outreal (1, _t_45);
outstring (1, "\n");
; // null statement 
}
}

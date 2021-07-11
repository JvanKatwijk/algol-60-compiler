#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.4		*/
/* input file: jensen3.alg		*/
/* Compiled at Mon Apr 26 18:07:23 2021		*/


#include	<stdio.h>
#include "jensen3.h"

//	Code for the global declarations

 /* RAND declared at line 7*/
int _RAND_46 (){ 
 struct ___RAND_46_rec local_data_RAND;
struct ___RAND_46_rec *LP = & local_data_RAND;
 (LP ) -> __res_val = (int)((random ()) * ((double)(100)));
return LP -> __res_val;

}
 /* SUM declared at line 8*/
double _SUM_48 (int LO_,int HI_,char	*LINDEX_, int (*AINDEX_)( char *, int), int (*VINDEX_)(char *, int),char	*LEXPR_, double (*AEXPR_)( char *, double), double (*VEXPR_)(char *, int)){ 
 struct ___SUM_48_rec local_data_SUM;
struct ___SUM_48_rec *LP = & local_data_SUM;
LP -> LO_= LO_;
LP -> HI_= HI_;
LP -> LINDEX_ = LINDEX_;
LP -> AINDEX_ = AINDEX_;
LP -> VINDEX_ = VINDEX_;
LP -> LEXPR_ = LEXPR_;
LP -> AEXPR_ = AEXPR_;
LP -> VEXPR_ = VEXPR_;

{ // code for block at line 12
(LP) ->  _ACCUM_50=0.0;
for (((LP) -> AINDEX_) ((LP) -> LINDEX_, (LP) ->  LO_); ( ((LP) -> VINDEX_)(((LP) -> LINDEX_), 0)- ((LP) ->  HI_)) * sign ((double)1 )<= 0;((LP) -> AINDEX_)((LP) -> LINDEX_, ((LP) -> VINDEX_)(((LP) -> LINDEX_), 0)+1))(LP) ->  _ACCUM_50=((LP) ->  _ACCUM_50) + (((LP) -> VEXPR_)(((LP) -> LEXPR_), 0));
 (LP ) -> __res_val = (LP) ->  _ACCUM_50;
}
return LP -> __res_val;

}
int _I_52; /* I declared at line 25*/
int  A_jff_0A (char *LP, int V){
return _I_52 = V;
}
int  _jff_0A (char *LP, int d){
return _I_52;
}
int  A_jff_1A (char *LP, int V){
return _I_52 = V;
}
int  _jff_1A (char *LP, int d){
return _I_52;
}
int _I_53; /* I declared at line 32*/
int  A_jff_2A (char *LP, int V){
return _I_53 = V;
}
int  _jff_2A (char *LP, int d){
return _I_53;
}
int  A_jff_3A (char *LP, int V){
fault (" no assignable object",33);
}
int  _jff_3A (char *LP, int d){
return __mod (_RAND_46 (), 6);
}
int __dv0 [2 * 1 + DOPE_BASE];
double _DATA_54[10 - 1 +1]; /* DATA declared at line 38*/
int _I_54; /* I declared at line 39*/
double _MEAN_54; /* MEAN declared at line 40*/
double _SUMD_54; /* SUMD declared at line 40*/
double _SUMSQ_54; /* SUMSQ declared at line 40*/
double  A_jff_4A (char *LP, double V){
return _DATA_54 [_I_54-1] = V;
}
double  _jff_4A (char *LP, int d){
return _DATA_54 [_I_54-1];
}
int  A_jff_5A (char *LP, int V){
return _I_54 = V;
}
int  _jff_5A (char *LP, int d){
return _I_54;
}
double  A_jff_6A (char *LP, double V){
return _DATA_54 [_I_54-1] = V;
}
double  _jff_6A (char *LP, int d){
return _DATA_54 [_I_54-1];
}
int  A_jff_7A (char *LP, int V){
return _I_54 = V;
}
int  _jff_7A (char *LP, int d){
return _I_54;
}
double  A_jff_8A (char *LP, double V){
fault (" no assignable object",45);
}
double  _jff_8A (char *LP, int d){
return (_DATA_54 [_I_54-1]) * (_DATA_54 [_I_54-1]);
}


// The main program
int	main () {
 char	*LP = (char *)NULL;

{ // code for block at line 7

{ // code for block at line 25
outreal (1, _SUM_48 (1, 20, LP, A_jff_0A, _jff_0A, LP, A_jff_1A, _jff_1A));
outstring (1, "\n");
; // null statement 
}

{ // code for block at line 32
outreal (1, _SUM_48 (1, 10, LP, A_jff_2A, _jff_2A, LP, A_jff_3A, _jff_3A));
outstring (1, "\n");
; // null statement 
}

{ // code for block at line 38
__dv0 [0] =  (1 *256) + sizeof (double);
__dv0 [ DOPE_BASE +0] = 1;
__dv0 [ DOPE_BASE +1] = 10;
__dv_init (__dv0);
outstring (1, "type in now 10 numbers (real)\n");
for (_I_54=r_lwb (__dv0, _DATA_54, 1); ( _I_54- (r_upb (__dv0, _DATA_54, 1))) * sign ((double)1 )<= 0;_I_54 +=1)
{ // code for block at line 0
inreal (0, LP, A_jff_4A, _jff_4A);
}
_SUMD_54=_SUM_48 (1, 10, LP, A_jff_5A, _jff_5A, LP, A_jff_6A, _jff_6A);
_SUMSQ_54=_SUM_48 (1, 10, LP, A_jff_7A, _jff_7A, LP, A_jff_8A, _jff_8A);
outstring (1, "Mean is: ");
_MEAN_54=(_SUMD_54)/(10.0);
outreal (1, _MEAN_54);
outstring (1, "Variance is :");
outreal (1, ((_SUMSQ_54)/(10.0)) - ((_MEAN_54) * (_MEAN_54)));
; // null statement 
}
}
}

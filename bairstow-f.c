#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.4		*/
/* input file: bairstow-f.alg		*/
/* Compiled at Wed Sep 18 13:37:20 2019		*/


#include	<stdio.h>
#include "bairstow-f.h"

//      Code for the global declarations

 /* ABS declared at line 3 */
double
_ABS_4 (double x)
{
  double __res_val;
  __res_val = fabs (x);
  return __res_val;

}

 /* SIGNE declared at line 5 */
int
_SIGNE_7 (double x)
{
  int __res_val;
  __res_val = sign (x);
  return __res_val;

}

 /* RAC2 declared at line 8 */
double
_RAC2_11 (double e)
{
  double __res_val;
  __res_val = sqrt (e);
  return __res_val;

}

 /* BAIRSTOW declared at line 2 */
void
_BAIRSTOW_42 (int N, int *DA, double *A, char *LS0,
	      double (*AS0) (char *, double), double (*VS0) (char *, int),
	      char *LP0, double (*AP0) (char *, double),
	      double (*VP0) (char *, int), char *LEPS1,
	      double (*AEPS1) (char *, double), double (*VEPS1) (char *, int),
	      char *LEPS2, double (*AEPS2) (char *, double),
	      double (*VEPS2) (char *, int), char *LMAXITER,
	      int (*AMAXITER) (char *, int), int (*VMAXITER) (char *, int),
	      int *DX, double *X, int *DY, double *Y, char *LDIVERG,
	      jmp_buf * (*ADIVERG) (char *, jmp_buf *),
	      jmp_buf * (*VDIVERG) (char *, int))
{
  struct ___BAIRSTOW_42_rec local_data_BAIRSTOW;
  struct ___BAIRSTOW_42_rec *LP = &local_data_BAIRSTOW;
  LP->N = N;
  LP->DA = __jff_descriptor_for_value (DA, sizeof (double), LP);
  LP->A = __jff_allocate_array (LP->DA, LP);
  __typed_copy (DA, LP->DA, A, LP->A);
  LP->LS0 = LS0;
  LP->AS0 = AS0;
  LP->VS0 = VS0;
  LP->LP0 = LP0;
  LP->AP0 = AP0;
  LP->VP0 = VP0;
  LP->LEPS1 = LEPS1;
  LP->AEPS1 = AEPS1;
  LP->VEPS1 = VEPS1;
  LP->LEPS2 = LEPS2;
  LP->AEPS2 = AEPS2;
  LP->VEPS2 = VEPS2;
  LP->LMAXITER = LMAXITER;
  LP->AMAXITER = AMAXITER;
  LP->VMAXITER = VMAXITER;
  LP->DX = DX;
  LP->X = X;
  LP->DY = DY;
  LP->Y = Y;
  LP->LDIVERG = LDIVERG;
  LP->ADIVERG = ADIVERG;
  LP->VDIVERG = VDIVERG;

  {				// code for block at line 20
    (LP)->__dv0[0] = (1 * 256) + sizeof (double);
    (LP)->__dv0[DOPE_BASE + 0] = -(2);
    (LP)->__dv0[DOPE_BASE + 1] = (LP)->N;
    __dv_init ((LP)->__dv0);
    (LP)->_B_44 = (double *) __jff_allocate_array (&((LP)->__dv0), LP);
    (LP)->_C_44 = (double *) __jff_allocate_array (&((LP)->__dv0), LP);
    *(double *) __jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1, -(2)) =
      *(double *) __jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1,
					 -(1)) = (double) (0);
    *(double *) __jff_element_address ((LP)->_C_44, &((LP)->__dv0), 1, -(2)) =
      *(double *) __jff_element_address ((LP)->_C_44, &((LP)->__dv0), 1,
					 -(1)) = (double) (0);
    (LP)->_T1_44 = ((LP)->VEPS1) (((LP)->LEPS1), 0);
    if (((LP)->N) == (0))
      goto L_BOUT_44;
    if (((LP)->N) == (1))
      {
	*(double *) __jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1,
					   0) =
	  *(double *) __jff_element_address ((LP)->A, (LP)->DA, 1, 0);
	*(double *) __jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1,
					   1) =
	  *(double *) __jff_element_address ((LP)->A, (LP)->DA, 1, 1);
	goto L_DERZERO_44;
	;			// null statement 
      }
  L_TESTO_44:(LP)->_I_44 = ((LP)->N) + (1);
    (LP)->_I_44 = ((LP)->_I_44) - (11);
    while ((int)
	   (((*(double *) __jff_element_address ((LP)->A, (LP)->DA, 1, 1)) ==
	     ((double) (0))) && (((LP)->_I_44) > (1))))
      {
	{
	  *(double *) __jff_element_address ((LP)->X, (LP)->DX, 1,
					     (LP)->_I_44) = (double) (0);
	  *(double *) __jff_element_address ((LP)->Y, (LP)->DY, 1,
					     (LP)->_I_44) = (double) (0);
	  (LP)->N = ((LP)->N) - (1);
	  ;			// null statement 
	}
	(LP)->_I_44 = ((LP)->_I_44) - (11);
      }
  L_DEGTEST_44:if (((LP)->N) > (2))
      goto L_BOUCLE_44;
    (LP)->_S2_44 =
      (-(*(double *) __jff_element_address ((LP)->A, (LP)->DA, 1, 1))) /
      (*(double *) __jff_element_address ((LP)->A, (LP)->DA, 1, 0));
    (LP)->_P2_44 =
      (*(double *) __jff_element_address ((LP)->A, (LP)->DA, 1, 2)) /
      (*(double *) __jff_element_address ((LP)->A, (LP)->DA, 1, 0));
    goto L_ETIQ2_44;
    (LP)->_S_44 = ((LP)->VS0) (((LP)->LS0), 0);
    (LP)->_P_44 = ((LP)->VP0) (((LP)->LP0), 0);
  L_BOUCLE_44:((LP)->AEPS1) ((LP)->LEPS1, (LP)->_T1_44);
    (LP)->_NITER_44 = 0;
    if ((*(double *)
	 __jff_element_address ((LP)->A, (LP)->DA, 1,
				((LP)->N) - (2))) == ((double) (0)))
      if (((_ABS_4 ((LP)->_S_44)) + (_ABS_4 ((LP)->_P_44))) == ((double) (0)))
	{
	  (LP)->_S_44 = 0.1;
	  (LP)->_P_44 = 0.2;
	  ;			// null statement 
	}
  L_ITER_44:(LP)->_NITER_44 = ((LP)->_NITER_44) + (1);
    if (((LP)->_NITER_44) > (((LP)->VMAXITER) (((LP)->LMAXITER), 0)))
      {
	((LP)->AEPS1) ((LP)->LEPS1,
		       ((double) (10)) * (((LP)->VEPS1) (((LP)->LEPS1), 0)));
	if ((((LP)->VEPS1) (((LP)->LEPS1),
			    0)) > (((LP)->VEPS2) (((LP)->LEPS2), 0)))
	  __jff_longjmp (((LP)->VDIVERG) (((LP)->LDIVERG), 0));
	(LP)->_NITER_44 = 1;
      }
    for ((LP)->_I_44 = 0; ((LP)->_I_44 - ((LP)->N)) * sign ((double) 1) <= 0;
	 (LP)->_I_44 += 1)
      {
	*(double *) __jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1,
					   (LP)->_I_44) =
	  ((*(double *)
	    __jff_element_address ((LP)->A, (LP)->DA, 1,
				   (LP)->_I_44)) +
	   (((LP)->_S_44) *
	    (*(double *)
	     __jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1,
				    ((LP)->_I_44) - (1))))) -
	  (((LP)->_P_44) *
	   (*(double *)
	    __jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1,
				   ((LP)->_I_44) - (2))));
	*(double *) __jff_element_address ((LP)->_C_44, &((LP)->__dv0), 1,
					   (LP)->_I_44) =
	  ((*(double *)
	    __jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1,
				   (LP)->_I_44)) +
	   (((LP)->_S_44) *
	    (*(double *)
	     __jff_element_address ((LP)->_C_44, &((LP)->__dv0), 1,
				    ((LP)->_I_44) - (1))))) -
	  (((LP)->_P_44) *
	   (*(double *)
	    __jff_element_address ((LP)->_C_44, &((LP)->__dv0), 1,
				   ((LP)->_I_44) - (2))));
	;			// null statement 
      }
    *(double *) __jff_element_address ((LP)->_C_44, &((LP)->__dv0), 1,
				       ((LP)->N) - (1)) =
      (*(double *)
       __jff_element_address ((LP)->_C_44, &((LP)->__dv0), 1,
			      ((LP)->N) - (1))) -
      (*(double *)
       __jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1,
			      ((LP)->N) - (1)));
    (LP)->_S1_44 =
      ((*(double *)
	__jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1,
			       (LP)->N)) *
       (*(double *)
	__jff_element_address ((LP)->_C_44, &((LP)->__dv0), 1,
			       ((LP)->N) - (3)))) -
      ((*(double *)
	__jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1,
			       ((LP)->N) -
			       (1))) *
       (*(double *)
	__jff_element_address ((LP)->_C_44, &((LP)->__dv0), 1,
			       ((LP)->N) - (2))));
    (LP)->_P1_44 =
      ((*(double *)
	__jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1,
			       (LP)->N)) *
       (*(double *)
	__jff_element_address ((LP)->_C_44, &((LP)->__dv0), 1,
			       ((LP)->N) - (2)))) -
      ((*(double *)
	__jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1,
			       ((LP)->N) -
			       (1))) *
       (*(double *)
	__jff_element_address ((LP)->_C_44, &((LP)->__dv0), 1,
			       ((LP)->N) - (1))));
    (LP)->_DELTA_44 =
      ((*(double *)
	__jff_element_address ((LP)->_C_44, &((LP)->__dv0), 1,
			       ((LP)->N) -
			       (2))) *
       (*(double *)
	__jff_element_address ((LP)->_C_44, &((LP)->__dv0), 1,
			       ((LP)->N) - (2)))) -
      ((*(double *)
	__jff_element_address ((LP)->_C_44, &((LP)->__dv0), 1,
			       ((LP)->N) -
			       (1))) *
       (*(double *)
	__jff_element_address ((LP)->_C_44, &((LP)->__dv0), 1,
			       ((LP)->N) - (3))));
    (LP)->_S2_44 = ((LP)->_S_44) + (((LP)->_S1_44) / ((LP)->_DELTA_44));
    (LP)->_P2_44 = ((LP)->_P_44) + (((LP)->_P1_44) / ((LP)->_DELTA_44));
    if (((_ABS_4 (((LP)->_S2_44) - ((LP)->_S_44))) <
	 (((LP)->VEPS1) (((LP)->LEPS1), 0)))
	&& ((_ABS_4 (((LP)->_P2_44) - ((LP)->_P_44))) <
	    (((LP)->VEPS1) (((LP)->LEPS1), 0))))
      goto L_ETIQ2_44;
    (LP)->_S_44 = (LP)->_S2_44;
    (LP)->_P_44 = (LP)->_P2_44;
    goto L_ITER_44;
  L_ETIQ2_44:(LP)->_DISCR_44 =
      ((((LP)->_S2_44) * ((LP)->_S2_44)) / ((double) (4))) -
      ((LP)->_P2_44);
    if (((LP)->_DISCR_44) > ((double) (0)))
      goto L_SOLREEL_44;
    if (((LP)->_DISCR_44) == ((double) (0)))
      {
	(LP)->_R_44 = ((LP)->_S2_44) / ((double) (2));
	(LP)->_X1_44 = (LP)->_X2_44 = (LP)->_R_44;
	(LP)->_Y1_44 = (LP)->_Y2_44 = (double) (0);
	goto L_SORTIE_44;
      }
    (LP)->_Y1_44 = _RAC2_11 (-((LP)->_DISCR_44));
    (LP)->_Y2_44 = -((LP)->_Y1_44);
    goto L_SORTIE_44;
  L_SOLREEL_44:(LP)->_X1_44 =
      (((LP)->_S2_44) / ((double) (2))) +
      (((double) (_SIGNE_7 ((LP)->_S2_44))) * (_RAC2_11 ((LP)->_DISCR_44)));
    (LP)->_X2_44 = ((LP)->_P2_44) / ((LP)->_X1_44);
    (LP)->_Y1_44 = (double) (0);
    (LP)->_Y2_44 = (double) (0);
  L_SORTIE_44:*(double *) __jff_element_address ((LP)->X, (LP)->DX, 1, (LP)->N) =
      (LP)->_X1_44;
    *(double *) __jff_element_address ((LP)->Y, (LP)->DY, 1, (LP)->N) =
      (LP)->_Y1_44;
    *(double *) __jff_element_address ((LP)->X, (LP)->DX, 1,
				       ((LP)->N) - (1)) = (LP)->_X2_44;
    *(double *) __jff_element_address ((LP)->Y, (LP)->DY, 1,
				       ((LP)->N) - (1)) = (LP)->_Y2_44;
    (LP)->N = ((LP)->N) - (2);
    if (((LP)->N) == (1))
      goto L_DERZERO_44;
    if (((LP)->N) == (0))
      goto L_BOUT_44;
  L_SUITE_44:for ((LP)->_K_44 = 0; ((LP)->_K_44 - ((LP)->N)) * sign ((double) 1) <= 0;
	 (LP)->_K_44 += 1)
      *(double *) __jff_element_address ((LP)->A, (LP)->DA, 1, (LP)->_K_44) =
	*(double *) __jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1,
					   (LP)->_K_44);
    goto L_DEGTEST_44;
  L_DERZERO_44:(LP)->_X1_44 =
      (*(double *) __jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1, 1))
      /
      (*(double *) __jff_element_address ((LP)->_B_44, &((LP)->__dv0), 1, 0));
    *(double *) __jff_element_address ((LP)->X, (LP)->DX, 1, (LP)->N) =
      (LP)->_X1_44;
    *(double *) __jff_element_address ((LP)->Y, (LP)->DY, 1, (LP)->N) =
      (double) (0);
  L_BOUT_44:;			// null statement 
  }
  __deallocate (LP);

}

int _I_48;			/* I declared at line 101 */
int _N_48;			/* N declared at line 101 */
int _MAXITER_48;		/* MAXITER declared at line 101 */
double _S0_48;			/* S0 declared at line 101 */
double _P0_48;			/* P0 declared at line 101 */
double _EPS1_48;		/* EPS1 declared at line 101 */
double _EPS2_48;		/* EPS2 declared at line 101 */
jmp_buf _DIVERG_49;
int __dv1[2 * 1 + DOPE_BASE];
double *_X_49;			/* X declared at line 107 */
double *_Y_49;			/* Y declared at line 107 */
int __dv2[2 * 1 + DOPE_BASE];
double *_A_49;			/* A declared at line 107 */
double
A_jff_0A (char *LP, double V)
{
  return _S0_48 = V;
}

double
_jff_0A (char *LP, int d)
{
  return _S0_48;
}

double
A_jff_1A (char *LP, double V)
{
  return _P0_48 = V;
}

double
_jff_1A (char *LP, int d)
{
  return _P0_48;
}

double
A_jff_2A (char *LP, double V)
{
  return _EPS1_48 = V;
}

double
_jff_2A (char *LP, int d)
{
  return _EPS1_48;
}

double
A_jff_3A (char *LP, double V)
{
  return _EPS2_48 = V;
}

double
_jff_3A (char *LP, int d)
{
  return _EPS2_48;
}

int
A_jff_4A (char *LP, int V)
{
  return _MAXITER_48 = V;
}

int
_jff_4A (char *LP, int d)
{
  return _MAXITER_48;
}

jmp_buf *
A_jff_5A (char *LP, jmp_buf * V)
{
  fault (" no assignable object", 113);
}

jmp_buf *
_jff_5A (char *LP, int d)
{
  return _DIVERG_49;
}


// The main program
int
main ()
{
  char *LP = (char *) NULL;

  {				// code for block at line 2

    {				// code for block at line 101
      _N_48 = 4;
      _MAXITER_48 = 50;
      _S0_48 = 0.0;
      _P0_48 = 0.0;
      _EPS1_48 = 0.000001;
      _EPS2_48 = 0.0;
      outstring (1, "\n");

      {				// code for block at line 107
	if (setjmp (_DIVERG_49))
	  goto L_DIVERG_49;
	__dv1[0] = (1 * 256) + sizeof (double);
	__dv1[DOPE_BASE + 0] = 1;
	__dv1[DOPE_BASE + 1] = _N_48;
	__dv_init (__dv1);
	_X_49 = (double *) __jff_allocate_array (__dv1, LP);
	_Y_49 = (double *) __jff_allocate_array (__dv1, LP);
	__dv2[0] = (1 * 256) + sizeof (double);
	__dv2[DOPE_BASE + 0] = 0;
	__dv2[DOPE_BASE + 1] = _N_48;
	__dv_init (__dv2);
	_A_49 = (double *) __jff_allocate_array (__dv2, LP);
	*(double *) __jff_element_address (_A_49, __dv2, 1, 0) = -(2.);
	*(double *) __jff_element_address (_A_49, __dv2, 1, 1) = (double) (2);
	*(double *) __jff_element_address (_A_49, __dv2, 1, 2) = (double) (1);
	*(double *) __jff_element_address (_A_49, __dv2, 1, 3) =
	  (double) (-(2));
	*(double *) __jff_element_address (_A_49, __dv2, 1, 4) = (double) (1);
	for (_I_48 = 0; (_I_48 - (_N_48)) * sign ((double) 1) <= 0;
	     _I_48 += 1)
	  outreal (1,
		   *(double *) __jff_element_address (_A_49, __dv2, 1,
						      _I_48));
	_BAIRSTOW_42 (_N_48, __dv2, _A_49, LP, A_jff_0A, _jff_0A, LP,
		      A_jff_1A, _jff_1A, LP, A_jff_2A, _jff_2A, LP, A_jff_3A,
		      _jff_3A, LP, A_jff_4A, _jff_4A, __dv1, _X_49, __dv1,
		      _Y_49, LP, A_jff_5A, _jff_5A);
	outstring (1, "\n");
	for (_I_48 = 1; (_I_48 - (_N_48)) * sign ((double) 1) <= 0;
	     _I_48 += 1)
	  outreal (1,
		   *(double *) __jff_element_address (_X_49, __dv1, 1,
						      _I_48));
	outstring (1, "\n");
	for (_I_48 = 1; (_I_48 - (_N_48)) * sign ((double) 1) <= 0;
	     _I_48 += 1)
	  outreal (1,
		   *(double *) __jff_element_address (_Y_49, __dv1, 1,
						      _I_48));
	outstring (1, "\n");
	goto L_FINPROG_49;
      L_DIVERG_49:_N_48 = 0;
	outstring (1, " DIVERGENCE BAIRSTOW");
      L_FINPROG_49:;		// null statement 
      }
    }
    ;				// null statement 
  }
}

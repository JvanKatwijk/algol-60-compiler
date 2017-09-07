#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: example20.alg		*/
/* Compiled at Thu Sep  7 08:58:12 2017		*/


#include	<stdio.h>
#include "example20.h"

//      Code for the global declarations

 /* GPS declared at line 10 */
double
_GPS_41 (char *LI, double (*AI) (char *, double), double (*VI) (char *, int),
	 char *LN, double (*AN) (char *, double), double (*VN) (char *, int),
	 char *LZ, double (*AZ) (char *, double), double (*VZ) (char *, int),
	 char *LV, double (*AV) (char *, double), double (*VV) (char *, int))
{
  struct ___GPS_41_rec local_data_GPS;
  struct ___GPS_41_rec *LP = &local_data_GPS;
  LP->LI = LI;
  LP->AI = AI;
  LP->VI = VI;
  LP->LN = LN;
  LP->AN = AN;
  LP->VN = VN;
  LP->LZ = LZ;
  LP->AZ = AZ;
  LP->VZ = VZ;
  LP->LV = LV;
  LP->AV = AV;
  LP->VV = VV;
  for (((LP)->AI) ((LP)->LI, (double) (1));
       (((LP)->VI) (((LP)->LI),
		    0) - (((LP)->VN) (((LP)->LN),
				      0))) * sign ((double) (double) (1)) <=
       0; ((LP)->AI) ((LP)->LI, ((LP)->VI) (((LP)->LI), 0) + (double) (1)))
    ((LP)->AZ) ((LP)->LZ, ((LP)->VV) (((LP)->LV), 0));
  (LP)->__res_val = (double) (1);
  return LP->__res_val;

}

double _i_44;			/* i declared at line 20 */
double _j_44;			/* j declared at line 20 */
int __dv0[2 * 2 + DOPE_BASE];
double *_A_44;			/* A declared at line 21 */
double
A_jff_0A (char *LP, double V)
{
  return _j_44 = V;
}

double
_jff_0A (char *LP, int d)
{
  return _j_44;
}

double
A_jff_1A (char *LP, double V)
{
  fault (" no assignable object", 23);
}

double
_jff_1A (char *LP, int d)
{
  return 3.0;
}

double
A_jff_2A (char *LP, double V)
{
  return _i_44 = V;
}

double
_jff_2A (char *LP, int d)
{
  return _i_44;
}

double
A_jff_3A (char *LP, double V)
{
  fault (" no assignable object", 23);
}

double
_jff_3A (char *LP, int d)
{
  return _GPS_41 (LP, A_jff_4A, _jff_4A, LP, A_jff_5A, _jff_5A, LP, A_jff_6A,
		  _jff_6A, LP, A_jff_7A, _jff_7A);
}

double
A_jff_4A (char *LP, double V)
{
  return _i_44 = V;
}

double
_jff_4A (char *LP, int d)
{
  return _i_44;
}

double
A_jff_5A (char *LP, double V)
{
  fault (" no assignable object", 23);
}

double
_jff_5A (char *LP, int d)
{
  return 2.0;
}

double
A_jff_6A (char *LP, double V)
{
  return *(double *) __jff_element_address (_A_44, __dv0, 2, (int) (_i_44),
					    (int) (_j_44)) = V;
}

double
_jff_6A (char *LP, int d)
{
  return *(double *) __jff_element_address (_A_44, __dv0, 2, (int) (_i_44),
					    (int) (_j_44));
}

double
A_jff_7A (char *LP, double V)
{
  fault (" no assignable object", 23);
}

double
_jff_7A (char *LP, int d)
{
  return (_i_44) + (_j_44);
}

 /* testmatr declared at line 36 */
void
_testmatr_46 (int n, int *Da, double *a)
{
  double _c_48;
  double _d_48;
  int _i_48;
  int _j_48;

  {				// code for block at line 37
    _c_48 = (double) ((((n) * ((n) + (1))) * (((2) * (n)) - (5))) / (6));
    _d_48 = ((double) (1)) / (_c_48);
    *(double *) __jff_element_address (a, Da, 2, n, n) = -(_d_48);
    for (_i_48 = 1; (_i_48 - ((n) - (1))) * sign ((double) 1) <= 0;
	 _i_48 += 1)
      {
	*(double *) __jff_element_address (a, Da, 2, _i_48, n) =
	  *(double *) __jff_element_address (a, Da, 2, n, _i_48) =
	  (_d_48) * ((double) (_i_48));
	*(double *) __jff_element_address (a, Da, 2, _i_48, _i_48) =
	  (_d_48) * (_c_48 - (double) (__ipow (_i_48, 2)));
	for (_j_48 = 1; (_j_48 - ((_i_48) - (1))) * sign ((double) 1) <= 0;
	     _j_48 += 1)
	  *(double *) __jff_element_address (a, Da, 2, _i_48, _j_48) =
	    *(double *) __jff_element_address (a, Da, 2, _j_48, _i_48) =
	    ((-(_d_48)) * ((double) (_i_48))) * ((double) (_j_48));
      }
  }

}

 /* invert_140 declared at line 49 */
void
_invert_140_51 (int n, double eps, char *Lout,
		jmp_buf * (*Aout) (char *, jmp_buf *),
		jmp_buf * (*Vout) (char *, int), int *Da, double *a)
{
  struct ___invert_140_51_rec local_data_invert_140;
  struct ___invert_140_51_rec *LP = &local_data_invert_140;
  LP->n = n;
  LP->eps = eps;
  LP->Lout = Lout;
  LP->Aout = Aout;
  LP->Vout = Vout;
  LP->Da = Da;
  LP->a = a;

  {				// code for block at line 52
    _print_matrix_58 ("parameter ", (LP)->n, (LP)->Da, (LP)->a);
    outstring (1, "epsilon = ");
    outreal (1, (LP)->eps);
    newline (1);
    for ((LP)->_i_53 = 1; ((LP)->_i_53 - ((LP)->n)) * sign ((double) 1) <= 0;
	 (LP)->_i_53 += 1)
      {
	outstring (1, "Diagonal values ");
	outinteger (1, (LP)->_i_53);
	space (1);
	outreal (1,
		 *(double *) __jff_element_address ((LP)->a, (LP)->Da, 2,
						    (LP)->_i_53,
						    (LP)->_i_53));
	space (1);
	newline (1);
	_print_matrix_58 ("parameter", (LP)->n, (LP)->Da, (LP)->a);
	if ((abs
	     (*(double *)
	      __jff_element_address ((LP)->a, (LP)->Da, 2, (LP)->_i_53,
				     (LP)->_i_53))) <= ((LP)->eps))
	  {
	    newline (1);
	    outstring (1, "Yep, singular since ");
	    outinteger (1, (LP)->_i_53);
	    space (1);
	    outreal (1,
		     *(double *) __jff_element_address ((LP)->a, (LP)->Da, 2,
							(LP)->_i_53,
							(LP)->_i_53));
	    outstring (1, " <= ");
	    outreal (1, (LP)->eps);
	    newline (1);
	    _print_matrix_58 ("parameter", (LP)->n, (LP)->Da, (LP)->a);
	    outstring (1, "Escaping through out\n");
	    __jff_longjmp (((LP)->Vout) (((LP)->Lout), 0));
	  }
	(LP)->_q_53 =
	  ((double) (1)) /
	  (*(double *)
	   __jff_element_address ((LP)->a, (LP)->Da, 2, (LP)->_i_53,
				  (LP)->_i_53));
	*(double *) __jff_element_address ((LP)->a, (LP)->Da, 2, (LP)->_i_53,
					   (LP)->_i_53) = (double) (1);
	for ((LP)->_k_53 = 1;
	     ((LP)->_k_53 - ((LP)->n)) * sign ((double) 1) <= 0;
	     (LP)->_k_53 += 1)
	  *(double *) __jff_element_address ((LP)->a, (LP)->Da, 2,
					     (LP)->_i_53, (LP)->_k_53) =
	    (*(double *)
	     __jff_element_address ((LP)->a, (LP)->Da, 2, (LP)->_i_53,
				    (LP)->_k_53)) * ((LP)->_q_53);
	for ((LP)->_j_53 = 1;
	     ((LP)->_j_53 - ((LP)->n)) * sign ((double) 1) <= 0;
	     (LP)->_j_53 += 1)
	  if (((LP)->_i_53) != ((LP)->_j_53))
	    {
	      (LP)->_q_53 =
		*(double *) __jff_element_address ((LP)->a, (LP)->Da, 2,
						   (LP)->_j_53, (LP)->_i_53);
	      *(double *) __jff_element_address ((LP)->a, (LP)->Da, 2,
						 (LP)->_j_53, (LP)->_i_53) =
		(double) (0);
	      for ((LP)->_k_53 = 1;
		   ((LP)->_k_53 - ((LP)->n)) * sign ((double) 1) <= 0;
		   (LP)->_k_53 += 1)
		*(double *) __jff_element_address ((LP)->a, (LP)->Da, 2,
						   (LP)->_j_53, (LP)->_k_53) =
		  (*(double *)
		   __jff_element_address ((LP)->a, (LP)->Da, 2, (LP)->_j_53,
					  (LP)->_k_53)) -
		  (((LP)->_q_53) *
		   (*(double *)
		    __jff_element_address ((LP)->a, (LP)->Da, 2, (LP)->_i_53,
					   (LP)->_k_53)));
	    }
      }
  }

}

 /* print_matrix declared at line 82 */
void
_print_matrix_58 (char *name, int n, int *Da, double *a)
{
  int _i_60;
  int _j_60;
  double _r_60;

  {				// code for block at line 84
    outstring (1, "Matrix ");
    outstring (1, name);
    outstring (1, ":\n");
    for (_i_60 = 1; (_i_60 - (n)) * sign ((double) 1) <= 0; _i_60 += 1)
      {
	for (_j_60 = 1; (_j_60 - (n)) * sign ((double) 1) <= 0; _j_60 += 1)
	  {
	    _r_60 =
	      *(double *) __jff_element_address (a, Da, 2, _i_60, _j_60);
	    outreal (1,
		     ((abs
		       (*(double *)
			__jff_element_address (a, Da, 2, _i_60,
					       _j_60))) <
		      (epsilon ()))? (double) (0) : *(double *)
		     __jff_element_address (a, Da, 2, _i_60, _j_60));
	  }
	outchar (1, "\n", 1);
      }
  }

}

int _n_45;			/* n declared at line 101 */
jmp_buf _sing_63;
int __dv1[2 * 2 + DOPE_BASE];
double *_A_63;			/* A declared at line 106 */
double *_B_63;			/* B declared at line 106 */
double *_C_63;			/* C declared at line 106 */
int _i_63;			/* i declared at line 106 */
int _j_63;			/* j declared at line 106 */
int _k_63;			/* k declared at line 106 */
jmp_buf *
A_jff_8A (char *LP, jmp_buf * V)
{
  fault (" no assignable object", 113);
}

jmp_buf *
_jff_8A (char *LP, int d)
{
  return _sing_63;
}

int
A_jff_9A (char *LP, int V)
{
  return _i_63 = V;
}

int
_jff_9A (char *LP, int d)
{
  return _i_63;
}

double
A_jff_10A (char *LP, double V)
{
  fault (" no assignable object", 118);
}

double
_jff_10A (char *LP, int d)
{
  return 1.0;
}

double
A_jff_11A (char *LP, double V)
{
  return *(double *) __jff_element_address (_C_63, __dv1, 2, 1, 1) = V;
}

double
_jff_11A (char *LP, int d)
{
  return *(double *) __jff_element_address (_C_63, __dv1, 2, 1, 1);
}

double
A_jff_12A (char *LP, double V)
{
  fault (" no assignable object", 118);
}

double
_jff_12A (char *LP, int d)
{
  return 0.0;
}

int
A_jff_13A (char *LP, int V)
{
  return _i_63 = V;
}

int
_jff_13A (char *LP, int d)
{
  return _i_63;
}

double
A_jff_14A (char *LP, double V)
{
  fault (" no assignable object", 118);
}

double
_jff_14A (char *LP, int d)
{
  return ((double) ((_n_45) - (1))) *
    (_GPS_41
     (LP, A_jff_15A, _jff_15A, LP, A_jff_16A, _jff_16A, LP, A_jff_21A,
      _jff_21A, LP, A_jff_22A, _jff_22A));
}

int
A_jff_15A (char *LP, int V)
{
  return _j_63 = V;
}

int
_jff_15A (char *LP, int d)
{
  return _j_63;
}

double
A_jff_16A (char *LP, double V)
{
  fault (" no assignable object", 119);
}

double
_jff_16A (char *LP, int d)
{
  return ((double) ((_n_45) - (1))) *
    (_GPS_41
     (LP, A_jff_17A, _jff_17A, LP, A_jff_18A, _jff_18A, LP, A_jff_19A,
      _jff_19A, LP, A_jff_20A, _jff_20A));
}

int
A_jff_17A (char *LP, int V)
{
  return _k_63 = V;
}

int
_jff_17A (char *LP, int d)
{
  return _k_63;
}

int
A_jff_18A (char *LP, int V)
{
  return _n_45 = V;
}

int
_jff_18A (char *LP, int d)
{
  return _n_45;
}

double
A_jff_19A (char *LP, double V)
{
  return *(double *) __jff_element_address (_C_63, __dv1, 2, _i_63, _j_63) =
    V;
}

double
_jff_19A (char *LP, int d)
{
  return *(double *) __jff_element_address (_C_63, __dv1, 2, _i_63, _j_63);
}

double
A_jff_20A (char *LP, double V)
{
  fault (" no assignable object", 119);
}

double
_jff_20A (char *LP, int d)
{
  return (*(double *) __jff_element_address (_C_63, __dv1, 2, _i_63, _j_63)) +
    ((*(double *) __jff_element_address (_A_63, __dv1, 2, _i_63, _k_63)) *
     (*(double *) __jff_element_address (_B_63, __dv1, 2, _k_63, _j_63)));
}

double
A_jff_21A (char *LP, double V)
{
  return *(double *) __jff_element_address (_C_63, __dv1, 2, _i_63,
					    (_j_63) + (1)) = V;
}

double
_jff_21A (char *LP, int d)
{
  return *(double *) __jff_element_address (_C_63, __dv1, 2, _i_63,
					    (_j_63) + (1));
}

double
A_jff_22A (char *LP, double V)
{
  fault (" no assignable object", 120);
}

double
_jff_22A (char *LP, int d)
{
  return 0.0;
}

double
A_jff_23A (char *LP, double V)
{
  return *(double *) __jff_element_address (_C_63, __dv1, 2, (_i_63) + (1),
					    1) = V;
}

double
_jff_23A (char *LP, int d)
{
  return *(double *) __jff_element_address (_C_63, __dv1, 2, (_i_63) + (1),
					    1);
}

double
A_jff_24A (char *LP, double V)
{
  fault (" no assignable object", 120);
}

double
_jff_24A (char *LP, int d)
{
  return 0.0;
}


// The main program
int
main ()
{
  char *LP = (char *) NULL;

  {				// code for block at line 10
  L_first_example_40:;
    {				// code for block at line 20
      __dv0[0] = (2 * 256) + sizeof (double);
      __dv0[DOPE_BASE + 0] = 1;
      __dv0[DOPE_BASE + 1] = 2;
      __dv0[DOPE_BASE + 2] = 1;
      __dv0[DOPE_BASE + 3] = 3;
      __dv_init (__dv0);
      _A_44 = (double *) __jff_allocate_array (__dv0, LP);
      outstring (1, "First example\n");
      _i_44 =
	_GPS_41 (LP, A_jff_0A, _jff_0A, LP, A_jff_1A, _jff_1A, LP, A_jff_2A,
		 _jff_2A, LP, A_jff_3A, _jff_3A);
      outstring (1, "Matrix A:\n");
      outreal (1, *(double *) __jff_element_address (_A_44, __dv0, 2, 1, 1));
      outreal (1, *(double *) __jff_element_address (_A_44, __dv0, 2, 1, 2));
      outreal (1, *(double *) __jff_element_address (_A_44, __dv0, 2, 1, 3));
      outstring (1, "\n");
      outreal (1, *(double *) __jff_element_address (_A_44, __dv0, 2, 2, 1));
      outreal (1, *(double *) __jff_element_address (_A_44, __dv0, 2, 2, 2));
      outreal (1, *(double *) __jff_element_address (_A_44, __dv0, 2, 2, 3));
      outstring (1, "\n");
    }
  L_second_example_40:;
    {				// code for block at line 36
      _n_45 = 5;
      outstring (1, "Second example\n");

      {				// code for block at line 106
	if (setjmp (_sing_63))
	  goto L_sing_63;
	__dv1[0] = (2 * 256) + sizeof (double);
	__dv1[DOPE_BASE + 0] = 1;
	__dv1[DOPE_BASE + 1] = 5;
	__dv1[DOPE_BASE + 2] = 1;
	__dv1[DOPE_BASE + 3] = 5;
	__dv_init (__dv1);
	_A_63 = (double *) __jff_allocate_array (__dv1, LP);
	_B_63 = (double *) __jff_allocate_array (__dv1, LP);
	_C_63 = (double *) __jff_allocate_array (__dv1, LP);
	_testmatr_46 (_n_45, __dv1, _A_63);
	_print_matrix_58 ("A", _n_45, __dv1, _A_63);
	_testmatr_46 (_n_45, __dv1, _B_63);
	_print_matrix_58 ("B", _n_45, __dv1, _B_63);
	_invert_140_51 (_n_45, epsilon (), LP, A_jff_8A, _jff_8A, __dv1,
			_B_63);
	goto L_skip_63;
      L_sing_63:;
	fault ("Matrix is singular", (double) (_n_45));
      L_skip_63:;
	_print_matrix_58 ("B = inv(A)", _n_45, __dv1, _B_63);
	_i_63 =
	  (int) ((_GPS_41
		  (LP, A_jff_9A, _jff_9A, LP, A_jff_10A, _jff_10A, LP,
		   A_jff_11A, _jff_11A, LP, A_jff_12A,
		   _jff_12A)) * (_GPS_41 (LP, A_jff_13A, _jff_13A, LP,
					  A_jff_14A, _jff_14A, LP, A_jff_23A,
					  _jff_23A, LP, A_jff_24A,
					  _jff_24A)));
	_print_matrix_58 ("C = A * B", _n_45, __dv1, _C_63);
      }
    }
  }
}

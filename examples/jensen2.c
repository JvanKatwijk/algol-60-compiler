#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.4		*/
/* input file: jensen2.alg		*/
/* Compiled at Thu Apr 29 21:36:44 2021		*/


#include	<stdio.h>
#include "jensen2.h"

//      Code for the global declarations

 /* outer declared at line 2 */
void
_outer_46 ()
{
  struct ___outer_46_rec local_data_outer;
  struct ___outer_46_rec *LP = &local_data_outer;

  {				// code for block at line 4
    (LP)->__dv0[0] = (1 * 256) + sizeof (double);
    (LP)->__dv0[DOPE_BASE + 0] = 1;
    (LP)->__dv0[DOPE_BASE + 1] = 4;
    __dv_init ((LP)->__dv0);
    (LP)->_a_48 = (double *) __jff_allocate_array (&((LP)->__dv0), LP);
    for ((LP)->_i_48 = 1; ((LP)->_i_48 - (4)) * sign ((double) 1) <= 0;
	 (LP)->_i_48 += 1)
      *(double *) __jff_element_address ((LP)->_a_48, &((LP)->__dv0), 1,
					 (LP)->_i_48) =
	(double) (((LP)->_i_48) + (1));
    (LP)->_t_48 = _jensen1_49 (LP, A_jff_0A, _jff_0A, LP, A_jff_1A, _jff_1A);
    outstring (1, "E\n");
    outreal (1, (LP)->_t_48);
    outstring (1, "\n");
    ;				// null statement 
  }
  __deallocate (LP);

}

 /* jensen1 declared at line 7 */
double
_jensen1_49 (char *Li_, int (*Ai_) (char *, int), int (*Vi_) (char *, int),
	     char *La_, double (*Aa_) (char *, double), double (*Va_) (char *,
								       int))
{
  struct ___jensen1_49_rec local_data_jensen1;
  struct ___jensen1_49_rec *LP = &local_data_jensen1;
  LP->Li_ = Li_;
  LP->Ai_ = Ai_;
  LP->Vi_ = Vi_;
  LP->La_ = La_;
  LP->Aa_ = Aa_;
  LP->Va_ = Va_;

  {				// code for block at line 10
    for (((LP)->Ai_) ((LP)->Li_, 1);
	 (((LP)->Vi_) (((LP)->Li_), 0) - (4)) * sign ((double) 1) <= 0;
	 ((LP)->Ai_) ((LP)->Li_, ((LP)->Vi_) (((LP)->Li_), 0) + 1))
      (LP)->_s_51 = ((LP)->_s_51) + (((LP)->Va_) (((LP)->La_), 0));
    (LP)->__res_val = (LP)->_s_51;
    ;				// null statement 
  }
  return LP->__res_val;

}

int
A_jff_0A (char *LP, int V)
{
  return (((struct ___outer_46_rec *) (LP)))->_i_48 = V;
}

int
_jff_0A (char *LP, int d)
{
  return (((struct ___outer_46_rec *) (LP)))->_i_48;
}

double
A_jff_1A (char *LP, double V)
{
  return *(double *)
    __jff_element_address ((((struct ___outer_46_rec *) (LP)))->_a_48,
			   &((((struct ___outer_46_rec *) (LP)))->__dv0), 1,
			   (((struct ___outer_46_rec *) (LP)))->_i_48) = V;
}

double
_jff_1A (char *LP, int d)
{
  return *(double *)
    __jff_element_address ((((struct ___outer_46_rec *) (LP)))->_a_48,
			   &((((struct ___outer_46_rec *) (LP)))->__dv0), 1,
			   (((struct ___outer_46_rec *) (LP)))->_i_48);
}


// The main program
int
main ()
{
  char *LP = (char *) NULL;

  {				// code for block at line 2
    _outer_46 ();
    ;				// null statement 
  }
}

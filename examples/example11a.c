#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: example11a.alg		*/
/* Compiled at Thu Sep  7 08:58:58 2017		*/


#include	<stdio.h>
#include "example11a.h"

//      Code for the global declarations

 /* main declared at line 2 */
void
_main_41 ()
{
  volatile struct ___main_41_rec local_data_main;
  volatile struct ___main_41_rec *LP = &local_data_main;

  {				// code for block at line 4
    if (setjmp ((LP)->_L2_43))
      goto L_L2_43;
    if (setjmp ((LP)->_L1_43))
      goto L_L1_43;
    outstring (1, "Example 11: use of switches\n");
    (LP)->_n_43 = 2;
    (LP)->_b_43 = true;
    _do_it_48 (LP);
  L_L1_43:;
    outstring (1, "Incorrect\n");
    goto L_L_end_43;
  L_L2_43:;
    outstring (1, "Correct\n");
  L_L_end_43:;
  }

}

void
D_go_to_44 (char *link, int n, ...)
{
  int i;
  char *p1[4];
  va_list vl;
  if (n != 1)
    fault ("wrong number of parameters for go_to", (double) 4);
  va_start (vl, 4);
  for (i = 0; i < 4; i++)
    p1[i] = va_arg (vl, char *);
  va_end (vl);
  _go_to_44 (*(jmp_buf * *)(__eval_value_thunk (&p1, 1, 'j')));
}

 /* go_to declared at line 4 */
void
_go_to_44 (jmp_buf * L)
{
  __jff_longjmp (L);

}

 /* dummy declared at line 5 */
void
_dummy_46 (char *Dp, void (*p) (), char *LL,
	   jmp_buf * (*AL) (char *, jmp_buf *), jmp_buf * (*VL) (char *, int))
{
  struct ___dummy_46_rec local_data_dummy;
  struct ___dummy_46_rec *LP = &local_data_dummy;
  LP->Dp = Dp;
  LP->p = p;
  LP->LL = LL;
  LP->AL = AL;
  LP->VL = VL;
  ((LP)->p) ((LP)->Dp, 1, (char *) (('j' << 8) + 'T'), (LP)->LL, (LP)->AL,
	     (LP)->VL);

}

 /* do_it declared at line 7 */
void
_do_it_48 (struct ___main_41_rec *ELP)
{
  struct ___do_it_48_rec local_data_do_it;
  struct ___do_it_48_rec *LP = &local_data_do_it;
  LP->__l_field = ELP;

  {				// code for block at line 9
    _dummy_46 (((struct ___main_41_rec
		 *) ((((struct ___do_it_48_rec *) (LP)))->__l_field)),
	       D_go_to_44, LP, A_jff_0A, _jff_0A);
  }

}

 /* L declared at line 9 */
jmp_buf *
_L_50 (char *LP, int n)
{
  switch (n)
    {
    default:
    case 1:
      return (((struct ___main_41_rec
		*) ((((struct ___do_it_48_rec *) (LP)))->__l_field)))->_L1_43;
    case 2:
      return ((((struct ___main_41_rec
		 *) ((((struct ___do_it_48_rec *) (LP)))->__l_field)))->
	      _b_43)
	? (((struct ___main_41_rec *) ((((struct ___do_it_48_rec *) (LP)))->
				       __l_field)))->
	_L2_43
	: (((struct ___main_41_rec *) ((((struct ___do_it_48_rec *) (LP)))->
				       __l_field)))->_L1_43;

    };				// end of switch list 
}

jmp_buf *
A_jff_0A (char *LP, jmp_buf * V)
{
  fault (" no assignable object", 10);
}

jmp_buf *
_jff_0A (char *LP, int d)
{
  return _L_50 (((struct ___do_it_48_rec *) (LP)),
		(((struct ___main_41_rec
		   *) ((((struct ___do_it_48_rec *) (LP)))->__l_field)))->
		_n_43);
}


// The main program
int
main ()
{
  char *LP = (char *) NULL;

  {				// code for block at line 2
    _main_41 ();
  }
}

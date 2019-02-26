#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.2		*/
/* input file: example11a.alg		*/
/* Compiled at Sun Jan 13 17:48:53 2019		*/


#include	<stdio.h>
#include "example11a.h"

//      Code for the global declarations

 /* main declared at line 2 */
void
_main_44 ()
{
  volatile struct ___main_44_rec local_data_main;
  volatile struct ___main_44_rec *LP = &local_data_main;

  {				// code for block at line 4
    if (setjmp ((LP)->_L2_46))
      goto L_L2_46;
    if (setjmp ((LP)->_L1_46))
      goto L_L1_46;
    outstring (1, "Example 11: use of switches\n");
    (LP)->_n_46 = 2;
    (LP)->_b_46 = true;
    _do_it_51 (LP);
  L_L1_46:;			// null statement 
    outstring (1, "Incorrect\n");
    goto L_L_end_46;
  L_L2_46:;			// null statement 
    outstring (1, "Correct\n");
  L_L_end_46:;			// null statement 
    ;				// null statement 
  }

}

void
D_go_to_47 (char *link, int n, ...)
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
  _go_to_47 (*(jmp_buf * *)(__eval_value_thunk (&p1, 1, 'j')));
}

 /* go_to declared at line 4 */
void
_go_to_47 (jmp_buf * L)
{
  __jff_longjmp (L);

}

 /* dummy declared at line 5 */
void
_dummy_49 (char *Dp, void (*p) (), char *LL,
	   jmp_buf * (*AL) (char *, jmp_buf *), jmp_buf * (*VL) (char *, int))
{
  struct ___dummy_49_rec local_data_dummy;
  struct ___dummy_49_rec *LP = &local_data_dummy;
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
_do_it_51 (struct ___main_44_rec *ELP)
{
  struct ___do_it_51_rec local_data_do_it;
  struct ___do_it_51_rec *LP = &local_data_do_it;
  LP->__l_field = ELP;

  {				// code for block at line 9
    _dummy_49 (((struct ___main_44_rec
		 *) ((((struct ___do_it_51_rec *) (LP)))->__l_field)),
	       D_go_to_47, LP, A_jff_0A, _jff_0A);
    ;				// null statement 
  }

}

 /* L declared at line 9 */
jmp_buf *
_L_53 (char *LP, int n)
{
  switch (n)
    {
    default:
    case 1:
      return (((struct ___main_44_rec
		*) ((((struct ___do_it_51_rec *) (LP)))->__l_field)))->_L1_46;
    case 2:
      return ((((struct ___main_44_rec
		 *) ((((struct ___do_it_51_rec *) (LP)))->__l_field)))->
	      _b_46)
	? (((struct ___main_44_rec *) ((((struct ___do_it_51_rec *) (LP)))->
				       __l_field)))->
	_L2_46
	: (((struct ___main_44_rec *) ((((struct ___do_it_51_rec *) (LP)))->
				       __l_field)))->_L1_46;

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
  return _L_53 (((struct ___do_it_51_rec *) (LP)),
		(((struct ___main_44_rec
		   *) ((((struct ___do_it_51_rec *) (LP)))->__l_field)))->
		_n_46);
}


// The main program
int
main ()
{
  char *LP = (char *) NULL;

  {				// code for block at line 2
    _main_44 ();
    ;				// null statement 
  }
}

#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: example10.alg		*/
/* Compiled at Thu Sep  7 08:57:10 2017		*/


#include	<stdio.h>
#include "example10.h"

//      Code for the global declarations

jmp_buf _L2_40;
 /* do_it declared at line 2 */
void
_do_it_41 ()
{
  struct ___do_it_41_rec local_data_do_it;
  struct ___do_it_41_rec *LP = &local_data_do_it;

  {				// code for block at line 4
  L_try_again_43:;
    _dummy_48 (LP, 5, LP, D_go_to_44, LP, A_jff_0A, _jff_0A);
    outstring (1, "This is not right\n");
    goto L_try_again_43;
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
  _go_to_44 ((char *) (__get_thunk_link (&p1, 1)),
	     (char *) (__get_address_thunk (&p1, 1, 'j')),
	     (char *) (__get_value_thunk (&p1, 1, 'j')));
}

 /* go_to declared at line 4 */
void
_go_to_44 (char *LL, jmp_buf * (*AL) (char *, jmp_buf *),
	   jmp_buf * (*VL) (char *, int))
{
  struct ___go_to_44_rec local_data_go_to;
  struct ___go_to_44_rec *LP = &local_data_go_to;
  LP->LL = LL;
  LP->AL = AL;
  LP->VL = VL;
  __jff_longjmp (((LP)->VL) (((LP)->LL), 0));

}

 /* X declared at line 5 */
void
_X_46 (char *Dp, void (*p) (), char *LL, jmp_buf * (*AL) (char *, jmp_buf *),
       jmp_buf * (*VL) (char *, int))
{
  struct ___X_46_rec local_data_X;
  struct ___X_46_rec *LP = &local_data_X;
  LP->Dp = Dp;
  LP->p = p;
  LP->LL = LL;
  LP->AL = AL;
  LP->VL = VL;
  ((LP)->p) ((LP)->Dp, 1, (char *) (('j' << 8) + 'T'), (LP)->LL, (LP)->AL,
	     (LP)->VL);

}

 /* dummy declared at line 6 */
void
_dummy_48 (struct ___do_it_41_rec *ELP, int n, char *Dp, void (*p) (),
	   char *LL, jmp_buf * (*AL) (char *, jmp_buf *),
	   jmp_buf * (*VL) (char *, int))
{
  struct ___dummy_48_rec local_data_dummy;
  struct ___dummy_48_rec *LP = &local_data_dummy;
  LP->__l_field = ELP;
  LP->n = n;
  LP->Dp = Dp;
  LP->p = p;
  LP->LL = LL;
  LP->AL = AL;
  LP->VL = VL;
  if (((LP)->n) <= (1))
    _X_46 ((LP)->Dp, (LP)->p, (LP)->LL, (LP)->AL, (LP)->VL);

  else
    _dummy_48 (((struct ___do_it_41_rec
		 *) ((((struct ___dummy_48_rec *) (LP)))->__l_field)),
	       ((LP)->n) - (1), (LP)->Dp, (LP)->p, (LP)->LL, (LP)->AL,
	       (LP)->VL);

}

jmp_buf *
A_jff_0A (char *LP, jmp_buf * V)
{
  fault (" no assignable object", 11);
}

jmp_buf *
_jff_0A (char *LP, int d)
{
  return _L2_40;
}


// The main program
int
main ()
{
  char *LP = (char *) NULL;

  {				// code for block at line 2
    if (setjmp (_L2_40))
      goto L_L2_40;
    outstring (1, "Example 10: Useless use of formal procedures\n");
    _do_it_41 ();
  L_L2_40:;
    outstring (1, "Yes, we made it\n");
  }
}

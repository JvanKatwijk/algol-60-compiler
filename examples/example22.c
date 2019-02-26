#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.2		*/
/* input file: example22.alg		*/
/* Compiled at Sun Jan 13 14:48:21 2019		*/


#include	<stdio.h>
#include "example22.h"

//      Code for the global declarations

int _a_43;			/* a declared at line 3 */
int _b_43;			/* b declared at line 3 */
int _c_43;			/* c declared at line 3 */
 /* p declared at line 4 */
void
_p_44 (char b, char *Dq, void (*q) (), char *Dr, void (*r) (), char *Ds,
       void (*s) ())
{
  struct ___p_44_rec local_data_p;
  struct ___p_44_rec *LP = &local_data_p;
  LP->b = b;
  LP->Dq = Dq;
  LP->q = q;
  LP->Dr = Dr;
  LP->r = r;
  LP->Ds = Ds;
  LP->s = s;
  if ((LP)->b)
    ((LP)->q) ((LP)->Dq, 1, (char *) (('v' << 8) + 'F'), (LP)->Ds, (LP)->s);

  else
    ((LP)->r) ((LP)->Dr, 1, (char *) (('v' << 8) + 'F'), (LP)->Ds, (LP)->s);

}

void
D_f1_46 (char *link, int n, ...)
{
  int i;
  char *p1[3];
  va_list vl;
  if (n != 1)
    fault ("wrong number of parameters for f1", (double) 10);
  va_start (vl, 3);
  for (i = 0; i < 3; i++)
    p1[i] = va_arg (vl, char *);
  va_end (vl);
  _f1_46 ((char *) (__get_function_link (&p1, 1, 'v')),
	  (char *) (__get_function_address (&p1, 1, 'v')));
}

 /* f1 declared at line 10 */
void
_f1_46 (char *Dp1, void (*p1) ())
{
  struct ___f1_46_rec local_data_f1;
  struct ___f1_46_rec *LP = &local_data_f1;
  LP->Dp1 = Dp1;
  LP->p1 = p1;

  {				// code for block at line 10
    ((LP)->p1) ((LP)->Dp1, 3, (char *) (('i' << 8) + 'T'), LP, A_jff_0A,
		_jff_0A, (char *) (('i' << 8) + 'T'), LP, A_jff_1A, _jff_1A,
		(char *) (('i' << 8) + 'T'), LP, A_jff_2A, _jff_2A);
  }

}

int
A_jff_0A (char *LP, int V)
{
  return _a_43 = V;
}

int
_jff_0A (char *LP, int d)
{
  return _a_43;
}

int
A_jff_1A (char *LP, int V)
{
  return _b_43 = V;
}

int
_jff_1A (char *LP, int d)
{
  return _b_43;
}

int
A_jff_2A (char *LP, int V)
{
  return _c_43 = V;
}

int
_jff_2A (char *LP, int d)
{
  return _c_43;
}

void
D_f2_48 (char *link, int n, ...)
{
  int i;
  char *p1[3];
  va_list vl;
  if (n != 1)
    fault ("wrong number of parameters for f2", (double) 11);
  va_start (vl, 3);
  for (i = 0; i < 3; i++)
    p1[i] = va_arg (vl, char *);
  va_end (vl);
  _f2_48 ((char *) (__get_function_link (&p1, 1, 'v')),
	  (char *) (__get_function_address (&p1, 1, 'v')));
}

 /* f2 declared at line 11 */
void
_f2_48 (char *Dp1, void (*p1) ())
{
  struct ___f2_48_rec local_data_f2;
  struct ___f2_48_rec *LP = &local_data_f2;
  LP->Dp1 = Dp1;
  LP->p1 = p1;

  {				// code for block at line 11
    ((LP)->p1) ((LP)->Dp1, 2, (char *) (('i' << 8) + 'T'), LP, A_jff_3A,
		_jff_3A, (char *) (('i' << 8) + 'T'), LP, A_jff_4A, _jff_4A);
  }

}

int
A_jff_3A (char *LP, int V)
{
  return _a_43 = V;
}

int
_jff_3A (char *LP, int d)
{
  return _a_43;
}

int
A_jff_4A (char *LP, int V)
{
  return _b_43 = V;
}

int
_jff_4A (char *LP, int d)
{
  return _b_43;
}

void
D_a1_50 (char *link, int n, ...)
{
  int i;
  char *p1[12];
  va_list vl;
  if (n != 3)
    fault ("wrong number of parameters for a1", (double) 12);
  va_start (vl, 12);
  for (i = 0; i < 12; i++)
    p1[i] = va_arg (vl, char *);
  va_end (vl);
  _a1_50 ((char *) (__get_thunk_link (&p1, 1)),
	  (char *) (__get_address_thunk (&p1, 1, 'i')),
	  (char *) (__get_value_thunk (&p1, 1, 'i')),
	  (char *) (__get_thunk_link (&p1, 2)),
	  (char *) (__get_address_thunk (&p1, 2, 'i')),
	  (char *) (__get_value_thunk (&p1, 2, 'i')),
	  (char *) (__get_thunk_link (&p1, 3)),
	  (char *) (__get_address_thunk (&p1, 3, 'i')),
	  (char *) (__get_value_thunk (&p1, 3, 'i')));
}

 /* a1 declared at line 12 */
void
_a1_50 (char *La, int (*Aa) (char *, int), int (*Va) (char *, int), char *Lb,
	int (*Ab) (char *, int), int (*Vb) (char *, int), char *Lc,
	int (*Ac) (char *, int), int (*Vc) (char *, int))
{
  struct ___a1_50_rec local_data_a1;
  struct ___a1_50_rec *LP = &local_data_a1;
  LP->La = La;
  LP->Aa = Aa;
  LP->Va = Va;
  LP->Lb = Lb;
  LP->Ab = Ab;
  LP->Vb = Vb;
  LP->Lc = Lc;
  LP->Ac = Ac;
  LP->Vc = Vc;
  ((LP)->Aa) ((LP)->La,
	      (((LP)->Vb) (((LP)->Lb), 0)) + (((LP)->Vc) (((LP)->Lc), 0)));

}

void
D_a2_52 (char *link, int n, ...)
{
  int i;
  char *p1[8];
  va_list vl;
  if (n != 2)
    fault ("wrong number of parameters for a2", (double) 13);
  va_start (vl, 8);
  for (i = 0; i < 8; i++)
    p1[i] = va_arg (vl, char *);
  va_end (vl);
  _a2_52 ((char *) (__get_thunk_link (&p1, 1)),
	  (char *) (__get_address_thunk (&p1, 1, 'i')),
	  (char *) (__get_value_thunk (&p1, 1, 'i')),
	  (char *) (__get_thunk_link (&p1, 2)),
	  (char *) (__get_address_thunk (&p1, 2, 'i')),
	  (char *) (__get_value_thunk (&p1, 2, 'i')));
}

 /* a2 declared at line 13 */
void
_a2_52 (char *La, int (*Aa) (char *, int), int (*Va) (char *, int), char *Lb,
	int (*Ab) (char *, int), int (*Vb) (char *, int))
{
  struct ___a2_52_rec local_data_a2;
  struct ___a2_52_rec *LP = &local_data_a2;
  LP->La = La;
  LP->Aa = Aa;
  LP->Va = Va;
  LP->Lb = Lb;
  LP->Ab = Ab;
  LP->Vb = Vb;
  ((LP)->Aa) ((LP)->La, ((LP)->Vb) (((LP)->Lb), 0));

}


// The main program
int
main ()
{
  char *LP = (char *) NULL;

  {				// code for block at line 3
    _b_43 = 1;
    _c_43 = 2;
    _p_44 (true, NULL, D_f1_46, NULL, D_f2_48, NULL, D_a1_50);
    outstring (1, " after the call to a1 ");
    outinteger (1, _a_43);
    newline (1);
    _p_44 (false, NULL, D_f1_46, NULL, D_f2_48, NULL, D_a2_52);
    outstring (1, " after the call to a2 ");
    outinteger (1, _a_43);
    newline (1);
    ;				// null statement 
  }
}

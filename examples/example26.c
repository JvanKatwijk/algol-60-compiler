#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: example26.alg		*/
/* Compiled at Wed Sep 13 13:03:25 2017		*/


#include	<stdio.h>
#include "example26.h"

//      Code for the global declarations

 /* S declared at line 4 */
void
_S_41 (char *Lx, double (*Ax) (char *, double), double (*Vx) (char *, int))
{
  struct ___S_41_rec local_data_S;
  struct ___S_41_rec *LP = &local_data_S;
  LP->Lx = Lx;
  LP->Ax = Ax;
  LP->Vx = Vx;
  ((LP)->Ax) ((LP)->Lx, (double) (0));

}

double
D_r_43 (char *link, int n, ...)
{
  if (n != 0)
    fault ("wrong number of parameters for r", (double) 5);
  return _r_43 ();
}

 /* r declared at line 5 */
double
_r_43 ()
{
  double __res_val;
  __res_val = (double) (1);
  _S_41 (NULL, NULL, _r_43);
  ;				// null statement 
  return __res_val;

}

double _x_40;			/* x declared at line 10 */
double
A_jff_0A (char *LP, double V)
{
  fault (" no assignable object", 12);
}

double
_jff_0A (char *LP, int d)
{
  return ((_x_40) == ((double) (1))) ? _r_43 () : _x_40;
}


// The main program
int
main ()
{
  char *LP = (char *) NULL;

  {				// code for block at line 4
    _x_40 = (double) (1);
    _S_41 (LP, A_jff_0A, _jff_0A);
    outreal (1, _x_40);
    newline (1);
    ;				// null statement 
  }
}

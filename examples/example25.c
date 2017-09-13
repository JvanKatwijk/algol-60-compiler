#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: example25.alg		*/
/* Compiled at Wed Sep 13 12:40:31 2017		*/


#include	<stdio.h>
#include "example25.h"

//      Code for the global declarations

double _V_40[1 - 1 + 1];	/* V declared at line 4 */
double _A_40[1 - 1 + 1];	/* A declared at line 4 */
double _C_40[1 - 1 + 1];	/* C declared at line 4 */
int _k_40;			/* k declared at line 5 */
 /* i declared at line 6 */
int
_i_41 ()
{
  int __res_val;
  __res_val = 1;
  _k_40 = (_k_40) + (1);
  ;				// null statement 
  return __res_val;

}


// The main program
int
main ()
{
  char *LP = (char *) NULL;

  {				// code for block at line 4
    _k_40 = 0;
    _A_40[1 - 1] = (double) (1);
    _C_40[1 - 1] = (double) (3);
    for (_V_40[_i_41 () - 1] = _A_40[_i_41 () - 1]; (_V_40[_i_41 () - 1] - (_C_40[_i_41 () - 1])) * sign ((double) _A_40[_i_41 () - 1]) <= 0; _V_40[_i_41 () - 1] = _V_40[_i_41 () - 1] + _A_40[_i_41 () - 1]);	// null statement 
    ;				// null statement 
    outreal (1, (double) (_k_40));
  }
}

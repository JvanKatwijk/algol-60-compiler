#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: 321.alg		*/
/* Compiled at Sun Apr 22 18:17:51 2018		*/


#include	<stdio.h>
#include "321.h"

//      Code for the global declarations

 /* doit declared at line 16 */
int
_doit_42 (int n)
{
  struct ___doit_42_rec local_data_doit;
  struct ___doit_42_rec *LP = &local_data_doit;
  LP->n = n;

  {				// code for block at line 20
    (LP)->_count_44 = 0;
  L_do_44:;			// null statement 
    if (_odd_45 (LP, (LP)->n))
      (LP)->n = ((3) * ((LP)->n)) + (1);

    else
      (LP)->n = ((LP)->n) / (2);
    (LP)->_count_44 = ((LP)->_count_44) + (1);
    if (((LP)->n) != (1))
      goto L_do_44;
    (LP)->__res_val = (LP)->_count_44;
    ;				// null statement 
  }
  return LP->__res_val;

}

 /* odd declared at line 20 */
char
_odd_45 (struct ___doit_42_rec *ELP, int x)
{
  struct ___odd_45_rec local_data_odd;
  struct ___odd_45_rec *LP = &local_data_odd;
  LP->__l_field = ELP;
  LP->x = x;
  (LP)->__res_val =
    ((((struct ___doit_42_rec *) ((((struct ___odd_45_rec *) (LP)))->
				  __l_field)))->n) !=
    ((((((struct ___doit_42_rec *) ((((struct ___odd_45_rec *) (LP)))->
				    __l_field)))->n) / (2)) * (2));
  return LP->__res_val;

}

int _i_41;			/* i declared at line 41 */
int _n_41;			/* n declared at line 41 */
int _val_41;			/* val declared at line 41 */
int _max_41;			/* max declared at line 41 */
int _NN_41;			/* NN declared at line 41 */


// The main program
int
main ()
{
  char *LP = (char *) NULL;

  {				// code for block at line 16
    _NN_41 = 500;
    outstring (1, "Hi!\n                n           iterations\n");
    for (_i_41 = 1; (_i_41 - (_NN_41)) * sign ((double) 1) <= 0; _i_41 += 1)
      {
	_doit_42 (_i_41);
	;			// null statement 
      }
    outstring (1, "...");
    outstring (1, "\nnow looking for maxima:");
    outstring (1, "\n                n           iterations\n");
    _n_41 = 0;
    _max_41 = -(1);
    for (_i_41 = 1; (_i_41 - (_NN_41)) * sign ((double) 1) <= 0; _i_41 += 1)
      {				// code for block at line 0
	outstring (1, "i = ");
	outinteger (1, _i_41);
	outstring (1, "  ");
	outinteger (1, _max_41);
	outstring (1, "\n");
      L_do_48:;		// null statement 
	if ((_n_41) < (100000))
	  {
	    _n_41 = (_n_41) + (1);
	    _val_41 = _doit_42 (_n_41);
	    if ((_val_41) <= (_max_41))
	      goto L_do_48;
	    ;			// null statement 
	  }
	outinteger (1, _n_41);
	outstring (1, " ");
	outinteger (1, _val_41);
	outstring (1, "\n");
	_max_41 = _val_41;
	;			// null statement 
      }
    outstring (1, "...\ndone.");
  }
}

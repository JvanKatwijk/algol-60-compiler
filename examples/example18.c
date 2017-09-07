#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: example18.alg		*/
/* Compiled at Thu Sep  7 12:30:13 2017		*/


#include	<stdio.h>
#include "example18.h"

//      Code for the global declarations

int _i_40;			/* i declared at line 2 */
int _count_40;			/* count declared at line 3 */
 /* A declared at line 4 */
int
_A_41 (int k, char *Lx1, int (*Ax1) (char *, int), int (*Vx1) (char *, int),
       char *Lx2, int (*Ax2) (char *, int), int (*Vx2) (char *, int),
       char *Lx3, int (*Ax3) (char *, int), int (*Vx3) (char *, int),
       char *Lx4, int (*Ax4) (char *, int), int (*Vx4) (char *, int),
       char *Lx5, int (*Ax5) (char *, int), int (*Vx5) (char *, int))
{
  struct ___A_41_rec local_data_A;
  struct ___A_41_rec *LP = &local_data_A;
  LP->k = k;
  LP->Lx1 = Lx1;
  LP->Ax1 = Ax1;
  LP->Vx1 = Vx1;
  LP->Lx2 = Lx2;
  LP->Ax2 = Ax2;
  LP->Vx2 = Vx2;
  LP->Lx3 = Lx3;
  LP->Ax3 = Ax3;
  LP->Vx3 = Vx3;
  LP->Lx4 = Lx4;
  LP->Ax4 = Ax4;
  LP->Vx4 = Vx4;
  LP->Lx5 = Lx5;
  LP->Ax5 = Ax5;
  LP->Vx5 = Vx5;

  {				// code for block at line 7
    _count_40 = (_count_40) + (1);
    if (((LP)->k) <= (0))
      (LP)->__res_val =
	(((LP)->Vx4) (((LP)->Lx4), 0)) + (((LP)->Vx5) (((LP)->Lx5), 0));

    else
      _B_44 (LP);
  }
  return LP->__res_val;

}

int
D_B_44 (char *link, int n, ...)
{
  if (n != 0)
    fault ("wrong number of parameters for B", (double) 7);
  return _B_44 (link);
}

 /* B declared at line 7 */
int
_B_44 (struct ___A_41_rec *ELP)
{
  struct ___B_44_rec local_data_B;
  struct ___B_44_rec *LP = &local_data_B;
  LP->__l_field = ELP;
  (((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->__l_field)))->k =
    ((((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->__l_field)))->
     k) - (1);
  (((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->__l_field)))->
    __res_val = (LP)->__res_val =
    _A_41 ((((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->
				     __l_field)))->k,
	   ((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->
				    __l_field)), NULL, _B_44,
	   (((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->
				     __l_field)))->Lx1,
	   (((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->
				     __l_field)))->Ax1,
	   (((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->
				     __l_field)))->Vx1,
	   (((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->
				     __l_field)))->Lx2,
	   (((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->
				     __l_field)))->Ax2,
	   (((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->
				     __l_field)))->Vx2,
	   (((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->
				     __l_field)))->Lx3,
	   (((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->
				     __l_field)))->Ax3,
	   (((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->
				     __l_field)))->Vx3,
	   (((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->
				     __l_field)))->Lx4,
	   (((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->
				     __l_field)))->Ax4,
	   (((struct ___A_41_rec *) ((((struct ___B_44_rec *) (LP)))->
				     __l_field)))->Vx4);
  return LP->__res_val;

}

int
A_jff_0A (char *LP, int V)
{
  fault (" no assignable object", 19);
}

int
_jff_0A (char *LP, int d)
{
  return 1;
}

int
A_jff_1A (char *LP, int V)
{
  fault (" no assignable object", 19);
}

int
_jff_1A (char *LP, int d)
{
  return -(1);
}

int
A_jff_2A (char *LP, int V)
{
  fault (" no assignable object", 19);
}

int
_jff_2A (char *LP, int d)
{
  return -(1);
}

int
A_jff_3A (char *LP, int V)
{
  fault (" no assignable object", 19);
}

int
_jff_3A (char *LP, int d)
{
  return 1;
}

int
A_jff_4A (char *LP, int V)
{
  fault (" no assignable object", 19);
}

int
_jff_4A (char *LP, int d)
{
  return 1;
}


// The main program
int
main ()
{
  char *LP = (char *) NULL;

  {				// code for block at line 2
    outstring (1, "man or boy?\n");
    for (_i_40 = 1; (_i_40 - (15)) * sign ((double) 1) <= 0; _i_40 += 1)
      {				// code for block at line 0
	_count_40 = 0;
	outinteger (1,
		    _A_41 (_i_40, LP, A_jff_0A, _jff_0A, LP, A_jff_1A,
			   _jff_1A, LP, A_jff_2A, _jff_2A, LP, A_jff_3A,
			   _jff_3A, LP, A_jff_4A, _jff_4A));
	newline (1);
	outstring (1, "Recursie diepte ");
	outinteger (1, _count_40);
	newline (1);
      }
  }
}

#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: trac.alg		*/
/* Compiled at Fri Jun  4 08:22:38 2004		*/


#include	<stdio.h>
#include "trac.h"

//      Code for the global declarations

int _Trac_Sharp_Sign_40;	/* Trac_Sharp_Sign declared at line 2 */
int _LPAR_40;			/* LPAR declared at line 3 */
int _RPAR_40;			/* RPAR declared at line 4 */
int _FN_START_40;		/* FN_START declared at line 5 */
int _FN_END_40;			/* FN_END declared at line 5 */
int _last_open_40;		/* last_open declared at line 7 */
int _active_string_40[1000 - 1 + 1];	/* active_string declared at line 8 */
int _passive_string_40[2 - 1 + 1][1000 - 1 + 1];	/* passive_string declared at line 9 */
int _user_defs_40[10000 - 1 + 1];	/* user_defs declared at line 10 */
int _active_char_40;		/* active_char declared at line 12 */
int _passive_char_40;		/* passive_char declared at line 13 */
 /* end_of_active_string declared at line 15 */
int
_end_of_active_string_41 ()
{
  int __res_val;
  __res_val = 1000;
  return __res_val;

}

 /* init_active_and_passive_string declared at line 18 */
void
_init_active_and_passive_string_43 ()
{

  {				// code for block at line 20
    _active_char_40 = _end_of_active_string_41 ();
    _passive_char_40 = 1;
    _add_to_active_string_46 (41);
    _add_to_active_string_46 (41);
    _add_to_active_string_46 (115);
    _add_to_active_string_46 (114);
    _add_to_active_string_46 (40);
    _add_to_active_string_46 (_Trac_Sharp_Sign_40);
    _add_to_active_string_46 (44);
    _add_to_active_string_46 (115);
    _add_to_active_string_46 (112);
    _add_to_active_string_46 (40);
    _add_to_active_string_46 (_Trac_Sharp_Sign_40);
  }

}

 /* add_to_active_string declared at line 20 */
void
_add_to_active_string_46 (int ch)
{
  _active_string_40[_active_char_40 - 1] = ch;
  _active_char_40 = (_active_char_40) - (1);

}

 /* move_to_passive_string declared at line 42 */
void
_move_to_passive_string_48 (int ch, jmp_buf * l)
{
  _passive_string_40[1 - 1][_passive_char_40 - 1] = ch;
  _passive_char_40 = (_passive_char_40) + (1);

}

 /* eval_built_in declared at line 49 */
void
_eval_built_in_50 (jmp_buf * l)
{

}

 /* eval_user_defined declared at line 50 */
void
_eval_user_defined_52 (jmp_buf * l)
{

}

 /* is_built_in declared at line 51 */
char
_is_built_in_54 ()
{
  char __res_val;
  __res_val = false;
  return __res_val;

}

 /* get_char_from_active_string declared at line 52 */
int
_get_char_from_active_string_56 (jmp_buf * l)
{
  int __res_val;
  if ((_active_char_40) > (_end_of_active_string_41 ()))
    __jff_longjmp (l);
  __res_val = _active_string_40[_active_char_40 - 1];
  return __res_val;

}

 /* announce declared at line 61 */
void
_announce_58 (char *s)
{
  outstring (1, s);
  newline (1);

}

 /* set_up_data_structures declared at line 66 */
void
_set_up_data_structures_60 ()
{

}

 /* read_config declared at line 68 */
void
_read_config_62 (char *s)
{

}

 /* read_user_defined_functions declared at line 70 */
void
_read_user_defined_functions_64 (jmp_buf * l)
{

}

 /* eval_active_till_call declared at line 72 */
void
_eval_active_till_call_66 (jmp_buf * l)
{
  struct ___eval_active_till_call_66_rec local_data_eval_active_till_call;
  struct ___eval_active_till_call_66_rec *LP =
    &local_data_eval_active_till_call;
  LP->l = l;

  {				// code for block at line 74
    (LP)->_no_function_yet_68 = true;
    (LP)->_dummy_68 = 0;
    while ((int) ((LP)->_no_function_yet_68))
      {
	{			// code for block at line 162
	  _print_passive_and_active_string_78 ();
	  (LP)->_ch_84 = _get_char_from_active_string_56 ((LP)->l);
	  if (((LP)->_ch_84) == (_Trac_Sharp_Sign_40))
	    {
	      _active_char_40 = (_active_char_40) + (1);
	      _process_sharp_sign_73 ((LP)->l);
	    }

	  else if (((LP)->_ch_84) == (_LPAR_40))
	    {
	      _active_char_40 = (_active_char_40) + (1);
	      _process_protected_string_69 (LP, (LP)->l);
	    }

	  else if (((LP)->_ch_84) == (_RPAR_40))
	    {
	      (LP)->_no_function_yet_68 = false;
	      _active_char_40 = (_active_char_40) + (1);
	      _move_to_passive_string_48 (_FN_END_40, (LP)->l);
	    }

	  else
	    {
	      _active_char_40 = (_active_char_40) + (1);
	      _move_to_passive_string_48 ((LP)->_ch_84, (LP)->l);
	    }
	}
	(LP)->_dummy_68 = 0;
      }
  }

}

 /* process_protected_string declared at line 77 */
void
_process_protected_string_69 (struct ___eval_active_till_call_66_rec *ELP,
			      jmp_buf * l)
{
  struct ___process_protected_string_69_rec
    local_data_process_protected_string;
  struct ___process_protected_string_69_rec *LP =
    &local_data_process_protected_string;
  LP->__l_field = ELP;
  LP->l = l;

  {				// code for block at line 79
    (LP)->_par_count_71 = 1;
    (((struct ___eval_active_till_call_66_rec
       *) ((((struct ___process_protected_string_69_rec *) (LP)))->
	   __l_field)))->_dummy_68 = 0;
    while ((int) (((LP)->_par_count_71) > (0)))
      {
	{
	  (LP)->_char_71 = _get_char_from_active_string_56 ((LP)->l);
	  _active_char_40 = (_active_char_40) + (1);
	  if (((LP)->_char_71) == (_LPAR_40))
	    {
	      (LP)->_par_count_71 = ((LP)->_par_count_71) + (1);
	      _move_to_passive_string_48 ((LP)->_char_71, (LP)->l);
	    }

	  else if (((LP)->_char_71) == (_RPAR_40))
	    {
	      (LP)->_par_count_71 = ((LP)->_par_count_71) - (1);
	      if (((LP)->_par_count_71) > (0))
		_move_to_passive_string_48 ((LP)->_char_71, (LP)->l);
	    }
	}
	(((struct ___eval_active_till_call_66_rec
	   *) ((((struct ___process_protected_string_69_rec *) (LP)))->
	       __l_field)))->_dummy_68 = 0;
      }
  }

}

 /* process_sharp_sign declared at line 102 */
void
_process_sharp_sign_73 (jmp_buf * l)
{
  int _ch_75;

  {				// code for block at line 104
    _ch_75 = _get_char_from_active_string_56 (l);
    if ((_ch_75) == (_LPAR_40))
      {
	_active_char_40 = (_active_char_40) + (1);
	_add_open_function_to_passive_string_76 ();
      }

    else if ((_ch_75) == (_Trac_Sharp_Sign_40))
      {
	_active_char_40 = (_active_char_40) + (1);
	_ch_75 = _get_char_from_active_string_56 (l);
	if ((_ch_75) == (_LPAR_40))
	  {
	    _active_char_40 = (_active_char_40) + (1);
	    _move_to_passive_string_48 (_Trac_Sharp_Sign_40, l);
	    _move_to_passive_string_48 (_LPAR_40, l);
	  }

	else
	  {
	    _move_to_passive_string_48 (_Trac_Sharp_Sign_40, l);
	    _move_to_passive_string_48 (_Trac_Sharp_Sign_40, l);
	  }
      }

    else
      {
	_active_char_40 = (_active_char_40) + (1);
	_move_to_passive_string_48 (_Trac_Sharp_Sign_40, l);
	_move_to_passive_string_48 (_ch_75, l);
      }
  }

}

 /* add_open_function_to_passive_string declared at line 105 */
void
_add_open_function_to_passive_string_76 ()
{
  _passive_string_40[2 - 1][_passive_char_40 - 1] = _last_open_40;
  _last_open_40 = _passive_char_40;
  _passive_string_40[1 - 1][_passive_char_40 - 1] = _FN_START_40;
  _passive_char_40 = (_passive_char_40) + (1);

}

 /* print_passive_and_active_string declared at line 146 */
void
_print_passive_and_active_string_78 ()
{
  int _i_80;

  {				// code for block at line 148
    for (_i_80 = 1;
	 (_i_80 - ((_passive_char_40) - (1))) * sign ((double) 1) <= 0;
	 _i_80 += 1)
      raw_out (1, _passive_string_40[1 - 1][_i_80 - 1]);
    outstring (1, "<<<>>>");
    for (_i_80 = (_active_char_40) + (1);
	 (_i_80 - (_end_of_active_string_41 ())) * sign ((double) 1) <= 0;
	 _i_80 += 1)
      raw_out (1, _active_string_40[_i_80 - 1]);
    newline (1);
  }

}
jmp_buf _Trac_restart_85;
int _i_85;			/* i declared at line 196 */
int _ch_85;			/* ch declared at line 197 */
 /* __for_body_0 declared at line 0 */
void
___for_body_0_86 ()
{
  _ch_85 = _passive_string_40[1 - 1][_i_85 - 1];
  raw_out (1, _ch_85);

}


// The main program
int
main ()
{
  char *LP = (char *) NULL;

  {				// code for block at line 2

    {				// code for block at line 196
      if (setjmp (_Trac_restart_85))
	goto L_Trac_restart_85;
      _Trac_Sharp_Sign_40 = 35;
      _LPAR_40 = 40;
      _RPAR_40 = 41;
      _FN_START_40 = 91;
      _FN_END_40 = 93;
    L_Trac_start_85:_announce_58 ("Trac version 0.1");
      _set_up_data_structures_60 ();
      _read_config_62 ("trac_config");
      _read_user_defined_functions_64 (_Trac_restart_85);
    L_Trac_restart_85:_init_active_and_passive_string_43 ();
    L_Eval_loop_85:_eval_active_till_call_66 (_Trac_restart_85);
      outstring (1, "Ready to evaluate a function\n");
      _ch_85 = 0;
      _i_85 = _last_open_40;
      ___for_body_0_86 ();
      _i_85 = (_i_85) + (1);
      while ((int) (((_ch_85) != (44)) && ((_ch_85) != (_FN_END_40))))
	{
	  ___for_body_0_86 ();
	  _i_85 = (_i_85) + (1);
	}
      newline (1);
      if (_is_built_in_54 ())
	_eval_built_in_50 (_Trac_restart_85);

      else
	_eval_user_defined_52 (_Trac_restart_85);
      goto L_Eval_loop_85;
    }
  }
}

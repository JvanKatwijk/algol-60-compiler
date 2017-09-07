#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: trac.alg		*/
/* Compiled at Fri Jun  4 08:22:38 2004		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	void newline (int); /* newline declared at line 24*/
extern	void outstring (int,char	*); /* outstring declared at line 26*/
extern	void raw_out (int,int); /* raw_out declared at line 60*/
extern int _Trac_Sharp_Sign_40; /* Trac_Sharp_Sign declared at line 2*/
extern int _LPAR_40; /* LPAR declared at line 3*/
extern int _RPAR_40; /* RPAR declared at line 4*/
extern int _FN_START_40; /* FN_START declared at line 5*/
extern int _FN_END_40; /* FN_END declared at line 5*/
extern int _last_open_40; /* last_open declared at line 7*/
extern int _active_string_40 []; // 
extern int _passive_string_40 [ ][]; // 
extern int _active_char_40; /* active_char declared at line 12*/
extern int _passive_char_40; /* passive_char declared at line 13*/
extern	int _end_of_active_string_41 (); /* end_of_active_string declared at line 15*/
extern	void _init_active_and_passive_string_43 (); /* init_active_and_passive_string declared at line 18*/
extern	void _add_to_active_string_46 (int); /* add_to_active_string declared at line 20*/
extern	void _move_to_passive_string_48 (int,jmp_buf *); /* move_to_passive_string declared at line 42*/
extern	void _eval_built_in_50 (jmp_buf *); /* eval_built_in declared at line 49*/
extern	void _eval_user_defined_52 (jmp_buf *); /* eval_user_defined declared at line 50*/
extern	char _is_built_in_54 (); /* is_built_in declared at line 51*/
extern	int _get_char_from_active_string_56 (jmp_buf *); /* get_char_from_active_string declared at line 52*/
extern	void _announce_58 (char	*); /* announce declared at line 61*/
extern	void _set_up_data_structures_60 (); /* set_up_data_structures declared at line 66*/
extern	void _read_config_62 (char	*); /* read_config declared at line 68*/
extern	void _read_user_defined_functions_64 (jmp_buf *); /* read_user_defined_functions declared at line 70*/
extern	void _eval_active_till_call_66 (jmp_buf *); /* eval_active_till_call declared at line 72*/
struct ___eval_active_till_call_66_rec {
char *__l_field;
jmp_buf * l;
char _no_function_yet_68; /* no_function_yet declared at line 74*/
int _dummy_68; /* dummy declared at line 75*/
int _ch_84; /* ch declared at line 162*/
};
extern	void _process_protected_string_69 (struct ___eval_active_till_call_66_rec	*,jmp_buf *); /* process_protected_string declared at line 77*/
struct ___process_protected_string_69_rec {
struct ___eval_active_till_call_66_rec	*__l_field;
jmp_buf * l;
int _par_count_71; /* par_count declared at line 79*/
int _char_71; /* char declared at line 79*/
};
extern	void _process_sharp_sign_73 (jmp_buf *); /* process_sharp_sign declared at line 102*/
extern	void _add_open_function_to_passive_string_76 (); /* add_open_function_to_passive_string declared at line 105*/
extern	void _print_passive_and_active_string_78 (); /* print_passive_and_active_string declared at line 146*/
extern	jmp_buf _Trac_restart_85; /* Trac_restart declared at line 209*/
extern int _i_85; /* i declared at line 196*/
extern int _ch_85; /* ch declared at line 197*/
extern	void ___for_body_0_86 (); /* __for_body_0 declared at line 0*/

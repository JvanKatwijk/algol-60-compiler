#
//
//	jff_a2c
//	a simple translator from Algol 60 to plain C
//	just for fun, but with educational value
//
//	Version 2.1
//	Copyright:
//	Jan van Katwijk
//	TU Delft
//	The Netherlands
//	July 2002
//
//
//
// frontend.h Definitions and prototypes for frontend.c and jff-algol.c
//
// Copyright (C) 2002, 2003 J. van Katwijk
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, you can either send email to this
// program's maintainer or write to: The Free Software Foundation,
// Inc.; 59 Temple Place, Suite 330; Boston, MA 02111-1307, USA.
//	date of last modification: august 2003
//
//
#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#

//typedef char * treenode;
struct  flub {
   struct flub *f;
};
typedef struct flub  treenode;

struct string_element {
	struct string_element *left, *right;
	char string_value [1];
};

#define	TRUE	1
#define	FALSE	0
/*
 *	Symbol definitions
 */
#define	S_CPROC		2
#define S_ARRAY		3
#define S_BOOL		5
#define S_DO		6
#define S_END		7
#define S_ELSE		8
#define S_EXTERNAL	10
#define S_FOR		11
#define S_FALSE		12
#define S_GOTO		13
#define	S_GO		14
#define	S_TO		15
#define S_IF		17
#define S_INT		18
#define S_IDIV		19
#define S_LABEL		20
#define S_NOT		21
#define S_PROC		23
#define S_REAL		24
#define S_STEP		25
#define S_SWITCH	26
#define S_STRING	27
#define S_THEN		28
#define S_TRUE		29
#define S_UNTIL		30
#define S_VALUE		31
//#define S_VIRTUAL	32
#define S_WHILE		33
#define S_EOF		34
#define S_COMMENT	35
#define	S_BEGIN		36
#define	S_OWN		37
#define	S_SEMI		39
#define	S_COMMA		40
#define	S_IDENT		41
#define	S_LPAR		42
#define	S_RPAR		43
#define S_SUB		44
#define	S_BUS		45
#define S_ASSIGN	54
#define	S_ERROR		-1
#define	S_COLON		61
#define S_INUMBER	62
#define	S_RNUMBER	63
#define	S_OPERATOR	67
#define	S_STRINGC	69
#define	S_BASICTYPE	70
#define	MAX_IDENT_SIZE	255
#define	MAX_STRING_SIZE	255
#define MAX_NUMBER_SIZE	255

//
//	for the namelist
//
#define	SEGMENT_SIZE	255
#define	NO_OF_ENTRIES	100000*SEGMENT_SIZE

//	the node types
#define	C_DECLARATION	1
#define	ARRAY_TYPE	2
#define	PROC_TYPE	3
#define LABEL_TYPE	4
#define	ANY_TYPE	5
#define	STRING_TYPE	6
#define	ERROR_TYPE	7
#define BIN_PARAM	8
#define BINOP		9
#define UNPARAM		10
#define UNOP		11
#define	BOUNDS		12
#define IF_STAT		13
#define ASSIGNMENT	14
#define GOTO_STAT	15
#define NULL_STAT	16
#define FOR_STAT	17
#define	BINARY_EXPRESSION	18
#define UNARY_EXPRESSION	19
#define	INUMBER			20
#define	FNUMBER			21
#define	BNUMBER			22
#define	STRING_CONSTANT		23
#define ID_AS_PRIM		24
#define	ACT_PAR			25
#define	FUNCTION_CALL		26
#define INDEXING		27
#define CONDITIONAL		28
#define THUNK			29
#define VARIABLE		30
#define LABEL_DECL		31
#define PARAM_DECL		32
#define	PROC_DECL		33
#define BLOCK			34
#define COMPOUND		35
#define SUBTYPE			36
#define SINGLE_FOR_ELEMENT	37
#define	WHILE_ELEMENT		38
#define STEP_UNTIL		39
#define	FOR_STATEMENT		40
#define SWITCH_DECL		41
#define	SIMPLE_TYPE		42

#define	MAX_ERRORS	50
/*
 * The scanner defines
 */
struct symbol {int sym_value;
               char *sym_rep;
               int lineno;
               int charno;
              };

extern	int		print_prelude;
extern	int		print_trace;
extern	int		delete_files;
extern	int		scanner_trace;
extern	treenode	*int_type;
extern	treenode	*real_type;
extern	treenode	*bool_type;
extern	treenode	*void_type;
extern	treenode	*any_type;
extern	treenode	*string_type;
extern	treenode	*lab_type;
extern	treenode	*error_type;
extern	int		max_prio;
extern	int		errors;
extern	int		sem_errors;

#define	IS_CONSTANT		01
#define	PARAMETER_NEEDS_THUNKS	02
#define	NEED_DEALLOCATION	04
#define	IS_ACCESSED		010
#define	FAR_ACCESS		020
#define	NEED_STATIC_LINK	040
#define	IS_ELABORATED		0100
#define	C_PROC			0200
#define	IS_ASSIGNED_TO		0400
#define	IS_ERROR		01000
#define	IS_VALUE		02000
#define	PROC_AS_PARAMETER	04000
#define	SUBTYPE_NEEDS_DESCRIPTOR	04000
#define	STATEMENT_HAS_LABEL		010000
#define	STATIC_ARRAY			020000
#define	IS_OWN				040000
#define	IS_DEFINED			0100000
#define	PROC_NEEDS_AR			0200000

extern	int	program_needs_deallocation;

#define	ASSERT(x, y)	if (!x) { fprintf (stderr, y); abort (); }

#define	DOPE_BASE	2
extern	FILE	*f_out;
extern	char	*current_file;

#define	symbol_value(x)		(x -> sym_value)
#define	symbol_repr(x)		(x -> sym_rep)
#define	symbol_lineno(x)	(x -> lineno)
#define	symbol_charno(x)	(x -> charno)

struct glob_list {
	treenode *first, *last;
};

#define	set_first_in_globals(x, y)	x -> first = y
#define	get_first_in_globals(x)		x -> first
#define	set_last_in_globals(x, y)	x -> last = y
#define	get_last_in_globals(x)		x -> last

extern	struct glob_list	*globals;
//	functions and constants
//
//	all functions defined in the file compiler.c are specified
//	here
//
//	First functions for the read_prelude operation
//
void	compile (char *src_name);
//
//	functions for prelude manipulation
//
treenode *read_type  (struct symbol *);
treenode *read_types (struct symbol *);
treenode *get_type (char *);
treenode *get_internal_type (char *);
treenode *get_arraytype (treenode *);
treenode *get_proctype (treenode *);
treenode *get_labeltype ();
treenode *read_bin_param  (struct symbol *);
treenode *read_bin_params (struct symbol *);
treenode *read_binary (struct symbol *);
treenode *read_binaries (struct symbol *);
treenode *get_binoperator (int, char *);
treenode *get_bdef (treenode *, treenode *, treenode *);
treenode *read_un_param  (struct symbol *);
treenode *read_un_params (struct symbol *);
treenode *read_unary (struct symbol *);
treenode *read_unaries (struct symbol *);
treenode *get_unoperator (int, char *);
treenode *get_udef (treenode *, treenode *);
void	read_prelude (struct symbol *);
//
//	functions for the scanner
//
void	get_char ();
int	is_blank (int ch);
void	get_nonblank ();
void	get_scannerchar ();
int	convert_to_ivalue (char *);
char	*convert_char_to_int (char);
int	Is_Letter (char);
int	Is_Digit (char);
int	Is_Octal_Digit (char);
void	add_keyword (int, char *);
void	init_keywords ();
int	equal_string (char *, char *);
int	Lookup (char *);
int	length (char *);
int	compare (char *, struct string_element *);
struct string_element *init_element (char *);
char	*store_in_tree (char *);
char	*Read_Identifier ();
int	Read_Stropped (char **);
char	*Read_String ();
int	Read_Number (char **);
char	Read_Octal ();
char	Read_Escaped_Char ();
void	next_algol_token (struct symbol *);
int	ends_comment_after_end (int);
void	peek_ahead (struct symbol **);
void	next_symbol (struct symbol *);
void	init_scanner (char *);
void	skip_until (int, struct symbol *);
int	check_for (int, int, struct symbol *);
//
//	parser functions
//
treenode *parse_primary (struct symbol *);
treenode *parse_expression (int, struct symbol *);
int	starts_decl (struct symbol *);
void	parse_switch_declaration (treenode *, treenode *, struct symbol *);
void	parse_simdecl (treenode *, treenode *, struct symbol *, int);
void	parse_simdecls (treenode *, treenode *, struct symbol *, int);
treenode *parse_bounds (struct symbol *);
void	parse_array_ident  (treenode *, treenode *st, struct symbol *, int);
void	parse_array_identifiers (treenode *, treenode *st, struct symbol * s, int);
void	parse_arraydecl (treenode *, treenode *el_type, struct symbol *, int);
void	parse_arraydecls (treenode *, treenode *, struct symbol *, int);
void	parse_value_ids (treenode *, struct symbol *);
void	parse_value_id  (treenode *, struct symbol *);
int	param_separator (struct symbol *);
void	parse_params (treenode *, struct symbol *);
void	parse_param  (treenode *, struct symbol *);
void	parse_parspec (treenode *, treenode* , struct symbol *);
void	parse_parspecs (treenode *, treenode *, struct symbol *);
void	parse_param_spec (treenode *, struct symbol *);
void	parse_param_specs (treenode *, struct symbol *);
void	parse_procdecl (treenode *, treenode *, struct symbol *, int);
int	parse_decl (treenode *, struct symbol *, int);
void	parse_non_own_declaration (treenode *, struct symbol *, int, int);
void	parse_decls (treenode *, struct symbol *, int);
void	parse_stats (treenode *, treenode *,  struct symbol *);
treenode *parse_expressionlist (struct symbol *);
treenode *parse_actpar (struct symbol *);
treenode *parse_actparlist (struct symbol *);
treenode *parse_assignmentrhs (struct symbol *);
treenode *parse_id_as_stat (treenode *, treenode *, struct symbol *);
treenode *parse_stat (treenode *, treenode *, struct symbol *);
treenode *parse_goto (treenode *, treenode *, struct symbol *);
treenode *parse_block_or_compound (treenode *, treenode *, struct symbol *);
treenode *parse_if_stat (treenode *, treenode *, struct symbol *);
treenode *parse_for_stat (treenode *, treenode *, struct symbol *);
treenode *parse_step_element (treenode *, treenode *, struct symbol *);
treenode *parse_while_element (treenode *, treenode *, struct symbol *);
treenode *parse_forelement (treenode *, struct symbol *);
treenode *parse_forelements (treenode *, struct symbol *);
void	syn_error (struct symbol *, char *, char *, char *);
//
//	analyse
//
void	analyse			(treenode *, treenode *);
void	analyse_switch		(treenode *, treenode *);
void	analyse_labdecl		(treenode *, treenode *);
void	analyse_procdecl	(treenode *, treenode *);
void	analyse_bounds		(treenode *, treenode *);
void	analyse_subtype	 	(treenode *, treenode *);
void	analyse_vardecl		(treenode *, treenode *);
treenode *analyse_id_as_lhs 	(treenode *, treenode *);
treenode *analyse_indexing_as_lhs (treenode *, treenode *);
treenode *analyse_lhs		(treenode *, treenode *);
void	analyse_assignment 	(treenode *, treenode *);
void	analyse_functioncall 	(treenode *, treenode *, treenode *, int);
void	analyse_parameters 	(treenode *, treenode *, treenode *, int);
void	analyse_unspecified_actuals (treenode *, treenode *, treenode *, int);
void	actual_is_thunk (treenode *, treenode *, treenode *, int);
void	actual_is_array_id (treenode *, treenode *, treenode *, treenode *, int);
void	actual_is_string_id (treenode *, treenode *, treenode *, treenode *, int);
void	actual_is_just_param_to_be_passed (treenode *, treenode *, treenode *, treenode *, int);
void	actual_is_function_id (treenode *, treenode *, treenode *, treenode *, int);
void	actual_is_plain_id (treenode *, treenode *, treenode *, treenode *, int);
void	analyse_actual_parameter (treenode *, treenode *, treenode *, treenode *, int);
void	analyse_forelement	(treenode *, treenode *, treenode *);
void	analyse_forstat		(treenode *, treenode *);
void	analyse_expressions 	(treenode *, treenode *, treenode *, int);
void	analyse_constant 	(char *, treenode *, treenode *, treenode *);
void	analyse_id_as_prim 	(treenode *, treenode *, treenode *, int);
void	analyse_indexing	(treenode *, treenode *, treenode *, int);
void	match_with_indices	(treenode *, treenode *, treenode *, int);
void	analyse_conditional	(treenode *, treenode *, treenode *, int);
void	analyse_unary_expression (treenode *, treenode *, treenode *, int);
void	analyse_binary_expression (treenode *, treenode *, treenode *, int);
void	analyse_expression (treenode *, treenode *, treenode *, int);
treenode *look_for_good_entity (treenode *, char *, treenode *);
void	sem_error (int, char *, char *, char *);
//
//		back end				
//
void	generate_kop		(FILE *, char *, char *, char *);
void	generate_headers	(treenode *);
void	generate_switch_spec	(treenode *);
void	generate_lab_spec 	(treenode *);
void	generate_subtype_spec	(treenode *);
void	generate_proc_spec	(treenode *);
void	generate_c_spec		(treenode *);
void	generate_spec_for_c_type_proc (treenode *);
void	generate_spec_for_jff_type_proc (treenode *);
void	generate_envelope_spec	(treenode *);
void	generate_envelope	(treenode *);
void	transfer_code		(treenode *, treenode *, int);
void	generate_thunk_spec	(treenode *);
void	parameter_specs		(treenode *);
void	parameter_spec		(treenode *);
void	generate_par_fields	(treenode *);
void	parameter_field		(treenode *);
void	generate_local_fields	(treenode *);
void	parameter_decls		(treenode *);
void	parameter_decl		(treenode *);
void	init_activation_record	(treenode *);
void	init_parameter_in_ar	(treenode *, treenode *);
void	generate_var_spec	(treenode *);
void	generate_var_decl	(treenode *, treenode *);
void	generate_elab_code	(treenode *, treenode *);
void	generate_proc_code	(treenode *);
void	generate_body_for_jff_proc (treenode *);
void	generate_body_for_c_proc (treenode *);
void	generate_local_declarations (treenode *);
void	generate_thunk_code	(treenode *);
void	generate_body_for_address_thunk (treenode *);
void	generate_body_for_value_thunk (treenode *);
void	generate_switch_decl	(treenode *);
void	generate_subtype_decl	(treenode *);
void	generate_lab_decl	(treenode *);
void	generate_declaration_code (treenode *, treenode *);
void	generate_var_elab	(treenode *, treenode *);
void	generate_subtype_elab	(treenode *, treenode *);
void	code_for_block_body	(treenode *, treenode *);
void	statement_code		(treenode *, treenode *);
void	generate_if_stat	(treenode *, treenode *);
void	code_for_expression	(treenode *, treenode *, treenode *);
void	generate_call		(treenode *, treenode *, treenode *, int);
void	call_to_formal		(treenode *, treenode *, treenode *, int);
void	pr_data_for_hard_param	(char, char);
void	hard_parameter		(treenode *, treenode *, int);
void	hard_param_is_parameter (treenode *, treenode *, int);
void	call_to_regular_proc	(treenode *, treenode *, treenode *);
void	code_for_actual		(treenode *, treenode *, treenode *);
void	code_for_function_as_actual (treenode *, treenode *);
void	code_for_array_as_actual (treenode *, treenode *, treenode *);
void	code_for_switch_as_actual (treenode *, treenode *, treenode *);
void	code_for_string_as_actual (treenode *, treenode *, treenode *);
void	thunk_or_function_as_actual (treenode *, treenode *, treenode *);
void	assign_to_simple	(treenode *, treenode *, treenode *);
void	increment_simple	(treenode *, treenode *, treenode *);
void	assign_to_indexed	(treenode *, treenode *, treenode *);
void	increment_indexed	(treenode *, treenode *, treenode *);
void	assignment_code		(treenode *, treenode *, treenode *);
void	increment_code		(treenode *, treenode *, treenode *);
void	generate_block_code	(treenode *, treenode *);
void	call_value_thunk	(treenode *, treenode *);
void	code_for_id_as_prim	(treenode *, treenode *);
void	code_for_indexed_switch (treenode *, treenode *, treenode *);
void	code_for_indexed_static (treenode *, treenode *, treenode *);
void	code_for_indexed_dynamic (treenode *, treenode *, treenode *);
void	code_for_indexed_value	(treenode *, treenode *);
treenode *get_lb		(treenode *, int);
void	ith_lower_bound		(treenode *, int, treenode *);
void	generate_for_stat	(treenode *, treenode *);
void	generate_for_element	(treenode *, treenode *, treenode *, treenode *);
void	generate_single_fe	(treenode *, treenode *, treenode *, treenode *);
void	generate_while_fe	(treenode *, treenode *, treenode *, treenode *);
void	generate_step_until_fe	(treenode *, treenode *, treenode *, treenode *);
void	generate_goto		(treenode *, treenode *);
void	code_for_unary_expression (treenode *, treenode *);
void	code_for_binary_expression (treenode *, treenode *);
void	link_statement		(treenode *, treenode *);
void	link_declaration	(treenode *, treenode *);
void	link_in_front_to	(treenode *, treenode *);
void	link_to_globals		(treenode *);
void	link_to_environmental_proc (treenode *);
char	*type_name		(treenode *);
char	*c_type_name		(treenode *);
char	*op_name		(treenode *);
void	set_access		(treenode *, treenode *, int);
treenode *get_environmental_proc (treenode *);
int	get_dimensions		(treenode *);
int	in_scope		(treenode *, treenode *);
int	proc_level_of		(treenode *);
int	is_compatible		(treenode *, treenode *);
char	*c_nameof		(treenode *);
treenode *create_thunk		(treenode *, treenode *, treenode *);
treenode *thunk_as_param	(treenode *);
int	block_of		(treenode *);
void	pr_access_to_simple_entity (treenode *, treenode *);
void	pr_name_of_formal_string (treenode *, treenode *);
void	pr_address_of_switch	(treenode *, treenode *);
void	pr_address_of_formal_switch (treenode *, treenode *);
void	pr_link_for_switch (treenode *, treenode *);
void	pr_link_of_formal_switch (treenode *, treenode *);
void	pr_x_descriptor (treenode *, treenode *, int);
void	pr_name_of_descriptor    (treenode *, treenode *);
void	pr_address_of_descriptor (treenode *, treenode *);
void	pr_name_of_array	(treenode *, treenode *);
void	pr_link_for_formal_proc (treenode *, treenode *);
void	pr_address_of_formal_proc (treenode *, treenode *);
void	pr_address_of_regular_proc (treenode *, treenode *);
void	pr_link_to_proc_env (treenode *, treenode *);
void	pr_access_to_label (treenode *, treenode *);
void	pr_address_of_value_thunk (treenode *, treenode *);
void	pr_address_of_address_thunk (treenode *, treenode *);
void	pr_link_to_thunk (treenode *, treenode *);
void	pr_access_to_local_entity (treenode *, treenode *, char *);
treenode *proc_embedded_in_to	(treenode *, treenode *);
void	pr_link_x		(treenode *, treenode *);
void	pr_link			(treenode *, treenode *);
void	pr_type_of_ar		(treenode *);
void	pr_declaration_comment	(treenode *);
int	count_entities		(treenode *);
char	*new_for_id		(treenode *);
treenode *make_proc_call	(treenode *, treenode *);
treenode *result_type		(treenode *);
treenode *type_of		(treenode *);
treenode *element_type		(treenode *);
int	is_single_statement	(treenode *);
void	set_own			(treenode *);
int	is_own			(treenode *);
void	set_needs_deallocation	(treenode *);
int	needs_deallocation	(treenode *);
void	set_array_as_parameter	(treenode *);
void	set_subtype_needs_descriptor (treenode *);
int	subtype_needs_descriptor (treenode *);
int	is_defined		(treenode *);
void	set_defined		(treenode *);
int	is_valid_value_param	(treenode *);
void	set_static_array	(treenode *);
int	is_static_array		(treenode *);
int	can_be_assigned_to	(treenode *);
int	type_of_entity_is_simple (treenode *);
int	is_parameter		(treenode *);
int	is_arithmetic_array	(treenode *);
int	is_switch		(treenode *);
int	has_a_proc_type		(treenode *);
int	is_a_proc_decl		(treenode *);
int	has_label_type		(treenode *);
int	has_string_type		(treenode *);
int	is_specified_as_value	(treenode *);
void	set_specified_as_value	(treenode *);
void	set_statement_has_label (treenode *);
int	has_statement_label	(treenode *);
void	set_proc_as_parameter	(treenode *);
int	is_proc_as_parameter	(treenode *);
int	is_accessed		(treenode *);
void	set_accessed		(treenode *);
void	set_constant_expression	(treenode *);
void	set_assigned		(treenode *);
int	is_assigned_to		(treenode *);
int	is_constant_expression	(treenode *);
int	is_elaborated 		(treenode *);
void	set_elaborated		(treenode *);
void	set_error		(treenode *);
int	is_erroneous		(treenode *);
int	is_cproc		(treenode *);
int	need_static_link	(treenode *);
void	set_need_static_link	(treenode *);
void	set_needs_ar		(treenode *);
int	will_be_compiled_as_c_proc (treenode *);
int	has_far_access		(treenode *);
void	set_far_access		(treenode *);
int	matching_param_type	(treenode *, treenode *);
int	formal_requires_thunk	(treenode *);
void	add_to_output		(char *);
char	*num_to_string		(int);
char	*char_to_string		(char);
//
//	namelist defines
//
void	init_nametables		();
int	create_scope		(treenode *);
void	leave_scope		();
void	add_entry		(treenode *, char *);
treenode *find_in_scope		(int, char *);
treenode *find_definition	(int, char *);
void	put_in_forgotten_list	(int, char *);
int	in_forgotten_list	(int, char *);


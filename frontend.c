#
//
//	jff_a2c
//	a simple translator from Algol 60 to plain C
//	just for fun, but with educational value
//
//	This file contains the complete front end source.
//
//	This front end translates an ALGOL program 
//	into an equivalent C program and a header file
//	with prototypes.
//	This front end will be called by a driver program
//	passing all required parameters, but can be called separately
//
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
//
//
//
#include	<time.h>
#include	"frontend.h"
#include	<string.h>

#ifndef VERSION
#define VERSION "2.4"
#endif

char	*compile_time	= "no time specified";
char	*infile		= NULL;
char	*c_file		= NULL;
char	*include_file	= NULL;
char	*header_file	= HEADER;
char	*op_file	= OPERATOR_E;
char	*prelude	= PRELUDE_E;

int	languageFlag	= 0;

FILE	*f_out;
int	errors		= 0;
int	sem_errors	= 0;
struct glob_list aa;
struct glob_list	*globals = &aa;
struct symbol s;
void	compile (char *);

int main (int argc, char **argv) {
int	i;
	for (i = 1; i < argc; i ++) {
	   if (argv [i][0] == '-') {	// it is an option
	      switch (argv [i][1]) {
	         case 'c': 	c_file = argv [i + 1]; i ++;
	                        break;

	         case 'F':	languageFlag = atoi (argv [i + 1]); i ++;
	                        break;

	         case 'f':	include_file = argv [i + 1]; i ++;
	                        break;

		 case 'o':	op_file = argv [i + 1]; i ++;
				break;

	         case 'p':	prelude = argv [i + 1]; i ++;
	                        break;

	         case 'h':	header_file = argv [i + 1]; i ++;
	                        break;

	         case 't':	compile_time = argv [i + 1]; i ++;
	                        break;

	         default:	break;
	      }
	   }
	   else {
	      // it is the name of the file to be compiled
	      infile = argv [i];
	   }
	}
	if (infile == (char *)0) {
	   fprintf (stderr, "No input file given\n");
	   exit (EXIT_FAILURE);
	}
	compile (infile);
	exit (EXIT_SUCCESS);
}


//	tree handling
//	in this version of jff-a2c, we made a stupid tree 
//	in an array like fashion.
//	reason: I want to be able to translate this into
//	algol itself

//class treenode {
//public:
//   int nodeid;
//   treenode *nextnode;
//   int line_no, char_no;
//   unsigned int node_flag;
//};

#define	NODEID		0
#define	NEXTNODE	1
#define	LINE_NO		2
#define	CHAR_NO		3
#define	NODE_FLAGS	4

int	get_nodeid (treenode *t) {
	return  (int)(t [NODEID]. f);
}

treenode *get_nextnode (treenode *t) {
	return  (treenode *)(t [NEXTNODE]. f);
}

void	set_nextnode (treenode *x, treenode *y) {
	x [NEXTNODE]. f = y;
}

int	get_lineno (treenode *t) {
	return (int)(t [LINE_NO]. f);
}

void	set_lineno (treenode *t, int l) {
	t [LINE_NO]. f = (treenode *)l;
}

int	get_charno (treenode *t) {
	return (int)(t [CHAR_NO]. f);
}

void	set_charno (treenode *t, int cn) {
	t [CHAR_NO]. f = (treenode *)cn;
}

unsigned int get_flags (treenode *t) {
	return (unsigned int)(t [NODE_FLAGS]. f);
}

void	set_flags (treenode *t, unsigned int f) {
	t [NODE_FLAGS]. f = (treenode *)f;
}


//class declaration: public treenode {
//public:
//	char		*decl_ident;
//	treenode 	*decl_env;
//	treenode	*next_dec;
//	char		*c_name;
//};

#define	DECL_IDENT	NODE_FLAGS+1
#define	DECL_ENV	NODE_FLAGS+2
#define NEXT_DEC	NODE_FLAGS+3
#define	C_NAME		NODE_FLAGS+4
#define	SIZEOF_DECLARATION	C_NAME+1

//class type_def: public treenode {
//public:
//	char	*type_id;
//	char	*internal_name;
//	char	*c_type;
//};
//
//class	simple_type: public type_def {
//public:
//};
//
//
//class label_type: public type_def {
//public:
//};
//
//class anytype: public type_def {
//public:
//};
//
//class stringtype: public type_def {
//public:
//};
//
//class errortype: public type_def {
//public:
//};

#define	TYPE_ID		NODE_FLAGS+1
#define	INTERNAL_NAME	NODE_FLAGS+2
#define	C_TYPE		NODE_FLAGS+3

#define	SIZEOF_TYPE_DEF		C_TYPE+1
#define	SIZEOF_SIMPLE_TYPE	SIZEOF_TYPE_DEF
#define	SIZEOF_LABEL_TYPE	SIZEOF_TYPE_DEF
#define	SIZEOF_ANY_TYPE		SIZEOF_TYPE_DEF
#define	SIZEOF_STRING_TYPE	SIZEOF_TYPE_DEF
#define	SIZEOF_ERROR_TYPE	SIZEOF_TYPE_DEF

char	*get_decl_ident (treenode *t) {
	return (char *)(t [DECL_IDENT]. f);
}

void	set_decl_ident (treenode *t, char *s) {
	t [DECL_IDENT]. f = (treenode *)s;
}

treenode *get_decl_env (treenode *t) {
	return t [DECL_ENV]. f;
}

void	set_decl_env (treenode *t, treenode *e) {
	t [DECL_ENV]. f = e;
}

treenode *get_next_dec (treenode *t) {
	return t [NEXT_DEC]. f;
}

void	set_next_dec (treenode *t, treenode *n) {
	t [NEXT_DEC]. f = n;
}

char	*get_c_name (treenode *t) {
	return (char *)(t [C_NAME]. f);
}

void	set_c_name (treenode *t, char *s) {
	t [C_NAME]. f = (treenode *)s;
}

char	*get_type_id (treenode *t) {
	return (char *)(t [TYPE_ID]. f);
}

void	set_type_id (treenode *t, char *id) {
	t [TYPE_ID]. f = (treenode *)id;
}

char	*get_internal_name (treenode *t) {
	return (char *)(t [INTERNAL_NAME]. f);
}

void	set_internal_name (treenode *t, char *in) {
	t [INTERNAL_NAME]. f = (treenode *)in;
}

char	*get_c_type (treenode *t) {
	return (char *)(t [C_TYPE]. f);
}

void	set_c_type (treenode *t, char *ct) {
	t [C_TYPE]. f = (treenode *)ct;
}


//class array_type: public type_def {
//public:
//	treenode *element_type;
//};

#define	ELEMENT_TYPE 		C_TYPE+1
#define	SIZEOF_ARRAY_TYPE	ELEMENT_TYPE+1

treenode *get_element_type (treenode *t) {
	return t [ELEMENT_TYPE]. f;
}

void	set_element_type (treenode *t, treenode *et) {
	t [ELEMENT_TYPE]. f = et;
}

//class proc_type: public type_def {
//public:
//	treenode *proctype_returntype;
//};

#define	PROCTYPE_RETURNTYPE C_TYPE+1
#define	SIZEOF_PROC_TYPE	PROCTYPE_RETURNTYPE+1

treenode *get_proctype_returntype (treenode *t) {
	return t [PROCTYPE_RETURNTYPE]. f;
}

void	set_proctype_returntype (treenode *t, treenode *rt) {
	t [PROCTYPE_RETURNTYPE]. f = rt;
}

//class bin_param: public treenode {
//public:
//	treenode *left_operand_for_bin;
//	treenode *right_operand_for_bin;
//	treenode *return_type_for_bin;
//	char * c_string_for_bin;
//};

#define	LEFT_OPERAND_FOR_BIN	NODE_FLAGS+1
#define	RIGHT_OPERAND_FOR_BIN	NODE_FLAGS+2
#define	RETURN_TYPE_FOR_BIN	NODE_FLAGS+3
#define	C_STRING_FOR_BIN	NODE_FLAGS+4
#define	SIZEOF_BINPARAM		C_STRING_FOR_BIN+1

treenode *get_left_operand_for_bin (treenode *t) {
	return t [LEFT_OPERAND_FOR_BIN]. f;
}

void	set_left_operand_for_bin (treenode *t, treenode *lo) {
	t [LEFT_OPERAND_FOR_BIN]. f = lo;
}

treenode *get_right_operand_for_bin (treenode *t) {
	return t [RIGHT_OPERAND_FOR_BIN]. f;
}

void	set_right_operand_for_bin (treenode *t, treenode *ro) {
	t [RIGHT_OPERAND_FOR_BIN]. f = ro;
}

treenode *get_return_type_for_bin (treenode *t) {
	return t [RETURN_TYPE_FOR_BIN]. f;
}

void	set_return_type_for_bin (treenode *t, treenode *rt) {
	t [RETURN_TYPE_FOR_BIN]. f = rt;
}

char	*get_c_string_for_bin (treenode *t) {
	return (char *)(t [C_STRING_FOR_BIN]. f);
}

void	set_c_string_for_bin (treenode *t, char *cs) {
	t [C_STRING_FOR_BIN]. f = (treenode *)cs;
}

//class binop: public treenode {
//public:
//	char	*opsym_for_bin;
//	int	binary_prio;
//	treenode *binary_params;
//};

#define	OPSYM_FOR_BIN	NODE_FLAGS+1
#define	BINARY_PRIO	NODE_FLAGS+2
#define	BINARY_PARAMS	NODE_FLAGS+3
#define	SIZEOF_BINOP	BINARY_PARAMS+1

char	*get_opsym_for_bin (treenode *t) {
	return (char *)(t [OPSYM_FOR_BIN]. f);
}

void	set_opsym_for_bin (treenode *t, char *op) {
	t [OPSYM_FOR_BIN]. f = (treenode *)op;
}

int	get_binary_prio (treenode *t) {
	return (int)(t [BINARY_PRIO]. f);
}

void	set_binary_prio (treenode *t, int prio) {
	t [BINARY_PRIO]. f = (treenode *)prio;
}

treenode *get_binary_params (treenode *t) {
	return t [BINARY_PARAMS]. f;
}

void	set_binary_params (treenode *t, treenode *par) {
	t [BINARY_PARAMS]. f = par;
}

//class un_param: public treenode {
//public:
//	treenode *left_for_un;
//	treenode *return_type_for_un;
//	char	*c_string_for_un;
//};

#define	LEFT_FOR_UN		NODE_FLAGS+1
#define	RETURN_TYPE_FOR_UN	NODE_FLAGS+2
#define	C_STRING_FOR_UN		NODE_FLAGS+3
#define	SIZEOF_UNPARAM		C_STRING_FOR_UN+1

treenode *get_left_for_un (treenode *t) {
	return t [LEFT_FOR_UN]. f;
}

treenode set_left_for_un (treenode *t, treenode *left) {
	t [LEFT_FOR_UN]. f = left;
}

treenode *get_return_type_for_un (treenode *t) {
	return t [RETURN_TYPE_FOR_UN]. f;
}

void	set_return_type_for_un (treenode *t, treenode *rt) {
	t [RETURN_TYPE_FOR_UN]. f = rt;
}

char	*get_c_string_for_un (treenode *t) {
	return (char *)(t [C_STRING_FOR_UN]. f);
}

void	set_c_string_for_un (treenode *t, char *cs) {
	t [C_STRING_FOR_UN]. f = (treenode *)cs;
}

//class unop: public treenode {
//public:
//	char	*opsym_for_un;
//	int	unary_prio;
//	treenode *unary_params;
//};

#define	OPSYM_FOR_UN	NODE_FLAGS+1
#define	UNARY_PRIO	NODE_FLAGS+2
#define	UNARY_PARAMS	NODE_FLAGS+3
#define	SIZEOF_UNOP	UNARY_PARAMS+1

char	*get_opsym_for_un (treenode *t) {
	return (char *)(t [OPSYM_FOR_UN]. f);
}

void	set_opsym_for_un (treenode *t, char *op) {
	t [OPSYM_FOR_UN]. f = (treenode *)op;
}

int	get_unary_prio (treenode *t) {
	return (int)(t [UNARY_PRIO]. f);
}

void	set_unary_prio (treenode *t, int prio) {
	t [UNARY_PRIO]. f = (treenode *)prio;
}

treenode *get_unary_params (treenode *t) {
	return t [UNARY_PARAMS]. f;
}

void	set_unary_params (treenode *t, treenode *un) {
	t [UNARY_PARAMS]. f = un;
}

//class statement : public treenode {
//public:
//	treenode *label;
//};

#define	LABEL	NODE_FLAGS+1
#define	SIZEOF_STATEMENT	LABEL+1

treenode *get_label (treenode *t) {
	return t [LABEL]. f;
}

void	set_label (treenode *t, treenode *lab) {
	t [LABEL]. f = lab;
}

//class env: public statement {
//public:
//	treenode	*surr;
//	treenode	*statements;
//	treenode	*last_statement;
//};

#define	SURR		LABEL+1
#define	STATEMENTS	LABEL+2
#define	LAST_STATEMENT	LABEL+3
#define	SIZEOF_ENV	LAST_STATEMENT+1

treenode *get_surrounding (treenode *t) {
	return t [SURR]. f;
}

void	set_surrounding (treenode *t, treenode *sur) {
	t [SURR]. f = sur;
}

treenode *get_statements (treenode *t) {
	return t [STATEMENTS]. f;
}

void	set_statements (treenode *t, treenode *st) {
	t [STATEMENTS]. f = st;
}

treenode *get_last_statement (treenode *t) {
	return t [LAST_STATEMENT]. f;
}

void	set_last_statement (treenode *t, treenode *lt) {
	t [LAST_STATEMENT]. f = lt;
}

//class for_element: public treenode {
//public:;
//};

//class expression: public treenode {
//public:
//	treenode *expr_type;
//};

#define	EXPR_TYPE		NODE_FLAGS+1
#define	SIZEOF_EXPRESSION	EXPR_TYPE+1

treenode *get_expr_type (treenode *t) {
	return t [EXPR_TYPE]. f;
}

void	set_expr_type (treenode *t, treenode *typ) {
	t [EXPR_TYPE]. f = typ;
}

//class bounds: public expression {
//public:
//	treenode *first_bound;
//	treenode *second_bound;
//};

#define	FIRST_BOUND	EXPR_TYPE+1
#define	SECOND_BOUND	EXPR_TYPE+2
#define	SIZEOF_BOUNDS	SECOND_BOUND+1

treenode *get_first_bound (treenode *t) {
	return t [FIRST_BOUND]. f;
}

treenode *get_second_bound (treenode *t) {
	return t [SECOND_BOUND]. f;
}

void	set_first_bound (treenode *t, treenode *fb) {
	t [FIRST_BOUND]. f = fb;
}

void	set_second_bound (treenode *t, treenode *sb) {
	t [SECOND_BOUND]. f = sb;
}

//class if_stat: public statement {
//public:
//	treenode	*ifcondition;
//	treenode	*ifthenpart;
//	treenode	*ifelsepart;
//};

#define	IFCONDITION	LABEL+1
#define	IFTHENPART	LABEL+2
#define	IFELSEPART	LABEL+3
#define	SIZEOF_IF_STAT	IFELSEPART+1

treenode *get_ifcondition (treenode *t) {
	return t [IFCONDITION]. f;
}

treenode *get_ifthenpart (treenode *t) {
	return t [IFTHENPART]. f;
}

treenode *get_ifelsepart (treenode *t) {
	return t [IFELSEPART]. f;
}
void	set_ifcondition (treenode *t, treenode *ifc) {
	t [IFCONDITION]. f = ifc;
}

void	set_ifthenpart (treenode *t, treenode *ift) {
	t [IFTHENPART]. f = ift;
}

void	set_ifelsepart (treenode *t, treenode *ife){
	t [IFELSEPART]. f = ife;
}

//class assignment: public statement {
//public:
//	treenode *lhs_expression;
//	treenode *rhs_expression;
//};

#define LHS_EXPRESSION	LABEL+1
#define	RHS_EXPRESSION	LABEL+2
#define	SIZEOF_ASSIGNMENT	RHS_EXPRESSION+1

treenode *get_lhs_expression (treenode *t) {
	return t [LHS_EXPRESSION]. f;
}

void	set_lhs_expression (treenode *t, treenode *lhs) {
	t [LHS_EXPRESSION]. f = lhs;
}

treenode *get_rhs_expression (treenode *t) {
	return t [RHS_EXPRESSION]. f;
}

void	set_rhs_expression (treenode *t, treenode *rhs) {
	t [RHS_EXPRESSION]. f = rhs;
}

//class goto_stat: public statement {
//public:
//	treenode	*goto_target;
//};

#define	GOTO_TARGET	LABEL+1
#define	SIZEOF_GOTO_STAT	GOTO_TARGET+1

treenode *get_target (treenode *t) {
	return t [GOTO_TARGET]. f;
}

void	set_target (treenode *t, treenode *targ) {
	t [GOTO_TARGET]. f = targ;
}

//class null_statement : public statement {
//public:
//};
#define	SIZEOF_NULL_STAT	SIZEOF_STATEMENT

//class for_stat: public statement {
//public:
//;
//};
#define	SIZEOF_FOR_STAT		LABEL+1

//class binary_expression: public expression {
//public:
//	treenode 	*bin_operator;
//	treenode	*binary_left_operand, *binary_right_operand;
//	treenode	*bin_opdef;
//};
//

#define	BIN_OPERATOR		EXPR_TYPE+1
#define	BINARY_LEFT_OPERAND	EXPR_TYPE+2
#define	BINARY_RIGHT_OPERAND	EXPR_TYPE+3
#define	BIN_OPDEF		EXPR_TYPE+4
#define	SIZEOF_BINARY_EXPRESSION	BIN_OPDEF+1

treenode *get_bin_operator (treenode *t) {
	return t [BIN_OPERATOR]. f;
}

void	set_bin_operator (treenode *t, treenode *binop) {
	t [BIN_OPERATOR]. f = binop;
}

treenode *get_binary_left_operand (treenode *t) {
	return t [BINARY_LEFT_OPERAND]. f;
}

void	set_binary_left_operand (treenode *t, treenode *lo) {
	t [BINARY_LEFT_OPERAND]. f = lo;
}

treenode *get_binary_right_operand (treenode *t) {
	return t [BINARY_RIGHT_OPERAND]. f;
}

void	set_binary_right_operand (treenode *t, treenode *ro) {
	t [BINARY_RIGHT_OPERAND]. f = ro;
}

treenode *get_bin_opdef (treenode *t) {
	return t [BIN_OPDEF]. f;
}

void	set_bin_opdef (treenode *t, treenode *opdef) {
	t [BIN_OPDEF]. f = opdef;
}

//class unary_expression: public expression {
//public:
//	treenode	*un_operator;
//	treenode	*un_opdef;
//	treenode	*unary_operand;
//};

#define	UN_OPERATOR	EXPR_TYPE+1
#define	UN_OPDEF	EXPR_TYPE+2
#define	UNARY_OPERAND	EXPR_TYPE+3
#define	SIZEOF_UNARY_EXPRESSION	UNARY_OPERAND+1

treenode *get_un_operator (treenode *t) {
	return t [UN_OPERATOR]. f;
}

void	set_un_operator (treenode *t, treenode *unop) {
	t [UN_OPERATOR]. f = unop;
}

treenode *get_unary_operand (treenode *t) {
	return t [UNARY_OPERAND]. f;
}

void	set_unary_operand (treenode *t, treenode *uo) {
	t [UNARY_OPERAND]. f = uo;
}

treenode *get_un_opdef (treenode *t) {
	return t [UN_OPDEF]. f;
}

void	set_un_opdef (treenode *t, treenode *un) {
	t [UN_OPDEF]. f = un;
}

//class inumber: public expression {
//public:
//	char  *i_value;
//};

//class fnumber: public expression {
//public:
//	char  *f_value;
//};
//
//class bnumber : public expression {
//public:
//	char	*b_value;
//};
//
//class string_constant : public expression {
//public:
//	char	*s_value;
//};

#define	X_VALUE		EXPR_TYPE+1
#define	SIZEOF_NUMBER	X_VALUE+1
char	*get_x_value (treenode *t) {
	return (char *)(t [X_VALUE]. f);
}

void	set_x_value (treenode *t, char *s) {
	t [X_VALUE]. f = (treenode *)s;
}

//class id_as_prim: public expression {
//public:
//	char		*resolve_ident;
//	treenode	*id_def;
//};
#define	RESOLVE_IDENT	EXPR_TYPE+1
#define	ID_DEF		RESOLVE_IDENT+1
#define	SIZEOF_ID_AS_PRIM	ID_DEF+1

char	 *get_resolve_ident (treenode *t) {
	return (char *)(t [RESOLVE_IDENT]. f);
}

void	set_resolve_ident (treenode *t, char *id) {
	t [RESOLVE_IDENT]. f = (treenode *)id;
}

treenode *get_id_def (treenode *t) {
	return t [ID_DEF]. f;
}

void	set_id_def (treenode *t, treenode *def) {
	t [ID_DEF]. f = def;
}

//class act_par: public expression {
//public:
//	treenode	*act_exp;
//};

#define	ACT_EXP		EXPR_TYPE+1
#define	SIZEOF_ACT_PAR	ACT_EXP+1

treenode *get_act_exp (treenode *t) {
	return t [ACT_EXP]. f;
}

void	set_act_exp (treenode *t, treenode *exp) {
	t [ACT_EXP]. f = exp;
}

//class function_call: public expression {
//public:
//	char		*function_ident;
//	treenode	*called_function;
//	treenode	*actuals;
//	int		num_of_actuals;
//};

#define	FUNCTION_IDENT	EXPR_TYPE+1
#define	CALLED_FUNCTION	FUNCTION_IDENT+1
#define	ACTUALS		CALLED_FUNCTION+1
#define	NUM_OF_ACTUALS	ACTUALS+1
#define	SIZEOF_FUNCTION_CALL	NUM_OF_ACTUALS+1

char	*get_function_ident (treenode *t) {
	return (char *)(t [FUNCTION_IDENT]. f);
}

void	set_function_ident (treenode *t, char *id) {
	t [FUNCTION_IDENT]. f = (treenode *)id;
}

treenode *get_called_function (treenode *t) {
	return t [CALLED_FUNCTION]. f;
}

void	set_called_function (treenode *t, treenode *f) {
	t [CALLED_FUNCTION]. f = f;
}

treenode *get_actuals (treenode *t) {
	return t [ACTUALS]. f;
}

void	set_actuals (treenode *t, treenode *a) {
	t [ACTUALS]. f = a;
}

int	get_num_of_actuals (treenode *t) {
	return (int)(t [NUM_OF_ACTUALS]. f);
}

void	set_num_of_actuals (treenode *t, int n) {
	t [NUM_OF_ACTUALS]. f = (treenode *)n;
}

//class indexing: public expression {
//public:
//	char		*array_ident;
//	treenode	*array_def;
//	treenode	*subscripts;
//	int		num_of_subscripts;
//};

#define	ARRAY_IDENT	EXPR_TYPE+1
#define	ARRAY_DEF	ARRAY_IDENT+1
#define	SUBSCRIPTS	ARRAY_DEF+1
#define	NUM_OF_SUBSCRIPTS	SUBSCRIPTS+1
#define	SIZEOF_INDEXING	NUM_OF_SUBSCRIPTS+1

char	*get_array_ident (treenode *t) {
	return (char *)(t [ARRAY_IDENT]. f);
}

void	set_array_ident (treenode *t, char *id) {
	t [ARRAY_IDENT]. f = (treenode *)id;
}

treenode *get_array_def (treenode *t) {
	return t [ARRAY_DEF]. f;
}

void	set_array_def (treenode *t, treenode *def) {
	t [ARRAY_DEF]. f = def;
}

treenode *get_subscripts (treenode *t) {
	return t [SUBSCRIPTS]. f;
}

void	set_subscripts (treenode *t, treenode *subs) {
	t [SUBSCRIPTS]. f = subs;
}

int	get_num_of_subscripts (treenode *t) {
	return (int)(t [NUM_OF_SUBSCRIPTS]. f);
}

void	set_num_of_subscripts (treenode *t, int num) {
	t [NUM_OF_SUBSCRIPTS]. f = (treenode *)num;
}

//class conditional: public expression {
//public:
//	treenode *cond_of_condition;
//	treenode *condition_thenpart;
//	treenode *condition_elsepart;
//};

#define	COND_OF_CONDITION	EXPR_TYPE+1
#define	CONDITION_THENPART	COND_OF_CONDITION+1
#define	CONDITION_ELSEPART	COND_OF_CONDITION+2
#define	SIZEOF_CONDITIONAL	CONDITION_ELSEPART+1

treenode *get_cond_of_condition (treenode *t) {
	return t [COND_OF_CONDITION]. f;
}

void	set_cond_of_condition (treenode *t, treenode *c) {
	t [COND_OF_CONDITION]. f = c;
}

treenode *get_condition_thenpart (treenode *t) {
	return t [CONDITION_THENPART]. f;
}

void	set_condition_thenpart (treenode *t, treenode *tp) {
	t [CONDITION_THENPART]. f = tp;
}

treenode *get_condition_elsepart (treenode *t) {
	return t [CONDITION_ELSEPART]. f;
}

void	set_condition_elsepart (treenode *t, treenode *ep) {
	t [CONDITION_ELSEPART]. f = ep;
}

//class thunk: public declaration {
//public:
//	treenode	*type_of_thunk;
//	treenode	*thunk_expr;
//};

#define	TYPE_OF_THUNK	C_NAME+1
#define	THUNK_EXPR	C_NAME+2
#define	SIZEOF_THUNK	THUNK_EXPR+1

treenode *get_type_of_thunk (treenode *t) {
	return t [TYPE_OF_THUNK]. f;
}

void	set_type_of_thunk (treenode *t, treenode *typ) {
	t [TYPE_OF_THUNK]. f = typ;
}

treenode *get_thunk_expr (treenode *t) {
	return t [THUNK_EXPR]. f;
}

void	set_thunk_expr (treenode *t, treenode *te) {
	t [THUNK_EXPR] .f = te;
}

//class variable: public declaration {
//public:
//	treenode *type_of_var;
//};

#define	TYPE_OF_VAR	C_NAME+1
#define	SIZEOF_VARIABLE	TYPE_OF_VAR+1

treenode *get_type_of_var (treenode *t) {
	return t [TYPE_OF_VAR]. f;
}

void	set_type_of_var (treenode *t, treenode *tt) {
	t [TYPE_OF_VAR]. f = tt;
}

//class label_decl: public declaration {
//public:
//	treenode	*value_of_label;
//};

#define	VALUE_OF_LABEL	C_NAME+1
#define	SIZEOF_LABEL_DECL	VALUE_OF_LABEL+1

treenode *get_value_of_label (treenode *t) {
	return t [VALUE_OF_LABEL]. f;
}

void	set_value_of_label (treenode *t, treenode *v) {
	t [VALUE_OF_LABEL]. f = v;
}

//class param_decl: public declaration {
//public:
//	treenode	*param_type;
//};

#define	PARAM_TYPE	C_NAME+1
#define	SIZEOF_PARAM_DECL	PARAM_TYPE+1

treenode *get_param_type (treenode *t) {
	return t [PARAM_TYPE]. f;
}

void	set_param_type (treenode *t, treenode *pt) {
	t [PARAM_TYPE]. f = pt;
}

//class proc_decl: public declaration {
//public:
//	treenode	*proc_returntype;
//	treenode	*proc_parameters;
//	treenode	*proc_lastpar;
//	treenode	*proc_body;
//	treenode	*first_dec_in_proc;
//	treenode	*last_dec_in_proc;
//	int		blockno_of_proc;
//	int		num_of_pars;
//	int		proc_level;
//};

#define	PROC_RETURNTYPE		C_NAME+1
#define	PROC_PARAMETERS		C_NAME+2
#define	PROC_LASTPAR		C_NAME+3
#define	PROC_BODY		C_NAME+4
#define	FIRST_DEC_IN_PROC	C_NAME+5
#define	LAST_DEC_IN_PROC	C_NAME+6
#define	BLOCKNO_OF_PROC		C_NAME+7
#define	NUM_OF_PARS		C_NAME+8
#define	PROC_LEVEL		NUM_OF_PARS+1
#define	SIZEOF_PROC_DECL	PROC_LEVEL+1

treenode *get_proc_returntype (treenode *t) {
	return t [PROC_RETURNTYPE]. f;
}

void	set_proc_returntype (treenode *t, treenode *type) {
	t [PROC_RETURNTYPE]. f = type;
}

treenode *get_proc_parameters (treenode *t) {
	return t [PROC_PARAMETERS]. f;
}

void	set_proc_parameters (treenode *t, treenode *par) {
	t [PROC_PARAMETERS]. f = par;
}

treenode *get_proc_lastpar (treenode *t) {
	return t [PROC_LASTPAR]. f;
}

void	set_proc_lastpar (treenode *t, treenode *lp) {
	t [PROC_LASTPAR]. f = lp;
}

treenode *get_proc_body (treenode *t) {
	return t [PROC_BODY]. f;
}

void	set_proc_body (treenode *t, treenode *body) {
	t [PROC_BODY]. f = body;
}

treenode *get_first_dec_in_proc (treenode *t) {
	return t [FIRST_DEC_IN_PROC]. f;
}

void	set_first_dec_in_proc (treenode *t, treenode *fd) {
	t [FIRST_DEC_IN_PROC]. f = fd;
}

treenode *get_last_dec_in_proc (treenode *t) {
	return t [LAST_DEC_IN_PROC]. f;
}

void	set_last_dec_in_proc (treenode *t, treenode *ld) {
	t [LAST_DEC_IN_PROC]. f = ld;
}

int	get_blockno_of_proc (treenode *t) {
	return (int)(t [BLOCKNO_OF_PROC]. f);
}

void	set_blockno_of_proc (treenode *t, int bn) {
	t [BLOCKNO_OF_PROC]. f = (treenode *)bn;
}

int	get_num_of_pars (treenode *t) {
	return (int)(t [NUM_OF_PARS]. f);
}

void	set_num_of_pars (treenode *t, int nop) {
	t [NUM_OF_PARS]. f = (treenode *)nop;
}

int	get_proc_level (treenode *t) {
	return (int)(t [PROC_LEVEL]. f);
}

void	set_proc_level (treenode *t, int l) {
	t [PROC_LEVEL]. f = (treenode *)l;
}

//class block: public env {
//public:
//	treenode	*block_decls;
//	treenode	*last_block_decl;
//	int		block_number;
//};

#define	BLOCK_DECLS	LAST_STATEMENT+1
#define	LAST_BLOCK_DECL	LAST_STATEMENT+2
#define	BLOCK_NUMBER	LAST_STATEMENT+3
#define	SIZEOF_BLOCK	BLOCK_NUMBER+1

treenode *get_block_decls (treenode *t) {
	return t [BLOCK_DECLS]. f;
}

void	set_block_decls (treenode *t, treenode *bd) {
	t [BLOCK_DECLS]. f = bd;
}

treenode *get_last_block_decl (treenode *t) {
	return t [LAST_BLOCK_DECL]. f;
}

void	set_last_block_decl (treenode *t, treenode *lbd) {
	t [LAST_BLOCK_DECL]. f = lbd;
}

int	get_block_number (treenode *t) {
	return (int)(t [BLOCK_NUMBER]. f);
}

void	set_block_number (treenode *t, int bn) {
	t [BLOCK_NUMBER]. f = (treenode *)bn;
}

//class compound: public env {
//public:
//};

#define	SIZEOF_COMPOUND	SIZEOF_ENV

//class subtype: public declaration {
//public:
//	treenode	*basetype;
//	treenode	*subtype_bounds;
//	int		subtype_dims;
//};

#define	BASETYPE	C_NAME+1
#define	SUBTYPE_BOUNDS	C_NAME+2
#define	SUBTYPE_DIMS	C_NAME+3
#define	SIZEOF_SUBTYPE	SUBTYPE_DIMS+1

treenode *get_basetype (treenode *t) {
	return t [BASETYPE]. f;
}

void	set_basetype (treenode *t, treenode *bt) {
	t [BASETYPE]. f = bt;
}

treenode *get_subtype_bounds (treenode *t) {
	return t [SUBTYPE_BOUNDS]. f;
}

void	set_subtype_bounds (treenode *t, treenode *sb) {
	t [SUBTYPE_BOUNDS]. f = sb;
}

int	get_subtype_dims (treenode *t) {
	return (int)(t [SUBTYPE_DIMS]. f);
}

void	set_subtype_dims (treenode *t, int dims) {
	t [SUBTYPE_DIMS]. f = (treenode *)dims;
}

//class single_for_element: public for_element {
//public:
//	treenode	*single_expr;
//};

#define	SINGLE_EXPR	NODE_FLAGS+1
#define	SIZEOF_SINGLE_FOR_ELEMENT	SINGLE_EXPR+1

treenode *get_single_expr (treenode *t) {
	return t [SINGLE_EXPR]. f;
}

void	set_single_expr (treenode *t, treenode *se) {
	t [SINGLE_EXPR]. f = se;
}

//class while_element: public for_element {
//public:
//	treenode	*while_init;
//	treenode	*while_condition;
//};

#define	WHILE_INIT	NODE_FLAGS+1
#define	WHILE_CONDITION	NODE_FLAGS+2
#define	SIZEOF_WHILE_ELEMENT	WHILE_CONDITION+1

treenode *get_while_init (treenode *t) {
	return t [WHILE_INIT]. f;
}

void	set_while_init (treenode *t, treenode *wi) {
	t [WHILE_INIT]. f = wi;
}

treenode *get_while_condition (treenode *t) {
	return t [WHILE_CONDITION]. f;
}

void	set_while_condition (treenode *t, treenode *wc) {
	t [WHILE_CONDITION]. f = wc;
}

//class step_until: public for_element {
//public:
//	treenode	*step_init;
//	treenode	*incr_expression;
//	treenode	*until_expression;
//};

#define	STEP_INIT		NODE_FLAGS+1
#define	INCR_EXPRESSION		NODE_FLAGS+2
#define	UNTIL_EXPRESSION	NODE_FLAGS+3
#define	SIZEOF_STEP_UNTIL	UNTIL_EXPRESSION+1

treenode *get_step_init (treenode *t) {
	return t [STEP_INIT]. f;
}

void	set_step_init (treenode *t, treenode *si) {
	t [STEP_INIT]. f = si;
}

treenode *get_incr_expression (treenode *t) {
	return t [INCR_EXPRESSION]. f;
}

void	set_incr_expression (treenode *t, treenode *ie) {
	t [INCR_EXPRESSION]. f = ie;
}

treenode *get_until_expression (treenode *t) {
	return t [UNTIL_EXPRESSION]. f;
}

void	set_until_expression (treenode *t, treenode *ue) {
	t [UNTIL_EXPRESSION]. f = ue;
}

//class for_statement: public statement {
//public:
//	treenode	*for_var;
//	treenode	*for_body;
//	treenode	*for_el_list;
//};

#define	FOR_VAR		LABEL+1
#define	FOR_BODY	LABEL+2
#define	FOR_EL_LIST	LABEL+3
#define	SIZEOF_FOR_STATEMENT	FOR_EL_LIST+1

treenode *get_for_var (treenode *t) {
	return t [FOR_VAR]. f;
}

void	set_for_var (treenode *t, treenode *fv) {
	t [FOR_VAR]. f = fv;
}

treenode *get_for_body (treenode *t) {
	return t [FOR_BODY]. f;
}

void	set_for_body (treenode *t, treenode *fb) {
	t [FOR_BODY]. f = fb;
}

treenode *get_for_el_list (treenode *t) {
	return t [FOR_EL_LIST]. f;
}

void	set_for_el_list (treenode *t, treenode *fel) {
	t [FOR_EL_LIST]. f = fel;
}

//class switch_decl: public declaration {
//public:
//	treenode	*switchlist;
//	int		num_of_switch_elements;
//};

#define	SWITCHLIST		C_NAME+1
#define	NUM_OF_SWITCH_ELEMENTS	SWITCHLIST+1
#define	SIZEOF_SWITCH_DECL	NUM_OF_SWITCH_ELEMENTS+1

treenode *get_switchlist (treenode *t) {
	return t [SWITCHLIST]. f;
}

void	set_switchlist (treenode *t, treenode *sl) {
	t [SWITCHLIST]. f = sl;
}

int	get_num_of_switch_elements (treenode *t) {
	return (int)(t [NUM_OF_SWITCH_ELEMENTS]. f);
}

void	set_num_of_switch_elements (treenode *t, int nose) {
	t [NUM_OF_SWITCH_ELEMENTS]. f = (treenode *)nose;
}

struct sizetable {
int key;
int val;} size_table [42] =
{
{C_DECLARATION,		 SIZEOF_DECLARATION},
{ARRAY_TYPE,		 SIZEOF_ARRAY_TYPE},
{PROC_TYPE,		 SIZEOF_PROC_TYPE},
{LABEL_TYPE,		 SIZEOF_LABEL_TYPE},
{ANY_TYPE,		 SIZEOF_ANY_TYPE},
{STRING_TYPE,		 SIZEOF_STRING_TYPE},
{ERROR_TYPE,		 SIZEOF_ERROR_TYPE},
{BIN_PARAM,		 SIZEOF_BINPARAM},
{BINOP,			 SIZEOF_BINOP	},
{UNPARAM,		 SIZEOF_UNPARAM},
{UNOP,			 SIZEOF_UNOP},
{BOUNDS,		 SIZEOF_BOUNDS},
{IF_STAT,		 SIZEOF_IF_STAT},
{ASSIGNMENT,		 SIZEOF_ASSIGNMENT},
{GOTO_STAT,		 SIZEOF_GOTO_STAT},
{NULL_STAT,		 SIZEOF_NULL_STAT},
{FOR_STAT,		 SIZEOF_FOR_STAT},
{BINARY_EXPRESSION,	 SIZEOF_BINARY_EXPRESSION},
{UNARY_EXPRESSION,	 SIZEOF_UNARY_EXPRESSION},
{INUMBER,		 SIZEOF_NUMBER},
{FNUMBER,		 SIZEOF_NUMBER},
{BNUMBER,		 SIZEOF_NUMBER},
{STRING_CONSTANT,	 SIZEOF_NUMBER},
{ID_AS_PRIM,		 SIZEOF_ID_AS_PRIM},
{ACT_PAR,		 SIZEOF_ACT_PAR},
{FUNCTION_CALL,		 SIZEOF_FUNCTION_CALL},
{INDEXING,		 SIZEOF_INDEXING},
{CONDITIONAL,		 SIZEOF_CONDITIONAL},
{THUNK,			 SIZEOF_THUNK},
{VARIABLE,		 SIZEOF_VARIABLE},
{LABEL_DECL,		 SIZEOF_LABEL_DECL},
{PARAM_DECL,		 SIZEOF_PARAM_DECL},
{PROC_DECL,		 SIZEOF_PROC_DECL},
{BLOCK,			 SIZEOF_BLOCK},
{COMPOUND,		 SIZEOF_COMPOUND},
{SUBTYPE,		 SIZEOF_SUBTYPE},
{SINGLE_FOR_ELEMENT,	 SIZEOF_SINGLE_FOR_ELEMENT},
{WHILE_ELEMENT,		 SIZEOF_WHILE_ELEMENT},
{STEP_UNTIL,		 SIZEOF_STEP_UNTIL},
{FOR_STATEMENT,		 SIZEOF_FOR_STATEMENT},
{SWITCH_DECL,		 SIZEOF_SWITCH_DECL},
{SIMPLE_TYPE,		 SIZEOF_SIMPLE_TYPE}
};

int	get_sizeof (int nodeid) {
	return size_table [nodeid - 1]. val;
}

treenode *new_node (int id, int l, int cn) {
treenode *t;
int i;
	t = (treenode *)malloc (get_sizeof (id) * sizeof (treenode *));
	memset (t, 0, get_sizeof (id) * sizeof (treenode *));
	t [NODEID].  f = (treenode *)id;
	t [LINE_NO]. f = (treenode *)l;
	t [CHAR_NO]. f = (treenode *)cn;
	return t;
}


void	compile (char *src_name) {
char	v [1024];
treenode	*dummy;
treenode	*environment;
treenode	 *st;
//	some basic initializations
	init_nametables ();
	init_scanner (op_file); next_symbol (&s);
	read_prelude (&s);	// read and process operator file

//	now start being Algol: read the environmental block
	init_scanner (prelude); next_symbol (&s);
	environment = new_node (BLOCK, 0, 0);
	set_block_number (environment, create_scope (environment));
	parse_decls (environment, &s, TRUE);

//	now process the user provided file
	init_scanner (infile); next_symbol (&s);
	st = parse_stat (environment, environment, &s);
	leave_scope ();
	if (errors != 0) {
	   printf ("parsing %s complete, %d errors\n", infile, errors);
	   exit (EXIT_FAILURE);
	}

	analyse ((treenode *)0, environment);
	if (sem_errors != 0) {
	   fprintf (stderr, 
	         "analysis %s complete, %d errors\n", infile, sem_errors);
	   exit (EXIT_FAILURE);
	}

	if (include_file == (char *)0)
	   f_out = stderr;
	else
	if ((f_out = fopen (include_file, "w")) == NULL) {
	   fprintf (stderr, "error with include file %s (fatal)\n",
	            include_file);
	   exit (EXIT_FAILURE);
	}

//	now for code generation, first some general stuff
	generate_kop (f_out, infile, HEADER, compile_time);

//	then the global specifications for the include file
	generate_headers (get_first_in_globals (globals));

//	now close the ".h" file and continue with the ".c" file
	if (include_file != (char *)0)
	   fclose (f_out);

	if (c_file == (char *)0)
	   f_out = stderr;
	else
	if ((f_out = fopen (c_file, "w")) == NULL) {
	   fprintf (stderr, "error in opening %s (fatal)\n", c_file);
	   exit (EXIT_FAILURE);
	}

//	then the global declarations and the main program
	generate_kop (f_out, infile, include_file, compile_time);
	generate_elab_code    (globals -> first, environment);
	if (c_file != (char *)0)
	   fclose (f_out);
}

/*
 *	Prelude manipulation
 *	In order to minimize the amount of interpretation
 *	within the compiler itself,
 *	definitions of operators are given in the prelude
 *	although the lay out of the prelude is undocumented, it follows from
 *	the given prelude
 */
treenode	*type_defs;
treenode	*int_type;
treenode	*real_type;
treenode	*bool_type;
treenode	*void_type;
treenode	*any_type;
treenode	*error_type;
treenode	*lab_type;
treenode	*string_type;
char		*type_rep;
char		*s_unary;
char		*s_binary;
char		*s_constant_operator;

treenode *read_type  (struct symbol *s) {
char	*ti, *tb, *tc;
treenode *t;

	if ((symbol_value (s) != S_IDENT)
	   || (symbol_repr (s) != type_rep))
	   return (treenode *) 0;

	next_symbol (s);
	if (check_for (S_IDENT, S_SEMI, s) == 0)
	   return (treenode *)0;

	ti = symbol_repr (s);
	next_symbol (s);
	if (check_for (S_COLON, S_SEMI, s) == 0)
	   return (treenode *)0;

	next_symbol (s);
	if (check_for (S_IDENT, S_SEMI, s) == 0)
	   return (treenode *)0;

	tb = symbol_repr (s);
	next_symbol (s);
	if (check_for (S_COLON, S_SEMI, s) == 0)
	   return (treenode *)0;

	next_symbol (s);
	if (check_for (S_IDENT, S_SEMI, s) == 0)
	   return (treenode *) 0;

	tc = symbol_repr (s);
	next_symbol (s);
	add_keyword (S_BASICTYPE, ti);
	t = new_node (SIMPLE_TYPE, -1, -1);
	set_type_id  (t, ti);
	set_internal_name (t, tb);
	set_c_type (t, tc);
	return t;
}

treenode *read_types (struct symbol *s) {
treenode *t1, *t2, *t3;

	t1 = t2 = t3 = read_type (s);
	while (symbol_value (s) == S_SEMI && t3 != (treenode *)0) {
	   next_symbol (s);
	   t3 = read_type (s);
	   set_nextnode (t2, t3);
	   t2 = t3;
	}

	check_for (S_END, S_SEMI, s); 
	next_symbol (s);
	check_for (S_SEMI, S_SEMI, s);
	next_symbol (s);
	return t1;
}

treenode *get_type (char *s) { 
treenode *h = type_defs;

	while (h != (treenode *)0) {
	   if (get_type_id (h) == s) 
	      return h;
	   h = get_nextnode (h);
	}

	return (treenode *)0;
}

treenode *get_internal_type (char *s) { 
treenode *h = type_defs;

	while (h != (treenode *)0) {
	   if (get_internal_name (h) == s) 
	      return h;
	   h = get_nextnode (h);
	}

	return (treenode *)0;
}
//
//	give me an array type with element type et
treenode *get_arraytype (treenode *et) {
treenode *h =  type_defs;

	while (h != (treenode *)0) {
	   if ((get_nodeid (h) == ARRAY_TYPE) && get_element_type (h) == et)
	      return h;
	   h = get_nextnode (h);
	}

	h = new_node (ARRAY_TYPE, -1, -1);
	set_element_type (h, et);
	set_nextnode (h, type_defs);
	type_defs = h;
	return h;
}

treenode *get_proctype (treenode *rt) {
treenode *h = type_defs;

	while (h != (treenode *)0) {
	   if ((get_nodeid (h) == PROC_TYPE) &&
	       (get_proctype_returntype (h) ==  rt))
	      return h;
	   h = get_nextnode (h);
	}

	h = new_node (PROC_TYPE, -1, -1);
	set_proctype_returntype (h, rt);
	set_nextnode (h, type_defs);
	type_defs = h;
	return h;
}

treenode *get_labeltype () {
treenode *h = type_defs;

	while (h != (treenode *)0) {
	   if (get_nodeid (h) == LABEL_TYPE)
	      return h;
	   h = get_nextnode (h);
	}

	h = new_node (LABEL_TYPE, -1, -1);
	set_nextnode (h, type_defs);
	type_defs = h;
	return h;
}

//	end of type preprocessing
//	now starting with operator definitions
//
treenode *bin_operators;
int max_prio = -10000;

// read_bin_params reads a sequence of (x y z s) elements
treenode *read_bin_param  (struct symbol *s) {
treenode *h;

	if (symbol_value (s) != S_LPAR)
	   return (treenode *)0;

	next_symbol (s);
	if (symbol_value (s) != S_BASICTYPE) 
	   return (treenode *)0;

	h = new_node (BIN_PARAM, 0, 0);
	set_left_operand_for_bin (h, get_type (symbol_repr (s)));
	next_symbol (s);
	if (symbol_value (s) != S_BASICTYPE) 
	   return (treenode *)0;

	set_right_operand_for_bin (h, get_type (symbol_repr (s)));
	next_symbol (s);
	if (symbol_value (s) != S_BASICTYPE)
	   return (treenode *)0;

	set_return_type_for_bin (h, get_type (symbol_repr (s)));
	next_symbol (s);
	
	if (symbol_value (s) == S_IDENT) 
	   if (symbol_repr (s) == s_constant_operator) {
	      next_symbol (s);
	      set_constant_expression (h);
	   }
	   else
	      return (treenode *)0;

	if (symbol_value (s) != S_STRINGC)
	   return (treenode *)0;

	set_c_string_for_bin (h, symbol_repr (s));
	next_symbol (s);
	if (symbol_value (s) != S_RPAR)
	   return (h);

	next_symbol (s);
	return (h);
}

treenode *read_bin_params (struct symbol *s) {
treenode *h = read_bin_param (s);

	if (symbol_value (s) != S_LPAR)
	   return h;

	set_nextnode (h, read_bin_params (s));
	return (h);
}

treenode *read_binary (struct symbol *s) {
treenode *b;
	if (symbol_value (s) != S_SUB)
	   return (treenode *)0;

	next_symbol (s);
	if (symbol_value (s) != S_OPERATOR) 
	   if (symbol_value (s) == S_IDENT) 
	      add_keyword (S_OPERATOR, symbol_repr (s));
	   else {
	      syn_error (s, "In operators: line %d %s\n", symbol_repr (s), "");
	      return (treenode *)0;
	   }

	b = new_node (BINOP, 0, 0);
	set_opsym_for_bin (b, store_in_tree (symbol_repr (s)));
	next_symbol (s);
	if (check_for (S_INUMBER, S_BUS, s) == 0)
	   return (treenode *)0;

	set_binary_prio (b, convert_to_ivalue (symbol_repr (s)));
	if (get_binary_prio (b) > max_prio)
	   max_prio = get_binary_prio (b);
	next_symbol (s);
	if (check_for (S_LPAR, S_SEMI, s) == 0)
	   return (treenode *)0;

	next_symbol (s); // this should be the '(' of the first parameter desc
	set_binary_params (b, read_bin_params (s));
	if (check_for (S_RPAR, S_SEMI, s)== 0)
	   return (treenode *)0;

	next_symbol (s);
	if (check_for (S_BUS, S_SEMI, s) == 0)
	   return b;

	next_symbol (s);
	return b;
}

treenode *read_binaries (struct symbol *s) {
treenode *t;

	t = read_binary (s);
	if (symbol_value (s) == S_SUB) 
	   set_nextnode (t, read_binaries (s));
	return t;
}

treenode *get_binoperator (int prio, char *rep) {
treenode *h = bin_operators;

	while (h != (treenode *)0) {
	   if ((get_opsym_for_bin (h) == rep) &&
	       (get_binary_prio (h) == prio))
	      return h;
	   h = get_nextnode (h);
	}

	return (treenode *)0;
}

treenode *get_bdef (treenode *bo, treenode *lo, treenode *ro) {
treenode *h = get_binary_params (bo);

	while (h != (treenode *)0) {
	   if ((get_left_operand_for_bin (h) == lo) &&
	       (get_right_operand_for_bin (h) == ro) )
	      return h;
	   h = get_nextnode (h);
	}

	return (treenode *)0;
}
//
//	now for the unary operators
//
treenode *un_operators;

// read_un_params reads a sequence of (x y s) elements
treenode *read_un_param  (struct symbol *s) {
treenode *h;

	if (symbol_value (s) != S_LPAR)
	   return (treenode *)0;

	next_symbol (s);
	if (symbol_value (s) != S_BASICTYPE) 
	   return (treenode *)0;

	h = new_node (UNPARAM, 0, 0);
	set_left_for_un (h, get_type (symbol_repr (s)));
	next_symbol (s);
	if (symbol_value (s) != S_BASICTYPE)
	   return (treenode *)0;

	set_return_type_for_un (h, get_type (symbol_repr (s)));
	next_symbol (s);
	if (symbol_value (s) == S_IDENT) 
	   if (symbol_repr (s) == s_constant_operator) {
	      next_symbol (s);
	      set_constant_expression (h);
	   }
	   else
	      return (treenode *)0;

	if (symbol_value (s) != S_STRINGC)
	   return (treenode *)0;

	set_c_string_for_un (h, symbol_repr (s));
	next_symbol (s);
	if (symbol_value (s) != S_RPAR)
	   return (h);

	next_symbol (s);
	return h;
}

treenode *read_un_params (struct symbol *s) {
treenode *h = read_un_param (s);

	if (symbol_value (s) != S_LPAR)
	   return h;

	set_nextnode (h, read_un_params (s));
	return (h);
}

treenode *read_unary (struct symbol *s) {
treenode *b;

	if (symbol_value (s) != S_SUB)
	   return (treenode *)0;

	next_symbol (s);
	if (symbol_value (s) != S_OPERATOR) 
	   if (symbol_value (s) == S_IDENT) 
	      add_keyword (S_OPERATOR, symbol_repr (s));
	   else {
	      syn_error (s, "In operators: line %d %s\n",
	                 symbol_repr (s), "");
	      return (treenode *)0;
	   }

	b = new_node (UNOP, 0, 0);
	set_opsym_for_un (b, store_in_tree (symbol_repr (s)));
	next_symbol (s);
	if (check_for (S_INUMBER, S_BUS, s) == 0)
	   return (treenode *)0;

	set_unary_prio (b, convert_to_ivalue (symbol_repr (s)));
	if (get_unary_prio (b) > max_prio)
	   max_prio =  get_unary_prio (b);

	next_symbol (s);
	if (check_for (S_LPAR, S_SEMI, s) == 0)
	   return (treenode *)0;

	next_symbol (s); // this should be the '(' of the first parameter desc
	set_unary_params (b, read_un_params (s));

	if (check_for (S_RPAR, S_SEMI, s)== 0)
	   return (treenode *)0;

	next_symbol (s);
	if (check_for (S_BUS, S_SEMI, s) == 0)
	   return b;

	next_symbol (s);
	return b;
}

treenode *read_unaries (struct symbol *s) {
treenode *t;

	t = read_unary (s);
	if (symbol_value (s) == S_SUB) 
	   set_nextnode (t, read_unaries (s));
	return t;
}

treenode *get_unoperator (int prio, char *rep) {
treenode *h = un_operators;

	while (h != (treenode *)0) {
	   if ((get_opsym_for_un (h) == rep) &&
	        (get_unary_prio (h) == prio))
	      return h;
	   h = get_nextnode (h);
	}
	return (treenode *)0;
}

treenode *get_udef (treenode *bo, treenode *lo) {
treenode *h = get_unary_params (bo);

	while (h != (treenode *)0) {
	   if ((get_left_for_un (h) == lo))
	      return h;

	   h = get_nextnode (h);
	}

	return (treenode *)0;
}

void	read_prelude (struct symbol *s){
	type_rep	= store_in_tree ("typedef");
	s_unary		= store_in_tree ("unary");
	s_binary	= store_in_tree ("binary");
	s_constant_operator = store_in_tree ("constant");

	if ((symbol_value (s) == S_IDENT) &&
	    (symbol_repr (s) == type_rep)) {
	   type_defs = read_types (s);
	   int_type  = get_internal_type (store_in_tree ("A_int"));
	   real_type = get_internal_type (store_in_tree ("A_real"));
	   bool_type = get_internal_type (store_in_tree ("A_bool"));
	   void_type = get_internal_type (store_in_tree ("void"));
	   if ((int_type == (treenode *)0) ||
	       (real_type == (treenode *)0) ||
	       (bool_type == (treenode *)0) ||
	       (void_type == (treenode *)0) ) {
	      fprintf (stderr, "Fatal: basic type(s) undefined\n");
	      exit (EXIT_FAILURE);
	   }
//
//	define some additional types
	   lab_type	= get_labeltype ();
	   error_type	= new_node (ERROR_TYPE, -1, -1);
	   any_type	= new_node (ANY_TYPE, -1, -1);
	   string_type	= new_node (STRING_TYPE, -1, -1);
	}

	if ((symbol_value (s) == S_IDENT) &&
	    (symbol_repr (s) == s_binary)) {
	   next_symbol (s);
	   bin_operators = read_binaries (s);
	   check_for (S_END, S_SEMI, s);
	   next_symbol (s);
	   check_for (S_SEMI, S_SEMI, s);
	   next_symbol (s);
	}

	if ((symbol_value (s) == S_IDENT) &&
	    (symbol_repr (s) == s_unary)) {
	   next_symbol (s);
	   un_operators = read_unaries (s);
	   check_for (S_END, S_SEMI, s);
	   next_symbol (s);
	   check_for (S_SEMI, S_SEMI, s);
	   next_symbol (s);
	}
}

//
//	The scanner
//	the scanner is a straight forward scanner, handwritten
//	according to the books
//
#define	MAX_KEYWORDS	200
#define	STROPPED	1
#define	NORMAL		0

int		scanmodus		= NORMAL;
int		has_peeked_ahead	= FALSE;
struct symbol	look_ahead_symbol;
int		ch;
FILE		*fin;
int		lineno;
int		charno;
char		*current_file;

void get_char () {
	ch = fgetc (fin);
	if (ch == EOF)
	   return;
	if (ch == '\012') {
	   lineno ++;
	   charno = 0;
	}
	else
	   charno ++;
}

int	is_blank (int ch) {
	if (ch == EOF)
	   return FALSE;
	return ch <= ' ';
}

void	get_nonblank () {
	get_char ();
	while (is_blank (ch)) get_char ();
}

void	get_scannerchar () {
	if (scanmodus == STROPPED) 
	   get_nonblank ();
	else
	   get_char ();
	return;
}

int convert_to_ivalue (char *s) {
int h;
	sscanf (s, "%d", &h);
	return h;
}

char	*convert_char_to_int (char s) {
char	v[5];
	sprintf (v, "%d", (s &0377));
	return store_in_tree (v);
}

int	Is_Letter (char c) {
	return (('a' <= c && c <= 'z') ||
	        ('A' <= c && c <= 'Z'));
}

int	Is_Digit (char c) {
	return '0' <= c && c <= '9';
}

int	Is_Octal_Digit (char c) {
	return '0' <= c && c <= '7';
}

struct key_word {
	int	key_value;
	char	*representation;
} key_table [MAX_KEYWORDS];

int	first_free_keyword	= 0;

void	add_keyword (int sym_val, char *s) {
int	i;
	i = first_free_keyword ++;
	if (first_free_keyword > MAX_KEYWORDS) {
	   fprintf (stderr, "Overflow in keyword table (fatal)\n");
	   exit (EXIT_FAILURE);
	}

	key_table [i]. representation = s;
	key_table [i]. key_value      = sym_val;
}


void	init_French_keywords () {
	add_keyword (S_CPROC, "c_procedure");
	add_keyword (S_CPROC, "c_proc");
	add_keyword (S_ARRAY, "TABLEAU");
	add_keyword (S_BEGIN, "DEBUT");
	add_keyword (S_DO, "FAIRE");
	add_keyword (S_END, "FIN");
	add_keyword (S_ELSE, "SINON");
	add_keyword (S_FOR, "POUR");
	add_keyword (S_FALSE, "false");
	add_keyword (S_FALSE, "FALSE");
	add_keyword (S_TRUE, "true");
	add_keyword (S_TRUE, "TRUE");
	add_keyword (S_GOTO, "ALLERA");
	add_keyword (S_IF, "SI");
	add_keyword (S_LABEL, "ETIQUETTE");
	add_keyword (S_PROC, "PROCEDURE");
	add_keyword (S_PROC, "procedure");
	add_keyword (S_PROC, "proc");
	add_keyword (S_STEP, "PAS");
	add_keyword (S_SWITCH, "switch");
	add_keyword (S_STRING, "string");
	add_keyword (S_THEN, "ALORS");
	add_keyword (S_UNTIL, "JUSQUA");
	add_keyword (S_VALUE, "VALEUR");
	add_keyword (S_WHILE, "TANTQUE");
	add_keyword (S_COMMENT, "COMMENTAIRE");
	add_keyword (S_OWN, "own");
}
void	init_English_keywords () {
	add_keyword (S_CPROC, "c_procedure");
	add_keyword (S_CPROC, "c_proc");
	add_keyword (S_ARRAY, "array");
	add_keyword (S_BEGIN, "begin");
	add_keyword (S_DO, "do");
	add_keyword (S_END, "end");
	add_keyword (S_ELSE, "else");
	add_keyword (S_FOR, "for");
	add_keyword (S_FALSE, "false");
	add_keyword (S_FALSE, "FALSE");
	add_keyword (S_TRUE, "true");
	add_keyword (S_TRUE, "TRUE");
	add_keyword (S_GOTO, "goto");
	add_keyword (S_GO, "go");
	add_keyword (S_TO, "to");
	add_keyword (S_IF, "if");
	add_keyword (S_LABEL, "label");
	add_keyword (S_PROC, "procedure");
	add_keyword (S_PROC, "proc");
	add_keyword (S_STEP, "step");
	add_keyword (S_SWITCH, "switch");
	add_keyword (S_STRING, "string");
	add_keyword (S_THEN, "then");
	add_keyword (S_UNTIL, "until");
	add_keyword (S_VALUE, "value");
	add_keyword (S_WHILE, "while");
	add_keyword (S_COMMENT, "comment");
	add_keyword (S_OWN, "own");
}

void	init_keywords () {
	if (languageFlag == 0)
	   init_English_keywords ();
	else
	   init_French_keywords ();
}

int equal_string (char *s1, char *s2) {
	while (*s1  == *s2  && *s1 != (char)0) { s1 ++; s2++; }
	return *s1 == *s2;
}

int Lookup (char *s) {
int i;
	for (i = 0; key_table [i]. representation != NULL; i++) 
	   if (equal_string (key_table [i]. representation, s))
	       return key_table [i]. key_value;
	return -1;
}

int	length (char	*s) {
int	i = 0;
	while (*s ++ != (char) 0) i ++;
	return i + 1;
}

struct string_element *init_element (char *s) {
struct string_element *t;
int	i;
int	l = length (s);
	t = (struct string_element *)malloc (sizeof(struct string_element) +l);
	t -> left	= NULL;
	t -> right	= NULL;
	for (i = 0; i < l; i ++) 
	   t -> string_value [i] = s [i];
	t -> string_value [i] = (char)0;
	return t;
}

// Profiling (and intuition) shows that this procedure is THE time consumer
// therefore, we optimize the procedure by removing all calls to other functions
// implementing the functionality locally
char	*store_in_tree (char	*s) {
static struct string_element *sf = (struct string_element *)0;
struct string_element **se =  &sf;
char	*s2;
char	*s1;

	while (*se != (struct string_element *)0) {
	   s1 = s;
	   s2 = (*se) -> string_value;
	   while ((*s1  != (char)0) && (*s1 == *s2)) {
	      s1 ++;
	      s2 ++;
	   };
	   if (*s1 == *s2) 
	      return (*se) -> string_value;

	   if (*s1 >= *s2)
	      se = &((*se) -> right);
	   else
	      se = &((*se) -> left);
	}

	*se = init_element (s);
	return  (*se) -> string_value;
}

char *Read_Identifier () {
char temp [MAX_IDENT_SIZE];
int	i = 0;
	while (Is_Letter (ch) || Is_Digit (ch) || ch == '_') {
	   temp [i ++] = ch;
	   get_scannerchar ();
	   if (i >= MAX_IDENT_SIZE) {
	      fprintf (stderr, "Identifier too long (line %d, file %s)\n",
	               lineno, current_file);
	      i --; 
	      break;
	   }
	}
	temp [i] = (char)0;
	return store_in_tree (&temp [0]);
}

int	Read_Stropped (char **v) {
char	temp [MAX_IDENT_SIZE];
int	i = 0;
int	val;
	
	while (Is_Letter (ch)) {
	   temp [ i ++] = ch;
	   get_nonblank ();
	   if (i >= MAX_IDENT_SIZE) {
	      fprintf (stderr, "Symbol oversized (line %d, file %s)\n",
	               lineno, current_file);
	      i --;
	      break;
	   }
	}

	if (i < MAX_IDENT_SIZE && ch != '\'') {
	   fprintf (stderr, "Stropped word not ended (line %d, file %s)\n",
	            lineno, current_file);
	}
	get_nonblank ();
	temp [i] = 0;
	*v = store_in_tree (temp);
	val = Lookup (*v);
	if (val == -1) {
	   fprintf (stderr, "Unrecognized keyword %s (line %d, file %s)\n",
	                temp, lineno, current_file);
	   return -1;
	}
	return val;
}

char *Read_String () {
char temp [MAX_STRING_SIZE];
int i = 0;
char *s;
	while (ch != '\"' && i < MAX_STRING_SIZE - 1) {
	   temp [i ++] = ch;
	   if (ch == '\\') {
	      get_char (); temp [i ++] = ch;
	   }
	   get_char ();
	}

	if (i >= MAX_STRING_SIZE) {
	   fprintf (stderr, "Line %d, file %s: string too long\n",
	            lineno, current_file);
	}

	temp [i] = (char)0;
	get_char ();
	s = store_in_tree (temp);
	return s;
}

int	Read_Number (char **r) {
char temp [MAX_NUMBER_SIZE];
int i	= 0;
char *s;
int state	= 1;

	while (Is_Digit (ch)) {
	    temp [i++] = ch;
	    get_scannerchar ();
	}

	if (ch == '.') {
	   if (i == 0) {
	      temp [i ++] = '0';
	   }
	   goto state_4; 
	}
	if (ch == '@' || ch == 'e' || ch == 'E') {
	   if (i == 0)
	      temp [i ++] = '0';
	   temp [i ++] = '.';
	   temp [i ++] = '0';
	   goto state_5;
	}

	temp [i] = (char)0;
	*r = store_in_tree (temp);
	return S_INUMBER;

state_4: temp [i++] = ch;
	get_scannerchar ();
	while (Is_Digit (ch)) {
	    temp [i ++] = ch;
	    get_scannerchar ();
	}
	if (ch == '@' || ch == 'e' || ch == 'E') goto state_5;
	temp [i] = (char)0;
	*r =  store_in_tree (temp);
	return S_RNUMBER;

state_5: temp [i ++] = 'E';
	get_scannerchar ();
	if (ch == '+' || ch == '-') {
	   temp [i ++] = ch;
	   get_scannerchar ();
	}
	if (! Is_Digit (ch)) goto state_error;

state_7: while (Is_Digit (ch)) {
	     temp [i ++] = ch;
	     get_scannerchar ();
	 }
	 temp [i] = (char)0;
	 *r = store_in_tree (temp);
	 return S_RNUMBER;

state_error: return S_ERROR;
}
//	Definitely non-standard Algol
//	we allow C like specifications such as \043 as character
//	in the denotation
char	Read_Octal () {
char c1;
int  res;

	if (!Is_Octal_Digit (ch)) {
	   fprintf (stderr, "Illegal denotation for Escaped char\n");
	   return (char)0;
	}
	res = ch - '0';
	get_char ();
	while (Is_Octal_Digit (ch)) {
	   res = 010 * res + (ch - '0');
	   get_char ();
	}

	if (res > 255) {
	   fprintf (stderr, "Denotation of (too) large octal number (%d)\n",
	            res);
	   res = 0377;
	}
	return res;
}

char	Read_Escaped_Char () {
char	c;
	switch (ch) {
	   case 's':	c = ' '; break;
	   case 'n':	c = '\n'; break;
	   case 'f':	c = '\f'; break;
	   case 't':	c = '\t'; break;
	   case '0':	get_char ();
	                return Read_Octal ();
	   default:
	      c = ch; break;
	}
	get_char (); return c;
}

// The scanner routine, read a sequence of characters forming a symbol
void make_symbol (struct symbol *s, int a, char *b, int l, int cn) {
	s -> sym_value = a;
	s -> sym_rep   = b;
	s -> lineno    = l;
	s -> charno    = cn;
}

void next_algol_token (struct symbol *sym) {
int t1, t2, t3; 
char	*v;

	while (TRUE) {
	   switch (ch) {
	      case '(':
	         make_symbol (sym, S_LPAR, "(", lineno, charno);
	         get_scannerchar ();
	         return;

	      case ')':
	         make_symbol (sym, S_RPAR, ")", lineno, charno);
	         get_scannerchar ();
	         return;

	      case '[':
	         make_symbol (sym, S_SUB, "[", lineno, charno);
	         get_scannerchar ();
	         return;

	      case ']':
	         make_symbol (sym, S_BUS, "]", lineno, charno);
	         get_scannerchar ();
	         return;

	      case '/':
	      case '+':
	      case '-':
	      case '=':
	         make_symbol (sym, S_OPERATOR, char_to_string (ch), lineno, charno);
	         get_scannerchar ();
	         return;

	      case '*':
	         make_symbol (sym, S_OPERATOR, "*", lineno, charno);
	         get_scannerchar ();
	         if (ch == '*') {
	            make_symbol (sym, S_OPERATOR, "^", lineno, charno);
	            get_scannerchar ();
	         }
	         return;

	      case '^':
	         make_symbol (sym, S_OPERATOR, "^", lineno, charno);
	         get_scannerchar ();
	         if (ch == '=') {
	            make_symbol (sym, S_OPERATOR, "^=", lineno, charno);
	            get_scannerchar ();
	         }
	         return;

	      case ',':
	         make_symbol (sym, S_COMMA, ",", lineno, charno);
	         get_scannerchar ();
	         return;

	      case ';':
	         make_symbol (sym, S_SEMI, ";", lineno, charno);
	         get_scannerchar ();
	         return;

	      case ':':
	         make_symbol (sym, S_COLON, ":", lineno, charno);
	         get_scannerchar ();
	         if (ch == '=') {
	            make_symbol (sym, S_ASSIGN, ":=", lineno, charno);
	            get_scannerchar ();
	         }
	         return;

	      case '<':
	         make_symbol (sym, S_OPERATOR, "<", lineno, charno);
	         get_scannerchar ();
	         if (ch == '=') {
	            make_symbol (sym, S_OPERATOR, "<=", lineno, charno);
	            get_scannerchar ();
	         }
	         return;

	      case '>':
	         make_symbol (sym, S_OPERATOR, ">", lineno, charno);
	         get_scannerchar ();
	         if (ch == '=') {
	            make_symbol (sym, S_OPERATOR, ">=", lineno, charno);
	            get_scannerchar ();
	         }
	         return;

	      case '\"':
	         t1 = lineno; t2 = charno;
	         get_char ();
	         v = Read_String ();
	         make_symbol (sym, S_STRINGC, v, t1, t2);
	         return;

	      case '\'':
	         get_scannerchar ();
	         if (scanmodus == STROPPED) {
	            t1 = Read_Stropped (&v);
	            make_symbol (sym, t1, v, lineno, charno);
	            return;
	         }
	         fprintf (stderr, "Warning: cannot handle \', ignored\n");
	         get_scannerchar ();
	         return;

	      case '&':
	         get_char ();
	         t1 = ch;
	         if (ch == '\\') {
	            get_char ();
	            t1 = Read_Escaped_Char ();
	         }
	         else
	            get_char ();	// stupid, but Read.. reads ahead
	
	         make_symbol (sym, S_INUMBER, convert_char_to_int ((char)t1), lineno, charno);
	         return;

	   case '!':
	      get_scannerchar ();
	      if (ch == '=') { 
	         get_scannerchar ();
	         make_symbol (sym, S_OPERATOR, "^=", lineno, charno);
	         return;
	      }
	      make_symbol (sym, S_OPERATOR, "not", lineno, charno);
	      return;

	   default:
	      t1 = lineno, t2 = charno;
	      if (Is_Letter (ch)) {
	          v = Read_Identifier ();
	          if (scanmodus == STROPPED)
	             make_symbol (sym, S_IDENT, v, t1, t2);
	          else
	          if (Lookup (v) == -1)
	             make_symbol (sym, S_IDENT, v, t1, t2);
	          else
	             make_symbol (sym, Lookup (v), v, t1, t2);
	          return;
	      }

	      if (Is_Digit (ch) || (ch == '.')) {
	         t3 = Read_Number (&v);
	         make_symbol (sym, t3, v, t1, t2);
	         return;
	      }

	      if (ch == EOF) {
	         make_symbol (sym, S_EOF, NULL, t1, t2);
	         return;
	      } 
	// I do not know, just skip the damned character
	         get_scannerchar ();
	   }
	}
}

/*
 *	In Algol 60 comments are of handled fairly specially
 */
#define ST_E	1
#define ST_O	2
#define ST_B	3

int ends_comment_after_end (int s) {
	return (s == S_END || s == S_ELSE || s == S_SEMI || s == S_EOF);
}

void	peek_ahead (struct symbol **s) {
	if (has_peeked_ahead) {
	   fprintf (stderr, "cannot peek-ahead double\n");
	}
	else {
	   next_symbol (&look_ahead_symbol);
	   has_peeked_ahead = TRUE;
	   *s = &look_ahead_symbol;
	}
}

void next_symbol (struct symbol *s) {
static int state = ST_O;
	if (has_peeked_ahead) {
	   s -> sym_value	= look_ahead_symbol. sym_value;
	   s -> sym_rep		= look_ahead_symbol. sym_rep;
	   s -> lineno		= look_ahead_symbol. lineno;
	   s -> charno		= look_ahead_symbol. charno;
	   has_peeked_ahead	= FALSE;
	   return;
	}
	   
	next_algol_token (s);
	if (state == ST_E) 
	   while (!ends_comment_after_end (symbol_value (s))) 
	      next_algol_token (s);

	if (state == ST_B && symbol_value (s) == S_COMMENT) {
	   while ((ch != EOF && ch != ';')) get_char ();
	   get_char (); next_symbol (s);
	   return;
	}

	switch (symbol_value (s)) {
	   case S_BEGIN:
	   case S_SEMI:
	      state = ST_B;
	      break;

	   case S_END:
	      state = ST_E;
	      break;

	   default:
	      state = ST_O;
	      break;
	}
}

void init_scanner (char *f) {
static int cnt = 0;

	if (fin != NULL)
	   fclose (fin);

	lineno = 1;
	charno = 1;
	ch     = 0;
	fin = fopen (f, "r");
	if (fin == NULL) {
	   fprintf (stderr, "Fatal: cannot open file %s\n", f);
	   exit (EXIT_FAILURE);
	}

	current_file = f;
	if (cnt ++ == 0) {
	   init_keywords ();
	}

	get_nonblank ();
	if (ch == '\'')
	   scanmodus = STROPPED;
	else
	   scanmodus = NORMAL;
}

void skip_until (int skips, struct symbol *s) {
	while (symbol_value (s) != skips &&
	       symbol_value (s) != S_EOF)
	      next_symbol (s);
}

int check_for (int ds, int skips, struct symbol *s) {
	if (symbol_value (s) == ds)
	   return TRUE;

	errors ++;
	fprintf (stderr,
	         "file %s: On line %d (char %d), symbol %s illegal, skipping input until %d\n",
	        current_file,
	        s -> lineno,
	        s -> charno,
	        s -> sym_rep,
	        skips);
	skip_until (skips, s);
	return FALSE;
}

//
//	Parser module for jff-a2c compiler
//	Version 1.3
//	
//	Straight ahead recursive descent parsing
//	Grammar is almost LL(1), parameter separator makes it a local
//	LL(2) grammar, that is why we introduce a lookahead possibility in the
//	scanner

//	recognize an algol primary, i.e.
//	id{(expressionlist)|[expressionlist]}
//	

treenode *parse_indexing (struct symbol *s,int lineno, int charno, char *ident) {
treenode *e;
	e = new_node (INDEXING, lineno, charno);
	set_array_ident (e, ident);
	next_symbol (s);
	set_subscripts (e, parse_expressionlist (s));
	set_num_of_subscripts (e, count_entities (get_subscripts (e)));
	if (check_for (S_BUS, S_SEMI, s)) 
	   next_symbol (s);
	return e;
}

treenode *parse_functioncall (struct symbol *s, int lineo, int charno, char *ident) {
treenode *e;
	e = new_node (FUNCTION_CALL, lineno, charno);
	set_function_ident (e, ident);
	next_symbol (s);
	set_actuals (e, parse_actparlist (s));
	set_num_of_actuals (e, count_entities (get_actuals (e)));
	if (check_for (S_RPAR, S_SEMI, s)) 
	   next_symbol (s);
	return e;
}

treenode *parse_id_as_primary (struct symbol *s) {
char	*ident	= symbol_repr (s);
int	lineno  = symbol_lineno (s);
int	charno  = symbol_charno (s);
treenode	*e;

	next_symbol (s);
	if (symbol_value (s) == S_LPAR)  // a function call
	   return parse_functioncall (s, lineno, charno, ident);

	if (symbol_value (s) == S_SUB)  // some indexed thing
	   return parse_indexing (s, lineno, charno, ident);

//	just an identifier
	e = new_node (ID_AS_PRIM, lineno, charno);
	set_resolve_ident (e, ident);
	return e;
}

treenode *parse_conditional (struct symbol *s) {
treenode *t1;

	t1 = new_node (CONDITIONAL, symbol_lineno (s), symbol_charno (s));
	next_symbol (s);
	set_cond_of_condition(t1, parse_expression (0, s));
	if (!check_for (S_THEN, S_SEMI, s)) 
	   return (treenode *)0;

	next_symbol (s);
	set_condition_thenpart (t1, parse_expression (0, s));
	if (!check_for (S_ELSE, S_SEMI, s)) 
	   return (treenode *)0;

	next_symbol (s);
	set_condition_elsepart (t1, parse_expression (0, s));
	return t1;
}
//	recognize a full algol expression
//
//	operator handling is somewhat special since we do not know what was
//	in the operator file defined as priority for various operators
//
treenode *parse_primary (struct symbol *s) {
treenode *t;

	  switch (symbol_value (s)) {
	  case S_IDENT:
	     return parse_id_as_primary (s);

	  case S_INUMBER:
	     t = new_node (INUMBER, symbol_lineno (s), symbol_charno (s));
	     set_x_value (t, symbol_repr (s));
	     next_symbol (s);
	     return t;

	  case S_RNUMBER:
	     t = new_node (FNUMBER, symbol_lineno (s), symbol_charno (s));
	     set_x_value (t, symbol_repr (s));
	     next_symbol (s);
	     return t;

	  case S_TRUE:
	     t = new_node (BNUMBER, symbol_lineno (s), symbol_charno (s));
	     set_x_value(t, store_in_tree ("true"));
	     next_symbol (s);
	     return t;

	  case S_FALSE:
	     t = new_node (BNUMBER, symbol_lineno (s), symbol_charno (s));
	     set_x_value (t, store_in_tree ("false"));
	     next_symbol (s);
	     return t;

	  case S_STRINGC:
	     t = new_node (STRING_CONSTANT, symbol_lineno (s), symbol_charno (s));
	     set_x_value (t, symbol_repr (s));
	     next_symbol (s);
	     return t;

	  case S_LPAR:
	     next_symbol (s);
	     t = parse_expression (0, s);
	     check_for (S_RPAR, S_SEMI, s);
	     next_symbol (s);
	     return t;

	  case S_IF:
	     return parse_conditional (s);

	  default:
	     syn_error (s, "Illegal primary \"%s\"\n", symbol_repr (s), "");
	     t = new_node (INUMBER, symbol_lineno (s), symbol_charno (s));
	     set_x_value (t, store_in_tree ("0"));
	     return (treenode *)t;
	}
}

treenode *parse_expression (int prio, struct symbol *s) {
treenode *h1, *h, *t, *t2;

	if (prio > max_prio) 
	   return parse_primary (s);

	if (symbol_value (s) == S_OPERATOR) {
	   h1 = get_unoperator (prio, store_in_tree (symbol_repr (s)));
	   if (h1 != (treenode *)0) {
	      h = new_node (UNARY_EXPRESSION, symbol_lineno (s), symbol_charno (s));
	      next_symbol (s);
	      set_un_operator (h, h1);
	      set_unary_operand (h,  parse_expression (prio, s));
	      return h;
	   }
	}

	h = t = parse_expression (prio + 1, s);
	while ((symbol_value (s) == S_OPERATOR) &&
	        ((h1 = get_binoperator (prio, store_in_tree (symbol_repr (s)))))) {
	   h = new_node (BINARY_EXPRESSION, symbol_lineno (s), symbol_charno (s));
	   set_bin_operator (h, h1);
	   set_binary_left_operand (h, t);
	   next_symbol (s);
	   set_binary_right_operand (h, parse_expression (prio + 1, s));
	   t = h;
	}

	return h;
}

// just a simple predicate for determining whether or not the symbol s
// may start a declaration
int starts_decl (struct symbol *s) {
	switch (symbol_value (s)) {
	   case S_BASICTYPE:
	   case S_PROC:
	   case S_SWITCH:
	   case S_ARRAY:
	   case S_OWN:
	      return TRUE;

	   default:
	      return FALSE;
	}
}

//	parse a switch declaration, hang it in the tree
void	parse_switch_declaration (treenode *b, treenode *t, struct symbol *s) {
treenode *d;

	d = new_node (SWITCH_DECL, symbol_lineno (s), symbol_charno (s));
	set_decl_ident (d, symbol_repr (s));
	set_decl_env (d, b);
	next_symbol (s);
	if (!check_for (S_ASSIGN, S_SEMI, s)) 
	   return;

	next_symbol (s);
	set_switchlist (d, parse_expressionlist (s));
	if (find_in_scope (get_block_number (b), get_decl_ident (d))) {
	   syn_error (s, "Declaration switch %s not unique\n",
	              get_decl_ident (d), "");
	}
	else
	{  add_entry (d, get_decl_ident (d));
	   set_decl_env (d, b);
	   link_declaration (b, d);
	}
}

// parse a simple variable declaration, hang it in the tree and process it.
// Whether or not t is "own" is inherited, the "type" is also inherited
void	parse_simdecl (treenode *b, treenode *t, struct symbol *s, int is_own) {
treenode *v;

	v = new_node (VARIABLE, symbol_lineno (s), symbol_charno (s));
	set_decl_ident (v, symbol_repr (s));
	set_type_of_var (v, t);
	if (find_in_scope (get_block_number (b), get_decl_ident (v))) {
	   syn_error (s, "Declaration %s not unique \n", get_decl_ident (v), "");
	   return;
	}

	add_entry (v, get_decl_ident (v));
	set_decl_env (v, b);
	link_declaration (b, v);

	if (is_own)
	   set_own (v);
	next_symbol (s);
}

//	process the idlist in [own] type id {, id}*
void	parse_simdecls (treenode *b, treenode *t, struct symbol *s, int is_own) {
	parse_simdecl (b, t, s, is_own);
	while (symbol_value (s) == S_COMMA) {
	   next_symbol (s);
	   parse_simdecl (b, t, s, is_own);
	}

	check_for (S_SEMI, S_SEMI, s);
}

// array declarations are awful, due to the generalized form
// type a, b, c [e1:e2], d, e, f [e3:e4];
treenode *parse_bounds (struct symbol *s) {
treenode *e1, *e2; 
treenode *b1, *b2, *b3;

	e1 = parse_expression (0, s);
	if (!check_for (S_COLON, S_SEMI, s)) 
	   return (treenode *)0;

	next_symbol (s);
	b1 = b2 = b3 = new_node (BOUNDS, 0, 0);
	set_first_bound (b1, e1);
	set_second_bound (b1, parse_expression (0, s));
	while (symbol_value (s) == S_COMMA) {
	   next_symbol (s);
	   e1 = parse_expression (0, s); 
	   if (!check_for (S_COLON, S_SEMI, s)) 
	      return b1;

	   next_symbol (s);
	   b3 = new_node (BOUNDS, 0, 0);
	   set_first_bound (b3, e1);
	   set_second_bound (b3,  e2 = parse_expression (0, s));
	   set_nextnode (b2, b3);
	   b2 = b3;
	}

	return b1;
}

// process a single identifier appearing in a list
// as int array x, y, z ...
//
void	parse_array_ident  (treenode *b, treenode *st, struct symbol *s, int is_own) {
treenode *t;

	if (symbol_value (s) == S_IDENT) {
	   t = new_node (VARIABLE, symbol_lineno (s), symbol_charno (s));
	   set_decl_ident (t, symbol_repr (s));
	   set_type_of_var (t, st);
	   next_symbol (s);
	   if (find_in_scope (get_block_number (b), get_decl_ident (t))) {
	      syn_error (s, "Declaration of array variable %s not unique\n",
	                 get_decl_ident (t), "");
	   }
	   else
	   {  add_entry (t, get_decl_ident (t));
	      set_decl_env (t, b);
	      link_declaration (b, t);
	   }
	   if (is_own)
	      set_own (t);
	}
}

//
// process the whole list identifiers in an array declaration
// int array X, Y, ..., Z [ ...
//
void	parse_array_identifiers (treenode *b, treenode *st, struct symbol * s, int is_own) {
	parse_array_ident (b, st, s, is_own);
	while (symbol_value (s) == S_COMMA) {
	   next_symbol (s);
	   parse_array_ident (b, st, s, is_own);
	}
}

void	parse_arraydecl (treenode *b, treenode *el_type, struct symbol *s, int is_own) {
treenode *bnd;
treenode *ad;

	if (symbol_value (s) != S_IDENT)
	   return;

	ad = new_node (SUBTYPE, 0, 0);
	set_basetype (ad, get_arraytype (el_type));
	set_decl_env (ad, b);
	link_declaration (b, ad);
	if (is_own)
	   set_own (ad);

	parse_array_identifiers (b, ad, s, is_own);
	if (!check_for (S_SUB, S_SEMI, s)) 
	   return;

	next_symbol (s);
	bnd = parse_bounds (s);
	set_subtype_bounds (ad, bnd);
	set_subtype_dims (ad, count_entities (get_subtype_bounds (ad)));
	if (!check_for (S_BUS, S_SEMI, s)) 
	   return;

	next_symbol (s);
}

void	parse_arraydecls (treenode *b, treenode *t, struct symbol *s, int is_own) {

	parse_arraydecl (b, t, s, is_own);
	while (symbol_value (s) == S_COMMA) {
	   next_symbol (s);
	   parse_arraydecl (b, t, s, is_own);
	}
}
//
//	parse VALUE ID_LIST
void	parse_value_params (treenode *p, struct symbol *s) {
	next_symbol (s);
	parse_value_ids (p, s);
	check_for (S_SEMI, S_SEMI, s);
	next_symbol (s);
}

void	parse_value_ids (treenode *p, struct symbol *s) {
	parse_value_id (p, s);
	while (symbol_value (s) == S_COMMA) {
	   next_symbol (s);
	   parse_value_id (p, s);
	}
}

void	parse_value_id  (treenode *p, struct symbol *s) {
treenode *t;

	if (symbol_value (s) != S_IDENT) {
	   syn_error (s, "Value specification for proc %s contains garbage\n",
	              get_decl_ident (p), "");
	   return;
	}

	t = find_in_scope (get_blockno_of_proc (p), symbol_repr (s));
	if (t == (treenode *)0) {
	   syn_error (s, "Illegal value specification for %s in procedure %s\n",
	              symbol_repr (s), get_decl_ident (p));
	}
	else
	if (is_specified_as_value (t)) {
	   syn_error (s, "Identifier %s double in value list (proc %s)\n",
	              symbol_repr (s), get_decl_ident (p));
	}
	else
	   set_specified_as_value (t);
	next_symbol (s);
}
//	the LL(2) construct in Algol.
//	recognize
//	  {,|) ident :(}
//	which obviously conflicts with the S_RPAR as terminating symbol
int	param_separator (struct symbol *s) {
struct symbol *la;

	if (symbol_value (s) == S_COMMA) {
	   next_symbol (s);
	   return TRUE;
	}

	if (symbol_value (s) != S_RPAR) 
	   return FALSE;

	peek_ahead (&la);
	if (symbol_value (la) != S_IDENT)
	   return FALSE;

	next_symbol (s);	// get rid of the look ahead
	next_symbol (s);
	if (symbol_value (s) != S_COLON) {
	   syn_error (s, "Illegal parameter separator (got %s)\n", 
	              symbol_repr (s), "");
	   return FALSE;
	}

	next_symbol (s);
	if (symbol_value (s) != S_LPAR) {
	   syn_error (s, "( expected in parameter separator (got %s)\n",
	              symbol_repr (s), "");
	   return FALSE;
	}

	next_symbol (s);
	return TRUE;
}

//	recognize and process id {SEPARATOR id}*
//	and process them as parameters
void	parse_params (treenode *p, struct symbol *s) {
struct symbol la;
	// we assume we start with an ident
	parse_param (p, s);
	// here an ugly separator may appear
	while (param_separator (s)) {
	   parse_param (p, s);
	}
	if (symbol_value (s) != S_RPAR) 
	   syn_error (s, "Parameter list not ended by ) (got %s)\n",
	              symbol_repr (s), "");
	next_symbol (s);
}

//	recognize and process a single parameter identifier
void	parse_param  (treenode *p, struct symbol *s) {
treenode *t1;

	if (symbol_value (s) != S_IDENT) {
	   syn_error (s, "Identifier expected as formal parameter (got %s)\n",
	              symbol_repr (s), "");
	   return;
	}
	t1 = new_node (PARAM_DECL, symbol_lineno (s), symbol_charno (s));
	set_decl_ident (t1, symbol_repr (s));

	if (find_in_scope (get_blockno_of_proc (p), get_decl_ident (t1))) {
	   syn_error (s, "In procedure %s, parameter %s not unique\n",
	              get_decl_ident (p),  get_decl_ident (t1));
	}
	else 
	   add_entry (t1, get_decl_ident (t1));

	link_declaration (p, t1);
	set_decl_env (t1, p);
	next_symbol (s);
}

//	recognize and process a single id in a parameter specification
void	parse_parspec (treenode *p, treenode* tp, struct symbol *s) {
treenode *t;

	if (symbol_value (s) != S_IDENT) {
	  syn_error (s, "Identifier expected (rather than %s) as specifier\n",
	             symbol_repr (s), "");
	   next_symbol (s);
	   return;
	}

	t = find_in_scope (get_blockno_of_proc (p), symbol_repr (s));
	if (t == (treenode *)0) {
	   syn_error (s, "%s not declared as parameter\n",
	              symbol_repr (s), "");
	   next_symbol (s);
	   return;
	}

	if (is_defined (t)) {
	   syn_error (s, "Param %s specified more than once \n",
	              symbol_repr (s), "");
	}
	else
	{  set_param_type (t, tp);
	   set_defined (t);
	}

	next_symbol (s);
}

//	parse and process id {, id}* in a specification of parameters
void	parse_parspecs (treenode *p, treenode* t, struct symbol *s) {
	parse_parspec (p, t, s);
	while (symbol_value (s) == S_COMMA)  {
	   next_symbol (s);
	   parse_parspec (p, t, s);
	}
}

//	parse and process
//	{type| type array | type procedure |
//	 procedure | switch |array | label | string} id {, id}*

void	parse_param_spec (treenode *p, struct symbol *s) {
treenode *h;

	if (symbol_value (s) == S_BASICTYPE) {
	      h = get_type (symbol_repr (s));
	      if (h == (treenode *)0) return;
	      next_symbol (s);
	      switch (symbol_value (s)) {
	         case S_IDENT: 
	              parse_parspecs (p, h, s);
	              return;

	         case S_ARRAY:
	              next_symbol (s);
	              parse_parspecs (p, get_arraytype (h), s);
	              return;

	         case S_PROC:
	              next_symbol (s);
	              parse_parspecs (p, get_proctype (h), s);
	              return;

	         default:
	              ASSERT (FALSE, ("Expert error 1"));
	              return;
	      }
	      return;
	}

	h = (treenode *)0;	//the default value
	if (symbol_value (s) == S_LABEL) {
	   h = lab_type;
	}
	else
	if (symbol_value (s) ==  S_PROC) {
	   h = get_proctype (void_type);
	}
	else
	if (symbol_value (s) == S_ARRAY) {
	   h = get_arraytype (real_type);
	}
	else
	if (symbol_value (s) == S_STRING) {
	   h = string_type;
	}
	else
	if (symbol_value (s) == S_SWITCH) {
	   h = get_arraytype (lab_type);
	}
//	h should have gotten a suitable value by now or ?
	if (h == (treenode *)0)
	   return;		// it is just something else

	next_symbol (s);
	parse_parspecs (p, h, s);
}

//	parse and process the whole parameter specification
void	parse_param_specs (treenode *p, struct symbol *s) {

	parse_param_spec (p, s);
	while (symbol_value (s) == S_SEMI) {
	   next_symbol (s);
	   parse_param_spec (p, s);
	}
}

//	parse and process a whole procedure declaration
//	the type (if any) is inherited
//	the flag p indicates whether or not we are in the prelude
//	where the use of external procedure specifications is allowed
//	id [(id {SEPARATOR id} *) ; [value {id {, id}*}; ] specification] ...
void	parse_procdecl (treenode *b, treenode *t, struct symbol *s, int p) {
treenode *pd;

	pd = new_node (PROC_DECL, symbol_lineno (s), symbol_charno (s));
	set_decl_ident (pd, symbol_repr (s));
	set_proc_returntype (pd, t);

	if (find_in_scope (get_block_number (b), get_decl_ident (pd))) {
	   syn_error (s, "Decl of procedure %s not unique in block\n",
	              get_decl_ident (pd), "");
	}
	else
	{  add_entry (pd, get_decl_ident (pd));
	   set_decl_env (pd,  b);
	   link_declaration (b, pd);
	}

	set_blockno_of_proc (pd, create_scope (pd));
	next_symbol (s);
	if (symbol_value (s) == S_LPAR) { // we have got parameters
	   next_symbol (s);
	// parse them up to and including the corresponding RPAR, so here
	// expect a SEMI colon
	   parse_params (pd, s);
	   if (!check_for (S_SEMI, S_SEMI, s)) 
	      return;

	   next_symbol (s);
	   if (symbol_value (s) == S_VALUE)
	      parse_value_params (pd, s); // he checks itself for a semi if not empty
	   parse_param_specs (pd, s);
	}
	else
	{  check_for (S_SEMI, S_SEMI, s);
	   next_symbol (s);
	}

	if (p && (symbol_value (s) == S_CPROC)) {
	   set_proc_body (pd, 0);
	   set_flags (pd, get_flags (pd) | C_PROC);
	   next_symbol (s);
	}
	else
	{  set_proc_body (pd, new_node (BLOCK, symbol_lineno (s), symbol_charno (s)));
	   set_surrounding (get_proc_body (pd), pd);
	   set_block_number (get_proc_body (pd),
		        create_scope (get_proc_body (pd)));
	   parse_stat (get_proc_body (pd), get_proc_body (pd), s);
	   leave_scope ();
	}

	leave_scope ();
}

//	parse_decl processes a declaration. The declaration can be
//	an own declaration, so first factor own out, if any
//
//	[own] declaration
int	parse_decl (treenode *b, struct symbol *s, int p) {
	if (!starts_decl (s))
	   return FALSE;

	if (symbol_value (s) == S_OWN) {
	   next_symbol (s);
	   parse_non_own_declaration (b, s, p, TRUE);
	}
	else
	   parse_non_own_declaration (b, s, p, FALSE);

	return TRUE;
}

//	any form of a non own declaration
//	basic type id {, id}* |
//	[basic type] {array_declaration | proc declaration} |
//	switch id := expression {, expression_list}
void	parse_non_own_declaration (treenode *b, struct symbol *s, int p, int is_own) {
treenode *t, *d;

	switch (symbol_value (s)) {
	   case S_BASICTYPE: // this is the complex one
	      t = get_type (symbol_repr (s));
	      next_symbol (s);
	      switch (symbol_value (s)) {
	         case S_IDENT: // declaration of simple variable list
	            parse_simdecls (b, t, s, is_own);
	            return;

	         case S_ARRAY: // declaration of arrays
	            next_symbol (s);
	            if (!check_for (S_IDENT, S_SEMI, s)) 
	               return;

	            parse_arraydecls (b, t, s, is_own);
	            return;

	         case S_PROC:  // non-void procedure declaration
	            next_symbol (s);
	            if (!check_for (S_IDENT, S_SEMI, s)) 
	               return;
	            if (is_own) 
	               syn_error (s, "Proc (%s) can not be own\n", symbol_repr (s), "");
	            parse_procdecl (b, t, s, p);
	            return;

	         default:
	            syn_error (s, "Unexpected token %s in (presumed) declaration\n",
	                       symbol_repr (s), "");
	            return;
	      }

	   case S_PROC:  // void procedure
	      next_symbol (s);
	      if (!check_for (S_IDENT, S_SEMI, s)) 
	         return;

	      if (is_own)
	         syn_error (s, "proc %s can not be own\n", symbol_repr (s) , "");
	      parse_procdecl (b, void_type, s, p);
	      return;

	   case S_ARRAY: // declaration of arrays
	      next_symbol (s);
	      if (!check_for (S_IDENT, S_SEMI, s)) 
	          return;

	      parse_arraydecls (b, real_type, s, is_own);
	      return;

	   case S_SWITCH: 
	      next_symbol (s);
	      if (!check_for (S_IDENT, S_SEMI, s)) 
	         return;

	      if (is_own)
	         syn_error (s, "switch cannot be own\n", symbol_repr (s), "");
	      parse_switch_declaration (b, lab_type, s);
	      return;

	   default:
	     return;
	}
}

//	declaration {; declaration}*
//	here the catch is that in A60 there is no marker between
//	declarations and statements in a block
void	parse_decls (treenode *b, struct symbol *s, int p) {
int t = parse_decl (b, s, p);

	while (t != 0) {
	   if (!check_for (S_SEMI, S_SEMI, s)) 
	       return;
           next_symbol (s);
           t = parse_decl (b, s, p);
	}
}

//
//	stat {; stat} *
void	parse_stats (treenode *e, treenode *b,  struct symbol *s) {
treenode *t1;

	parse_stat (e, b, s);
	while (symbol_value (s) == S_SEMI) {
	   next_symbol (s);
	   parse_stat (e, b, s);
	}
}

//	expression {, expression} *
treenode *parse_expressionlist (struct symbol *s) {
treenode *t1, *t2, *t3;

	t1 = t2 = t3 = parse_expression (0, s);
	while ((symbol_value (s) == S_COMMA) &&
	       (t3 != (treenode *)0)) {
	   next_symbol (s);
	   t3 = parse_expression (0, s);
	   set_nextnode (t2, t3);
	   t2 = t3;
	}

	return t1;
}

//	actparlist is more or less the same as an expressionlist
//	expression {PARAMETER SEPARATOR expression} *
treenode *parse_actpar (struct symbol *s) {
treenode *t1;

	t1 = new_node (ACT_PAR, symbol_lineno (s), symbol_charno (s));
	set_act_exp (t1, parse_expression (0, s));
	return t1;
}

treenode *parse_actparlist (struct symbol *s) {
treenode *t1, *t2;

	t1 = t2 = parse_actpar (s);
	while (param_separator (s)) {
	   // next_symbol (s);
	   set_nextnode (t2, parse_actpar (s));
	   t2 = get_nextnode (t2);
	}

	return t1;
}

//	expression {:= expression}*
treenode *parse_assignmentrhs (struct symbol *s) {
treenode *t1, *t2, *t3;

	t1 = parse_expression (0, s);
	if (symbol_value (s) == S_ASSIGN) {
	   next_symbol (s);
	   t3 = new_node (ASSIGNMENT, symbol_lineno (s), symbol_charno (s));
	   t2 = parse_assignmentrhs (s);
	   set_lhs_expression (t2, t1);
	   set_rhs_expression (t3, t2);
	   return t3;
	}

	t2 = new_node (ASSIGNMENT, symbol_lineno (s), symbol_charno (s));
	set_rhs_expression (t2, t1);
	return t2;
}


//	encountering a single id is awful
//	id : refers to a label
//	id ( refers to a procedure call
//	id [ refers to a subscripted variable, must be an lhs
//	id := refers to a left hand side of an expression
//	id in other cases must refer to a parameterless procedure call
//	labels are especially awful,
//	labels are linked to empty statements in the tree
treenode *parse_id_as_stat (treenode *env, treenode *b, struct symbol *s) {
treenode *l, *d, *exp, *f;
char *ident = symbol_repr (s);
int  lineno = symbol_lineno (s);
int  charno = symbol_charno (s);

	next_symbol (s);
	switch (symbol_value (s)) {
	   case S_COLON:	// a label declaration
	      l = new_node (LABEL_DECL, lineno, charno);
	      set_decl_ident (l, ident);
	      if (find_in_scope (block_of (b), get_decl_ident (l))) {
	         syn_error (s, "%s (declared as label) was already declared\n",
	                 get_decl_ident (l), "");
	      }

	      add_entry (l, get_decl_ident (l));
	      set_decl_env (l, b);
	      link_in_front_to (b, l);
	      f = new_node (NULL_STAT, symbol_lineno (s), symbol_charno (s));
	      set_label (f, l);
	      set_value_of_label (l, f);
	      link_statement (env, f);
	      next_symbol (s);
	      parse_stat (env, b, s);
	      return f;

	   case S_LPAR:  // It is a procedure call with parameters
	      exp = parse_functioncall (s, lineno, charno, ident);
	      link_statement (env, exp);
	      return exp;

	   case S_SUB:
	      exp = parse_indexing (s, lineno, charno, ident);
	      if (!check_for (S_ASSIGN, S_SEMI, s)) 
	         return (treenode *)0;

	      next_symbol (s);
	      f = parse_assignmentrhs (s);
	      set_lhs_expression (f, exp);
	      link_statement (env, f);
	      return f;

	   case S_ASSIGN:
	      exp = new_node (ID_AS_PRIM, symbol_lineno (s), symbol_charno (s));
	      set_resolve_ident (exp, ident);
	      next_symbol (s);
	      f = parse_assignmentrhs (s);
	      set_lhs_expression (f, exp);
	      link_statement (env, f);
	      return f;

	   default: // it must be a parameterless call
	      f = new_node (FUNCTION_CALL, lineno, charno);
	      set_function_ident (f, ident);
	      link_statement (env, f);
	      return f;
	}
}

// parse a single statement
treenode *parse_stat (treenode *env, treenode *b, struct symbol *s) {
treenode *t1;

	switch (symbol_value (s)) {
	   case S_IDENT:  // this can be a label, a procedure call or the left
	                  // hand side for an assignment
	      return parse_id_as_stat (env, b, s);

	   case S_IF: // This is an IF statement
	      return parse_if_stat (env, b, s);

	   case S_GOTO:
	   case S_GO:
	      return parse_goto (env, b, s);

	   case S_FOR: 
	      return parse_for_stat (env, b, s);

	   case S_BEGIN: // a block or a compound statement
	      return parse_block_or_compound (env, b, s);

	   default:	// it is a null statement
	      t1 = new_node (NULL_STAT, symbol_lineno (s), symbol_charno (s));
	      link_statement (env, t1);
	      return t1;
	}
}

//
//	goto expr OR go to expr
treenode *parse_goto (treenode *env, treenode *b, struct symbol *s) {
treenode *t1;

	if (symbol_value (s) == S_GO) {
	   next_symbol (s);
	   if (!check_for (S_TO, S_SEMI, s))
	      return (treenode *)0;
	}

	next_symbol (s);
	t1 = new_node (GOTO_STAT, symbol_lineno (s), symbol_charno (s));
	set_target (t1, parse_expression (0, s));
	link_statement (env, t1);
	return t1;
}

//
//	we read a S_BEGIN and are processing
//	[declarations;] statements END
//	If there are no declarations, the statement is a compound
//	rather than a block (no scope border)
// 	Notice that statements are linked in either a compound
//	or block, while declarations naturally are linked into a
//	block
treenode *parse_block_or_compound (treenode *e, treenode *b, struct symbol *s) {
treenode *t1;

	next_symbol (s);
// first determine whether there is a declaration or not
	if (starts_decl (s)) {
	   t1 = new_node (BLOCK, symbol_lineno (s), symbol_charno (s));
	   set_surrounding (t1, e);
	   set_block_number (t1, create_scope (t1));
	   parse_decls (t1, s, FALSE);
	   parse_stats (t1, t1, s);
	   leave_scope ();
	}
	else {
	   t1 = new_node (COMPOUND, symbol_lineno (s), symbol_charno (s));
	   set_surrounding (t1, e);
	   parse_stats (t1, b, s);
	}

	check_for (S_END, S_SEMI, s);
	next_symbol (s);
	link_statement (e, t1);
	return t1;
}

//	if  expression then statement [else statement]
treenode *parse_if_stat (treenode *e, treenode *b, struct symbol *s) {
treenode *t1, *t2, *t3;
treenode *b2;

	t1 = new_node (IF_STAT, symbol_lineno (s), symbol_charno (s));
	next_symbol (s);
	set_ifcondition (t1, parse_expression (0, s));
	if (!check_for (S_THEN, S_SEMI, s)) 
	   return (treenode *)0;

	next_symbol (s);
	// create an environment for the then part (a compound environment)
	b2 = new_node (COMPOUND, 0, 0);
	set_surrounding (b2, e);
	if (symbol_value (s) == S_FOR) {
	   parse_stat (b2, b, s);
	   set_ifthenpart (t1, b2);
	   b2 = (treenode *)0;
	}
	else {
	   parse_stat (b2, b, s);
	   set_ifthenpart (t1, b2);
	   if (symbol_value (s) == S_ELSE) {
	      next_symbol (s);
	      b2 = new_node (COMPOUND, 0, 0);
	      set_surrounding (b2, b);
	      parse_stat (b2, b, s);
	   }
	   else
	      b2 = (treenode *)0;
	}

	set_ifelsepart (t1, b2);
	link_statement (e, t1);
	return t1;
}

//
//	for expression := for elements do S
//
treenode *parse_for_stat (treenode *e, treenode *b, struct symbol *s) {
treenode *t1, *proc, *bl;

	next_symbol (s);
	t1 = new_node (FOR_STATEMENT, symbol_lineno (s), symbol_charno (s));
	set_for_var (t1, parse_expression (0, s));
	if (!check_for (S_ASSIGN, S_SEMI, s)) 
	   return (treenode *)0;

	next_symbol (s);
	set_for_el_list (t1, parse_forelements (b, s));
	if (!check_for (S_DO, S_SEMI, s)) 
	   return (treenode *)0;

//	In case there is more than a single element in the for list,
//	the body is transformed into a procedure which will be called
//	during the execution of the for statement
//	The simple case is dealt with first
	if (get_nextnode (get_for_el_list (t1)) == (treenode *)0) {
	   bl = new_node (BLOCK, 0, 0);
	   set_surrounding (bl, e);
	   set_block_number (bl, create_scope (bl));
	   set_for_body (t1, bl);
	   next_symbol (s);
	   parse_stat (bl, bl, s);
	   leave_scope ();
	   link_statement (e, t1);
	   return t1;
	}
//
//	Now the tough case. We have to set up in the tree a structure
//	that resembles a procedure declaration and replace in the for statement
//	the statements by a call to this procedure
//	It is not complex, but basically just a lot of work
	proc = new_node (PROC_DECL, 0, 0);
	set_decl_ident (proc, new_for_id (b));
	set_proc_returntype (proc, void_type);
	add_entry (proc, get_decl_ident (proc));
	set_decl_env (proc, b);
	link_declaration (b, proc);
	set_blockno_of_proc (proc, create_scope (proc));
	next_symbol (s);
	set_proc_body (proc, new_node (BLOCK, 0, 0));
	set_surrounding (get_proc_body (proc), proc);
	set_block_number (get_proc_body (proc),
	              create_scope (get_proc_body (proc)));
	parse_stat (get_proc_body (proc),
	            get_proc_body (proc), s);
	leave_scope ();
	leave_scope ();
	set_for_body (t1, make_proc_call (b, proc));
	link_statement (e, t1);
	return t1;
}

//	expression step expression until expression |
//	expression while expression |
//	expression
treenode *parse_step_element (treenode *e, treenode *e1, struct symbol *s) {
treenode *e2, *fe;
//	last symbol read: STEP
	next_symbol (s);
	e2 = parse_expression (0, s);
	if (!check_for (S_UNTIL, S_SEMI, s)) 
	   return (treenode *)0;

	next_symbol (s);
	fe = new_node (STEP_UNTIL, symbol_lineno (s), symbol_charno (s));
	set_step_init (fe, e1);
	set_incr_expression (fe, e2);
	set_until_expression (fe, parse_expression (0, s));
	return fe;
}

treenode *parse_while_element (treenode *e, treenode *e1, struct symbol *s) {
treenode *fe;
//	last symbol read: WHILE
	next_symbol (s);
	fe = new_node (WHILE_ELEMENT, symbol_lineno (s), symbol_charno (s));
	set_while_init (fe, e1);
	set_while_condition (fe, parse_expression (0, s));
	return fe;
}

treenode *parse_forelement (treenode *e, struct symbol *s) {
treenode *e1;
treenode *fe;

	e1 = parse_expression (0, s);
	switch (symbol_value (s)) {
	   case S_STEP:
	      return parse_step_element (e, e1, s);

	   case S_WHILE:
	      return parse_while_element (e, e1, s);

	   default:
	      fe = new_node (SINGLE_FOR_ELEMENT, symbol_lineno (s), symbol_charno (s));
	      set_single_expr (fe, e1);
	      return fe;
	}
}

//	for_element {S_COMMA for_element}
//
treenode *parse_forelements (treenode *e, struct symbol *s) {
treenode *t1, *t2;

	t1 = t2 = parse_forelement (e, s);
	while (symbol_value (s) == S_COMMA) {
	   next_symbol (s);
	   set_nextnode (t2, parse_forelement (e, s));
	   t2 = get_nextnode (t2);
	}

	return t1;
}

void	syn_error (struct symbol *s, char *fmt, char *s1, char *s2) {
	fprintf (stderr, "Syntax analysis, line %d (file %s):",
	         symbol_lineno (s), current_file);
	fprintf (stderr, fmt, s1, s2);
	errors ++;
	if (errors > MAX_ERRORS) {
	   fprintf (stderr, "Too many errors, bailing out\n");
	   exit (EXIT_FAILURE);
	}
}

//
//	analyse
//	basically analyse the tree on name and typing aspects
//	and set some flags, useful for code generation
void	analyse		(treenode *c, treenode *n) {

	while (n != (treenode *)0) {
	   switch (get_nodeid (n)) {
	      case SWITCH_DECL:
	         analyse_switch  (c, n);
	         break;

	      case LABEL_DECL:
	         analyse_labdecl (c, n);
	         break;

	      case SUBTYPE:
	         analyse_subtype (c, n);
	         break;

	      case PROC_DECL:
	         analyse_procdecl (c, n);
	         break;

	      case VARIABLE:
	         analyse_vardecl  (c, n);
	         break;

	      case BLOCK:
	         analyse (n, get_block_decls (n));
	         analyse (n, get_statements (n));
	         break;

	      case COMPOUND:
	         analyse (c, get_statements (n));
	         break;

	      case FOR_STATEMENT:
	         analyse_forstat (c, n);
	         break;

	      case FUNCTION_CALL:
	         analyse_functioncall (c, void_type, n, FALSE);
	         break;

	      case ASSIGNMENT:
	         analyse_assignment   (c, n);
	         break;

	      case IF_STAT:
	         analyse_expression (c, bool_type, get_ifcondition (n), FALSE);
	         analyse            (c, get_ifthenpart (n));
	         analyse            (c, get_ifelsepart (n));
	         break;

	      case GOTO_STAT:
	         analyse_expression (c, lab_type, get_target (n), FALSE);
	         break;

	      case NULL_STAT:
	         break;

	      default:
	         ASSERT (FALSE, ("Expert error 2"));
	         return;
	   }
	   n = get_nextnode (n);
	}
}
//
//	analyse a switch declaration, type check the expressions and count them
//
void	analyse_switch	(treenode *b, treenode *s) {
int count	= 0;
treenode	*e = get_switchlist (s);
treenode	*p = get_environmental_proc (b);

	while (e != (treenode *)0) {
	   count ++;
//	   notice that the context of analysis is the switch decl
	   analyse_expression (s, lab_type, e, TRUE);
	   e = get_nextnode (e);
	}

	set_num_of_switch_elements (s,  count);
	set_elaborated (s);
	link_to_globals (s);
//	surrounding procedure cannot be compiled as simple C
	set_needs_ar (p);
	
}

//	analyse a label declaration, just keep it simple
//
void	analyse_labdecl		(treenode *b, treenode *l) {
	set_elaborated (l);
	set_statement_has_label (get_value_of_label (l));
	link_to_environmental_proc (l);
	set_needs_ar (get_environmental_proc (b));
}

//
//	analyse a procedure declaration
//
void	analyse_procdecl (treenode *b, treenode *p) {
int	count	= 0; // count the parameter
treenode	*par = get_proc_parameters (p);
treenode	*env_proc = get_environmental_proc (b);

	set_proc_level (p, proc_level_of (b) + 1);
	link_to_globals (p);

	while (par != (treenode *)0) {
	   count ++;
	   if (!is_defined (par)) {
	      sem_error (get_lineno (p),
	                "In proc %s, param %s insufficiently specified\n",
	                 get_decl_ident (p),  get_decl_ident (par));
	      set_defined (par);
	      set_param_type (par, error_type);
	   }

	   if (is_specified_as_value (par) &&
	       !is_valid_value_param (par)) {
	      sem_error (get_lineno (p),
	                 "param %s in proc %s cannot be value\n",
	                 get_decl_ident (par),
	                 get_decl_ident (p));
	   }

	   if (is_specified_as_value (par) &&
	       is_arithmetic_array (par))
	      set_needs_deallocation (p);
//	only NO activation record in case of
//	a. simple value parameter
//	b. by name array
//	c. string
	   if ((is_specified_as_value (par) && type_of_entity_is_simple (par)) ||
	       ((!is_specified_as_value (par)) && is_arithmetic_array (par)) ||
	       (has_string_type (par)) )
	   ;	// do not remove this null statement
	   else
	      set_needs_ar (p);

	   set_elaborated (par);
	   par = get_nextnode (par);
	}

	set_num_of_pars (p, count);
	set_elaborated (p);

	if (is_cproc (p)) 
	   return;

	analyse (get_proc_body (p), get_proc_body (p));

	if ((result_type (p) != void_type) && !is_assigned_to (p)) {
	   sem_error (get_lineno (p),
	              "In %s no assignment to proc variable\n",
	               get_decl_ident (p), "");
	}
//	if this proc needs a link, then the outer one
//	will need an ar
	if (need_static_link (p))
	   set_needs_ar (env_proc);
}

void	analyse_bounds	(treenode *b, treenode *bnd) {
	analyse_expression (b, int_type, get_first_bound (bnd), FALSE);
	analyse_expression (b, int_type, get_second_bound (bnd), FALSE);

	if (is_constant_expression (get_first_bound (bnd)) &&
	    is_constant_expression (get_second_bound (bnd))) 
	   set_constant_expression (bnd);
	if (is_erroneous (get_first_bound (bnd)) ||
	    is_erroneous (get_second_bound (bnd)))
	   set_error (bnd);
}
//
//
//	A stupid patch: since we cannot specify more dimensional
//	static arrays (i.e. int a [][]), we declare arrays
//	with more than one dimension non-static
void	analyse_subtype	 (treenode *environment, treenode *s) {
char	static_bounds = TRUE; // unless proven false
treenode *bnd = get_subtype_bounds (s);
int	num_of_bounds	= 0;

	while (bnd != (treenode *)0) {
	   analyse_bounds (environment, bnd);
	   num_of_bounds ++;
	   if (!is_constant_expression (bnd))  {
	      static_bounds = FALSE;
	   }
	   bnd = get_nextnode (bnd);
	}

	if ((static_bounds) && (num_of_bounds == 1) && (proc_level_of (s) == 0))
	   set_static_array (s);
	else {
	   set_needs_deallocation (environment);
	   set_subtype_needs_descriptor (s);
	}

	set_elaborated (s);
	link_to_environmental_proc (s);
}
//
//
void	analyse_vardecl	 (treenode *b, treenode *v) {
treenode *st;
treenode *p = get_environmental_proc (b);

	if (is_arithmetic_array (v)) {
	   st = get_type_of_var (v);
	   if (is_static_array (st))
	      set_static_array (v);
	   else
	      set_needs_ar (p);
	   
	}

	if (is_own (v)) {
	   if (is_arithmetic_array (v) &&  !is_static_array (st))
	      sem_error (get_lineno (v),
	                 "%s as own array should have static bounds\n",
	                 get_decl_ident (v), "");
	}

	link_to_environmental_proc (v);
	set_elaborated (v);
}

//
//	analyse the various statements
//
treenode *analyse_id_as_lhs (treenode *environment, treenode *lhs) {
treenode *d;

	d = look_for_good_entity (environment, get_resolve_ident (lhs), lhs);
	if (d == (treenode *)0) {
	    set_error (lhs);
	    return error_type;
	}

	set_id_def (lhs, d);
	if (can_be_assigned_to (d)) { // it should be a variable or par
	   set_access (d, environment, FALSE);
	   set_assigned (d);
	   set_expr_type (lhs, type_of (d));
	   return get_expr_type (lhs);
	}

	if (is_a_proc_decl (d) && in_scope (d, environment)) {
	   set_assigned (d);
	   set_expr_type (lhs, result_type (d));
	   return get_expr_type (lhs);
	}

	sem_error (get_lineno (d), "%s cannot be used as lhs\n",
	           get_decl_ident (d), "");
	set_error (lhs);
	return error_type;
}

treenode *analyse_indexing_as_lhs (treenode *environment, treenode *lhs) {
treenode *d;

	analyse_expression (environment, any_type, lhs, FALSE);
	if (!is_erroneous (lhs)) {
	   d = get_array_def (lhs);
	   if (!can_be_assigned_to (element_type (d))) {
	      sem_error (get_lineno (d),
	                 "Cannot use a switch element (%s) as lhs\n",
	                 get_decl_ident (d), "");
	      return error_type;
	   }
	   set_assigned (d);
	}

	return (type_of (lhs));
}

treenode *analyse_lhs	(treenode *e, treenode *lhs) {
treenode *d;

	switch (get_nodeid (lhs)) {
	   case ID_AS_PRIM:
	      return analyse_id_as_lhs (e, lhs);

	   case INDEXING:
	      return analyse_indexing_as_lhs (e, lhs);

	   default:
	      sem_error (get_lineno (lhs),
	                 "Entity not suited as lhs\n", "", "");
	}
}

void	analyse_assignment (treenode *e, treenode *as) {
	analyse_expression (e, analyse_lhs (e, get_lhs_expression (as)),
	                    get_rhs_expression (as), FALSE);
}
//
//	b is env, t = context type, f is function call, ct is "in context"
void	analyse_functioncall (treenode *b, treenode *t, treenode *f, int ct) {
treenode *fn;

	fn =  look_for_good_entity (b, get_function_ident (f), f);
	if (fn == (treenode *)0) {
	   set_error (f);
	   return;
	}

	set_called_function (f, fn);
	if (!has_a_proc_type (fn)) {
	   sem_error (get_lineno (f), "call to non-proc/function %s\n",
	              get_decl_ident (fn), "");
	   set_error (f);
	   return;
	}

//	check the return type
	if (!is_compatible (t, result_type (fn))) {
	   sem_error (get_lineno (f),
	              "function call to %s has incompatible type\n",
	              get_decl_ident (fn), "");
	   set_error (f);
	   return;
	}

// Now we are sure it is a function, differentiate between parameter and not
// we mark the procedure as "used" only if it is a non-recursive call
	if (!is_parameter (fn)) {
	   analyse_parameters (b, fn, f, TRUE);
	   set_access (fn, b, ct);
	}
	else   // it is a parameter, we know nothing
	   analyse_unspecified_actuals (b, fn, f, TRUE);
	set_expr_type (f, result_type (fn));
}

void	analyse_parameters (treenode *b, treenode *p, treenode *pd, int ct) {
treenode	*for_par= get_proc_parameters (p);
treenode	*ap	= get_actuals (pd);

	while (ap != (treenode *)0) {
	   if (for_par == (treenode *)0) {
	      sem_error (get_lineno (pd),
	                 "Call to %s with more actuals than formals\n",
	                 get_decl_ident (p), "");
	      return;
	   }

	   analyse_actual_parameter (b, p, for_par, ap, ct);
	   ap = get_nextnode (ap);
	   for_par = get_nextnode (for_par);
	}

	if (for_par != (treenode *)0) {
	   sem_error (get_lineno (pd),
	              "Call to %s with too few actuals\n",
	              get_decl_ident (p), "");
	}
}

void	analyse_unspecified_actuals (treenode *b, treenode *p,
		                     treenode *pd, int ct) {
treenode *ap = get_actuals (pd); 

	while (ap != (treenode *)0) {
	   analyse_actual_parameter (b, p, (treenode *)0, ap, ct);
	   ap = get_nextnode (ap);
	}
}

//
//	analysing actual parameters
//
//	because of we are dealing with both calls to
//	known and unknown (formal) procedures, we dispatch
//	the actuals
//
//	The actual parameter should be a thunk
//	create it and let it be analysed
void	actual_is_thunk (treenode *b, treenode *ap, treenode *fp, int ct) {
treenode	*th;
treenode	*type_of_fp;

	type_of_fp = (fp == (treenode *)0)? any_type : type_of (fp);
	th = create_thunk (b, get_act_exp (ap), type_of_fp);
	analyse_expression (th, type_of_fp, th, TRUE);
	set_act_exp (ap, thunk_as_param (th));
}

//
//	the actual parameter is an identifier (formal or variable)
//	indicating an array or a switch
void	actual_is_array_id (treenode *b, treenode *ap, treenode *fp, treenode *def, int ct) {
treenode *th, *exp, *type_of_fp;

	exp = get_act_exp (ap);
	type_of_fp = (fp == (treenode *)0) ? any_type : type_of (fp);
//	value arrays have more liberal rules in type compatibility
	if ((fp != (treenode *)0) && is_specified_as_value (fp)) {
	   if (matching_param_type (type_of (def), type_of_fp)) {
	      set_id_def (exp, def);
	      set_expr_type (exp, type_of (def));
	      set_array_as_parameter (def);
	      set_access(def, b, ct);
	      set_expr_type (ap, type_of_fp);
	      return;
	   }

	   sem_error (get_lineno (ap),
	              "mismatch in type actual formal, got %s expected %s\n",
	               type_name (type_of (def)), type_name (type_of_fp));
	   set_error (ap);
	   return;
	}

//	now for name and switches
	if (type_of_fp != any_type) {
	   if (element_type (type_of_fp) != element_type (def)) {
	      sem_error (get_lineno (ap),
	                 "mismatch in type actual formal, got %s expected %s\n",
	                  type_name (type_of (def)), type_name (type_of_fp));
	      set_error (ap);
	      return;
	   }
	}
//	types are sufficiently equal
	set_id_def (exp, def);
	set_expr_type (exp, type_of (def));
	if (get_nodeid (def) == VARIABLE) // it is an array now
	   set_array_as_parameter (def);
	set_access (def, b, ct);
	set_expr_type (ap, (type_of_fp));
}

//
//	the actual is an id indicating a string
//	should be a parameter
void	actual_is_string_id (treenode *b, treenode *ap, treenode *fp, treenode *def, int ct) {
treenode *th, *exp, *type_of_fp;

	exp = get_act_exp (ap);
	type_of_fp = (fp == (treenode *)0) ? any_type : type_of (fp);
	if (matching_param_type (type_of (def), type_of_fp)) {
	   set_id_def (exp, def);
	   set_expr_type (exp, type_of (def));
	   set_expr_type (ap, type_of (def));
	   set_access (def, b, ct);
	   return;
	}

	sem_error (get_lineno (ap),
	           "Actual formal: got string rather than %s\n",
	            type_name (type_of_fp), "");
	set_error (exp);
	return;
}

//
//	The actual is an id, indicating a function
//	Notice, id is NOT a formal parameter, it is a proc_decl
//
void	actual_is_function_id (treenode *b, treenode *ap, treenode *fp, treenode *def, int ct) {
treenode *th, *exp, *type_of_fp;

	exp = get_act_exp (ap);
	type_of_fp = (fp == (treenode *)0) ? any_type : type_of (fp);
//
//	first assume it has to be passed as function parameter
//	this implies that
//		either the formal is specified as such
//		or we do not know anything about the formal
//	since matching_param ... will return TRUE for type_of_fp = any_type
//	this is OK
	if (matching_param_type (type_of (def), type_of_fp)) {
	   set_id_def (exp, def);
	   set_expr_type (exp, type_of (def));
	   set_expr_type (ap, 
	          type_of_fp == any_type ? type_of (def) : type_of_fp);
	   set_proc_as_parameter (def);
	   set_access (def, b, ct);
	   return;
	}
//
//	otherwise, is should be a call, either passed
//	directly (value parameter) or as a thunk
	if (!matching_param_type (result_type (def), type_of_fp)) {
	    sem_error (get_lineno (exp),
	               "Incompatible types for %s (%s expected)\n",
	               get_decl_ident (def),
	               type_name (type_of_fp));
	    set_error (exp);
	    return;
	}
//	now the types are OK, analyse passing on the parameter
	set_id_def (exp, def);
	set_expr_type (exp, result_type (def));
	set_expr_type (ap, type_of_fp);
	set_access (def, b, ct);
	if (!is_specified_as_value (fp))
	   set_proc_as_parameter (def);
}

//
//	The remainder, the actual is just a variable id (param may be)
//	or a label
void	actual_is_plain_id (treenode *b, treenode *ap, treenode *fp, treenode *def, int ct) {
treenode *th, *exp, *type_of_fp;

	exp = get_act_exp (ap);
	type_of_fp = (fp == (treenode *)0) ? any_type : type_of (fp);
	if ((fp != (treenode *)0) &&
	     is_specified_as_value (fp)) { // just let the expression evaluate
	   analyse_expression (b, type_of_fp, ap, ct);
	   if (is_erroneous (ap)) { // report and fall through
	      sem_error (get_lineno (ap),
	                 " Actual formal: got %s rather than %s\n",
	                 type_name (type_of (def)), type_name (type_of_fp));
	   }
	   return;
	}
// not specified by value (or may be not specified at all), it is a thunk
	actual_is_thunk (b, ap, fp, ct);
}

//
//	main dispatching on the actual is done here
//
void	analyse_actual_parameter (treenode *b, treenode *p, treenode *fp, treenode *ap, int ct)
{
treenode *th, *exp, *def, *type_of_fp;

	exp = get_act_exp (ap);
	type_of_fp = (fp == (treenode *)0) ? any_type : type_of (fp);

	if (get_nodeid (exp) != ID_AS_PRIM) {
	   if (formal_requires_thunk (fp)) {
	      actual_is_thunk (b, ap, fp, ct);
	      return;
	   }
	   else	 { // just expression passed as parameter
	      analyse_expression (b, type_of_fp, ap, TRUE);
	      return;
	   }
	}
	//	now we know: actual is single id
	def = look_for_good_entity (b, get_resolve_ident (exp), exp);
	if (def == (treenode *)0) {
	    set_error (exp);
	    return;
	}
	//	it is defined, now dispatch on properties
	if (is_arithmetic_array (def) || is_switch (def)) {
	   actual_is_array_id (b, ap, fp,def, ct);
	   return;
	}

	if (has_string_type (def)) {	// this must be a string parameter
	   actual_is_string_id (b, ap, fp, def, ct);
	   return;
	}
	//	now it is either a function id or a var id
	//	if the actual is a function parameter, or
	//	a by name parameter, we just pass it on
	if (is_parameter (def) &&
	    !is_specified_as_value (def)) { // pass on
	   if (matching_param_type (type_of (def), type_of_fp)) {
	      set_id_def (exp, def);
	      set_expr_type (exp, type_of(def));
	      set_expr_type (ap,
	                     type_of_fp == any_type ? type_of (def): type_of_fp);
	      return;
	   }
//	if there are no matching types, and def is a proc,
//	it may be a call to the proc
	   if (has_a_proc_type (type_of (def))) {
	      if (matching_param_type (result_type (def), type_of_fp)) {
	         set_id_def (exp, def);
	         set_expr_type (exp, result_type (def));
	         set_expr_type (ap,
	                       type_of_fp == any_type ? type_of (def): type_of_fp);
	         return;
	      }
	   }
//	just give up
	   sem_error (get_lineno (ap),
	              "Actual/formal: got %s, expected %s\n",
	              type_name (type_of (def)),
	              type_name (type_of_fp) );
	   return;
	}
	// 	that was the easy case
	//	now we deal with by value params, function ids
	//	and regular variables
	if (is_a_proc_decl (def)) {  // it is a function id, not a parameter
	   actual_is_function_id (b, ap, fp, def, ct);
	   return;
	}
// 	What is left is just a simple identifier for a variable or label
//	that needs to be processed
	if ((get_nodeid (def) == VARIABLE) ||
	    (is_parameter (def)) ||
	     has_label_type (def)) {
	   actual_is_plain_id (b, ap, fp, def, ct);
	   return;
	}
	// we should not be here
	ASSERT (FALSE, ("Expert error 4"));
}

//
//
void	analyse_forelement (treenode *b, treenode *t, treenode *fe) {
	if (get_nodeid (fe) == SINGLE_FOR_ELEMENT) {
	      analyse_expression (b, t, get_single_expr (fe), FALSE);
	      return;
	}

	if (get_nodeid (fe) == WHILE_ELEMENT) {
	      analyse_expression (b, t, get_while_init (fe), FALSE);
	      analyse_expression (b, bool_type, get_while_condition (fe), FALSE);
	      return;
	}

	if (get_nodeid (fe) == STEP_UNTIL) {
	      analyse_expression (b, t, get_step_init (fe), FALSE);
	      analyse_expression (b, t, get_incr_expression (fe), FALSE);
	      analyse_expression (b, t, get_until_expression (fe), FALSE);
	      return;
	}
	//	that's it, we cannot be here
}

void	analyse_forstat	(treenode *b, treenode *f) {
treenode *for_el = get_for_el_list (f);
treenode *t;

	t = analyse_lhs (b, get_for_var (f));
	while (for_el != ((treenode *)0)) {
	   analyse_forelement (b, t, for_el);
	   for_el = get_nextnode (for_el);
	}

	analyse (b, get_for_body (f));
}

//
//	analyse expressions
//	e is the expr, t the context type, e the env block
void	analyse_expressions (treenode *e, treenode *t, treenode *exp, int ct) {
	while (exp != (treenode *)0) {
	   analyse_expression (e, t, exp, ct);
	   exp = get_nextnode (exp);
	}
}
//
//	et = expression type, ct = context type
void	analyse_constant (char *v, treenode *ct, treenode *exp, treenode *et) {
	set_constant_expression (exp);
	if (!is_compatible (ct, et)) {
	   set_error (exp);
	   sem_error (get_lineno (exp), "Constant %s, expected type %s\n",
	              v, type_name (ct));
	   return;
	}

	set_expr_type (exp, et);
}

void	analyse_id_as_prim (treenode *b, treenode *t, treenode *exp, int ct) {
treenode *def;

	def = look_for_good_entity (b, get_resolve_ident (exp), exp);
	if (def == (treenode *)0) {
	   set_error (exp);
	   return;
	}

	set_id_def (exp, def);
	if (!is_compatible (t,
	            has_a_proc_type (def)? result_type (def): type_of (def))) {
	    sem_error (get_lineno (exp),
	               "Incompatible types for %s (%s expected)\n",
	               get_decl_ident (def), type_name (t));
	    set_error (exp);
	    return;
	}

	if (has_a_proc_type (def) &&
	    !is_parameter (def)) 	// it should have no parameters
	   if (get_proc_parameters (def) != (treenode *)0) {
	      sem_error (get_lineno (exp),
	                 "proc %s needs parameters\n", get_decl_ident (def), "");
	      set_error (exp);
	      return;
	   }

	set_access (def, b, ct);
	set_expr_type (exp, has_a_proc_type (def) ?result_type (def): type_of (def));
}

void	analyse_indexing   (treenode *b, treenode *t, treenode *exp, int ct) {
treenode *def;

	def = look_for_good_entity (b, get_array_ident (exp), exp);
	if (def == (treenode *)0) {
	   set_error (exp);
	   return;
	}

	if (is_arithmetic_array (def) || is_switch (def)) 
	   match_with_indices (b, exp, def, ct);
	else
	{  sem_error (get_lineno (exp),
	              "Indexing a non indexable entity (%s)\n",
	              get_decl_ident (def), "");
	   set_error (exp);
	   return;
	}

	set_array_def (exp, def);
	if (!is_compatible (t, element_type (def))) {
	    sem_error (get_lineno (exp),
	               "Element type %s cannot be converted to %s\n",
	               type_name (element_type (def)),
	               type_name (t));
	    set_error (exp);
	    return;
	}

	set_expr_type (exp, element_type (def));
	set_access (def, b, ct);
}

void	match_with_indices (treenode *b, treenode *ind, treenode *d, int ct) {
int	dim;
treenode	*e;
	// We could assert here that d is either a variable declaration,
	// a switch declaration or a param declaration
	e = get_subscripts (ind);
	analyse_expressions (b, int_type, e, ct);	// just a list

	if (get_nodeid (d) == VARIABLE) { // it is a declared array
	   dim = get_subtype_dims (get_type_of_var (d));
	   if (dim != get_num_of_subscripts (ind)) {
	       sem_error (get_lineno (ind),
	                  "incorrect number of indices for %s\n",
	                  get_decl_ident (d), "");
	   }
	   return;
	}

	if (is_switch (d)) {
	   if (get_num_of_subscripts (ind) != 1) {
	       sem_error (get_lineno (ind),
	                  "Incorrect number of indices for switch %s\n",
	                  get_decl_ident (d), "");
	   }
	   return;
	}
	// do not bother
}

void	analyse_conditional (treenode *b, treenode *t, treenode *exp, int ct) {

	analyse_expression (b, bool_type, get_cond_of_condition (exp), ct);
	analyse_expression (b, t, get_condition_thenpart (exp), ct);
	analyse_expression (b, t, get_condition_elsepart (exp), ct);
	if (is_erroneous (get_cond_of_condition (exp)) ||
	    is_erroneous (get_condition_thenpart (exp)) ||
	    is_erroneous (get_condition_elsepart (exp)) ) {
	   set_error (exp);
	   return;
	}
	if (!is_compatible (type_of (get_condition_thenpart (exp)),
	                    type_of (get_condition_elsepart (exp)))) {
	   set_error (exp);
	   return;
	}
	set_expr_type (exp, type_of (get_condition_elsepart (exp)));
}

void	analyse_unary_expression (treenode *b, treenode *t, treenode *exp, int ct) {
treenode *un_oper;

	analyse_expression (b, any_type, get_unary_operand (exp), ct);
	un_oper = get_udef (get_un_operator (exp),
	                    type_of (get_unary_operand (exp)));
	if (un_oper == (treenode *)0) {
	   sem_error (get_lineno (exp),
	              "type problem for %s operator\n",
	              op_name (get_un_operator (exp)), "");
	   set_error (exp);
	   return;
	}

	set_un_opdef (exp, un_oper);
	if (!is_compatible (t, get_return_type_for_un (un_oper))) {
	    sem_error (get_lineno (exp),
	               "Return type of %s incompatible with %s\n",
	               op_name (get_un_operator (exp)),
	               type_name (t));
	    set_error (exp);
	}

	set_expr_type (exp, get_return_type_for_un (un_oper));
	if (is_constant_expression (get_unary_operand (exp)) &&
	    is_constant_expression (un_oper))
	   set_constant_expression (exp);
}

void	analyse_binary_expression (treenode *b, treenode *t, treenode *exp, int ct) {
treenode *binop;

	analyse_expression (b, any_type,
	                    get_binary_left_operand (exp), ct);
	analyse_expression (b, any_type,
	                    get_binary_right_operand (exp), ct);
	binop = get_bdef (get_bin_operator (exp),
	                  type_of (get_binary_left_operand (exp)),
	                  type_of (get_binary_right_operand (exp)));
	if (binop == (treenode *)0) {
	   sem_error (get_lineno (exp),
	              "No identification for binary operator %s\n",
	              op_name (get_bin_operator (exp)), "");
	   set_error (exp);
	   return;
	}

	set_bin_opdef (exp, binop);
	if (!is_compatible (t, get_return_type_for_bin (binop))) {
	    sem_error (get_lineno (exp),
	               "Return type of %s incompatible with %s\n",
	               op_name (get_bin_operator (exp)),
	               type_name (t));
	    set_error (exp);
	}

	set_expr_type (exp, get_return_type_for_bin (binop));
	if (is_constant_expression (get_binary_left_operand (exp)) &&
	    is_constant_expression (get_binary_right_operand (exp)) &&
	    is_constant_expression (binop))
	   set_constant_expression (exp);
}

//
//	remark	august 2003
//	For an expression we need to know whether or not
//	it is analysed in the context of
//	1. an actual parameter
//	2. a switchlist element
//	reason: we need to keep track of the use of a label in these
//	contexts, and mark them as "far away" labels
//
void	analyse_expression (treenode *b, treenode *t, treenode *exp, int ct) {
treenode *def;

	if (exp == (treenode *)0)
	   return;

	switch (get_nodeid (exp)) {
	   case INUMBER:
	      analyse_constant (get_x_value (exp), t, exp, int_type);
	      break;

	   case FNUMBER:
	      analyse_constant (get_x_value (exp), t, exp, real_type);
	      break;

	   case BNUMBER:
	      analyse_constant (get_x_value (exp), t, exp, bool_type);
	      break;

	   case STRING_CONSTANT:
	      analyse_constant (get_x_value (exp), t, exp, string_type);
	      break;

	   case FUNCTION_CALL:
	      analyse_functioncall (b, t, exp, ct);
	      break;

	   case ID_AS_PRIM:
	      analyse_id_as_prim (b, t, exp, ct);
	      break;

	   case INDEXING:
	      analyse_indexing (b, t, exp, ct);
	      break;

	   case CONDITIONAL:
	      analyse_conditional (b, t, exp, ct);
	      break;

	   case UNARY_EXPRESSION:
	      analyse_unary_expression (b, t, exp, ct);
	      break;

	   case BINARY_EXPRESSION:
	      analyse_binary_expression (b, t, exp, ct);
	      return;

	   case ASSIGNMENT:
	      analyse_assignment (b, exp);
	      return;

	   case THUNK:
	      analyse_expression (b, t, get_thunk_expr (exp), TRUE);
	      if (is_erroneous (get_thunk_expr (exp))) {
	         set_error (exp);
	      }
	      return;

	   case ACT_PAR:
	      analyse_expression (b, t, get_act_exp (exp), TRUE);
	      if (is_erroneous (get_act_exp (exp)))
	         set_error (exp);
	      else
	         set_expr_type (exp, get_expr_type (get_act_exp (exp)));
	      return;

	   default:
	      fprintf (stderr, "Node type %d\n", get_nodeid (exp));
	      ASSERT (FALSE, ("Expert error 6"));
	      return;
	}
}

//
//	a "good" entity is an entity that is declared
//	within the scope and whose declaration was elaborated or 
//	can be trusted to be elaborated (this is when a reference is made to
//	a variable in an outer scope
//
//	Complication: for a number of flag settings we need to
//	distinguish contexts such as THUNK and SWITCHDECL, since these
//	behave more or less like procedures
//
//	Look for an declaration
//	context might be
//	a block, a compound or a proc
//	a switch or a thunk declaration
treenode *look_for_good_entity (treenode *b, char *ident, treenode *e) {
treenode *d;
int	block_no;

	if ((get_nodeid (b) == THUNK) ||
	    (get_nodeid (b) == SWITCH_DECL)) 
	   return look_for_good_entity (get_decl_env (b), ident, e);

	if (get_nodeid (b) == COMPOUND) 
	   return look_for_good_entity (get_surrounding (b), ident, e);

//	now it should be a block or a proc
	block_no = block_of (b);

	d = find_definition (block_no, ident);
	if (d == (treenode *)0) {
	   if (!in_forgotten_list (block_no, ident)) {
	      sem_error (get_lineno (e),
	                 "Could not find %s (only reported once)\n",
	                 ident, "");
	      put_in_forgotten_list (block_no, ident);
	   }

	   return (treenode *)0;
	}

	if ((get_environmental_proc (get_decl_env (d))) ==
	     get_environmental_proc (b))
	   if (!is_elaborated (d)) {
	      sem_error (get_lineno (e),
	                 "var %s not yet elaborated\n",
	                 ident, "");
	   }

	return d;
}

void	sem_error (int l, char *fmt, char *s1, char *s2) {
	fprintf (stderr, "Analysis, line %d (file %s):", l, current_file);
	fprintf (stderr, fmt, s1, s2);
	sem_errors ++;
	if (sem_errors + errors > MAX_ERRORS) {
	   fprintf (stderr, "To many errors, bailing out\n");
	   exit (EXIT_FAILURE);
	}
}

//		back end				
//	The backend makes essentially two walks over the tree	
//	During the first walk, the specifications of the various 
//	procedures, (implicit ones and explicit ones) are       
//	generated, for each jff procedure, a specification
//	In the second walk the regular code is generated        
//	In order to avoid recursive definitions in C, we had built up 
//	a prefix ordered list of declarations that will be global in C 

//	just generate some header information
void	generate_kop	(FILE *f_out, char *infile,
	                 char *include_file, char *compile_time) {
	add_to_output ("#\n\n/* jff_algol (Jan van Katwijk) */");
	add_to_output ("\n/* Version ");
	add_to_output (VERSION);
	add_to_output ("		*/\n/* input file: ");
	add_to_output (infile);
	add_to_output ("		*/\n/* Compiled at ");
	add_to_output (compile_time);
	add_to_output ("		*/\n\n\n#include	<stdio.h>");
	if (include_file != NULL) {
	   add_to_output ("\n#include \"");
	   add_to_output (include_file);
	   add_to_output ("\"\n");
	}
}

//	Headers and code is generated for the declarations
//	that are collected in the global list
//	the declarations are all kind of global
//	After generation of the headers, the code of procedures
//	(and thunks) is generated
void	generate_headers	(treenode *n) {
	add_to_output ("/* Headers		*/\n");
	while (n != (treenode *)0) {
	   if (is_accessed (n)) {
	      switch (get_nodeid (n)) {
	         case SWITCH_DECL:
	            generate_switch_spec (n);
	            break;

	         case LABEL_DECL:
	            generate_lab_spec (n);
	            break;

	         case SUBTYPE:
	            generate_subtype_spec (n);
	            break;

	         case PROC_DECL:
	            generate_proc_spec (n);
	            break;

	         case VARIABLE:
	            generate_var_spec (n);
	            break;

	         case THUNK:
	            generate_thunk_spec (n);
	            break;

	         default:
	            ASSERT (FALSE, (" Expert error 8"));
	            return;
	      }
	   }
	   n = get_next_dec (n);
	}
}

//	a switch is translated into a procedure.
//	Be careful, if the switch is accessed from within
//	the procedure it is declared in, but the procedure
//	itself is NOT accessed, we skip it
void	generate_switch_spec	(treenode *d) {
treenode *p;

	p = get_environmental_proc (d);
	if ((p != (treenode *)0) && !is_accessed (p))
	   return;

	add_to_output ("jmp_buf	*");
	add_to_output (c_nameof (d));
	add_to_output (" (char *, int);	");
	pr_declaration_comment (d);
}

void	generate_lab_spec (treenode *d) {
	if (has_far_access (d)) {
	   add_to_output ("extern	jmp_buf ");
	   add_to_output (c_nameof (d));
	   add_to_output (";");
	   pr_declaration_comment (d);
	}
}

void	generate_subtype_spec	(treenode *d) {
	if (subtype_needs_descriptor (d)) {
	   add_to_output ("extern	int ");
	   add_to_output (c_nameof (d));
	   add_to_output (" [];\n");
	}
}

//	specification of a proc is either a C specification,
//	a jff_.... or may be it can be compiled into a straightforward
//	c function
//
void	generate_proc_spec (treenode *p) {

	if (is_cproc (p) || will_be_compiled_as_c_proc (p)) 
	   generate_c_spec (p);
	else
	   generate_spec_for_jff_type_proc (p);

	if (is_proc_as_parameter (p))
	   generate_envelope_spec (p);
}

//	a C specification is easy, 
void	generate_c_spec (treenode *p) {
	add_to_output ("extern	");
	add_to_output (c_type_name (result_type (p)));
	add_to_output (" ");
	add_to_output (c_nameof (p));
	add_to_output (" (");

	parameter_specs (p);

	add_to_output (");");
	pr_declaration_comment (p);
}

//
//	The specification of a jff_ ALGOL procedure. A procedure is mapped
//	onto an implementing C procedure
void	generate_spec_for_jff_type_proc (treenode *p) {
int	i;

	generate_c_spec (p);
	add_to_output ("struct ");
	pr_type_of_ar (p);
	add_to_output (" {\n");
	if (!need_static_link (p))
	   add_to_output ("char *__l_field;\n");
	else {
	   add_to_output ("struct ");
	   pr_type_of_ar (get_environmental_proc(get_decl_env (p)));
	   add_to_output ("	*__l_field;\n");
	}

	if (result_type (p) != void_type) {
	   add_to_output (c_type_name (result_type (p)));
	   add_to_output (" __res_val;\n");
	}

	generate_par_fields (p); // the parameters of the procedure
	generate_local_fields (p); // the locals of the procedure
	add_to_output ("};\n");
}

//	For each procedure that is passed as a formal, we create an envelope
//	procedure handling the verification and transfer of
//	parameters

int	get_amount_of_values (treenode *p) {
int	count	= 0;
treenode *fp;

	fp = get_proc_parameters (p);
	while (fp != 0) {
	   if (is_switch (fp))
	      count += 3;
	   else
	   if (is_arithmetic_array (fp))
	      count += 3;
	   else
	   if (has_a_proc_type (fp)) 
	      count += 3;
	   else
	   if (has_string_type (fp))
	      count += 2;
	   else
	   if (is_specified_as_value (fp))
	      count += 4;
	   else
	      count += 4;

	   fp = get_nextnode (fp);
	}
	return count;
}

void	generate_envelope_spec (treenode *p) {
	add_to_output ("extern ");
	add_to_output (c_type_name (result_type (p)));
	add_to_output (" D");
	add_to_output (c_nameof (p));
	add_to_output (" (char *, int, ...);	");
	pr_declaration_comment (p);
}

void	generate_envelope (treenode *p) {
int	i;
treenode *fp;
int	amount_of_values;

	add_to_output (c_type_name (result_type (p)));
	add_to_output (" D");
	add_to_output (c_nameof (p));
	add_to_output (" (char *link, int n, ...) {\n");
//	the body is simple
	amount_of_values =  get_amount_of_values (p);
	if (amount_of_values > 0) {
	   add_to_output (" int i;\n  char *p1 [");
	   add_to_output (num_to_string (amount_of_values));
	   add_to_output ("];\n va_list vl;\n");
	}

	add_to_output (" if (n != ");
	add_to_output (num_to_string (get_num_of_pars (p)));
	add_to_output (")\n fault (\"wrong number of parameters for ");
	add_to_output (get_decl_ident (p));
	add_to_output ("\", (double)");
	add_to_output (num_to_string (get_lineno (p)));
	add_to_output (");\n");

	if (amount_of_values > 0) {
	   add_to_output ("  va_start (vl, ");
	   add_to_output (num_to_string (amount_of_values));
	   add_to_output (");\n for (i = 0; i < ");
	   add_to_output (num_to_string (amount_of_values));
	   add_to_output ("; i ++) p1 [i] = va_arg (vl, char *);\n va_end (vl);\n");
	}

	if (result_type (p) != void_type)
	    add_to_output ("return ");
//	otherwise, just the call suffices

	add_to_output (c_nameof (p));
	add_to_output ( "(");

	fp = get_proc_parameters (p);
	i = 1;
	if (need_static_link (p)) {
	   add_to_output ("link");
	   while (fp != (treenode *)0) {
	      add_to_output (", ");
	      transfer_code (p, fp, i ++);
	      fp = get_nextnode (fp);
	   }
	   add_to_output (");\n}\n");
	   return;
	}
//	in case of no link
	if (fp != (treenode *)0) {
	   transfer_code (p, fp, i ++);
	   fp = get_nextnode (fp);
	   while (fp != (treenode *)0) {
	      add_to_output ( ",");
	      transfer_code (p, fp, i ++);
	      fp = get_nextnode (fp);
	   }
	}
	add_to_output (");\n}\n");
}

//	When we have to generate an envelope, we need to generate 
//	transfer code for the parameters. The check that the number of
//	parameters is OK was already generated.
//	Notice that a very limited set of kinds of
//	actual can appear here
void	transfer_code (treenode *p, treenode *fp, int i) {
char	*t;

	if (is_switch (fp)) {
	   add_to_output ("(char *)(__get_switch_link (&p1,");
	   add_to_output (num_to_string (i));
	   add_to_output (" )), ");
	   add_to_output ("(char *)(__get_switch_address (&p1, ");
	   add_to_output (num_to_string (i));
	   add_to_output (", \'L\'))");
	   return;
	}

	if (is_arithmetic_array (fp)) {
	   t = c_type_name (element_type (fp));
	   add_to_output ("(int *)(__get_array_descr (&p1, ");
	   add_to_output (num_to_string (i));
	   add_to_output (", \'"); add_to_output (char_to_string (t [0]));
	   add_to_output ("\')), ");
	   add_to_output ("("); add_to_output (t);
	   add_to_output (" *)(__get_array_address (&p1, ");
	   add_to_output (num_to_string (i));
	   add_to_output (", \'"); add_to_output (char_to_string (t [0]));
	   add_to_output ("\'))");
	   return;
	}

	if (has_a_proc_type (fp)) {
	   t = c_type_name (result_type (fp));
	   add_to_output ("(char *)(__get_function_link (&p1, ");
	   add_to_output (num_to_string (i));
	   add_to_output (", \'"); add_to_output (char_to_string (t [0]));
	   add_to_output ("\')), ");

	   add_to_output ("(char *)(__get_function_address (&p1, ");
	   add_to_output (num_to_string (i));
	   add_to_output (", \'"); add_to_output (char_to_string (t [0]));
	   add_to_output ("\'))");
	   return;
	}

	if (has_string_type (fp)) {
	   add_to_output ("(char *)(__get_string_address (&p1, ");
	   add_to_output (num_to_string (i));
	   add_to_output ("))");
	   return;
	}

	if (is_specified_as_value (fp)) { //value arrays are already hadled
	   t = c_type_name (type_of (fp));
	   add_to_output ("*("); add_to_output (t);
	   add_to_output (" *)(__eval_value_thunk (&p1, ");
	   add_to_output (num_to_string (i));
	   add_to_output (", \'"); add_to_output (char_to_string (t [0]));
	   add_to_output ("\'))");
	   return;
	}

//	when we are here, it should be a thunk
	t = c_type_name (type_of (fp));
	add_to_output ("(char *)(__get_thunk_link (&p1, ");
	add_to_output (num_to_string (i));
	add_to_output (")),");

	add_to_output ("(char *) (__get_address_thunk (&p1, ");
	add_to_output (num_to_string (i));
	add_to_output (", \'"); add_to_output (char_to_string (t [0]));
	add_to_output ("\')),");

	add_to_output ("(char *)(__get_value_thunk (&p1, ");
	add_to_output (num_to_string (i));
	add_to_output (", \'"); add_to_output (char_to_string (t [0]));
	add_to_output ("\'))");
}

void	generate_thunk_spec	(treenode *th) {
treenode	*ep;

	ep = get_environmental_proc (th);
	if ((ep != (treenode *)0) && !is_accessed (ep))
	   return;

	add_to_output ("\n//	specification for thunk\n");
	add_to_output ("extern ");
	add_to_output (c_type_name (type_of (th)));
	add_to_output (" A");
	add_to_output (c_nameof (th));
	add_to_output (" (char *, ");
	add_to_output (c_type_name (type_of (th)));
	add_to_output (");\n");
//	now for the value thunk
	add_to_output ("extern ");
	add_to_output (c_type_name (type_of (th)));
	add_to_output (" ");
	add_to_output (c_nameof (th));
	add_to_output (" (char *, int);\n");
}

void	parameter_specs (treenode *p) {
treenode *fp;

	fp = get_proc_parameters (p);

	if (need_static_link (p)) {
	   add_to_output ("struct ");
	   pr_type_of_ar (get_environmental_proc (get_decl_env (p)));
	   add_to_output ("	*");

	   if (fp == (treenode *)0)
	      return;

	   add_to_output (",");
	}

	while (fp != (treenode *)0) {
	   parameter_spec (fp);
	   if ((fp = get_nextnode (fp)) != (treenode *)0)
	      add_to_output (",");
	}
}

void	parameter_spec  (treenode *fp) {
treenode *t;

	t = type_of (fp);
	if (type_of_entity_is_simple (t)) {
	   if (is_specified_as_value (fp)) {
	      add_to_output (c_type_name (t));
	      return;
	   }
//	spec is a thunk
	   add_to_output ("char	*,");	// thunk link
	   add_to_output (c_type_name (t));	// for address thunk
	   add_to_output (" (*)(char *, ");
	   add_to_output (c_type_name (t));
	   add_to_output ("), ");		// end of address thunk

	   add_to_output (c_type_name (t));	// value thunk
	   add_to_output ("(*)(char *, int)");
	   return;
	}

	if (is_switch (fp)) {
	   add_to_output ("char * ,\n");
	   add_to_output ("jmp_buf * (*)(char *, int)\n");
	   return;
	}

	if (is_arithmetic_array (fp)) {
	   add_to_output ("int *, ");
	   add_to_output (c_type_name (element_type (fp)));
	   add_to_output ("	*");
	   return;
	}

	if (has_string_type (fp)) {
	   add_to_output ("char	*");
	   return;
	}

	if (has_a_proc_type (fp)) {
	   add_to_output ("char *, ");
	   add_to_output (c_type_name (result_type (fp)));
	   add_to_output (" (*)()");
	   return;
	}
}

//	For each (jff) procedure, a specification of the
//	activation record is generated
void	generate_par_fields (treenode *p) {
treenode *fp;

	fp = get_proc_parameters (p);
	while (fp != (treenode *)0) {
	   parameter_field (fp);
	   fp = get_nextnode (fp);
	}
}

void	parameter_field  (treenode *fp) {
treenode *t;

	t = type_of (fp);
	if (type_of_entity_is_simple (t)) {
	   if (is_specified_as_value (fp)) {
	      add_to_output (c_type_name (t)); add_to_output (" ");
	      add_to_output (c_nameof (fp));   add_to_output (";\n");
	      return;
	   }

//	now we know, we deal with a thunk
	   add_to_output ("char	*L"); add_to_output (c_nameof (fp));
	   add_to_output (";\n ");
	   add_to_output (c_type_name (t)); add_to_output (" (*A");
	   add_to_output (c_nameof (fp)); add_to_output (")(char *, ");
	   add_to_output (c_type_name (t)); add_to_output (");\n");

	   add_to_output (c_type_name (t)); add_to_output (" (*V");
	   add_to_output (c_nameof (fp)); add_to_output (")(char *, int);\n");
	   return;
	}

	if (is_switch (fp)) {
	   add_to_output ("char	*L");
	   add_to_output (c_nameof (fp)); add_to_output (";\n");
	   add_to_output ("jmp_buf	*(*"); add_to_output (c_nameof (fp));
	   add_to_output (")(char	*, int);\n");
	   return;
	}

	if (has_string_type (fp)) {
	   add_to_output ("char *");
	   add_to_output (c_nameof (fp));
	   add_to_output (";\n");
	   return;
	}

	if (is_arithmetic_array (fp)) {
	   add_to_output ("int	*D");
	   add_to_output (c_nameof (fp));
	   add_to_output (" ;\n");
	   add_to_output (c_type_name (element_type (fp)));
	   add_to_output ("	*");
	   add_to_output (c_nameof (fp));
	   add_to_output (" ;\n");
	   return;
	}

	if (has_a_proc_type (fp)) {
	   add_to_output ("char	*D"); add_to_output (c_nameof (fp));
	   add_to_output (";\n");
	   add_to_output (c_type_name (result_type (fp)));
	   add_to_output (" (*"); add_to_output (c_nameof (fp));
	   add_to_output (")();\n");
	   return;
	}

	if (has_label_type (fp)) {
	   add_to_output ("jmp_buf	*"); add_to_output (c_nameof (fp));
	   add_to_output (";\n");
	   return;
	}
}

//
//	In the activation record of a jff style procedure
//	we generate the locations of all locals in the proc
void	generate_local_fields (treenode *p) {
treenode *d;

	d = get_first_dec_in_proc (p);

	while (d != (treenode *)0) {
	   if (is_accessed (d) && !is_own (d)) {
	      switch (get_nodeid (d)) {
	         case LABEL_DECL:
	            generate_lab_decl (d);
	            break;

	         case SUBTYPE:
	            generate_subtype_decl (d);
	            break;

	         case SWITCH_DECL:	// there are moved forwards
	         case PROC_DECL:
	         case THUNK:
	            break;

	         case VARIABLE:
	            generate_var_decl (p, d);
	            break;

	         default:
	            break;
	      }
	   }
	   d = get_next_dec (d);
	}
}

//
//	declaration code for the parameters
//
void	parameter_decls (treenode *p) {
treenode	*fp;

	fp =get_proc_parameters (p);

	if (need_static_link (p)) {
	   add_to_output ("struct ");
	   pr_type_of_ar (get_environmental_proc (get_decl_env (p)));
	   add_to_output (" *ELP_");

	   if (fp == (treenode *)0)
	      return;

	   add_to_output (",");
	}

	while (fp != (treenode *)0) {
	   parameter_decl (fp);
	   if ((fp = get_nextnode (fp)) != (treenode *)0)
	      add_to_output (",");
	}
}

void	parameter_decl  (treenode *fp) {
treenode *t;
	t = type_of (fp);
	if (type_of_entity_is_simple (t)) {
	   if (is_specified_as_value (fp)) {
	      add_to_output (c_type_name (t));
	      add_to_output (" ");
	      add_to_output (c_nameof (fp));
	      return;
	   }
//	thunk stuff
	   add_to_output ("char	*L"); add_to_output (c_nameof (fp));
	   add_to_output (", "); add_to_output (c_type_name (t));
	   add_to_output (" (*A"); add_to_output (c_nameof (fp));
	   add_to_output (")( char *, "); add_to_output (c_type_name (t));
	   add_to_output ("), ");
	   add_to_output (c_type_name (t)); add_to_output (" (*V");
	   add_to_output (c_nameof (fp)); add_to_output (")(char *, int)");
	   return;
	}

	if (has_string_type (fp)) {
	   add_to_output ("char	*"); add_to_output (c_nameof (fp));
	   return;
	}

	if (is_switch (fp)) {
	   add_to_output ("char	*L"); add_to_output (c_nameof (fp));
	   add_to_output (", jmp_buf *(*"); add_to_output (c_nameof (fp));
	   add_to_output (") (char	*, int)\n");
	   return;
	}

	if (is_arithmetic_array (fp)) { // for name and value the same
	   add_to_output ("int *D"); add_to_output (c_nameof (fp));
	   add_to_output (", ");
	   add_to_output (c_type_name (element_type (fp)));
	   add_to_output ("  *"); add_to_output (c_nameof (fp));
	   return;
	}

	if (has_a_proc_type (fp)) {
	   add_to_output ("char	*D"); add_to_output (c_nameof (fp));
	   add_to_output (", "); add_to_output (c_type_name (result_type (fp)));
	   add_to_output (" (*"); add_to_output (c_nameof (fp));
	   add_to_output (")()");
	   return;
	}

	ASSERT (FALSE, ("Expert error 12"));
}

void	init_activation_record (treenode *p) {
treenode *fp;

	if (need_static_link (p)) 
	   add_to_output ("LP -> __l_field = ELP_;\n");

	fp = get_proc_parameters (p);
	while (fp != (treenode *)0) {
//	   if (is_accessed (fp))  // Known bug, ACCESS not set properly
	      init_parameter_in_ar (p, fp);
	   fp = get_nextnode (fp);
	}
}
//
//	generate init code for parameter fp in proc p
void	init_parameter_in_ar (treenode *p, treenode *fp) {
char	*fp_name;

	fp_name = c_nameof (fp);
	if (type_of_entity_is_simple (fp)) {
	   if (is_specified_as_value (fp)) {
	      add_to_output ("LP -> "); add_to_output (fp_name);
	      add_to_output ("= "); add_to_output (fp_name);
	      add_to_output (";\n");
	      return;
	   }
//	the thunk case
	   add_to_output ("LP -> L"); add_to_output (fp_name);
	   add_to_output (" = L"); add_to_output (fp_name);
	   add_to_output (";\n");
	   add_to_output ("LP -> A"); add_to_output (fp_name);
	   add_to_output (" = A"); add_to_output (fp_name);
	   add_to_output (";\n");
	   add_to_output ("LP -> V"); add_to_output (fp_name);
	   add_to_output (" = V"); add_to_output (fp_name);
	   add_to_output (";\n");
	   return;
	}

	if (is_switch (fp)) {
	   add_to_output ("LP -> L"); add_to_output (fp_name);
	   add_to_output (" = L"); add_to_output (fp_name);
	   add_to_output (";\n");
	   add_to_output ("LP -> "); add_to_output (fp_name);
	   add_to_output (" = "); add_to_output (fp_name);
	   add_to_output (";\n");
	   return;
	}

	if (is_arithmetic_array (fp)) {
	   if (is_specified_as_value (fp)) {
//	first LP ->Dx = __jff_descriptor (Dx, x, sizeof (t), LP)
	      add_to_output ("LP -> D"); add_to_output (fp_name);
	      add_to_output (" = __jff_descriptor_for_value (D");
	      add_to_output (fp_name); add_to_output (", sizeof (");
	      add_to_output (c_type_name (element_type (fp)));
	      add_to_output ("), LP);\n");
//	second LP -> x = __jff_allocate_array (LP -> Dx, LP);
	      add_to_output ("LP -> "); add_to_output (fp_name);
	      add_to_output (" = __jff_allocate_array (LP -> D");
	      add_to_output (fp_name); add_to_output (", LP);\n");
//	finally __typed_copy (Dx, LP -> Dx, LP -> x);
	      add_to_output ("__typed_copy (D"); add_to_output (fp_name);
	      add_to_output (", LP -> D"); add_to_output (fp_name);
	      add_to_output (", "); add_to_output (fp_name);
	      add_to_output (", LP -> "); add_to_output (fp_name);
	      add_to_output (");\n");
	      return;
	   }
	   add_to_output ("LP -> D"); add_to_output (fp_name);
	   add_to_output (" = D"); add_to_output (fp_name);
	   add_to_output (";\n");
	   add_to_output ("LP -> "); add_to_output (fp_name);
	   add_to_output (" = "); add_to_output (fp_name);
	   add_to_output (";\n");
	   return;
	}

	if (has_a_proc_type (fp)) {
	   add_to_output ("LP -> D"); add_to_output (fp_name);
	   add_to_output (" = D"); add_to_output (fp_name);
	   add_to_output (";\n");
	   add_to_output ("LP -> "); add_to_output (fp_name);
	   add_to_output (" = "); add_to_output (fp_name);
	   add_to_output (";\n");
	   return;
	}

	if (has_label_type (fp)) {
	   add_to_output ("LP -> "); add_to_output (fp_name);
	   add_to_output (" = P"); add_to_output (fp_name);
	   add_to_output (";\n");
	   return;
	}

	if (has_string_type (fp)) {
	   add_to_output ("LP -> "); add_to_output (fp_name);
	   add_to_output (" = "); add_to_output (fp_name);
	   add_to_output (";\n");
	   return;
	}
	// this should not happen
	ASSERT (FALSE, ("Expert error 13"));
}

void	generate_var_spec (treenode *d) {
int	i;
treenode	*st;
treenode	*bnd;

	if (is_static_array (d)) {
	      st = get_type_of_var (d);
	      add_to_output ("extern ");
	      add_to_output (c_type_name (element_type (d)));
	      add_to_output (" "); add_to_output (c_nameof (d));
	      add_to_output (" [");
	      bnd = get_subtype_bounds (st);
	      while (bnd != (treenode *)0) {
	          if (get_nextnode (bnd) != (treenode *)0)
	             add_to_output (" ][");
	          bnd = get_nextnode (bnd);
	      }

	      add_to_output ("]; // \n");
	      return;
	}

	if (is_arithmetic_array (d)) {
	   add_to_output ("extern ");
	   add_to_output (c_type_name (element_type (d)));
	   add_to_output ("	*");
	   add_to_output (c_nameof (d));
	   add_to_output (";");
	   pr_declaration_comment (d);
	   return;
	}

//	it is a simple var
	add_to_output ("extern ");
	add_to_output (c_type_name (type_of (d)));
	add_to_output (" ");
	add_to_output (c_nameof (d));
	add_to_output (";");
	pr_declaration_comment (d);
}

//
//	declaration code for "d" in proc "p"
void	generate_var_decl (treenode *p, treenode *d) {
int	i;
treenode	*st;
treenode	*bnd;

	if (is_static_array (d)) {
	   st = get_type_of_var (d);
	   add_to_output (c_type_name (element_type (d)));
	   add_to_output (" "); add_to_output (c_nameof (d));

	   bnd = get_subtype_bounds (st);
	   add_to_output ("[");
	   while (bnd != (treenode *)0) {
	       code_for_expression (p, get_second_bound (bnd), int_type);
	       add_to_output (" - ");
	       code_for_expression (p, get_first_bound (bnd), int_type);
	       add_to_output (" +1");
	       if (get_nextnode (bnd) != (treenode *)0)
	          add_to_output (" ][");
	       bnd = get_nextnode (bnd);
	   }
	   add_to_output ("];");
	   pr_declaration_comment (d);
	   return;
	}

	if (is_arithmetic_array (d)) { // but non static
	   add_to_output (c_type_name (element_type (d)));
	   add_to_output ("	*");
	   add_to_output (c_nameof (d));
	   add_to_output ( ";");
	   pr_declaration_comment (d);
	   return;
	}

	add_to_output (c_type_name (type_of (d)));
	add_to_output (" "); add_to_output (c_nameof (d));
	add_to_output (";");
	pr_declaration_comment (d);
}

//	generate elaboration code for d in block b
//
void	generate_elab_code	(treenode *d, treenode *b) {

	add_to_output ("\n//	Code for the global declarations\n\n");

	while (d != (treenode *)0) {
	   switch (get_nodeid (d)) {
	      case PROC_DECL:
	         generate_proc_code (d);
	         break;

	      case THUNK:
	         generate_thunk_code (d);
	         break;

	      case SWITCH_DECL:
	         generate_switch_decl (d);
	         break;

	      case SUBTYPE:
	         generate_subtype_decl (d);
	         break;

	      case LABEL_DECL:
	         generate_lab_decl (d);
	         break;

	      case VARIABLE:
	         generate_var_decl (get_environmental_proc(b), d);
	         break;

	      default:
	         break;
	   } 
	   d = get_next_dec (d);
	}
	add_to_output ("\n\n// The main program\n");
	add_to_output ("int	main () {\n char	*LP = (char *)NULL;\n");

	generate_declaration_code (NULL, b);
	statement_code   (NULL, get_statements (b));
	add_to_output ("}\n");
}

//	generating code for a procedure body
//	do not mess too much

void	generate_proc_code (treenode *p) {
treenode	*q;
	if (p == (treenode *)0)
	   return;

	q = p;
	while (q != NULL) {
	   if (!is_accessed (q)) {
//	      fprintf (stderr, "Name of proc %s\n", c_nameof (q));
	      return;
	   }
	   q = get_environmental_proc (get_decl_env (q));
	}

	if (is_proc_as_parameter (p))
	   generate_envelope (p);

	if (is_cproc (p))
	   return;

	if (will_be_compiled_as_c_proc (p))
	   generate_body_for_c_proc (p);
	else
	   generate_body_for_jff_proc (p);
}

//	generating code for a "normal" jff procedure
void	generate_body_for_jff_proc (treenode *p) {

	pr_declaration_comment (p);
	add_to_output (c_type_name (result_type (p)));
	add_to_output (" ");
	add_to_output (c_nameof (p));
	add_to_output (" (");

	parameter_decls (p);
	add_to_output ("){ \n ");
//
//	if we might end up in this frame through a longjmp
//	make record volatile
	if (has_far_access (p))
	   add_to_output ("volatile ");
	add_to_output ("struct ");
	pr_type_of_ar (p);
	add_to_output (" local_data_"); add_to_output (get_decl_ident (p));
	add_to_output (";\n");

	if (has_far_access (p))
	   add_to_output ("volatile ");
	add_to_output ("struct "); pr_type_of_ar (p);
	add_to_output (" *LP = & local_data_");
	add_to_output (get_decl_ident (p));
	add_to_output (";\n");

	init_activation_record (p);

	statement_code (p, get_proc_body (p));
	if (needs_deallocation (p)) 
	   add_to_output ("__deallocate (LP);\n");

	if (type_of (result_type (p)) != void_type)
	      add_to_output ("return LP -> __res_val;\n");

	add_to_output ("\n}\n");
}

//	some simple procedures can be translated without activation record
void	generate_body_for_c_proc (treenode *p) {

	pr_declaration_comment (p);
	add_to_output (c_type_name (result_type (p)));
	add_to_output (" ");
	add_to_output (c_nameof (p));
	add_to_output (" (");

	parameter_decls (p);
	add_to_output ("){ \n ");

	if (type_of (result_type (p)) != void_type) {
	   add_to_output (c_type_name (result_type (p)));
	   add_to_output (" __res_val;\n");
	}

	generate_local_declarations (p);
	statement_code (p, get_proc_body (p));

	if (type_of (result_type (p)) != void_type) 
	   add_to_output ("return __res_val;\n");

	add_to_output ("\n}\n");
}

//
//	contrary to the jff style procedures, the c style
//	procedures have their locals really as local
//	but there is a very limited set that is allowed
//	in a c style procedure
//
void	generate_local_declarations (treenode *p) {
treenode *d;

	d = get_first_dec_in_proc (p);
	while (d != (treenode *)0) {
	   if (is_accessed (d) && !is_own (d)) {
	      if (get_nodeid (d) == VARIABLE) {
	         add_to_output (c_type_name (type_of (d)));
	         add_to_output (" ");
	         add_to_output (c_nameof (d));
	         add_to_output (";\n");
	      }
	   }
// notice the get_next_dec  here, do not modify in get_nextnode
	   d = get_next_dec (d);
	}
}

//	generating thunk code is somewhat tricky, we
//	generate both an address and a value thunk
void	generate_thunk_code	(treenode *th) {
treenode *ep;

	ep = get_environmental_proc (th);
	if ((ep != (treenode *)0) && !is_accessed (ep))
	   return;

//	first the address thunk
	add_to_output (c_type_name (type_of (th)));
	add_to_output ("  A"); add_to_output (c_nameof (th));
	add_to_output (" (char *LP, ");
	add_to_output (c_type_name (type_of (th)));
	add_to_output (" V){\n");
	generate_body_for_address_thunk (th);
	add_to_output ("}\n");

// then the same for the value thunk
	add_to_output (c_type_name (type_of (th)));
	add_to_output ("  "); add_to_output (c_nameof (th));
	add_to_output (" (char *LP, int d){\n");
	generate_body_for_value_thunk (th);
	add_to_output ("}\n");
}

void	generate_fault_body (treenode *exp) {
	add_to_output ("fault (\" no assignable object\",");
	add_to_output (num_to_string (get_lineno (exp)));
	add_to_output (");\n");
}

//	Now for the bodies
void	generate_body_for_address_thunk (treenode *th) {
treenode *exp, *def;

	exp = get_thunk_expr (th);

	if (get_nodeid (exp) == ID_AS_PRIM) { // can only be a variable
	   def = get_id_def (exp);
	   if (!can_be_assigned_to (def)) {
	      generate_fault_body (exp);
	      return;
	   }

	   if (type_of (exp) != type_of (th)) {
	      add_to_output ("return (");
	      add_to_output (c_type_name (type_of (th)));
	      add_to_output (")("); 
//	if a parameter, it is a value one
	      pr_access_to_simple_entity (th, def);
	      add_to_output (" = ( ");
	      add_to_output (c_type_name (type_of (exp)));
	      add_to_output (")V);\n");
	      return;
	   }
//	types are equal, no cast needed
	   add_to_output ("return ");
//	if a parameter, it is a value par
	   pr_access_to_simple_entity (th, def);

	   add_to_output (" = V;\n");
	   return;
	}

	if (get_nodeid (exp) == INDEXING) {
	   if (!can_be_assigned_to (exp)) {
	      generate_fault_body (exp);
	      return;
	   }

	   if (type_of (exp) != type_of (th)) {
	      add_to_output ("return (");
	      add_to_output (c_type_name (type_of (th)));
	      add_to_output (")( ");
	      code_for_indexed_value (th, exp);
	      add_to_output (" = (");
	      add_to_output (c_type_name (type_of (th)));
	      add_to_output (") V;\n");
	      return;
	   }

	   add_to_output ("return ");
	   code_for_indexed_value (th, exp);
	   add_to_output (" = V;\n");
	   return;
	}
//	all that is left is an expression that does not have an address
	generate_fault_body (exp);
}

void	generate_body_for_value_thunk (treenode *th) {
	add_to_output ("return ");
	code_for_expression (th, get_thunk_expr (th), type_of (th));
	add_to_output (";\n");
}

void	generate_switch_decl	(treenode *d) {
int	i;
treenode *p, *e;

	p = get_environmental_proc (d);
	if ((p != (treenode *)0) && !is_accessed (p))
	   return;

	pr_declaration_comment (d);
	add_to_output ("jmp_buf *");add_to_output (c_nameof (d));
	add_to_output (" (char *LP, int n) {\n");
	add_to_output (" switch (n) {\n");
	add_to_output ("default:\n");

	e = get_switchlist (d);
	for (i = 1; i <= get_num_of_switch_elements(d); i ++) {
	   add_to_output ("case "); add_to_output (num_to_string (i));
	   add_to_output (": return ");
	   code_for_expression (d, e, lab_type);
	   add_to_output (";\n");
	   e = get_nextnode (e);
	}

	add_to_output ("\n}; // end of switch list \n} \n");
}

void	generate_subtype_decl	(treenode *d) {

	if (!subtype_needs_descriptor (d)) 
	   return;

	add_to_output ("int ");
	add_to_output (c_nameof (d));
	add_to_output (" [2 * ");
	add_to_output (num_to_string (get_subtype_dims (d)));
	add_to_output (" + DOPE_BASE];\n");
}

void	generate_lab_decl (treenode *d) {
	if (!has_far_access (d))
	   return;

	add_to_output ("jmp_buf "); add_to_output (c_nameof (d));
	add_to_output (";\n");
}

// generate additional code for initializations
//
void	generate_declaration_code (treenode *p, treenode *b) {
treenode *d;

	d = get_block_decls (b);
	while (d != (treenode *)0) {
	   if (is_accessed (d)) {
	      switch (get_nodeid (d)) {
	         case SWITCH_DECL:
	            break;

	         case LABEL_DECL:
	            if (has_far_access (d)) {
	               add_to_output ("if (setjmp (");
	               pr_access_to_label (p, d);
	               add_to_output (")) goto L");
	               add_to_output (c_nameof (d));
	               add_to_output (";\n");
	            }
	            break;

	         case VARIABLE:
	            generate_var_elab (p, d);
	            break;

	         case SUBTYPE:
	            generate_subtype_elab (p, d);
	            break;

	         case PROC_DECL:
	            break;

	         case THUNK:
	            break;

	         default:
	            return; // cannot happen
	      }
	   }
	   d = get_nextnode (d);
	}
}

void	generate_var_elab (treenode *p, treenode *d) {

	if (!is_arithmetic_array (d)) 
	   return;		// a simple variable

	if (is_static_array (d))
	   return;

	pr_name_of_array (p, d); add_to_output (" = (");
	add_to_output (c_type_name (element_type (d)));
	add_to_output (" *) __jff_allocate_array (");
	pr_address_of_descriptor (p, d);
	add_to_output (", LP);\n");
}

//	elaborating an array declaration declaration
//	generate code for initializing the dope vector
void	generate_subtype_elab (treenode *p, treenode *d) {
int	i;
treenode *bnd;

	if (!subtype_needs_descriptor (d))
	   return;

	pr_name_of_descriptor (p, d); add_to_output (" [0] =  (");
	add_to_output (num_to_string (get_subtype_dims (d)));
	add_to_output (" *256) + sizeof (");
	add_to_output (c_type_name (element_type (d)));
	add_to_output (");\n");

	bnd = get_subtype_bounds (d);
	i = 1;
	while (bnd != (treenode *)0) {
	   pr_name_of_descriptor (p, d); add_to_output (" [ DOPE_BASE +");
	   add_to_output (num_to_string (2 * (i - 1)));
	   add_to_output ("] = ");
	   code_for_expression (p, get_first_bound (bnd), int_type);
	   add_to_output (";\n");
	   pr_name_of_descriptor (p, d); add_to_output (" [ DOPE_BASE +");
	   add_to_output (num_to_string (2 * (i - 1) + 1));
	   add_to_output ("] = ");
	   code_for_expression (p, get_second_bound (bnd), int_type);
	   add_to_output (";\n");
	   bnd = get_nextnode (bnd);
	   i ++;
	}

	add_to_output ("__dv_init (");
	pr_name_of_descriptor (p, d);
	add_to_output (");\n");
}

//
//	avoid generating to many block brackets
void	code_for_block_body (treenode *p, treenode *s) {
	if (is_single_statement (s)) {
	   statement_code (p, s);
	   return;
	}

	add_to_output ("{ ");
	statement_code (p, s);
	add_to_output ("}\n");
}

void	statement_code (treenode *p, treenode *s) {

	while (s != (treenode *)0) {
	   if (has_statement_label (s)) {
	      add_to_output ("L");
	      add_to_output (c_nameof (get_label (s)));
	      add_to_output (":");
//	      if (get_nodeid (s) == NULL_STAT)
//	         add_to_output (";");
	   }

	   switch (get_nodeid (s)) {
	      case IF_STAT:
	         generate_if_stat (p, s);
	         break;

	      case FOR_STATEMENT:
	         generate_for_stat (p, s);
	         break;

	      case NULL_STAT:
	         if (get_nextnode (s) == NULL)
	            add_to_output ("; // null statement \n");
	         break;

	      case GOTO_STAT:
	         generate_goto (p, get_target (s));
	         break;

	      case ASSIGNMENT:
	         assignment_code (p, get_lhs_expression (s),
	                          get_rhs_expression (s)) ;
// assignment is also an expression, therefore:
	         add_to_output (";\n");
	         break;

	      case BLOCK:
	         generate_block_code (p, s);
	         break;

	      case COMPOUND:
	         statement_code (p, get_statements (s));
	         break;

	      case FUNCTION_CALL:
	         generate_call (p,
	                     get_called_function (s),
	                     get_actuals (s),
	                     get_num_of_actuals (s));
// function call is also an expression, therefore:
	         add_to_output (";\n");
	         break;

	      default:
	         ASSERT (FALSE,  ("Expert error 14"));
	         return;
	   }
	   s = get_nextnode (s);
	}
}

void	generate_if_stat (treenode *p, treenode *s) {

	add_to_output (" if (");
	code_for_expression (p, get_ifcondition (s), bool_type);
	add_to_output (")\n ");
	code_for_block_body (p, get_ifthenpart (s));
	if (get_ifelsepart (s) != (treenode *)0) {
	   add_to_output (" \n else ");
	   code_for_block_body (p, get_ifelsepart (s));
	}
}

void	code_for_expression (treenode *p, treenode *e, treenode *t) {
	if (type_of (e) != t) { // we need a cast
	   add_to_output ("(");
	   add_to_output (c_type_name (t));
	   add_to_output (")(");
	   code_for_expression (p, e, type_of (e));
	   add_to_output (")");
	   return;
	}

	switch (get_nodeid (e)) {
	   case INUMBER:
	   case FNUMBER:
	   case BNUMBER:
	      add_to_output (get_x_value (e));
	      break;

	   case STRING_CONSTANT:
	      add_to_output ("\"");
	      add_to_output (get_x_value (e));
	      add_to_output ("\"");
	      break;

	   case FUNCTION_CALL:
	      generate_call (p,
	                     get_called_function (e),
	                     get_actuals (e),
	                     get_num_of_actuals (e));
	      break;

	   case CONDITIONAL:
	      add_to_output (" ( ");
	      code_for_expression (p, get_cond_of_condition (e), bool_type);
	      add_to_output (" )? ");
	      code_for_expression (p, get_condition_thenpart (e), t);
	      add_to_output (" : ");
	      code_for_expression (p, get_condition_elsepart (e), t);
	      break;

	   case ID_AS_PRIM:
	      code_for_id_as_prim (p, e);
	      break;

	   case INDEXING:
	      code_for_indexed_value (p, e);
	      break;

	   case UNARY_EXPRESSION:
	      code_for_unary_expression (p, e);
	      break;

	   case BINARY_EXPRESSION:
	      code_for_binary_expression (p, e);
	      break;

	   case ASSIGNMENT:
	      assignment_code (p, get_lhs_expression (e),
	                          get_rhs_expression (e));
	      break;

	   default:
	      ASSERT (FALSE, ("Expert error 15\n"));
	      return;
	}
}

//
//	generating code for a call of d in context p
//	 dispatch the kind
void	generate_call (treenode *p, treenode *d, treenode *al, int num) {

	if (is_parameter (d)) 
	   call_to_formal (p, d, al, num);
	else
//	if (is_a_proc_decl (d))  
	   call_to_regular_proc (p, d, al);
}

//	This is a tricky one.
//	We generate code to call an envelope procedure that
// 	  1 checks the number of actual parameters
//	  2 calls the real procedure in a special way (with a lot
//	    of run time functions as parameter to transfer
//	    the real parameters to the function
// 
void	call_to_formal (treenode *p, treenode *d, treenode *al, int num) {
int	i;
	add_to_output ("(");
	pr_address_of_formal_proc (p, d);
	add_to_output (")(");
	pr_link_for_formal_proc (p, d);
	add_to_output (" ,");
	add_to_output (num_to_string (num));
	
//	Now for the parameters
	for (i = 1; i <= num; i ++) {
	   hard_parameter (p, get_act_exp (al), i);
	   al = get_nextnode (al);
	}
	add_to_output (")");
}

//
//	we generate for each parameter to a call to
//	a formal proc a descriptor:
//	data is packed as 't' << 8 + 'k', where
//	 t is an indication of the "type" and
//	 k is an indication of the "kind"
void	pr_data_for_hard_param (char t, char k) {
	add_to_output (" ,(char *)((\'");
	add_to_output (char_to_string (t));
	add_to_output ("\' << 8) + \'");
	add_to_output (char_to_string (k));
	add_to_output ("\')");
}
//
//	parameters to a call to a formal procedure
//	are thunk, array, switch, proc, string or other parameter
void	hard_parameter (treenode *p, treenode *e, int i) {
treenode	*def;
char	*t;

	switch (get_nodeid (e)) {
	   case ID_AS_PRIM:
	      def = get_id_def (e);
	      switch (get_nodeid (def)) {
	         case PARAM_DECL:
	            hard_param_is_parameter (p, def, i);
	            return;

	         case SWITCH_DECL:
	            pr_data_for_hard_param ('j', 'W');
	            add_to_output (", ");
	            pr_link_for_switch (p, def);
	            add_to_output (", ");
	            pr_address_of_switch (p, def);
	            return;

	         case PROC_DECL:
	            pr_data_for_hard_param (c_type_name (result_type (def))[0],
	                                    'F');
	            add_to_output (", ");
	            pr_link_to_proc_env (p, get_environmental_proc (get_decl_env (def)));
	            add_to_output (", ");
	            pr_address_of_regular_proc (p, def);
	            return;

	         case VARIABLE:	// can only be an array
	            pr_data_for_hard_param (c_type_name (element_type (def))[0],
	                                    'A');
	            add_to_output (", ");
	            pr_address_of_descriptor (p, def);
	            add_to_output (", ");
	            pr_name_of_array   (p, def);
	            return;

	         case THUNK:
	            pr_data_for_hard_param (c_type_name (type_of (def))[0], 'T');
	            add_to_output (", ");
	            pr_link_to_thunk (p, def);
	            add_to_output (", ");
	            pr_address_of_address_thunk (p, def);
	            add_to_output (", ");
	            pr_address_of_value_thunk   (p, def);
	            return;
	      }

	      ASSERT (FALSE, ("Expert error 16"));
	      return;

	   case STRING_CONSTANT:
	      pr_data_for_hard_param ('S', 'S');
	      add_to_output (", \"");
	      add_to_output (get_x_value (e));
	      add_to_output ("\"");
	      return;

	   default:
	      ASSERT (FALSE, ("Expert error 17\n"));
	      return;
	}
}
//
//	if the actual parameter to a call to a formal procedure
//	is a parameter itself, treat it with care
void	hard_param_is_parameter (treenode *p, treenode *def, int i) {
char	*t;

	if (is_switch (def)) {
	   pr_data_for_hard_param ('L', 'W');
	   add_to_output (", ");
	   pr_link_of_formal_switch (p, (treenode *)def);
	   add_to_output (", ");
	   pr_address_of_formal_switch (p, (treenode *)def);
	   return;
	}

	if (is_arithmetic_array (def)) {
	   t = c_type_name (element_type (def));
	   pr_data_for_hard_param (t [0], 'A');
	   add_to_output (", ");
	   pr_name_of_descriptor (p, def);
	   add_to_output (", ");
	   pr_name_of_array (p, def);
	   return;
	}

	if (has_a_proc_type (def)) {
	   t = c_type_name (result_type (def));
	   pr_data_for_hard_param (t [0], 'F');
	   add_to_output (", ");
	   pr_link_for_formal_proc (p, (treenode *)def);
	   add_to_output (", ");
	   pr_address_of_formal_proc (p, (treenode *)def);
	   return;
	}

	if (has_string_type (def)) {
	   pr_data_for_hard_param ('S', 'S');
	   add_to_output (", ");
	   pr_name_of_formal_string (p, def);
	   return;
	}

	if (!is_specified_as_value ((treenode *)def)) {
	   t = c_type_name (type_of (def));
	   pr_data_for_hard_param (t [0], 'T');
	   add_to_output (", ");
	   pr_link_to_thunk (p, def); add_to_output (", ");
	   pr_address_of_address_thunk (p, def); add_to_output (", ");
	   pr_address_of_value_thunk   (p, def);
	   return;
	}
	
	ASSERT (FALSE, ("Expert error 18"));
}

//
//	a call to a regular procedure is
//	at least somewhat easier than the call to the
//	formal procedure
void	call_to_regular_proc (treenode *pa, treenode *p, treenode *ap) {
treenode *fp =  get_proc_parameters (p);

	add_to_output (c_nameof (p));
	add_to_output (" (");

	if (need_static_link (p)) { 
	   pr_link_to_proc_env (pa, get_environmental_proc (get_decl_env (p)));
	   if (fp == (treenode *)0) {
	      add_to_output (")");
	      return;
	   }
	   add_to_output (", ");
	}

	while (fp != (treenode *)0) {
	    code_for_actual (pa, fp, ap);
	    fp = get_nextnode (fp);
	    ap = get_nextnode (ap);
	    if (ap != (treenode *)0)
	       add_to_output (", ");
	}

	add_to_output (")");
}

//	generate code for a known formal parameter
//	dispatch on the attributes of the formal
void	code_for_actual (treenode *pa, treenode *fp, treenode *ap) {
	if (has_a_proc_type (fp))
	   code_for_function_as_actual (pa, ap);
	else
	if (has_string_type (fp))
	   code_for_string_as_actual (pa, fp, ap);
	else
	if (is_switch (fp))
	   code_for_switch_as_actual (pa, fp, ap);
	else
	if (is_arithmetic_array (fp))
	   code_for_array_as_actual (pa, fp, ap);
	else
	if (is_specified_as_value (fp)) // arrays already dealt with
	   code_for_expression (pa, get_act_exp (ap), type_of (fp));
	else
	   thunk_or_function_as_actual (pa, fp, ap);
}

void	code_for_function_as_actual (treenode *p, treenode *ap) {
treenode *def;
treenode *e;

	e =  get_act_exp (ap);
	def = get_id_def (e);	// this is the function we are calling
	if (is_parameter (def)) {
	   pr_link_for_formal_proc (p, def);
	   add_to_output (", ");
	   pr_address_of_formal_proc (p, def);
	   return;
	}

//	we are actually passing the envelope rather than the real proc
	pr_link_to_proc_env (p, get_environmental_proc (get_decl_env (def)));
	add_to_output (", D");
	pr_address_of_regular_proc (p, def);
}

void	code_for_array_as_actual (treenode *p, treenode *fp, treenode *ap) {
treenode *def;
treenode *e;

	e = get_act_exp (ap);
	def = get_id_def (e);
	if (is_parameter (def)) 
	   pr_name_of_descriptor (p, def);
	else
	   pr_address_of_descriptor (p, def);

	add_to_output (", ");
	pr_name_of_array (p, def);
}

void	code_for_switch_as_actual (treenode *p, treenode *fp, treenode *ap) {
treenode *def, *e;

	e =  get_act_exp (ap);
	def = get_id_def (e);
	if (is_parameter (def)) {
	   pr_link_of_formal_switch (p, def);
	   add_to_output (", ");
	   pr_address_of_formal_switch (p, def);
	   return;
	}
//	it is an actual switch
	pr_link_for_switch (p, def);
	add_to_output (", ");
	pr_address_of_switch (p, def);
}

//	actual is a string
void	code_for_string_as_actual (treenode *p, treenode *fp, treenode *ap) {
treenode *e;

	e = get_act_exp (ap);
	if (get_nodeid (e) == STRING_CONSTANT) {
	   add_to_output ("\""); 
	   add_to_output (get_x_value (e));
	   add_to_output ("\"");
	   return;
	}
//	it is a parameter
	pr_name_of_formal_string (p, get_id_def (e));
}

// two cases arise here,
//	either we pass on an existing formal parameter
//	or we generate code for accessing the thunks
void	thunk_or_function_as_actual (treenode *p, treenode *fp, treenode *ap) {
treenode *e, *def;

	e = get_act_exp (ap);
	def =  get_id_def (e);

	if (is_parameter (def) &&
	    !has_a_proc_type (def)) {	// just pass on a formal
	   pr_link_to_thunk (p, def);
	   add_to_output (", ");
	   pr_address_of_address_thunk (p, def);
	   add_to_output (", ");
	   pr_address_of_value_thunk (p, def);
	   return;
	}

	if (is_parameter (def) &&
	    has_a_proc_type (def)) {	// pass on function
	   pr_link_for_formal_proc (p, def);
	   add_to_output (", (char *)0, ");
	   pr_address_of_formal_proc (p, def);
	   return;
	}

	if (is_a_proc_decl (def)) {	// a function but no formal
	   pr_link_to_proc_env (p, get_environmental_proc (get_decl_env (def)));
	   add_to_output (", NULL, ");
	   pr_address_of_regular_proc (p, def);
	   return;
	}
//
//	it is a thunk
	pr_link_to_thunk (p, def); add_to_output (", ");
	pr_address_of_address_thunk (p, def); add_to_output (", ");
	pr_address_of_value_thunk   (p, def);
}

//
//	assignments and increments
void	assign_to_simple (treenode *p, treenode *lhs, treenode *a) {
treenode *d;

	d =  get_id_def (lhs);

	if (is_a_proc_decl (d)) { // it is an assignment to the fun var
	   if (will_be_compiled_as_c_proc (p)) {
	      add_to_output ("__res_val = "); // can only be local
	      code_for_expression (p, a, type_of (lhs));
	      return;
	   }
	   add_to_output (" (");
	   pr_link_to_proc_env (p, d);
	   add_to_output (" ) -> __res_val = ");
	   code_for_expression (p, a, type_of (lhs));
	   return;
	}

	if (is_parameter (d)) {
	   if (!is_specified_as_value (d)) { // call the thunk
	      add_to_output ("(");
	      pr_address_of_address_thunk (p, d);
	      add_to_output (") (");
	      pr_link_to_thunk (p, d); add_to_output (", ");
	      code_for_expression (p, a, type_of (lhs));
	      add_to_output (")");
	      return;
	   }
	}
//
//	it is either a variable or a by value param
	pr_access_to_simple_entity (p, d);
	add_to_output ("=");
	code_for_expression (p, a, type_of (lhs));
}

//
//	increment is used in the translation of
//	a for statement
void	increment_simple (treenode *p, treenode *lhs, treenode *incr) {
treenode *d;

	d =  get_id_def (lhs);
	if (is_a_proc_decl (d)) { // it is an assignment to the fun var
	   if (will_be_compiled_as_c_proc (d)) {
	      add_to_output ("__res_val += ");
	   }
	   else {
	      add_to_output ("(");
	      pr_link_to_proc_env (p, d);
	      add_to_output (") -> __res_val += ");
	   }
	   code_for_expression (p, incr, type_of (lhs));
	   return;
	}

	if (is_parameter (d)) {
	   if (!is_specified_as_value (d)) { // call thunk
	      add_to_output ("(");
	      pr_address_of_address_thunk (p, d);
	      add_to_output (")(");
	      pr_link_to_thunk (p, d); add_to_output (", ");
	      code_for_expression (p, lhs, type_of (lhs));
	      add_to_output ( "+");
	      code_for_expression (p, incr, type_of (lhs));
	      add_to_output (")");
	      return;
	   }
	}
//	it is a variable or a value par
	pr_access_to_simple_entity (p, d);
	add_to_output (" +=");
	code_for_expression (p, incr, type_of (lhs));
}

//
//	now the same for indexed variables
void	assign_to_indexed (treenode *p, treenode *lhs, treenode *a) {
	code_for_indexed_value (p, lhs);
	add_to_output ("=");
	code_for_expression (p, a, type_of (lhs));
}

//
//	as with simple id, we use special code in a for statement
void	increment_indexed (treenode *p, treenode *lhs, treenode *incr) {
	code_for_indexed_value (p, lhs);
	add_to_output ("=");
	code_for_expression (p, lhs, type_of (lhs));
	add_to_output ("+");
	code_for_expression (p, incr, type_of (lhs));
}

void	assignment_code (treenode *p, treenode *lhs, treenode *rhs) {
	if (get_nodeid (lhs) == ID_AS_PRIM) 
	   assign_to_simple (p, lhs, rhs);
	else
//	if (get_nodeid (lhs) == INDEXING) {
	   assign_to_indexed (p, (treenode *)lhs, rhs);
}

// Generate code for the increment in a for statement
void	increment_code (treenode *p, treenode *lhs, treenode *incr) {
	if (get_nodeid (lhs) == ID_AS_PRIM) 
	   increment_simple (p, lhs, incr);
	else
//	if (get_nodeid (lhs) == INDEXING) {
	      increment_indexed (p, (treenode *)lhs, incr);
}

void	generate_block_code (treenode *p, treenode *b) {
treenode *t;

	if (get_block_decls (b) == (treenode *)0) {
	   statement_code (p, get_statements (b));
	   return;
	}

	add_to_output ("\n{ // code for block at line ");
	add_to_output (num_to_string (get_lineno (b)));
	add_to_output ("\n");

	generate_declaration_code (p, b);
	statement_code (p, get_statements (b));

	add_to_output ("}\n");
}

void	call_value_thunk (treenode *p, treenode *def) {
	add_to_output ("("); 
	pr_address_of_value_thunk (p, def);
	add_to_output (")((");
	pr_link_to_thunk (p, def);
	add_to_output ("), 0)");
}

//	an identifier as primary, a whole list
//	of possibilities
void	code_for_id_as_prim (treenode *p, treenode *prim) {
treenode *def = get_id_def (prim);

	if (has_a_proc_type (def)) {
	   generate_call (p, def, (treenode *)0, 0);
	   return;
	}

	if (is_parameter (def)) {
	   if (is_specified_as_value (def)) 
	      pr_access_to_simple_entity (p, def);
	   else
	      call_value_thunk (p, def);
	   return;
	}

	if ((get_nodeid (def) == VARIABLE) && !is_arithmetic_array (def)) {
	   pr_access_to_simple_entity (p, def);
	   return;
	}

	if ((get_nodeid (def) == VARIABLE) && (is_arithmetic_array (def))) {
	   pr_name_of_array (p, def);
	   return;
	}

	if (get_nodeid (def) == LABEL_DECL) {
	   pr_access_to_label (p, def);
	   return;
	}
	// 
	ASSERT (FALSE, ("Expert error 19"));
}

void	code_for_indexed_switch (treenode *p, treenode *d, treenode *ind) {

	if (is_parameter (d)) {
	   pr_address_of_formal_switch (p, d);
	   add_to_output (" (");
	   pr_link_of_formal_switch (p, d);
	}
	else {
	   pr_address_of_switch (p, d);
	   add_to_output (" (");
	   pr_link_for_switch (p, d);
	}
//	now the indexing
	add_to_output (", ");
	code_for_expression (p, ind, int_type);
	add_to_output (")");
}
//
//	just index a static array
void	code_for_indexed_static (treenode *p, treenode *d, treenode *ind) {
int	current_index = 1;
treenode	*index;

	index =  get_subscripts (ind);
	pr_name_of_array (p, d);	// no way this is a parameter
	add_to_output (" [");

	while (index != (treenode *)0) {
	   code_for_expression (p, index, int_type);
	   add_to_output ( "-");
	   ith_lower_bound (p, current_index ++, d);
	   index = get_nextnode (index);
	   if (index != (treenode *)0) 
	      add_to_output (" ][");
	}

	add_to_output ("]");
}
//
//	for indexing non static array, we need runtime support
void	code_for_indexed_dynamic (treenode *p, treenode *d, treenode *ind) {
int	current_index, index_count;
treenode	*index;

	index		= get_subscripts (ind);
	index_count	= get_num_of_subscripts (ind);
	current_index	= 1;

	add_to_output (" *(");
	add_to_output (c_type_name (element_type (d)));
	add_to_output (" *) __jff_element_address (");
	pr_name_of_array (p, d); add_to_output (", ");
	pr_address_of_descriptor (p, d); add_to_output (", ");
	add_to_output (num_to_string (get_num_of_subscripts (ind)));

	while (index != (treenode *)0) {
	   add_to_output (", ");
	   code_for_expression (p, index, int_type);
	   index = get_nextnode (index);
	}

	add_to_output (")");
}

void	code_for_indexed_value (treenode *p, treenode *ind) {
treenode	*d;

	d = get_array_def (ind);
	if (is_switch (d)) {
	   code_for_indexed_switch (p, d,  get_subscripts (ind));
	   return;
	}

	if (is_static_array (d)) {	// visible array
	   code_for_indexed_static (p, d, ind);
	   return;
	}

	code_for_indexed_dynamic (p, d, ind);
}

treenode *get_lb (treenode *st, int nr) {
treenode *bnd = get_subtype_bounds (st);

	while (nr > 1) {
	   bnd = get_nextnode (bnd);
	   nr --;
	}
	return bnd;
}
//
//	we only need this one for static arrays
void	ith_lower_bound (treenode *p, int cb, treenode *d) {
treenode *current_bnd;
treenode *st;

	ASSERT ((is_static_array (d)), ("Expert error 300"));
	st = get_type_of_var (d);
	current_bnd = get_lb (st, cb);
	code_for_expression (p, get_first_bound (current_bnd), int_type);
}

void	generate_for_stat (treenode *p, treenode *f) {
treenode	*for_el_list;
treenode	*control_var;

	for_el_list = get_for_el_list (f);
	control_var = get_for_var (f);
	while (for_el_list != (treenode *)0) {
	   generate_for_element (p, control_var, for_el_list, get_for_body (f));
	   for_el_list = get_nextnode (for_el_list);
	}
}

void	generate_for_element (treenode *p, treenode *cv, treenode *fe, treenode *s) {
	switch (get_nodeid (fe)) {
	   case SINGLE_FOR_ELEMENT:
	      generate_single_fe (p, cv, fe, s);
	      return;

	   case WHILE_ELEMENT:
	      generate_while_fe (p, cv, fe, s);
	      return;

	   case STEP_UNTIL:
	      generate_step_until_fe (p, cv, fe, s);
	      return;

	   default:;
	// cannot happen
	}
}

void	generate_single_fe (treenode *p, treenode *cv, treenode *fe, treenode *s) {
	assignment_code (p, cv, get_single_expr (fe));
	add_to_output (";\n");
	statement_code (p, s);
}

void	generate_while_fe (treenode *p, treenode *cv, treenode *fe, treenode *s) {
	assignment_code (p, cv, get_while_init (fe));
	add_to_output (";\n while (");
	code_for_expression (p, get_while_condition (fe), type_of (cv));
	add_to_output (") {");
	code_for_block_body (p, s);
	assignment_code (p, cv, get_while_init (fe));
	add_to_output ("; }\n");
}

void	generate_step_until_fe (treenode *p, treenode *cv, treenode *fe, treenode *s) {

	add_to_output ("for (");
	assignment_code (p, cv, get_step_init (fe));
	add_to_output ( "; ( ");
	code_for_expression (p, cv, type_of (cv));
	add_to_output ( "- (");
	code_for_expression (p, get_until_expression (fe), type_of (cv));
	add_to_output (")) * sign ((");
	add_to_output (c_type_name (real_type));
	add_to_output (")");
	code_for_expression (p, get_incr_expression (fe),
	                     type_of (cv));
	add_to_output (" )<= 0;");
	increment_code (p, cv, get_incr_expression (fe));
	add_to_output (")");
	code_for_block_body (p, s);
}

//
//	for a goto, we distinguish between a local one and others
void	generate_goto (treenode *p, treenode *e) {
treenode *def;

	if  (get_nodeid (e) == ID_AS_PRIM) {
	   def = get_id_def (e);
	   if (get_nodeid (def) == LABEL_DECL) {
	      if (get_environmental_proc (def) == p)  {	// just a local jump
	         add_to_output ("goto L");
	         add_to_output (c_nameof (def));
	         add_to_output (";\n");
	         return;
	      }
	   }
	}

	if (get_nodeid (e) == CONDITIONAL) {
	   add_to_output (" if ( ");
	   code_for_expression (p, get_cond_of_condition (e), bool_type);
	   add_to_output ( " ) ");
	   generate_goto (p, get_condition_thenpart (e));
	   add_to_output (" else ");
	   generate_goto (p, get_condition_elsepart (e));
	   add_to_output ("\n");
	   return;
	}
//
//	what remains is a longjmp
	add_to_output ("__jff_longjmp (");
	code_for_expression (p, e, lab_type);
	add_to_output (");\n");
}
//
//	generating code for expressions is like printing a simple
//	formatted string
void	code_for_unary_expression (treenode *p, treenode *un) {
treenode *op = get_un_opdef (un);
treenode *e  = get_unary_operand (un);
char *fmt    = get_c_string_for_un (op);

	while (*fmt != (char) 0) {
	   if (*fmt == '%') {
	      fmt ++;
	      if (*fmt == 'L') 
	         code_for_expression (p, e, type_of (get_left_for_un (op)));
	      else
	         add_to_output (char_to_string (*fmt));
	   }
	   else
	      add_to_output (char_to_string (*fmt));

	   fmt ++;
	}
}

void	code_for_binary_expression (treenode *p, treenode *bin) {
treenode	*op = get_bin_opdef (bin);
treenode	*e1 = get_binary_left_operand (bin);
treenode	*e2 = get_binary_right_operand (bin);
char	*fmt	= get_c_string_for_bin (op);

	while (*fmt != (char) 0) {
	   if (*fmt == '%') {
	      fmt ++;
	      switch (*fmt) {
	         case 'L':
	            code_for_expression (p, e1,
	                       type_of (get_left_operand_for_bin (op)));
	            break;

	         case 'R':
	            code_for_expression (p, e2,
	                       type_of (get_right_operand_for_bin (op)));
	            break;

	         default:
	            add_to_output (char_to_string (*fmt));
	            break;
	      }
	   }
	   else
	      add_to_output (char_to_string (*fmt));

	   fmt ++;
	}
}

//
//	SUPPORT FUNCTIONS, 
//	a mixture of functions
//
void	link_statement (treenode *e, treenode *n) {
	if ((get_nodeid (e) == BLOCK) ||
	    (get_nodeid (e) == COMPOUND)) {
	   if (get_statements (e) == (treenode *)0) {
	       set_statements (e, n);
	       set_last_statement (e, n);
	   }
	   else {
	      set_nextnode (get_last_statement (e), n);
	      set_last_statement (e, n);
	   }
	   return;
	}
	// cannot happen
}
//
void	link_declaration (treenode *e, treenode *n) {
	if (get_nodeid (e) == BLOCK) {
	   if (get_block_decls (e) == (treenode *)0) {
	      set_block_decls (e, n);
	      set_last_block_decl (e, n);
	   }
	   else {
	      set_nextnode (get_last_block_decl (e), n);
	      set_last_block_decl (e, n);
	   }
	   return;
	}

	if (is_a_proc_decl (e)) {
	   if (get_proc_parameters (e) == (treenode *)0) {
	      set_proc_parameters (e,  (treenode *)n);
	      set_proc_lastpar (e, (treenode *)n);
	   }
	   else {
	      set_nextnode (get_proc_lastpar (e), (treenode *)n);
	      set_proc_lastpar (e, (treenode *)n);
	   }
	   return;
	}
	// cannot happen
}

void	link_in_front_to (treenode *e, treenode *n) {
	if (get_nodeid (e) == BLOCK) {
	   if (get_block_decls (e) == (treenode *)0) {
	      set_block_decls (e, n);
	      set_last_block_decl (e, n);
	   }
	   else {
	      set_nextnode (n, get_block_decls (e));
	      set_block_decls (e, n);
	   }
	   return;
	}
	if (get_nodeid (e) == COMPOUND) {
	   link_in_front_to (get_surrounding (e), n);
	   return;
	}
	// cannot happen
}
//
//	we build a list of entities that result in global
//	global declarations in the C program
void	link_to_globals (treenode *d) {

	if (get_first_in_globals (globals) == (treenode *)0) {
	   set_first_in_globals (globals, d);
	   set_last_in_globals (globals, d);
	}
	else {
	   set_next_dec (get_last_in_globals (globals), d);
	   set_last_in_globals (globals, d);
	}
}
//
//	during code generation we print data on
//	all (well, most) of the declarations in a proc
//	or the main program.
//	that is why we link all declarations to the enclosing
//	unit
void	link_to_environmental_proc (treenode *d) {
treenode *p;

	p = get_environmental_proc (d);
	if ((p == (treenode *)0) || is_own (d)) {
	   link_to_globals (d);
	   return;
	}

	if (get_first_dec_in_proc (p) == (treenode *)0) {
	   set_first_dec_in_proc (p, d);
	   set_last_dec_in_proc (p, d);
	}
	else
	{  set_next_dec (get_last_dec_in_proc (p), d);
	   set_last_dec_in_proc (p, d);
	}
}
//
//	the type_name is used in error messages
char	*type_name (treenode *t) {
static char v [127];

	ASSERT ((t != (treenode *)0), ("Expert error 20"));
	switch (get_nodeid (t)) {
	   case SIMPLE_TYPE:
	      return get_type_id (t);

	   case LABEL_TYPE:
      	      return (" label");

   	   case ARRAY_TYPE:
	      sprintf (&v[0], "%s array", type_name (element_type (t)));
	      return v;

   	   case PROC_TYPE:
	      sprintf (&v[0], "%s proc", type_name (result_type (t)));
	      return v;

   	   case ANY_TYPE:
	      return "any_type";

   	   case ERROR_TYPE:
	      return "error_type";

   	   case STRING_TYPE:
	      return "string";

   	   default:
      	      ASSERT (FALSE, ("Expert error 21"));
	      return "?????";
   }
}
//
//	the c_type name is used in the generated code
char	*c_type_name (treenode *t) {
static char v [127];

	ASSERT ((t != (treenode *)0), ("Expert error 22"));
   	switch (get_nodeid (t)) {
   	case SIMPLE_TYPE:
      		return get_c_type (t);

   	case LABEL_TYPE:
      		return ("jmp_buf *");

   	case ARRAY_TYPE:
		sprintf (&v[0], "%s *", type_name (element_type (t)));
	        fprintf (stderr, "in arraytype %s\n", v);
		return v;

   	case PROC_TYPE:
		sprintf (&v[0], "%s (*)()", type_name (result_type (t)));
		return v;

   	case STRING_TYPE:
		return "char *";

   	default:
	        fprintf (stderr, "c_type_name, node %d\n", get_nodeid (t));
	        ASSERT (FALSE, ("Expert error 23\n"));
	        return "????";
	}
}
//
//	op_name is used to get the operator symbol for error messages
char	*op_name (treenode *op) {

	ASSERT ((op != (treenode *)0), ("Expert error 24"));
	if (get_nodeid (op) == UNOP) 
	   return get_opsym_for_un (op);

	if (get_nodeid (op) == BINOP)
	   return get_opsym_for_bin (op);

	ASSERT (FALSE, ("Expert error 25"));
}

// register that d is being accessed from anywhere in the block b
// eliminate recursive proc references
//	we pass on whether or not we are in the context of
//	1. switch element
//	2. actual parameter
//	labels in those contexts expect additional treatment
//	a fairly tricky function
//	d is the declaration, b the block we are in, and ct
//	the "strange context" indicator
void	set_access (treenode *d, treenode *b, int ct) {
treenode	*decl_env;
treenode	*curr_env;
treenode	*st;

	ASSERT ((d != (treenode *)0), ("Expert error 26\n"));
	if (get_nodeid (d) == PROC_DECL)	// special treatment
	   if (in_scope (d, b))
               // something recursive, does not count
	      return;

//	now really start
	set_accessed (d);
	if (get_nodeid (d) == VARIABLE && is_arithmetic_array (d)) 
	   set_accessed (get_type_of_var (d));
//	Now we check for a non local access that requires a static link
//	first determine the declaration environment
	if (get_nodeid (d) == PROC_DECL)
	   decl_env = get_environmental_proc(get_decl_env (d));
	else
	   decl_env = get_environmental_proc (d);	// proc of the declaration
//
//	now start thinking
//	if ct = TRUE and, we have a label, it means
//	we found a label either as
//	1. parameter
//	2. a switchlist element
//	we have to mark it, because it requires
//	additional declaration code (a jmpbuf is to be allocated)
	if (ct && has_label_type (d)) 
	   set_far_access (d);

//	now look at the context we are in
//	if the context is a thunk or a switchlist, we make
//	non local access to the entity, anyhow and the
//	declaration environment needs an jff activation record
//	and never can be local access
	if ((get_nodeid (b) == THUNK) ||
	    (get_nodeid (b) == SWITCH_DECL)) {
	   if (has_label_type (d)) 	// it is non local, code required
	      set_far_access (d);
	}

//	now do normal again
	curr_env = get_environmental_proc (b);	// current PROC environment
	if (curr_env == decl_env)	// just a local access
	   return;

	if (has_label_type (d)) 		// now we know it is non local
	   set_far_access (d);

	if (decl_env == (treenode *)0)
	   return;

	if (curr_env == (treenode *)0)	// we are on global level
	   return;

	while (curr_env != decl_env) {
	   set_need_static_link (curr_env);
	   curr_env = get_environmental_proc(get_decl_env (curr_env));
	}
}
//
//	find the proc you are in
treenode *get_environmental_proc (treenode *t) {

	while (t != (treenode *)0) {
	   switch (get_nodeid (t)) {
	      case PROC_DECL:
	         return (t);

	      case BLOCK:
	      case COMPOUND:
	         t = get_surrounding (t);
	         break;

	      case SWITCH_DECL:
	      case VARIABLE:
	      case LABEL_DECL:
	      case SUBTYPE:
	      case THUNK:
	      case PARAM_DECL:
	         t =  get_decl_env (t);
	         break;

	      default:
	         fprintf (stderr, "Node %d not handled\n", get_nodeid (t));
	         ASSERT (FALSE, ("Expert error 27\n"));
	         return (treenode *)0;
	   }
	}

	return (treenode *)0;
}

//
//	find whether the  proc "p" (which is called)
//	is enclosing us
int	in_scope (treenode *d, treenode *e) {

	ASSERT ((d != (treenode *)0), ("Expert error 29\n"));
	if (e == (treenode *)0)
	   return FALSE;

	switch (get_nodeid (e)) {
	   case BLOCK:
	   case COMPOUND:
	      return in_scope (d, get_surrounding (e));

	   case PROC_DECL:
	      if (e == d) 
	         return TRUE;
	      return in_scope (d, get_decl_env (e));

	   case THUNK:
	      return in_scope (d, get_environmental_proc (e));

	   case SWITCH_DECL:
	      return in_scope (d, get_environmental_proc (e));

	   default:
	      ASSERT (FALSE, ("Expert error 30"));
	      return FALSE;
	}
}

int	proc_level_of (treenode *n) {
	if (n == (treenode *)0)
	   return 0;

	switch (get_nodeid (n)) {
	   case VARIABLE:
	   case PARAM_DECL:
	   case LABEL_DECL:
	   case SUBTYPE:
	      return proc_level_of (get_decl_env (n));

	   case BLOCK:
	   case COMPOUND:
	      return proc_level_of (get_surrounding (n));

	   case PROC_DECL:
	      return get_proc_level (n);

	   case SWITCH_DECL:
	   case THUNK:
	      return proc_level_of (get_decl_env (n)) + 1;

	   default:
	      ASSERT (FALSE, ("Expert error 31"));
	      return 0;
	}
}
//
//	by convention, t1 is the context type
int	is_compatible (treenode *t1, treenode *t2) {
	if ((t1 == (treenode *)0) ||
	    (t2 == (treenode *)0))
	   return FALSE;

	t1 = type_of (t1);
	t2 = type_of (t2);
	if (t1 == t2)
	   return TRUE;

	if (t1 == any_type)
	   return TRUE;

	if ((t1 == void_type) && (t2 != void_type))
	   return TRUE;

	if ((t1 == error_type) && (t2 != error_type))
	   return TRUE;

	if ((t1 == real_type) && (t2 == int_type))
	   return TRUE;

	if ((t1 == int_type) && (t2 == real_type))
	   return TRUE;

	return FALSE;
}

//
//	all entities get a c name on the fly
char	*c_nameof (treenode *d) {
static int	count = 0;
static char	v [255];

	ASSERT ((d != (treenode *)0), ("Expert error 32\n"));
	switch (get_nodeid (d)) {
	   case PROC_DECL:
	   case VARIABLE:
	   case LABEL_DECL:
	   case SWITCH_DECL:
	      if (is_cproc (d))
	         return get_decl_ident (d);

	      if (get_c_name (d) == (char *)0) {
	         sprintf (v, "_%s_%d", get_decl_ident (d), block_of (d));
	         set_c_name (d, store_in_tree (v));
	      }
	      return get_c_name (d);

	   case SUBTYPE:
	      if (get_c_name (d) == (char *)0) {
	         sprintf (v, "__dv%d", count ++);
	         set_c_name (d, store_in_tree (v));
	      }
	      return get_c_name (d);

	   case PARAM_DECL:
	   {  char *n = get_decl_ident (d);
	      sprintf (v, "%s_", n);
	      return v;
	   }

	   case THUNK:
	      return get_decl_ident (d);

	   default:
	      ASSERT (FALSE, ("Expert error 33"));
	      return "???";
	}
}
//
//	b is the environment block, e is the expression, t the type
treenode *create_thunk (treenode *b, treenode *e, treenode *t) {
treenode *th;
static	int	count;
static	char	v [255];
treenode	*p = get_environmental_proc (b);
	th = new_node (THUNK, -1, -1);
	sprintf (v, "_jff_%dA", count++);
	set_decl_ident (th, store_in_tree (v));
	set_type_of_thunk (th, t);
	set_thunk_expr (th, e);
	set_decl_env (th, b);
	link_declaration (b, th);
	link_to_globals (th);
	set_flags (th, get_flags (th) | IS_ACCESSED);
	set_needs_ar (p);
	return th;
}

treenode	*thunk_as_param (treenode *t) {
treenode	*p;
	p = new_node (ID_AS_PRIM, 0, 0);
	set_resolve_ident (p, get_decl_ident (t));
	set_id_def (p, t);
	set_expr_type (p, type_of (t));
	return p;
}

int	block_of (treenode *t) {

	while (t != (treenode *)0) {
	   switch (get_nodeid (t)) {
	      case BLOCK:
	         return get_block_number (t);

	      case PROC_DECL:
	         return get_blockno_of_proc (t);

	      case COMPOUND:
	         t = get_surrounding (t);
	         break;

	      case VARIABLE:
	      case PARAM_DECL:
	      case SUBTYPE:
	      case LABEL_DECL:
	      case SWITCH_DECL:
	         t = get_decl_env (t);
	         break;

	      default:
	         ASSERT (FALSE, ("Expert error 34"));
	         return 0;
	   }
	}
}

//
// Print the access path to the entity "d" while being in context "p"
// series of functions

//	accessing a "simple" entity means a variable or a value par
//	p is the environment "from", d the declaration "to"
void	pr_access_to_simple_entity (treenode *p, treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 35\n"));
	if (!is_parameter (d)) {// must be a var
	   if ((proc_level_of (d) == 0) || is_own (d)) {	// global
	      add_to_output (c_nameof (d));
	      return;
	   }
	}

	if (will_be_compiled_as_c_proc (get_environmental_proc (d))) {
	   add_to_output (c_nameof (d));
	   return;
	}

//	this is the general case
	pr_access_to_local_entity (p, d, " ");
}

void	pr_name_of_formal_string (treenode *p, treenode *d) {
	pr_access_to_local_entity (p, d, " ");
}

void	pr_address_of_switch (treenode *p, treenode *d) {
	ASSERT ((d != (treenode *)0), ("Expert error 39\n"));
	ASSERT ((get_nodeid (d) == SWITCH_DECL), ("Expert error 40\n"));
//	switches are always global procedures
	add_to_output (c_nameof (d));
}

void	pr_address_of_formal_switch (treenode *p, treenode *d) {
	pr_access_to_local_entity (p, d, " ");
}

void	pr_link_for_switch (treenode *p, treenode *d) {
	ASSERT ((d != (treenode *)0), ("Expert error 41\n"));
	ASSERT ((get_nodeid (d) == SWITCH_DECL), ("Expert error 42"));
	pr_link (p, get_environmental_proc (d));
}

void	pr_link_of_formal_switch (treenode *p, treenode *d) {
	ASSERT ((d != (treenode *)0), ("Expert error 41\n"));
	ASSERT ((get_nodeid (d) == PARAM_DECL), ("Expert error 42"));
	pr_access_to_local_entity (p, d, "L");
}

//
//	print the address of an array descriptor
//	first a simple "support" function
//
void	pr_x_descriptor (treenode *p, treenode *d, int flag) {

	if (is_parameter (d)) {
	   if (will_be_compiled_as_c_proc (p)) {
	      add_to_output ("D");
	      add_to_output (c_nameof (d));
	      return;
	   }
	// it is found as a regular "local" entity
	   pr_access_to_local_entity (p, d, "D");
	   return;
	}

//	if it is not a parameter, we rather use the "subtype decl"
//	then the variable
	if (get_nodeid (d) == VARIABLE) {   // we need the descriptor
	    pr_x_descriptor (p, (get_type_of_var (d)), flag);
	    return;
	}

	if ((get_environmental_proc (d) == (treenode *)0) || is_own (d)) {
	   add_to_output (c_nameof (d));
	   return;
	}
//
//	this is the singular point, we might need an "&" operator
	if  (flag == 'a') {
	   add_to_output ("&(");
	   pr_access_to_local_entity (p, d, " ");
	   add_to_output (")");
	}
	else
	   pr_access_to_local_entity (p, d, " ");
}

void	pr_name_of_descriptor    (treenode *p, treenode *d) {
	pr_x_descriptor (p, d, 'n');
}

void	pr_address_of_descriptor (treenode *p, treenode *d) {
	pr_x_descriptor (p, d, 'a');
}

void	pr_name_of_array (treenode *p, treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 43"));
	if (is_parameter (d)) {
	   pr_access_to_local_entity (p, d, " ");
	   return;
	}
//	now it is a real array
	if ((proc_level_of (d) == 0) || is_own (d)) {
	   add_to_output (c_nameof (d));
	   return;
	}

	if (will_be_compiled_as_c_proc (get_environmental_proc (d))) {
	   add_to_output (c_nameof (d));
	   return;
	}

	pr_access_to_local_entity (p, d, " ");
}

void	pr_link_for_formal_proc (treenode *p, treenode *d) {
	pr_access_to_local_entity (p, d, "D");
}

void	pr_address_of_formal_proc (treenode *p, treenode *d) {
	pr_access_to_local_entity (p, d, " ");
}

void	pr_address_of_regular_proc (treenode *p, treenode *d) {
	add_to_output (c_nameof (d));
}
//
//	print the link from p to d, both p and d are proc_decl
//
void	pr_link_to_proc_env (treenode *p, treenode *d) {

	if (d == (treenode *)0) { // we might need something in global space
	   add_to_output ("NULL");
	   return;	
	}
	pr_link (p, d);
}

void	pr_access_to_label (treenode *p, treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 44"));
	ASSERT ((get_nodeid (d) == LABEL_DECL), ("Expert error 45"));
	if (get_environmental_proc (d) == (treenode *)0) {
	   add_to_output (c_nameof (d));
	   return;
	}
	pr_access_to_local_entity (p, d, " ");
}
//
//	thunk is either a real thunk or one passed as parameter
void	pr_address_of_value_thunk (treenode *p, treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 46"));
	if (get_nodeid (d) == THUNK) {
	   add_to_output (c_nameof (d));
	   return;
	}

	pr_access_to_local_entity (p, d, "V");
}

void	pr_address_of_address_thunk (treenode *p, treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 47"));
	if (get_nodeid (d) == THUNK) {
	   add_to_output ("A");
	   add_to_output (c_nameof (d));
	   return;
	}

	pr_access_to_local_entity (p, d, "A");
}

void	pr_link_to_thunk (treenode *p, treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 48"));
	if (get_nodeid (d) == THUNK) {
	   pr_link (p, get_environmental_proc (get_decl_env (d)));
	   return;
	}

	pr_access_to_local_entity (p, d, "L");
}
//
//	rewritten code for printing links
//
//	print the access path to the entity "d", from
//	environment "p". Address the entity with its c name prefixed
//	by the value of "a"
void	pr_access_to_local_entity (treenode *p, treenode *d, char *a) {

	if (will_be_compiled_as_c_proc (get_environmental_proc (d))) {
	   add_to_output (c_nameof (d));
	   return;
	}

	add_to_output ("(");
	pr_link (p, get_environmental_proc (d));
	add_to_output (") -> ");
	add_to_output (a);
	add_to_output (c_nameof (d));
}
//
//	stupid function, we have to find the
//	function that is embedded in "to", on our way
//	to "from"
treenode *proc_embedded_in_to (treenode *from, treenode *to) {

	ASSERT ((to != (treenode *)0), ("Expert error 49"));
	if (get_environmental_proc (get_decl_env (from)) == to)
	   return from;
	return proc_embedded_in_to (get_environmental_proc (get_decl_env (from)), to);
}

void	pr_link_x (treenode *from, treenode *to) {

//	for a thunk or switch decl, act like we are in the environmental
//	procedure
	if (get_nodeid (from) == THUNK ||
	    get_nodeid (from) == SWITCH_DECL) {
	   pr_link_x (get_environmental_proc (get_decl_env (from)), to);
	   return;
	}
//
//	this is where the recursion will stop
	if (from == to) {	// local access
	   add_to_output ("((struct ");
	   pr_type_of_ar (to);
	   add_to_output (" *)(LP))");
	   return;
	}

//	now environment represented by "from" is enclosed in to
	add_to_output ("((struct ");
	pr_type_of_ar (to);
	add_to_output (" *)((");
	pr_link_x (from, proc_embedded_in_to (from, to));
	add_to_output (") -> __l_field))");
	return;
}

//	print the representation of the link pointer from the
//	environment we are in (from), to the environment we want
//	to reach (to)
void	pr_link (treenode *from, treenode *to) {
int	current_level;
int	target_level;
	current_level = proc_level_of (from);
	target_level  = proc_level_of (to);

	if (target_level == 0) { // might happen
	   add_to_output ("LP");
	   return;
	}

	if (current_level == target_level) {  // it is local
	   if (will_be_compiled_as_c_proc (from)) 
	      add_to_output ("NULL"); // we should not be here
	   else
	      add_to_output ("LP");
	   return;
	}

	pr_link_x (from, to);
}

//
//	print the type of the activation record belonging
//	to procedure p
//
void	pr_type_of_ar (treenode *p) {

	ASSERT ((p != (treenode *)0), ("Expert error 50"));
	ASSERT ((get_nodeid (p) == PROC_DECL), ("Expert error 50a"));
	add_to_output ("__");
	add_to_output (c_nameof (p));
	add_to_output ("_rec");
}

void	pr_declaration_comment (treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 50"));
	add_to_output (" /* ");
	add_to_output (get_decl_ident (d));
	add_to_output (" declared at line ");
	add_to_output (num_to_string (get_lineno (d)));
	add_to_output ("*/\n");
}

// just count the entities in a list
int	count_entities (treenode *e) {
int	i = 0;
	while (e != (treenode *)0) {
	   i ++;
	   e = get_nextnode (e);
	}
	return i;
}
//
//	sometimes a for body is made into a procedure,
//	give it a decent name
char	*new_for_id	(treenode *b) {
char	v [31];
static	int	cnt	= 0;
	sprintf (v, "__for_body_%d", cnt++);
	return store_in_tree (v);
}
//
//	make a call to p in environment of block b
treenode *make_proc_call (treenode *b, treenode *p) {
treenode *f;
	f = new_node (FUNCTION_CALL, 0, 0);
	set_function_ident (f, get_decl_ident (p));
	set_actuals (f, (treenode *)0);
	set_called_function (f, p);
	set_expr_type (f, void_type);
	return f;
}

//
//	procs have a return type. From wherever you start, get it
treenode *result_type (treenode *n) {

	ASSERT ((n != (treenode *)0), ("Expert error 51"));
	n = type_of (n);
	if (get_nodeid (n) == PROC_TYPE)
	   return get_proctype_returntype (n);

	return error_type;
}

//
//	for any entity, determine a type
treenode *type_of (treenode *n) {
treenode *m = n;

	while (n != (treenode *)0) {
	   switch (get_nodeid (n)) {
	      case VARIABLE:
	         n = get_type_of_var (n);
	         break;

	      case PARAM_DECL:
	         n = get_param_type (n);
	         break;

	      case LABEL_DECL:
	         return lab_type;

	      case SUBTYPE:
	         n = get_basetype (n);
	         break;

	      case PROC_DECL:
	         n = get_proctype (get_proc_returntype (n));
	         break;

	      case THUNK:
	         n =  get_thunk_expr (n);
	         break;

	      case ASSIGNMENT:
	         n = get_lhs_expression (n);
	         break;

	      case UNARY_EXPRESSION:
	      case BINARY_EXPRESSION:
	      case INUMBER:
	      case FNUMBER:
	      case BNUMBER:
	      case STRING_CONSTANT:
	      case INDEXING:
	      case ID_AS_PRIM:
	      case FUNCTION_CALL:
	      case CONDITIONAL:
	         n = get_expr_type (n);
	         break;

	      case SIMPLE_TYPE:
	      case ARRAY_TYPE:
	      case PROC_TYPE:
	      case LABEL_TYPE:
	      case ERROR_TYPE:
	      case ANY_TYPE:
	      case STRING_TYPE:
	         return (treenode *) n;

	      case SWITCH_DECL:
	         return get_arraytype (lab_type);

	      case ACT_PAR:
	         n = get_act_exp (n);
	         break;

	      default:
	         return error_type;
	   }
	}

	if (m != NULL) 
	   fprintf (stderr, "line %d, char %d\n",
	               get_lineno (m), get_charno (m));
	ASSERT (FALSE, ("Expert error 53\n"));
}
//
//	get the element type of an array, from
//	wherever you start
treenode *element_type (treenode *n) {

	ASSERT ((n != (treenode *)0), ("Expert error 54\n"));
	n = type_of (n);
	if (get_nodeid (n) == ARRAY_TYPE)
	   return get_element_type (n);
	return FALSE;
}

int	is_single_statement (treenode *s) {
	if (s == (treenode *)0)
	   return TRUE;

	if ((get_nodeid (s) == BLOCK) &&
	    (get_block_decls (s) == (treenode *)0))
	   return is_single_statement (get_statements (s));

	if (get_nodeid (s)  == COMPOUND)
	   return is_single_statement (get_statements (s));

	if (get_nextnode (s) == (treenode *)0)
	   return TRUE;

	if (get_nodeid (s) == NULL_STAT)
	   return is_single_statement (get_nextnode (s));

	return FALSE;
}

void	set_own (treenode *v) {

	ASSERT ((v != (treenode *)0), ("Expert error 55\n"));
	set_flags (v, get_flags (v) | IS_OWN);
}

int	is_own (treenode *v) {

	ASSERT ((v != (treenode *)0), ("Expert error 56\n"));
	return get_flags (v) & IS_OWN;
}

void	set_needs_deallocation (treenode *b) {
treenode *p;

	ASSERT ((b != (treenode *)0), ("Expert error 57\n"));
	p = get_environmental_proc(b);
	if (p != (treenode *)0) 
	   set_flags (p, get_flags (p) | NEED_DEALLOCATION);
}

int	needs_deallocation (treenode *b) {
	if (b == (treenode *)0)
	   return TRUE;
	return get_flags (b) & NEED_DEALLOCATION;
}
//
//	this has to be reconsidered
void	set_array_as_parameter (treenode *d) {

	ASSERT ((d != (treenode *)NULL), ("Expert error 58"));
	if (get_nodeid (d) == VARIABLE) 
	   d = get_type_of_var (d);

	if (get_nodeid (d) == SUBTYPE) {
	   set_subtype_needs_descriptor (d);
	   set_accessed (d);
	   return;
	}
	// just return in other case
	// it can be a parameter, but who cares
}

void	set_subtype_needs_descriptor (treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 61"));
	ASSERT ((get_nodeid (d) == SUBTYPE), ("Expert error 59"));
	set_flags (d, get_flags (d) | SUBTYPE_NEEDS_DESCRIPTOR);
}

int	subtype_needs_descriptor (treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 61"));
	ASSERT ((get_nodeid (d) == SUBTYPE), ("Expert error 60"));
	return get_flags (d) & SUBTYPE_NEEDS_DESCRIPTOR;
}

int	is_defined (treenode *p) {

	ASSERT ((p != (treenode *)0), ("Expert error 61"));
	return get_flags (p) & IS_DEFINED;
}

void	set_defined (treenode *p) {

	ASSERT ((p != (treenode *)0), ("Expert error 62"));
	set_flags (p, get_flags (p) | IS_DEFINED);
}

int	is_valid_value_param (treenode *p) {

	ASSERT ((p != (treenode *)0), ("Expert error 63"));
	if (has_string_type (p))
	   return FALSE;

	if (has_a_proc_type (p))
	   return FALSE;

	return TRUE;
}

void	set_static_array (treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 64"));
	set_flags (d, get_flags (d) | STATIC_ARRAY);
}

int	is_static_array	(treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 64a"));
	return is_arithmetic_array (d) && (get_flags (d) & STATIC_ARRAY);
}
int	can_be_assigned_to (treenode *d) {
treenode *t;

	if (d == (treenode *)NULL)
	   return FALSE;
	t = type_of (d);
	return get_nodeid (t) == SIMPLE_TYPE;
}

int	type_of_entity_is_simple (treenode *d) {
	return can_be_assigned_to (d) ||
	       has_label_type (d);
}

int	is_parameter (treenode *d) {
	if (d == (treenode *)0)
	   return FALSE;
	return (get_nodeid (d) == PARAM_DECL);
}

int	is_arithmetic_array (treenode *n) {

	ASSERT ((n != (treenode *)0), ("Expert error 65"));
	n = type_of (n);
	return ((get_nodeid (n) == ARRAY_TYPE) &&
	        get_nodeid (get_element_type (n)) == SIMPLE_TYPE);
}

int	is_switch (treenode *n) {

	ASSERT ((n != (treenode *)0), ("Expert error 66\n"));
	n = type_of (n);

	if (get_nodeid (n) == ARRAY_TYPE)
	   return (get_element_type (n)) == lab_type;
	return FALSE;
}

int	has_a_proc_type	(treenode *n) {

	ASSERT ((n != (treenode *)0), ("Expert error 67"));
	n = type_of (n);
	return get_nodeid (n) == PROC_TYPE;
}

int	is_a_proc_decl (treenode *n) {

	ASSERT ((n != (treenode *)0), ("Expert error 68"));
	return get_nodeid (n) == PROC_DECL;
}

int	has_label_type (treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 69"));
	return type_of (d) == lab_type;
}

int	has_string_type (treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 70"));
	return type_of (d) == string_type;
}

int	is_specified_as_value (treenode *par) {

	ASSERT ((par != (treenode *)0), ("Expert error 71"));
	ASSERT ((is_parameter (par)), ("Expert error 71a"));
	return get_flags (par) & IS_VALUE;
}

void	set_specified_as_value (treenode *par) {

	ASSERT ((par != (treenode *)0), ("Expert error 72"));
	ASSERT ((is_parameter (par)), ("Expert error 72a"));
	set_flags (par, get_flags (par) | IS_VALUE);
}

void	set_statement_has_label (treenode *s) {

	ASSERT ((s != (treenode *)0), ("Expert error 73"));
	set_flags (s, get_flags (s) | STATEMENT_HAS_LABEL);
}

int	has_statement_label (treenode *s) {

	ASSERT ((s != (treenode *)0), ("Expert error 74"));
	return get_flags (s) & STATEMENT_HAS_LABEL;
}

void	set_proc_as_parameter (treenode *p) {

	ASSERT ((p != (treenode *)0), ("Expert error 75"));
	set_flags (p, get_flags (p) | PROC_AS_PARAMETER);
}

int	is_proc_as_parameter (treenode *p) {

	ASSERT ((p != (treenode *)0), ("Expert error 76"));
	return get_flags (p) & PROC_AS_PARAMETER;
}

int	is_accessed (treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 77\n"));
	return get_flags (d) & IS_ACCESSED;
	return (1);
}

void	set_accessed (treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 78"));
	set_flags (d, get_flags (d) | IS_ACCESSED);
}

void	set_constant_expression	(treenode *e) {

	ASSERT ((e != (treenode *)0), ("Expert error 79"));
	set_flags (e, get_flags (e) | IS_CONSTANT);
}

void	set_assigned	(treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 80"));
	set_flags (d, get_flags (d) | IS_ASSIGNED_TO);
}

int	is_assigned_to	(treenode *d) {

	ASSERT ((d != (treenode *)0), ("Expert error 81"));
	return get_flags (d) & IS_ASSIGNED_TO;
}

int	is_constant_expression	(treenode *e) {

	ASSERT ((e != (treenode *)0), ("Expert error 82"));
	return get_flags (e) & IS_CONSTANT;
}

int	is_elaborated (treenode *d) {
	return get_flags (d) & IS_ELABORATED;
}

void	set_elaborated (treenode *d) {
	set_flags (d, get_flags (d) | IS_ELABORATED);
}

void	set_error (treenode *e) {
	set_flags (e, get_flags (e) | IS_ERROR);
	set_expr_type (e, error_type);
}

int	is_erroneous (treenode *e) {
	return get_expr_type (e)== error_type || (get_flags (e) & IS_ERROR);
}

int	is_cproc (treenode *d) {
	return get_flags (d) & C_PROC;
}

int	need_static_link (treenode *p) {
	return get_flags (p) & NEED_STATIC_LINK;
}

void	set_need_static_link (treenode *p) {
	set_flags (p, get_flags (p) | NEED_STATIC_LINK);
}

void	set_needs_ar (treenode *p) {

	if (p == (treenode *)0)	// just outer level
	   return;

	set_flags (p, get_flags (p) | PROC_NEEDS_AR);
}

int	will_be_compiled_as_c_proc (treenode *p) {

	if (p == (treenode *)0)	//just outer level
	   return FALSE;

	if (get_flags (p) & PROC_NEEDS_AR)
	   return FALSE;

	if (need_static_link (p))
	   return FALSE;

	return TRUE;
}

int	has_far_access	(treenode *p) {

	ASSERT ((p != (treenode *)0), ("Expert error 90"));
	return (!(is_parameter (p)) && (get_flags (p) & FAR_ACCESS));
}

void	set_far_access (treenode *p) {
treenode *envp;

	ASSERT ((p != (treenode *)0), ("Expert error 91"));
	if (is_parameter (p))
	   return;

	set_flags (p, get_flags (p) | FAR_ACCESS);
	envp = get_environmental_proc (p);
	if (envp != (treenode *)0)
	   set_flags (envp, get_flags (envp) | FAR_ACCESS);
}

//
//	Look to see whether type of actual (tap) matches with 
//	type of formal (tfp)
int	matching_param_type (treenode *tap, treenode *tfp) {

	if (tfp == any_type)
	   return TRUE;

//	we are already back on base type level, so looking at switches
//	and strings is not needed
	if (tfp == tap)
	   return TRUE;

	if (has_a_proc_type (tfp) && has_a_proc_type (tap)) {
	   if (result_type (tfp) == void_type)
	      return TRUE;
	   return is_compatible (result_type (tfp), result_type (tap));
	}

	if (is_arithmetic_array (tfp) && is_arithmetic_array (tap))
	   return is_compatible (element_type (tfp), element_type (tap));

	return is_compatible (type_of (tfp), type_of (tap));
}

int	formal_requires_thunk (treenode *fp) {

	if (fp == (treenode *)0)
	   return TRUE;
	if (is_switch (fp) || has_string_type (fp) ||
	    is_arithmetic_array (fp) || has_a_proc_type (fp) ||
	    is_specified_as_value (fp))
	   return FALSE;

	return TRUE;
}

void	add_to_output (char *s) {
	fprintf (f_out, s);
}

char	*num_to_string (int n) {
char	v[100];

	sprintf (v, "%d", n);
	return store_in_tree (v);
}

char	*char_to_string (char c) {
char v [10];

	sprintf (v, "%c", c);
	return store_in_tree (v);
}

//
//	namelist management
//	we dynamically allocate elements
//
struct	X_block {
	char	*data;
	struct X_block	*next;
	int	lwb;
	int	upb;
};

struct X_block *new_X_block (int a, int b, int el_size) {
struct X_block *tmp;
	tmp = (struct X_block *)malloc (sizeof (struct X_block));
	memset (tmp, 0, sizeof (struct X_block));
	tmp -> data = (char *)malloc (SEGMENT_SIZE * el_size);
	memset (tmp -> data, 0, SEGMENT_SIZE * el_size);
	tmp -> next = (struct X_block *)0;
	tmp -> lwb  = a;
	tmp -> upb  = b;
	return tmp;
}

struct X_array {
	int	el_size;
	struct X_block *first_block;
	struct X_block *last_block;
};

struct X_array *new_X_array (int a) {
struct X_array *tmp;
	tmp = (struct X_array *)malloc (sizeof (struct X_array));
	memset (tmp, 0, sizeof (struct X_array));
	tmp -> el_size = a;
	tmp -> first_block = (struct X_block *)0;
	tmp -> last_block = (struct X_block *)0;
	return tmp;
}

struct X_block	*X_extend (struct X_array *a, int index) {
int	lwb, upb;
	lwb =  (index / SEGMENT_SIZE) * SEGMENT_SIZE;
	upb	= lwb + SEGMENT_SIZE - 1;
	if (a -> first_block == (struct X_block *)0) {
	   a -> first_block =
	      a -> last_block = new_X_block (lwb, upb, a -> el_size);
	}
	else {
	   a -> last_block -> next = new_X_block (lwb, upb, a -> el_size);
	   a -> last_block = a -> last_block -> next;
	}
	return a -> last_block;
}

char	*my_element (struct X_array *a, int index) {
struct X_block	*segment;
struct X_block *f =  a -> first_block;
	while (f != (struct X_block *)0) {
	   if (f -> lwb <= index && index <= f -> upb) 
	      return  &(f -> data [(index - f -> lwb) *a -> el_size]);
	   f = f -> next;
	}
	segment = X_extend (a, index);
	return &(segment -> data [(index - segment -> lwb) * a -> el_size]);
}

struct X_array *create_array (int el_size) {
	return new_X_array (el_size);
}

struct namelist_el {
	char *ident;
	treenode *definition;
};

struct X_array *table;
struct X_array	*create_namelist () {
	return create_array (sizeof (struct namelist_el));
}

struct namelist_el *get_table (struct X_array *nl, int index) {
	return (struct namelist_el *)my_element (nl, index);
}

void	set_table (struct X_array *nl, int index, struct namelist_el v) {
struct namelist_el *s = get_table (nl, index);
	*s = v;
}

struct env_descriptor {
	int	first_definition;
	int	number_of_entries;
	int	block_number;
	int	surrounding_block;
};

struct X_array	*block_table;
struct X_array	*create_block_table () {
	return create_array (sizeof (struct env_descriptor));
}

struct env_descriptor *get_block_table (struct X_array *nl, int index) {
	return (struct env_descriptor *)my_element (nl, index);
}

void	set_block_table (struct X_array *nl,
	                         int index, struct env_descriptor v) {
struct env_descriptor *s = get_block_table (nl, index);
	*s = v;
}

int	first_entry		= 0;
int	free_block		= 1;
int	current_block		= 0;
int	last_entry		= NO_OF_ENTRIES - 1;

void	init_nametables () {
	table = create_namelist ();
	block_table = create_block_table ();
}

int	create_scope (treenode *d) {
struct env_descriptor  *ed;
	ed = get_block_table (block_table, free_block);
	ed -> first_definition = first_entry;
	ed -> number_of_entries = 0;
	ed -> block_number = free_block;
	ed -> surrounding_block = current_block;
//	set_block_table (block_table, free_block, ed);
	current_block = free_block ++;
	return current_block;
}

void	leave_scope () {
int i;
struct env_descriptor  *ed;
	ed =  get_block_table (block_table, current_block);
	for (i = ed -> number_of_entries; i > 0;  i--) {
	   struct namelist_el s = *get_table (table, -- first_entry);
	   set_table (table, --last_entry, s);
	}
	ed -> first_definition = last_entry;
	current_block = ed -> surrounding_block;
}

void	add_entry (treenode *d, char *ident) {
struct namelist_el temp;
struct env_descriptor *ed;

	temp. ident = ident;
	temp. definition = d;
	ed = get_block_table (block_table, current_block);
	ed -> number_of_entries ++;
	set_table (table, first_entry, temp);
	if (first_entry ++ >= last_entry) {
	   fprintf (stderr, "Symbol table overflow, fatal\n");
	   exit (EXIT_FAILURE);
	}
}

treenode *find_in_scope	(int s, char *ident) {
int i;
struct namelist_el  *temp;
struct env_descriptor  *ed;

	ed = get_block_table (block_table, s);
	for (i = 0; i < ed -> number_of_entries; i ++) {
	   temp =  get_table (table, ed -> first_definition + i);
	   if (temp -> ident == ident)
	      return temp -> definition;
	}
//	not found
	return (treenode *)0;
}

treenode *find_definition(int s, char *ident) {
treenode *d;

	while (s != 0) {
	   d = find_in_scope (s, ident);
	   if (d != (treenode *)0)
	      return d;
	   s = get_block_table (block_table, s) -> surrounding_block;
	}

	return (treenode *)0;
}

// Reducing error reports
// Each undeclared ident is put in a list
// Since we allow only MAX_ERROR errors, the max size of the table
// is MAX_ERRORS + 1

char	*forgotten_list [MAX_ERRORS + 1];
int	pil	= 0;

void	put_in_forgotten_list (int b, char *id) {
	forgotten_list [pil ++] = id;
}

int	in_forgotten_list (int b, char *id) {
int	i;
	for (i = 0; i < pil; i ++) 
	   if (forgotten_list [i] == id)
	      return TRUE;
	return FALSE;
}


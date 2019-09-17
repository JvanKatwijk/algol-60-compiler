#
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
// jff-header, include file for compiled programs
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
#include <setjmp.h>
#include <math.h>
#include	<stdarg.h>
extern	void	*__jff_element_address (char *, int *, int, ...);
extern	void	__dv_init();
extern	int	*__jff_descriptor_for_value (int *, int, char *);
extern	char	*__jff_allocate_array (int *, char *);
extern	void	__typed_copy (int *, int *, char *, char *);
extern	void	__deallocate (char *);
extern	void	__print_depth (int, char *);
extern	char	*__eval_value_thunk (char **, int, char);
extern	char	*__get_function_address (char **, int, char);
extern	char	*__get_function_link (char **, int, char);
extern	char	*__get_array_address (char **, int, char);
extern	int 	*__get_array_descr (char **, int, char);
extern	char	*__get_value_thunk (char **,int, char);
extern	char	*__get_address_thunk (char **, int, char);
extern	char	*__get_thunk_link (char **, int);
extern	char	*__get_switch_address (char **, int, char);
extern	char	*__get_switch_link (char **, int);
extern	double	read_real (int);
int     raw_in  (int);  
int     raw_out (int fd, int val);

#define	DOPE_BASE	2
#define	true	1
#define	false	0

#define	arctan	atan
#define ln	log
extern	int	__ipow (int, int);
extern	double	__npow (double, int);
extern	double	__fpow (double, double);
extern	int	__mod  (int, int);
void	jff_longjmp (jmp_buf *);


/* Addressing parameters */
#define PPLUS(x, y) (char **)(((char **)x) + (int)y)
#define is_newer(x, y) ((char *)x) < ((char *)y)
#define IPLUS(x, y) (int *)(((int *)x) + (int)y)


/* end of jff_header.h */


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
// runtime.c, run time functions for compiled algol 60 programs
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

#include	<stdio.h>
#include	<stdlib.h>
#include	<stdarg.h>
#include	<stdint.h>
#include	"jff_header.h"
#
void fault (char *, double);
// First part: code for runtime support functions
  
// Array manipulation:
//      allocate allocates dynamically the space
//      dv_init initializes the dope vector (static part)
//      element_address generates the address of an array element
  
//      deallocation of dynamically allocated arrays is done on a per 
//      procedure basis. For each procedure that contains dynamically 
//      allocated arrays a "slot" is allocated with the base pointer
//      of the array as identifier. This slot contains a pointer to
//      a list of the dynamically allocated arrays
//      The slots are stacked through a dynamically linked list
//
//      In case of a long jump, elements on the stack are pulled of
//      and the associated arrays are free-ed
struct __array_link {
	struct __array_link *next;
};

struct __alloc_slot {
	char *ar;			// activation record it belongs to
	struct __alloc_slot *previous;
	struct __array_link *v;
};
struct __alloc_slot *last_slot;

struct __alloc_slot * __find_slot (char *p) {
struct __alloc_slot *l = last_slot;
	while (l != (struct __alloc_slot *) 0) {
	   if (l -> ar == p)
	      return l;
	   l = l -> previous;
	}
	return (struct __alloc_slot *) 0;
}
//
//	If we do not have a slot yet, allocate it
//
char	*__alloc_block (int size, char *lf) {
struct __array_link *t;
struct __alloc_slot *ll;

	t = (struct __array_link *) malloc (sizeof (struct __array_link) +
		  size);
	ll = __find_slot (lf);
	if (ll == (struct __alloc_slot *) 0) {
	   ll = (struct __alloc_slot *) malloc (sizeof (struct __alloc_slot));
	   ll -> previous = last_slot;
	   ll -> ar = lf;
	   ll -> v = (struct __array_link *)0;
	   last_slot = ll;
	}
	t -> next = ll -> v;
	ll -> v = t;
	return (char *)((char *)t + sizeof (struct __array_link));
}

void __deallocate (char *lf) {
struct __alloc_slot *ll;
struct __array_link *h, *n;

	h = last_slot -> v;
	while (h != (struct __array_link *) 0) {
	   n = h -> next;
	   free ((char *) h);
	   h = n;
	}
	ll = last_slot;
	last_slot = last_slot -> previous;
	free ((char *) ll);
}

void __jff_remove (jmp_buf * p) {
struct __alloc_slot *l = last_slot;
struct __alloc_slot *k;

	if (last_slot == (struct __alloc_slot *)0)
	   return;
//
	while (( last_slot != (struct __alloc_slot *)0) &&
               (is_newer (last_slot -> ar, p))) {
           __deallocate ((char *)last_slot);
	}
}

//
//	this is what the user sees
//
void __jff_longjmp (jmp_buf * env) {
 	__jff_remove (env);	// throw away all dynamically allocated stuff
	longjmp (*env, 1);
}

char * __jff_allocate_array (int *desc, char *lf) {
int size, el_size, ndim, i;

	size = 1;
	el_size = desc[0] & 0377;
	ndim = desc[0] >> 8;
	for (i = 1; i <= ndim; i++)
	   size = size * (desc[DOPE_BASE + 2 * i - 1] -
	                  desc[DOPE_BASE + 2 * i - 2] + 1);

	return  __alloc_block (size * el_size, lf);
}

//	According the the MR any arithmetic array can be passed by value
//	to any arithmetic formal array. This means interpretation

void	__typed_copy (int *old_desc, int *new_desc, char *src, char *dest) {
int	no_of_el, i, ndims, el_size_o, el_size_n;;

	no_of_el = 1;
	ndims = old_desc[0] >> 8;
	for (i = 1; i <= ndims; i++)
	   no_of_el = no_of_el * (old_desc [DOPE_BASE + 2 * i - 1] -
	                  old_desc [DOPE_BASE + 2 * i - 2] + 1);

	el_size_o = old_desc [0] &0377;
	el_size_n = new_desc [0] &0377;
//	Now some case analysis on the el_size

	if (el_size_o == el_size_n) {
	   for (i = 0; i < no_of_el; i ++) {
	      switch (el_size_o) {
	         case sizeof (char):
	            ((char *)dest)[i]		= ((char *)src)[i];
	            break;

	         case sizeof (int):
	            ((int *)dest)[i]		= ((int *)src)[i];
	            break;

	         case sizeof (double):
	            ((double *)dest) [i]	= ((double *)src) [i];
	            break;

	         default:
	             fprintf (stderr, "Copying value array with unknown value size %d\n",
	                      el_size_o);
	             exit (33);
	      }
	   }
	   return;
	}
//	when we are here, apparently, the types of value of src and dest are
//	different.
//	But basically it is simple, either float -> int or int -> float
	for (i = 0; i < no_of_el; i ++) {
	   switch (el_size_n) {
	      case sizeof (int):
	         ((int *)dest)[i] = (int) (((double *)src)[i]);
	         break;

	      case sizeof (double):
	         ((double *)dest) [i] = (double) (((int *)src)) [i];
	         break;

	      default:
	         fprintf (stderr, "Copying value array with unknown value size %d\n",
	                  el_size_o);
	         exit (33);
	   }
	}
}
//
//	In case of a by value array parameter, a new descriptor
//	is generated
//
int	*__jff_descriptor_for_value (int *old_desc, int el_size, char *lf) {
int	ndims, i;
int	*new_desc;
	ndims = (old_desc [0] >> 8) & 0xFF;
	new_desc = (int *) __alloc_block (sizeof (int) * (2 * ndims + DOPE_BASE), lf);
	for (i = 0; i < 2 * ndims + DOPE_BASE; i ++) 
	   new_desc [i] = old_desc [i];

	new_desc [0] = (ndims << 8) + el_size;
//	a new init is required
	__dv_init (new_desc);
	return new_desc;
}

void __dv_init (int *desc) {
int size, el_size, i;
char *t;
int ndim;
int u_min_l, temp;

	ndim = desc [0] >> 8;
	temp = desc [DOPE_BASE + 0];
	for (i = 2; i <= ndim; i++) {
	   u_min_l =
	      desc [DOPE_BASE + 2 * i - 1] - 
	      desc [DOPE_BASE + 2 * i - 2] + 1;
	   temp = temp * u_min_l + desc [DOPE_BASE + 2 * i - 2];
	}

	desc [1] = -temp;
}
//
//	The call may contain more
//	parameters, depending on the 
//	dimensionality. These params are all ints
void * __jff_element_address (char *v, int *desc, int dim, ...) {
int i, ndims, u_min_l, temp;
va_list vl;

	ndims = (desc [0] >> 8);
	if (dim != ndims) {
	   fault ("Subscripts do not match (fatal)\n", 121);
           abort ();
        }
	va_start (vl, dim);
	temp =  va_arg (vl, int);;

//	adressing the next parameter is machine dependent
	for (i = 2; i <= ndims; i++) {
	   u_min_l =
	      desc [DOPE_BASE + 2 * i - 1] -
	      desc [DOPE_BASE + 2 * i - 2] + 1;
           temp = temp * u_min_l + va_arg (vl, int);
        }

	va_end (vl);
  	return &v [(temp + desc [1]) * (desc [0] & 0377)];
}

//
//      Transfer of parameters to a procedure that is a formal itself
//      In the actuals descriptor information is added
//      and the procedure that is used as formal is packed in an enveloppe 
//      that deals with the parameter transfer
//      actual descriptions are:
#define	THUNK		'T'
#define	ARRAY		'A'
#define	FUNCTION	'F'
#define	SWITCH		'W'
#define	STRING		'S'
//
//	All actual parameters are either a thunk or some address
//
char	*__map_kind (char k) {
	switch (k) {
	   case THUNK:		return "THUNK";
	   case ARRAY:		return "ARRAY";
	   case FUNCTION:	return "FUNCTION";
	   case SWITCH:		return "SWITCH";
	   case STRING:		return "STRING";
	   default:
	   			return "?????";
	}
}

void __param_type (char *p1, int *k, int *t) {
	*t = ((int)(p1) >> 8);
	*k = ((int)(p1) & 0377);
}

int	__is_arithmetic (char c) {
	return ((c == "double"[0]) || (c == "int"[0]));
}
//
//	find, starting at the first parameter, the
//	address of the i-th one, just step through
//
char ** __get_parameter_position (char **p1, int i) {
int k, t;
int count	= 0;
	while (i > 1) {
	   __param_type (*p1, &k, &t);
	   switch (k) {
	      case THUNK:
	         p1 = PPLUS (p1, 4); // thunk par has 4 fields
	         count += 4;
	         break;

	      case SWITCH:
	         p1 = PPLUS (p1, 3); // switch par has three fields
	         count += 3;
	         break;

	      case FUNCTION:
	         p1 = PPLUS (p1, 3); // function as par has three fields
	         count += 3;
	         break;

	      case ARRAY:
	         p1 = PPLUS (p1, 3); // array as par has three fields
	         count += 3;
	         break;

	      case STRING:
	         p1 = PPLUS (p1, 2); // string as par has two fields
	         count += 2;
	         break;

	      default:
	         fprintf (stderr, "lost with parameter %d (%c)\n", i, k);
	         exit (21);
	   }
           i--;
	}
	return p1;
}

char	*__get_switch_link (char **p1, int i) {
int k, t;

	p1 = __get_parameter_position (p1, i);
	__param_type (*p1, &k, &t);
	if (k == SWITCH) {
	   p1 = PPLUS (p1, 1);
	   return (char *) (*p1);
	}

	fprintf (stderr, "Switch expected as actual (got %s)\n",
	         __map_kind (k));
	exit (21);
}

char	*__get_switch_address (char **p1, int i, char tp) {
int k, t;
	p1 = __get_parameter_position (p1, i);
	__param_type (*p1, &k, &t);
	if (k == SWITCH) {
	   p1 = PPLUS (p1, 2);
	   return (char *) (*p1);
	}

	fprintf (stderr, "Switch expected as actual (got %s)\n",
	         __map_kind (k));
	exit (21);
}

char	*get_string (char **p1, int i, char tp) {
int k, t;
	p1 = __get_parameter_position (p1, i);
	__param_type (*p1, &k, &t);
	if (k == STRING) {
	   p1 = PPLUS (p1, 1);
	   return (char *) (*p1);
	}

	fprintf (stderr, "String expected as actual, (got %s)\n",
	         __map_kind (k));
	exit (21);
}
//
//	tricky, when expecting a thunk, we might see a function
char	*__get_thunk_link (char **p1, int i) {
int k, t;
	p1 = __get_parameter_position (p1, i);
	__param_type (*p1, &k, &t);
	if (k == THUNK || k == FUNCTION) {
	   p1 =  PPLUS (p1, 1);
	   return (char *) (*p1);
	}

	fprintf (stderr, "Function or by name param expected as actual\n");
	fprintf (stderr, " we got %s\n", __map_kind (k));
	exit (21);
}

void * __no_address (void) {
	fprintf (stderr, "Attempt to access non-existent address thunk");
	exit (22);
}

char	*__get_address_thunk (char **p1, int i, char tp) {
int k, t;
	p1 = __get_parameter_position (p1, i);
	__param_type (*p1, &k, &t);
	if (k == THUNK) {
	   p1 = PPLUS (p1, 2);
	   return (char *) (*p1);
	}

	if (k == FUNCTION) 
           return (char *) (&__no_address);

	fprintf (stderr, "Normal by name param expected, (got %s)\n",
	         __map_kind (k));
	exit (21);
}

char	*__get_value_thunk (char **p1, int i, char tp) {
int k, t;

	p1 = __get_parameter_position (p1, i);
	__param_type (*p1, &k, &t);
	if (k == THUNK) // ordering: param_desc, link, addr, val
	   p1 = PPLUS (p1, 3); 
	else
	if (k == FUNCTION) // ordering: param_desc, mlink, f_addr
	   p1 =  PPLUS (p1, 2); 
	else {
	   fprintf (stderr, "Normal by name param expected, (got %s)\n",
	            __map_kind (k));
	   exit (21);
	}

	if ((t != tp) &&
	    (!(__is_arithmetic (t) && __is_arithmetic (tp)))) {
	   fprintf (stderr, "Illegal type for actual param (%c, %c)\n", 
	            tp, t);
	   exit (21);
	}

	return (char *) (*p1);
}

int	*__get_array_descr (char **p1, int i, char tp) {
int k, t;

	p1 = __get_parameter_position (p1, i);
	__param_type (*p1, &k, &t);
	if (k == ARRAY) {
	   p1 = PPLUS (p1, 1);
	   return (int *) (*p1);
	}

	fprintf (stderr, "Array expected (got %s)\n", __map_kind (k));
	exit (21);
}

char	*__get_array_address (char **p1, int i, char tp) {
int k, t;

	p1 = __get_parameter_position (p1, i);
	__param_type (*p1, &k, &t);
	if (k != ARRAY) {
	   fprintf (stderr, "Array expected (got %s)\n", __map_kind (k));
           exit (21);
	}

	p1 = PPLUS (p1, 2);
	if ((t != tp) &&
	     !(__is_arithmetic (t) && __is_arithmetic (tp))) {
           fprintf (stderr, "Illegal array type for actual (%c, %c)\n", tp, t);
	   exit (21);
	}

	return (char *) (*p1);
}

char	*__get_function_link (char **p1, int i, char tp) {
int k, t;

	p1 = __get_parameter_position (p1, i);
	__param_type (*p1, &k, &t);
	if (k == FUNCTION) {
	   p1 = PPLUS (p1, 1);
	   return (char *) (*p1);
	}

	fprintf (stderr, "Function expected (trying to get the link\n");
	fprintf (stderr, "We got a %s\n", __map_kind (k));
	exit (21);
}

char	*__get_function_address (char **p1, int i, char tp) {
int k, t;

	p1 = __get_parameter_position (p1, i);
	__param_type (*p1, &k, &t);
	if (k != FUNCTION) {
	   fprintf (stderr, "Function expected (trying to get address)\n");
	   fprintf (stderr, "We got a %s\n", __map_kind (k));
	   exit (21);
	}

	p1 = PPLUS (p1, 2);

	if ((tp == t) || (tp == "void"[0])) // anything is acceptable
	   return (char *)(*p1);

	if (!(__is_arithmetic (t) && __is_arithmetic (tp))) { // conversion not allowed
	   fprintf (stderr, "Error in type of function (%c, %c)\n", tp, t);
	   exit (36);
	}

	return (char *) (*p1);
}

//	Some time(s) we have to evaluate the actual parameter
//	This is a little tricky function
char	*__eval_value_thunk (char **p1, int i, char tp) {
int k, t;
char *l, *(*fn) ();

	__param_type (*(__get_parameter_position (p1, i)), &k, &t);
	fn = (char *(*)())  __get_value_thunk (p1, i, tp); 
	l  = __get_thunk_link (p1, i);
//	we want to extract the value, so we are going
//	to evaluate the thunk. For arithmetic operands,
//	we allow arithmetic conversions
	if (((char)t) != tp) {
	     if (!(__is_arithmetic ((char)t) && __is_arithmetic (tp))) {
	   fprintf (stderr,
	            "Illegal type for actual value (%c, %c)\n",
	            tp, t);
	   exit (21);
	}}
//	now start evaluating the function, it is (or should be)
//	parameterless
//	cast the result to the result specified as the formal one
	if (tp == "int"[0]) {
	   static int v;
	   int (*fn1)() = (int (*)()) fn;
	   v = (*fn1) (l, 0);
	   return (char *) (&v);
	}

	if (tp == "double"[0]) {
	   static double v;
	   double (*fn1)() = (double (*)()) fn;
	   v = (double)((*fn1) (l, 0));
	   return (char *) (&v);
	}

	if (tp == "char"[0]) {
	   static char v;
	   char (*fn1)() = (char (*)()) fn;
	   v = (*fn1) (l, 0);
	   return (char *) (&v);
	}

	if (tp == "jmp_buf"[0]) {
	   static jmp_buf *v;
	   jmp_buf *(*fn1)() = (jmp_buf *(*)()) fn;
	   v = (jmp_buf *)((*fn1) (l, 0));
	   return (char *)(&v);
	}

	fprintf (stderr, "Expert error 201\n");
	exit (33);
}

// Second part: code for prelude functions
double fabs (double e) {
	return (e < 0.0 ? -e : e);
}

int iabs (int e) {
	return (e < 0 ? -e : e);
}

double epsilon () {
	return (double) 1.0E-64;
}

char	isinfinite (double x) {
	return !isfinite (x);
}

double maxreal () {
	return (double) 1.0E64;
}

double minreal () {
	return (double) 1.0E-64;
}

int entier (double e) {
int c = e;
	if (c > e) c--;
	return c;
}

void stop () {
	exit (21);
}

void fault (char *s, double v) {
	printf ("%s", s);
	printf ("%d \n", (int) v);
	exit (22);
}

int length (char *s) {
int i = 1;

	while (*s++) i++;
	return i;
}

int sign (double v) {
	return v < 0 ? -1 : 1;
}
//
//	IO operations
//
#define MAX_FILES	32
FILE * __fildescr[MAX_FILES];

int	open_file (char *f, int k) {
char	*kk;
FILE	*fd;
int	i;

	switch (k) {
	   case 0:
	      kk = "r"; break;
	   case 1:
	      kk = "w"; break;
	   case 2:
	      kk = "a"; break;
	   default:
	      kk = "r"; break;
	}

	fd = fopen (f, kk);
	if (fd == (FILE *) NULL)
	   return -1;

	for (i = 3; i < MAX_FILES; i++)
	   if (__fildescr[i] == (FILE *) NULL) {
	      __fildescr[i] = fd;
	      return i;
           }

	fclose (fd);
	return -2;
}
//
//	we do not allow stdin, stdout and stderr to be closed
int	close_file (int fd) {

	if (2 < fd && fd < MAX_FILES)
	   if (__fildescr[fd] != (FILE *) 0) {
	      fclose (__fildescr[fd]);
	      __fildescr[fd] = (FILE *) 0;
	      return fd;
           }
  
	return -1;
}

int outchar (int fd, char *s, int c) {
	if (c <= 0 || c > length (s))
	   return -1;

	return raw_out (fd, s[c - 1]);
}

int __read_char (int fd, char *str) {
int c, i, res;

	res = -2;
	c = raw_in (fd);
	if (c <= 0) 
	   return -1;

	for (i = 0; i < length (str); i++) {
	   if (c == str[i]) {
	      res = i + 1;
	      break;
	   }
	}

	return res;
}
//
//	this function was created by writing it in Algol
//	and translating it
void inchar (int channel, char *str, char *Lv, int (*Av) (char *, int),
                          int (*Vv) (char *, int)) {
	(Av) (Lv, __read_char (channel, str));
}

void space (int ch) {
	outchar (ch, " ", 1);
}

void newline (int ch) {
	outchar (ch, "\n", 1);
}

void outstring (int ch, char *s) {
int i;
	for (i = 1; i <= length (s); i++)
	   outchar (ch, s, i);
}

void outterminator (int ch) {
	outchar (ch, " ", 1);
}

int __digits (int ch, int v) {
int j = v / 10;
	v = v - 10 * j;
	if (j != 0)
	   __digits (ch, j);
	   outchar (ch, "0123456789", v + 1);
}

int outinteger (int ch, int v) {

	if (v < 0) {
	   outchar (ch, "-", 1); v = -v;
	}

	__digits (ch, v);
	outterminator (ch);
}

int __ins (int fd) {
int n;

	n = __read_char (fd, "0123456789-+ ;\n");
//	fprintf (stderr, "gelezen char %d\n", n);
	return n > 11 ? 13 : n;
}

int __read_int (int channel) {
int k, m, d, sign;

	sign = m = d = 0;
	for (k = __ins (channel); k == 13; k = __ins (channel));
	if (k == 0 || k > 13)
	   fault ("invalid blank character\n", k);
	if (k == 11)
	   sign = 1;
	else
	{  m = k - 1;
	   d = 1;
	}
  
	for (k = __ins (channel); k > 0 && k < 11; k = __ins (channel)) {
	   m = 10 * m + k - 1;
	   d++;
	}
	if (d == 0)
	   fault ("invalid BLANK character\n", k);
	return sign ? -m : m;
}

void ininteger (int channel, char *Lv, int (*Av) (char *, int),
	                     int (*Vv) (char *, int)) {
	(Av) (Lv, __read_int (channel));
}				//    end of code for ininteger (_ininteger_0)

int __ins_r (int channel) {
int n;

	n = __read_char (channel, "0123456789-+.e ;\n");
	if (n == 17)
	   return 15;
	return n;
}

double __read_real (int channel) {
double res, r, s;
int j, k, m, b, d;

	for (k = __ins_r (channel); k == 15; k = __ins_r (channel));
	if (k == 0 || k > 15)
	   fault ("invalid character\n", k);

	b = (k != 11);
	d = true;
	m = 1;
	j = (k < 11) ? 2 : iabs (k + k - 23);
	r = (k < 11) ? k - 1 : 0.0;
	if (k != 14) {
	   for (k = __ins_r (channel); k < 14; k = __ins_r (channel)) {
	      if ((((k == 0) || (k == 11) || (k == 12) || k == 13)) &&
	          (j > 2)) {
	         fault ("invalid character\n", k);
	      }
	      if (d) {
	         if (k == 13)
		    j = 3;
	         else
		 {  if (j < 3)
		       r = 10.0 * r + k - 1;
	            else
	            {  s = pow (10.0, (double) -m);
		       m = m + 1;
		       r = r + s * (k - 1);
		       d = (r != r + s);
		    }
		    if ((j == 1) || (j == 3))
		       j = j + 1;
		 }
	      }
	   }

	   if ((j == 1) && (k != 14) || (j == 3))
	      fault ("invalid character\n", k);
	}
	if (k == 14) {
	   m = __read_int (channel);
	   r = (((j == 1) || (j == 5)) ? 1.0 : r) * pow (10.0, (double) m);
	}
  
	res = (b) ? r : -r;
	return res;
}

void inreal (int channel, char *Lv, double (*Av) (char *, double),
	                  double (*Vv) (char *, int)) {
	(Av) (Lv, __read_real (channel));
}

void outreal (int channel, double v) {
int n, j, k, m, p, fl, nines;

	if (v != v) {	// nan???
	   outstring (channel, " nan  ");
	   return;
	}
	if (!isfinite (v)) {
	   outstring (channel, " inf  ");
	   return;
	}
	m = 0;
	n = 10;
	if (v < 0.0) {
	   outchar (channel, "-", 1);
	   v = -v;
	}

	if (v < minreal ()) {
	   outstring (channel, "0.0");
	   outterminator (channel);
	   return;
	}
	for (m++; v >= 10.0; m++)
	   v = v / 10.0;
	for (m--; v < 1.0; m--)
	   v = v * 10.0;

	if (v >= 10.0) {	//rounding error
	   v = 1.0;
	   m++;
	}
	if ((m >= n) || (m < -2)) {
	   fl = true;
	   p = 1;
	}
	else
	{  fl = false;
	   p = ((m == n - 1) || (m < 0)) ? 0 : m + 1;
	   if (m < 0) {
	      outstring (channel, "0.");
	      if (m == -2)
	         outchar (channel, "0", 1);
	   }
	}

	nines = false;
	for (j = 1; j <= n; j++) {
	   if (nines)
	      k = 9;
	   else
	   {  k = entier (v);
	      if (k > 9) {
	         k = 9;
	         nines = true;
	      }
	      else
	         v = 10.0 * (v - (double) k);
	   }
           outchar (channel, "0123456789", k + 1);
	   if (j == p)
	      outchar (channel, ".", 1);
	}
  
	if (fl) {
	   outchar (channel, "e", 1);
	   outinteger (channel, m);
	}
	else
	   outterminator (channel);
}

void	outreal_16_11 (int channel, double v) {
	if (v != v) {	// nan???
	   outstring (channel, " nan  ");
	   return;
	}
	if (!isfinite (v)) {
	   outstring (channel, " inf  ");
	   return;
	}
	fprintf (stdout, " %16.11f ", v);
}

//	non standard functions

int	__lwb (int *d, int i) {
	if (i < 1 || i > ((((int *)d) [0] >> 8)& 0377))	// out of bounds
	   return ((((int *)d) [0] >> 8) );
	return ((int *)d) [DOPE_BASE + 2 * i - 2];
}

int	__upb (int *d, int i) {
	if (i < 1 || i > ((d [0] >> 8)& 0377))	// out of bounds
	   return ((d [0] >> 8));
	return ((int *)d) [DOPE_BASE + 2 * i - 1];
}

int	i_lwb (int	*d, int * a, int i) {
	return __lwb ((int *)d, i);
}

int	b_lwb (int	*d, char * a, int i) {
	return __lwb ((int *)d, i);
}

int	r_lwb (int	*d, double * a, int i) {
	return __lwb ((int *)d, i);
}

int	i_upb (int	*d, int * a, int i) {
	return __upb ((int *)d, i);
}

int	b_upb (int	*d, char * a, int i) {
	return __upb ((int *)d, i);
}

int	r_upb (int	*d, double * a, int i) {
	return __upb ((int *)d, i);
}

int	raw_in (int fd) {
int	c;
FILE	*f;

	if ((fd != 0) && ((fd <= 2) || (fd >= MAX_FILES)))
	   return -1;  // cannot read from file

	if  (__fildescr [fd] == (FILE *) 0)
	   f = __fildescr [fd] = stdin;
	else
	   f = __fildescr [fd];

	c = fgetc (f);
	return c;
}

int	raw_out (int fd, int val) {
FILE	*f;

	if ((1 < fd) || (fd >= MAX_FILES))
	   return -1;	// Can never be a file to write on

	if (__fildescr[fd] == (FILE *) 0) 
	   f = __fildescr [fd] = stdout;
	else
	   f = __fildescr [fd];
	return fputc (val, f);
}

//	now something for the power operation
//
int	__ipow (int a, int b) {
int k, result;
   if ((a == 0) && (b == 0)) {
      fault ("expi undefined", b);
   }
   if (a == 1) 
	return 1;
   result = 1;
   for (k = 1; k <= b; k ++) result = result * a;
   return result;
}

int	__mod (int a, int b) {
	return a % b;
}

double	__npow (double x, int n) {
double result;
int i;
   if ((n == 0) || (x == 0.0)) {
      fault ("expn undefined", n);
   }

   result = 1.0;
   for (i = iabs (n); i >= 1; i --) result = result * x;

   return (n < 0)? 1/result : result;
}

double	__fpow (double x, double r) {
  if (x > 0.0)
      return exp (r * ln (x));
  else
  if (x == 0.0 && r > 0.0)
      return 0.0;
  else
      fault ("expr undefined", x);
}


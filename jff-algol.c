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
// jff-algol, a driver program for jff-a2c
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
#include	<time.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<unistd.h>

char	*infile		= NULL;
char	*c_file		= NULL;
char	*tmp_file	= "tmpfile";
char	*outfile	= NULL;
char	*include	= NULL;
char	*header_file	= HEADER;
char	*operator	= OPERATOR_E;
char	*prelude	= PRELUDE_E;
char	*runtime	= RUNTIME;
char	*jff_a2c	= ACOMPILER;
char	*c_compiler	= CCOMPILER;
int	indent		= 1;
int	delete_files	= 0;
int	trace		= 0;
int	only_frontend	= 0;
int	languageFlag	= 0;

static	char	v0 [100];
static char	v1 [100];
static char	v2 [100];
static char	v3 [100];

int	process_filenames (char *infile) {
char	*tail;

	if (infile == (char *)0)
	   return 0;

	sprintf (v0, "%s", infile);
	tail = strstr (v0, ".alg");
	if ((tail == (char *)0) || (tail [4] != (char)0)) {
	   fprintf (stderr, "File %s does not end with \".alg\"\n", infile);
	   return 0;
	}

	tail [0] = (char)0;
 	sprintf (v1, "%s.c", v0); 
	c_file = v1;

	sprintf (v2, "%s.h", v0);
	include = v2;

	sprintf (v3, "%s",   v0);
	outfile = v3;

	return 1;
}

void	process_file () {
char	v [1024];
time_t	current_time;
char	compile_time [255];
int	error_code;

	current_time = time (NULL);
	memcpy (compile_time, ctime (&current_time), 24);
	compile_time [24] = (char)0;

	if (process_filenames (infile)  == 0)
	   return;

	sprintf (v, " %s -F %d -c %s -f %s -o %s -p %s -h %s -t \"%s\" %s",
	         jff_a2c,
	         languageFlag,
	         tmp_file,
	         include,
	         operator,
	         prelude,
	         header_file,
	         compile_time,
	         infile);

	if (trace)
	   fprintf (stderr, "Compiling with command %s\n", v);
	fflush (stderr);
	error_code = system (v);
	if (error_code != 0 ) {
	   fprintf (stderr,
	            "Error code %d, compiling %s aborted after front end\n",
	            error_code,
	            infile);
	   return;
	}
	
	if (only_frontend) 
	   return;

	if (indent && !delete_files) {
	      sprintf (v, "%s %s -o %s", INDENT, tmp_file, c_file);
	      system (v);
	      unlink (tmp_file);
	}
	else {
	   sprintf (v, "mv %s %s", tmp_file, c_file);
	   system (v);
	}

	sprintf (v, "%s -O3 -w -o %s %s %s -lm",
	         c_compiler, outfile, c_file, runtime);
	if (trace)
	   fprintf (stderr, "Processing the result %s\n", v);
	system (v);
	if (delete_files) {
	   unlink (include);
	   unlink (c_file);
	}
}

int main (int argc, char **argv) {
static char v [100];
struct stat x;
int	i;

	for (i = 1; i < argc; i ++) {
	   if (argv [i][0] == '-') {	// it is an option
	      switch (argv [i][1]) {
	         case 's':	operator	= argv [i + 1]; i ++;
	                        break;

	         case 'F':	operator	= OPERATOR_F;
	                        prelude		= PRELUDE_F;
	                        languageFlag	= 1;
	                        break;
	                        
	         case 'p':	prelude		= argv [i + 1]; i ++;
	                        break;

	         case 'h':	header_file	= argv [i + 1]; i ++;
	                        break;

		 case 'i':	indent		= 0;
				break;

	         case 'v':	trace = 1;
	                        break;

	         case 'r':	delete_files	= 1;
	                        break;

	         case 'f':	runtime		= argv [i + 1]; i ++;
	                        break;

	         case 'o':	only_frontend	= 1;
			        break;

	         default:	break;
	      }
	   }
	   else {
	      // it is the name of the file to be compiled
	      infile = argv [i];
	      if (indent && !delete_files) {
	         sprintf (v, "%s", INDENT);
	         if (stat (v, &x) == -1) 
	            indent = 0;
	      }
	      process_file ();
	   }
	}
	exit (0);
}



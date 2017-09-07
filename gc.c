#
#include	<stdlib.h>
#include	<stdio.h>

void	do_test (int a, int b, char *c, char *d) {

if (&b - &a > 0) {
   fprintf (stdout, "/* Addressing parameters */\n");
   fprintf (stdout, "#define PPLUS(x, y) (char **)(((char **)x) + (int)y)\n");
   fprintf (stdout, "#define is_newer(x, y) ((char *)x) > ((char *)y)\n");
   fprintf (stdout, "#define IPLUS(x, y) (int *)(((int *)x) + (int)y)\n");
}
else
{
   fprintf (stdout, "/* Addressing parameters */\n");
   fprintf (stdout, "#define PPLUS(x, y) (char **)(((char **)x) - (int)y)\n");
   fprintf (stdout, "#define is_newer(x, y) ((char *)x) < ((char *)y)\n");
   fprintf (stdout, "#define IPLUS(x, y) (int *)(((int *)x) - (int)y)\n");
}
   fprintf (stdout, "\n\n/* end of jff_header.h */\n\n");
}

int main () {
char *v, *w;
   do_test (1, 2, v, w);
   exit (EXIT_SUCCESS);
}


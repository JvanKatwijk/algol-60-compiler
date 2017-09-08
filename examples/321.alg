'begin'
	'comment'
		321.a60:			oct '90
		Erik Schoenfelder

		This is the
			0. Start with a natural number n.
			1. If n is odd, set n to be 3 * n + 1
			   If n is even, set n to be n / 2
			   Repeat step 1 until n is equal 1.
			2. Print the number of repetitons.
		fun.
		And: Who knows, if this termimates for any n...
	;

	'integer' 'procedure' doit (n);
	'value' n;
	'integer' n;
	'begin'
		'boolean' 'procedure' odd (x);
			'value' x; 'integer' x;
			odd := n 'notequal' (n 'div' 2) * 2;

		'integer' count;

		count := 0;
	do:
		'if' odd (n) 'then'
			n := 3 * n + 1
		'else'
			n := n 'div' 2;

		count := count + 1;
	
		'if' n 'notequal' 1 'then' 'goto' do;

		doit := count;
	'end';


	'integer' i, n, val, max, NN;

	NN := 1000;

	outstring  (1, "Hi!\n                n           iterations\n");
	'for' i := 1 'step' 1 'until' NN 'do' 'begin'
	   doit (i);
	'end';
	outstring (1, "...");

	outstring (1, "\nnow looking for maxima:");
	outstring (1,  "\n                n           iterations\n");

	n := 0;  max := -1;
	'for' i := 1 'step' 1 'until' NN 'do' 'begin'
	do:
		n := n + 1;
		val := doit (n);
		'if' val <= max 'then' 'goto' do;

		outinteger (1, n);
	        outstring  (1, " ");
	        outinteger (1, val);
	        outstring  (1, "\n");
		max := val;
	'end';
	outstring (1, "...\ndone.")
'end'

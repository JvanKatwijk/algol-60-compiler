begin
   integer array A [1 : 10];
   integer i;
   integer procedure sum (a, l, u, b);
   value l, u;
   integer a, l, u, b;
   begin
      integer h;
      h := 0;
      for a := l step 1 until u do
	begin
h := h + b;
outinteger (1, h);
end;
      sum := h;
   end;
   for i := 1 step 1 until 10 do A [i] := i * i;
   outstring (1, "Example 7: by name parameters\n");
   outinteger (1, sum (i, i_lwb (A, 1), i_upb (A, 1), A [i]));
   newline (1);
end;


begin
   integer array A, B [1: 10];
   integer i;
   procedure dummy (b); value b; array b;
   begin
      integer j;
      for j := r_lwb (b, 1) step 1 until r_upb (b, 1) do
      begin
         b [i] := b [i] + 1;
         B [i] := b [i];
      end;
   end;
   outstring (1, "Example 6: arrays by value\n");
   for i := 1 step 1 until 10 do A [i] := i * i;
   dummy (A);
   for i := 1 step 1 until 10 do
   begin
      outinteger (1, i); space (1); outinteger (1, B [i]); newline (1);
   end;
end;


begin
   integer array A [1:10-1+1];
   integer i;
   procedure init_array (b); integer array b;
   begin
      integer j;
      for j := i_lwb (b, 1) step 1 until i_upb (b, 1) do
         b [j] := j * j;
   end;
   outstring (1, "Example 4: arrays by name\n");
   init_array (A);
   for i := 1 step 1 until 10 do
   begin
      outinteger (1, i); space (1); outinteger (1, A [i]); newline (1);
   end;
end;


begin
   procedure do_it (n); value n; integer n;
   begin
      integer array A [1 : n];
      integer i;
      for i := 1 step 1 until n do A [i] := i * i;
      for i := 1 step 1 until 10 do
      begin
         outinteger (1, i); space (1); outinteger (1, A [i]); newline (1);
      end;
   end;
   outstring (1, "Example 5: arrays with non constant bounds\n");
   do_it (10);
end;


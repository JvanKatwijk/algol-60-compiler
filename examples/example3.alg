begin
   integer array A [1:10];
   integer i;
   outstring (1, "Example 3: simple static arrays\n");
   for i := 1 step 1 until 10 do A [i] := i * i;
   for i := 1 step 1 until 10 do
   begin
      outinteger (1, i); space (1); outinteger (1, A [i]); newline (1);
   end;
end;


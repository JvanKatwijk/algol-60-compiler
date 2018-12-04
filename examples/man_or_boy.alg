begin
   integer i;
	integer count;
   integer procedure A (k, x1, x2, x3, x4, x5);
   value k; integer k, x1, x2, x3, x4, x5;
   begin
      integer procedure B;
      begin
         k := k - 1;
         A := B := A (k, B, x1, x2, x3, x4);
      end;
	count := count + 1;
      if k <= 0 then A := x4 + x5 else B;
   end;
	count := 0;
   for i := 1 step 1 until 25 do
   begin
      outinteger (1, A (i, 1, -1, -1 , 1 , 1));
      newline (1);
      outstring (1, "Recursie diepte "); outinteger (1, count);
      count := 0;
      newline (1);
   end;
end;

   

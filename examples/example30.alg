begin
   integer a;
   integer b;
   a := 1;
   b := 10;
   begin
      integer array x1 [a : b];
      integer array x2 [1 : 10, a : b];
      for a := 1, a + 1 while a < b do begin
	 x1 [a] := a;
         x2 [a, a] := a;
	 outinteger (1, a); newline (1);
      end;
   end;
end;

         

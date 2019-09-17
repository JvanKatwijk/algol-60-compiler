begin
   comment testing of formal procedures;
   integer a, b, c;
   procedure p (b, q, r, s); 
      value b; boolean b;
      procedure q; procedure r; procedure s; 
   begin
      if b then q (s) else r (s)
   end;
   procedure f1 (p1); procedure p1; p1 (a, b, c);
   procedure f2 (p1); procedure p1; p1 (a, b);
   procedure a1 (a, b, c); integer a, b, c; a := b + c;
   procedure a2 (a, b); integer a, b; a := b;

   b := 1; c := 2;
   comment now two calls;
   p (true, f1, f2, a1); 
   outstring (1, " after the call to a1 "); outinteger (1, a); newline (1);
   p (false, f1, f2, a2); 
   outstring (1, " after the call to a2 "); outinteger (1, a); newline (1);
end;



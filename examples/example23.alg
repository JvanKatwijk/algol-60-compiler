begin
   comment testing of formal procedures anf non local accesses;
   procedure main;
   begin
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
      procedure mainer;
         begin
         procedure go_to (L); value L; label L; goto L;
         procedure dummy (p, L); procedure p; label L;
         p(L);
         procedure do_it;
         begin
            switch L := L1, if b then L2 else L1;
            dummy (go_to, L [n]);
         end;
         integer n;
         boolean b;
         n := 2; b := true;
         do_it;
     L1: outstring (1, "Incorrect\n");
         goto L_end;
     L_end:
      end;
      b := 1; c := 2;
      comment now two calls;
      outstring (1, "Example 23: switches, formals and non local access\n");
      p (true, f1, f2, a1); 
      outstring (1, " after the call to a1 "); outinteger (1, a); 
      p (false, f1, f2, a2); 
      outstring (1, " after the call to a2 "); outinteger (1, a); 
      mainer;
     L2: outstring(1, "Correct\n");
   end;
   main;
end



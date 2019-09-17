begin
   procedure go_to (L, n); integer n; switch L;
   begin
     outinteger (1, n);  goto L [n];
   end;
   procedure dummy (p, L, n); value n; procedure p; switch L; integer n;
   begin
      outinteger (1, n);
      p (L, n);
   end;
   procedure do_it;
   begin
      switch L := L1, if b then L2 else L1;
      dummy (go_to, L, m);
   end;
   integer m;
   boolean b;
   outstring (1, "Example 13: use of switches\n");
   m := 2; b := true;
   do_it;
L1: outstring (1, "Incorrect\n");
   goto L_end;
L2: outstring(1, "Correct\n");
L_end:
end;


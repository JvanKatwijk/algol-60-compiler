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
   outstring (1, "Example 11: use of switches\n");
   n := 2; b := true;
   do_it;
L1: outstring (1, "Incorrect\n");
   goto L_end;
L2: outstring(1, "Correct\n");
L_end:
end;


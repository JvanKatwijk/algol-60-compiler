begin
   procedure dummy (n); value n; integer n;
     if n <= 1 then goto L1 else dummy (n - 1);

   outstring (1, "Example 8: goto's\n");
   goto L2;
L1: outstring (1, "We terminated dummy\n");
    goto L_end;
L2: dummy (100);
L_end:
end;


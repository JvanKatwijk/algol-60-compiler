begin
   procedure dummy (n, L); value L, n; integer n; label L;
     if n <= 1 then goto L else dummy (n - 1, L);

   outstring (1, "Example 9: label as parameter\n");
   goto L2;
L1: outstring (1, "We terminated dummy\n");
    goto L_end;
L2: dummy (100, L1);
L_end:
outstring (1, "We are at the end\n");
end;


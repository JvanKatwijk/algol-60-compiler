begin
   procedure do_it;
   begin
      procedure go_to (L); label L; goto L;
      procedure X (p, L); label L; procedure p; p (L);
      procedure dummy (n, p, L); value n; 
      integer n; procedure p; label L;
         if n <= 1 then X (p, L) else dummy (n - 1, p, L);

try_again:
      dummy (5, go_to, L2);
      outstring (1, "This is not right\n");
      goto try_again;
   end;
   outstring (1, "Example 10: Useless use of formal procedures\n");
   do_it;
L2:
   outstring (1, "Yes, we made it\n");
end;


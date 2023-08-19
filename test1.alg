begin
integer procedure try (n); value n; integer n;
begin
      integer array ploc [1 : n];
      comment for i := 1 step 1 until n do ploc [i] := 1;
      try := 2 * n;
end try;
   Boolean b;
   integer k, n;
   n := 50;
   outinteger (1, n);
   k := try (n);
   outinteger (1, k);
   outstring (1, "ok\n");
end


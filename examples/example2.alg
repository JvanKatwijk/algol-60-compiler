begin
   integer h;
   procedure do_it;
   begin
      integer i, j;
      procedure increment;
      begin
         i := i + 1;
         h := h + 1;
      end;
      i := j := h := 0;
      for j := 1 step 1 until 100 do increment;
   end;
   do_it;
end;


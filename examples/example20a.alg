begin
   integer i;
   procedure do_it (s); string s;
   begin
      procedure go_to_1 (L); value L; label L; goto L;
      procedure switch_aaa (Laa); label Laa; 
      begin
         switch L := if i > 5 then L2 else L1, L1;
         go_to_1 (L [i]);
      L1:
         outstring (1, "first jump\n"); goto Laa;
      L2:
         outstring (1, "second jump\n"); goto Laa;
      end;
      for i := 1 step 1 until 10 do switch_aaa (Lb);
La:   outstring (1, "He he\n");
   end;
Lb: do_it ("Eindelijk");
end;


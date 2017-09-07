begin
integer  Trac_Sharp_Sign,
    LPAR,
    RPAR,
    FN_START, FN_END;

integer last_open; comment indicates the last function op on ps;
integer array active_string [1 : 1000];
integer array passive_string [1 : 2, 1 : 1000];
integer array user_defs [1 : 10000];

integer active_char;  comment points to first char in active string;
integer passive_char; comment points to first free in passive string;

integer proc end_of_active_string;
   end_of_active_string := 1000;

proc init_active_and_passive_string;
begin
   proc add_to_active_string (ch); value ch; integer ch;
   begin
      active_string [active_char] := ch;
      active_char := active_char - 1;
   end;

   active_char := end_of_active_string;
   passive_char := 1;
   add_to_active_string (&) );
   add_to_active_string (&) );
   add_to_active_string (&s );
   add_to_active_string (&r );
   add_to_active_string (&( );
   add_to_active_string (Trac_Sharp_Sign);
   add_to_active_string (&, );
   add_to_active_string (&s );
   add_to_active_string (&p );
   add_to_active_string (&( );
   add_to_active_string (Trac_Sharp_Sign);
end;


proc move_to_passive_string (ch, l);
   value ch, l; integer ch; label l;
begin
   passive_string [1, passive_char] := ch;
   passive_char := passive_char + 1;
end;

proc eval_built_in (l); value l; label l; begin; end;
proc eval_user_defined (l); value l; label l; begin ; end;
boolean proc is_built_in; is_built_in := false;
integer proc get_char_from_active_string (l); value l; label l;
begin
   if active_char > end_of_active_string 
   then
      goto l;
   get_char_from_active_string := active_string [active_char]
end;


procedure announce (s); string s;
begin
   outstring (1, s); newline (1);
end;

proc set_up_data_structures;;

proc read_config (s); string s; begin; end;

proc read_user_defined_functions (l); value l; label l; begin ; end;

proc eval_active_till_call (l); value l; label l;
begin
   boolean no_function_yet;
   integer dummy;
   comment this function is local to eval_active_to_call;
   proc process_protected_string (l); value l; label l;
   begin
      integer par_count, char;
      par_count := 1;  comment count the depth;
      for dummy := 0 while par_count > 0 do
      begin
         char := get_char_from_active_string (l);
         active_char := active_char + 1;
         if char = LPAR
         then
            begin
               par_count := par_count + 1;
               move_to_passive_string (char, l);
            end
         else
         if char = RPAR
         then
            begin
               par_count := par_count - 1;
               if par_count > 0
               then
                  move_to_passive_string (char, l);
            end;
      end;
   end;
   proc process_sharp_sign (l); value l; label l;
   begin
      integer ch;
      proc add_open_function_to_passive_string;
      begin
         passive_string [2, passive_char] := last_open;
         last_open := passive_char;
         passive_string [1, passive_char] := FN_START;
         passive_char := passive_char + 1;
      end;
      ch := get_char_from_active_string (l);
      if ch = LPAR
      then
         begin
            active_char := active_char + 1;
            add_open_function_to_passive_string;
         end
      else
      if ch = Trac_Sharp_Sign
      then
         begin
            active_char := active_char + 1;
            ch := get_char_from_active_string (l);
            if ch = LPAR
            then
               begin comment we found ;
                  active_char := active_char + 1;
                  move_to_passive_string (Trac_Sharp_Sign, l);
                  move_to_passive_string (LPAR, l);
               end
            else
               begin
                  move_to_passive_string (Trac_Sharp_Sign, l);
                  move_to_passive_string (Trac_Sharp_Sign, l);
               end
         end
      else
         begin
            active_char := active_char + 1;
            move_to_passive_string (Trac_Sharp_Sign, l);
            move_to_passive_string (ch, l);
         end
   end;

   proc print_passive_and_active_string;
   begin
      integer i;
      for i := 1 step 1 until passive_char - 1 do
         raw_out (1, passive_string [1, i]);
      outstring (1, "<<<>>>");
      for i := active_char + 1 step 1 until end_of_active_string do
         raw_out (1, active_string [i]);
      newline (1)
   end;

   comment here the body of eval_active_to_call starts;
   no_function_yet := true;

   for dummy := 0 while no_function_yet do
   begin
      integer ch;
      print_passive_and_active_string;
      ch := get_char_from_active_string (l);
      if ch = Trac_Sharp_Sign
      then
         begin
            active_char := active_char + 1;
            process_sharp_sign (l)
         end
      else
      if ch = LPAR
      then
         begin
            active_char := active_char + 1;
            process_protected_string (l)
         end
      else
      if ch = RPAR
      then
         begin
            no_function_yet := false;
            active_char := active_char + 1;
            move_to_passive_string (FN_END, l)
         end
      else 
         begin
            active_char := active_char + 1;
            move_to_passive_string (ch, l);
         end
   end
end;

comment main program starts here;
begin
      integer i;
      integer ch;
      Trac_Sharp_Sign := &# ;
      LPAR := &(;
      RPAR := &);
      FN_START := &[;
      FN_END   := &];
      
   Trac_start:
      announce ("Trac version 0.1");
      set_up_data_structures;
      read_config ("trac_config");
      read_user_defined_functions (Trac_restart);
   Trac_restart:
      init_active_and_passive_string;
   Eval_loop:
      eval_active_till_call (Trac_restart);
      outstring (1, "Ready to evaluate a function\n");

   ch := 0;
   for i := last_open, i + 1 while ch != &, and ch != FN_END do
   begin
      ch :=  passive_string [1, i];
      raw_out (1, ch)
   end;
   newline (1);
      if is_built_in
      then
         eval_built_in (Trac_restart)
      else
         eval_user_defined (Trac_restart);
      goto Eval_loop;
end;
end;


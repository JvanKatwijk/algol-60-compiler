begin
comment this example is taken from "the remaining trouble spots in Algol 60"
by Donald Knut;
procedure S (x); real x; x := 0;
real procedure r;
begin
   r := 1;
   S (r);
end;
real x;
   x := 1;
   S (if x = 1 then r else x);
   outreal (1, x); newline (1);
end;


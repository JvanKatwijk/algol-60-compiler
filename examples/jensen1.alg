begin
array a[1:4];
real t;
integer i;
   real procedure jensen1(i,a);
      integer i; real a;
   begin
      real s;
      for i:=1 step 1 until 4 do s:=s+a;
      jensen1:=s;
   end;
   for i:=1 step 1 until 4 do a[i]:=i+1;
      t:=jensen1(i,a[i]);
   outstring(1,"D\n");
   outreal(1,t);
    outstring(1,"\n");
end

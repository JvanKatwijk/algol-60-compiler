begin
comment This example is taken from the article "The remaining trouble
spots in Algol 60" (Donald Knut);
array V, A, C [1 : 1];
integer k;
integer procedure i; 
begin
   i := 1;
   k := k + 1;
end;

   k := 0; A [1] := 1; C [1] := 3;
   for V [i] := A [i] step A [i] until C [i] do ;
   ;
   outreal (1, k)
end;



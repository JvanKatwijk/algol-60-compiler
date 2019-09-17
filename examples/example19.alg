
begin integer color1,color2,color3,color4,
       row,col,oldrow,oldcol,maxcol;
integer array hyp[1:4],board[1:10,1:4],whites,blacks[1:10];
boolean array oldmat,newmat[1:4];

procedure patern(row); value row; integer row;
begin integer col;
       for col:=1,2,3,4 do
       if board[row,col]=1 then outstring(1,"RED ")
       else if board[row,col]=2 then outstring(1,"BLUE ")
       else if board[row,col]=3 then outstring(1,"GREEN ")
       else if board[row,col]=4 then outstring(1,"YELLOW ")
       else if board[row,col]=5 then outstring(1,"BLACK ")
       else if board[row,col]=6 then outstring(1,"WHITE ")
       else outstring(1,"SPACE ");
end print pattern;

procedure printrow;
begin outstring(1,"\nMy guess "); outinteger(1,row);
       outstring(1," is: ");
patern(row);
end print the current row;



start: outstring(1,"\n\nMastermind Codebreaker\nVersion 1 or 2 ?");

	ininteger (0, maxcol);
       if not (maxcol=1 or maxcol=2) then goto start;
       maxcol:=maxcol+5;
	row:=1;

       for color1:=1 step 1 until maxcol do
       for color2:=2 step 1 until maxcol,1 do
       for color3:=3 step 1 until maxcol,1,2 do
       for color4:=4 step 1 until maxcol,1,2,3 do
       begin
	integer black,white;
       hyp[1]:=color1; hyp[2]:=color2;
       hyp[3]:=color3; hyp[4]:=color4;
	comment set up the hypothesis row.
	a row is consistent with all previous rows if it
	gives rise to the same number of black and white information
	pegs as those rows;

	for oldrow:=1 step 1 until row-1 do
	begin
	   black:=0;
	   for col:=1,2,3,4 do
	   begin boolean temp;
	         temp:=oldmat[col]:=newmat[col]:= hyp[col]=board[oldrow,col];
	         if temp then black:=black+1;
	   end;

	   if black ^= blacks[oldrow] then goto not_viable;
	   white:=0;
	   for col:=1,2,3 do
	      for oldcol:=col+1 step 1 until 4 do
	      begin
	         if hyp[col]=board[oldrow,oldcol]
	         then
	            begin if not (newmat[col] or oldmat[oldcol])
	                  then
	                     begin newmat[col]:=oldmat[oldcol]:=true;
	                           white:=white+1;
	                     end;
	            end;
	         if hyp[oldcol]=board[oldrow,col]
	         then
	            begin
	               if not (newmat[oldcol] or oldmat[col])
	               then
	                  begin
	                     newmat[oldcol]:=oldmat[col]:=true;
	                     white:=white+1;
	                  end;
	            end;
	     end;
	   if white ^= whites[oldrow]
	   then goto not_viable;
	end look at each previous row;

comment at this point the hypothesis row is viable;
       for col:=1 step 1 until 4 do board[row,col]:=hyp[col];
               printrow;
junk:          outstring(1,"\nHow many black pegs ? ");
               ininteger (0, blacks[row]);
               if blacks[row]=4 then
               begin outstring(1,"\nThanks for the game");
                       goto start;
               end problem solved
               else if blacks[row]=3 then whites[row]:=0
               else
               begin
                       if blacks[row]<0 or blacks[row]>4 then
                       begin outstring(1,"TWIT !!"); goto junk;
                       end;
                       outstring(1,"How many white pegs ? ");
                       ininteger (0, whites[row]);
                       if whites[row]<0 or
                       whites[row]+blacks[row]>4 then
                       begin outstring(1,"TWIT !!"); goto junk;
                       end;
               end;
   row:=row+1;
   if row=10 then
      begin
       outstring(1,"\nWELL DONE, YOU WIN !!");
   goto start;
   end;

not_viable:
end look at each possible row;

       outstring(1,"*NTwit !!! you made a mistake");
       goto start;
end of mastermind codebreaker;;




begin
  comment
    this example was provided by Bob Tennent <rdt@cs.queensu.ca>
    to demonstrate non-trivial using call-by-name parameters., this
    program doesn't work properly with nase-a60 interpreter, however,
    it does work with the marst translator.,
    for further discussion see:
    J.C.Reynolds. Syntactic control of interference. In: Conference
    Record of the 5th Annual ACM Symposium on Principles of Programming
    Languages, pp.39-46, Tucson, Arizona, January 1978. ACM, New York.
    P.W.O'Hearn and R.D.Tennent. Parametricity and local variables.
    J.ACM, 42(3):658-709, May 1995. Preliminary version appeared in
    Proceedings of POPL 93;
  procedure makecounter(user);
    procedure user;
    begin
      integer n;
      procedure inc; 
        begin
          n := n-1
        end;
      n := 0;
      user(-n, inc)
    end;
  procedure myuser(val, inc);
    integer val;
    procedure inc;
    begin
      inc; inc; 
      outinteger(1, val);
      inc; inc;
      outinteger(1, val)
    end;
  makecounter(myuser);
  outstring(1, "\n")
end;


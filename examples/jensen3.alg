begin
    comment This is a simple example of Jensen's device;

    comment This takes the sum of expr from lo to hi, inclusive.
            The variable index is incremented through the range.;

   integer procedure RAND; RAND := (random * 100);
   real  procedure SUM(LO, HI, INDEX, EXPR); value LO, HI;
        integer LO, HI, INDEX;
        real EXPR;
        begin
            real ACCUM;

            comment initialize accum to zero and add the terms.;
            ACCUM := 0.0;
            for INDEX := LO step 1 until HI do begin
                ACCUM := ACCUM + EXPR
            end;

            SUM := ACCUM
        end;

    begin
        comment Sum of integers, 1 to 20.;
        integer I;
        outreal (1, SUM(1, 20, I, I));
        outstring (1, "\n");
    end;

    begin
        comment sum of 10 die rolls;
        integer I;
        outreal (1, SUM (1, 10, I, RAND mod 6));
        outstring (1, "\n");
    end;
begin
        comment mean and variance;
        real array DATA [1 : 10];
        integer I;
        real MEAN, SUMD, SUMSQ;
	outstring (1, "type in now 10 numbers (real)\n");
        for I:= r_lwb (DATA, 1) step 1 until r_upb (DATA, 1) do
            inreal (0, DATA[I]);
        SUMD   := SUM (1, 10, I, DATA[I]);
        SUMSQ  := SUM(1, 10, I, DATA[I]*DATA[I]);
        outstring  (1, "Mean is: ");
        MEAN   := SUMD / 10.0;
        outreal    (1, MEAN );
        outstring  (1, "Variance is :");
        outreal    (1, SUMSQ / 10.0 - MEAN * MEAN);
    end
end;


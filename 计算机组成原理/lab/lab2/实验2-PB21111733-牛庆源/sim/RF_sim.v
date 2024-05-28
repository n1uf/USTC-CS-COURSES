module RF_sim();
    reg clk;
    reg [2:0] ra0, ra1;
    reg [3:0] rd0, rd1;
    reg [2:0] wa;
    reg we;
    reg [3:0] wd;

    register_file rf (clk, ra0, rd0, ra1, rd1, wa, we, wd);

    initial begin
        clk = 0;
        ra0 = 3'b000;
        ra1 = 3'b001;
        forever begin
            #5 clk = ~clk;
        end
    end

    initial begin
        we = 1'b0;
        wa = 3'b000;
        wd = 4'h1;
        #7 we = 1'b1;
        #7 wa = 3'b001; wd = 4'h2;
        #7 wa = 3'b010; wd = 4'h3;
        #7 wa = 3'b011; wd = 4'h4;
        #7 wa = 3'b100; wd = 4'h5;
        #7 ra0 = 3'b010; ra1 = 3'b011;
        #7 ra0 = 3'b100;
        #7 we = 1'b0;
        #7 $finish;
    end
endmodule
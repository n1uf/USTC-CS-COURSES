`timescale 1ns / 1ps
module sim( );
reg clk;
reg [3:0] a,dpra;
reg [2:0] d;
reg we;
wire [2:0] dpo;
initial
begin
 clk = 0;
 forever
 #5 clk = ~clk;
end
initial
begin
 a = 0;dpra=0;d=0;we=0;
 #20
 repeat(5)
 begin
 @(posedge clk); #1;
 dpra = dpra +1;
 end
 repeat(10)
 begin
 @(posedge clk); #1;
 a = $random%16;
 dpra = $random%16;
 d = $random%8;
 we = $random%2;
 end
 @(posedge clk); #1;
 a = 0;
 dpra = 0;
 d = 0;
 we = 0;
 #20 $stop;
end
dist_mem_gen_0 dist_mem_gen_0(
.a (a), 
.d (d), 
.dpra (dpra), 
.clk (clk), 
.we (we), 
.dpo (dpo));
endmodule
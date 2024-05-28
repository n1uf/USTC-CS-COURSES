`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/11/24 15:05:57
// Design Name: 
// Module Name: lab7_3_sim
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module lab7_3_sim( );
reg clk;
reg rst;
wire [7:0] led;
wire [3:0] data;
wire [2:0] an;
initial
begin 
    clk = 0;
    forever #5 clk = ~clk;
end
initial rst = 0;
lab7_3 lab7_3(
.clk(clk),
.rst(rst),
.led(led),
.data(data),
.an(an));
endmodule

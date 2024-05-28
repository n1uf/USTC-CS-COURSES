`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/11/17 16:47:12
// Design Name: 
// Module Name: lab06_3
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


module lab06_3(
input clk, rst,
output reg [7:0] led);
reg [29:0] r;
always@(posedge clk)
begin
    if(rst)
        begin
            r <= 30'b0;
            led <= 8'h0;
        end
    else
        begin
            r <= r + 30'b1;
            led <= {r[29], r[28], r[27], r[26], r[25], r[24], r[23], r[22]};
        end
end
endmodule

`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/11/17 17:30:43
// Design Name: 
// Module Name: lab06_3_2
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


module lab06_3_2(
input clk, rst,
output reg [7:0] led);
reg [31:0] r;
always@(posedge clk)
begin
    if(rst)
        begin
            r <= 32'b0;
            led <= 8'h0;
        end
    else
        begin
            r <= r + 32'b1;
            led <= {r[31], r[30], r[29], r[28], r[27], r[26], r[25], r[24]};
        end
end
endmodule

`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/11/22 16:11:13
// Design Name: 
// Module Name: test
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


module test(
input clk,
input rst,
output [7:0] led);
wire clk_10m,clk_200m,locked;
reg [31:0] cnt_1,cnt_2;
always@(posedge clk_200m)
begin
 if(~locked)
 cnt_1 <= 32'hAAAA_AAAA;
 else
 cnt_1 <= cnt_1+1'b1;;
end
always@(posedge clk_10m)
begin
 if(~locked)
 cnt_2 <= 32'hAAAA_AAAA;
 else
 cnt_2 <= cnt_2+1'b1;;
end
assign led = {cnt_1[27:24],cnt_2[27:24]};
clk_wiz_0 clk_wiz_0_inst(
.clk_in1 (clk),
.clk_out1 (clk_10m),
.clk_out2 (clk_200m),
.reset (rst),
.locked (locked));
endmodule

`timescale 1ns / 1ps

module MUX_op2_sel(
input sel,
input [31:0] src0,
input [31:0] src1,
output [31:0] res
);
parameter op2_choose_rd1=1;
parameter op2_choose_imm=0;
assign res = (sel == op2_choose_rd1) ? src0 : src1;
endmodule
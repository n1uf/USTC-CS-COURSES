`timescale 1ns / 1ps

module ADD_PC(
input [31:0] rhs,
output [31:0] res
);
assign res=rhs+32'd4;
endmodule
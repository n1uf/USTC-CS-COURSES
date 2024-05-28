`timescale 1ns / 1ps

module AND_jalr(
input [31:0] rhs,
output [31:0] res
);
assign res=rhs&(-32'd2);
endmodule
`timescale 1ns / 1ps

module MUX_op1_sel(
input [31:0] src0,
input [31:0] src1,
input [1:0] sel,
output reg [31:0] res
);

parameter op1_choose_rd0=2'd0;
parameter op1_choose_pc=2'd1;
parameter op1_choose_zero=2'd2;

always@(*)
begin
    case(sel)
        op1_choose_rd0:
            res = src0;
        op1_choose_pc:
            res = src1;
        default:
            res = 0;
    endcase
end
endmodule
`timescale 1ns / 1ps

module ALU
(
    input [31:0] alu_op1, alu_op2,   // 两操作数（对于减运算，a为被减数）
    input [3:0] alu_ctrl,           // 操作功能（加、减、与、或、异或等）
    output reg [31:0] alu_res     // 运算结果（和、差...）
);

parameter alu_add=4'd0;
parameter alu_sub=4'd1;
parameter alu_and=4'd2;
parameter alu_or=4'd3;
parameter alu_xor=4'd4;
parameter alu_compare=4'd5;
parameter alu_compare_u=4'd6;
parameter alu_left_logic=4'd7;
parameter alu_right_logic=4'd8;
parameter alu_left_count=4'd9;
parameter alu_right_count=4'd10;
parameter alu_wrong_input=4'd11;

    always @(*) begin
        alu_res = 0;
        case(alu_ctrl)
            alu_add: 
                alu_res = (alu_op1 + alu_op2);
            alu_sub: 
                alu_res = (alu_op1 - alu_op2);
            alu_and:
                alu_res = (alu_op1 & alu_op2);
            alu_or:
                alu_res = (alu_op1 | alu_op2);
            alu_xor:
                alu_res = (alu_op1 ^ alu_op2);
            alu_compare:
                alu_res = ($signed(alu_op1) < $signed(alu_op2));
            alu_compare_u:
                alu_res = (alu_op1 < alu_op2);
            alu_left_logic:
                alu_res = (alu_op1 << alu_op2);
            alu_right_logic:
                alu_res = (alu_op1 >> alu_op2);
            alu_left_count:
                alu_res = (alu_op1 <<< alu_op2);
            alu_right_count:
                alu_res = ($signed(alu_op1) >>> alu_op2);
            default:
                alu_res = 0;
        endcase
    end
endmodule
`timescale 1ns / 1ps

module MUX_write_back_sel(
input [1:0] sel,
input [31:0] src1,
input [31:0] src0,
input [31:0] src2,
output reg [31:0] res
);
parameter NAN=2'd0;
parameter choose_pc_add4=2'd1;
parameter choose_alu_res=2'd2;
parameter choose_mem_read_data=2'd3;

always@(*)
begin
    case(sel)
        choose_pc_add4:
            res = src1;
        choose_mem_read_data:
            res = src2;
        choose_alu_res:
            res = src0;
        default:    
            res = 0;
    endcase
end
endmodule
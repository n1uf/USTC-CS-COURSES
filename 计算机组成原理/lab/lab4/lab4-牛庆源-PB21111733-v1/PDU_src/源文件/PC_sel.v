`timescale 1ns / 1ps

module PC_sel(
input jal,
input jalr,
input br,
input [31:0] pc_add4,
input [31:0] pc_jalr,
input [31:0] pc_jal_br,
output reg [31:0] pc_next
);

always@(*)
begin
    if(jalr)
        pc_next = pc_jalr;
    else if(br | jal)
        pc_next = pc_jal_br;
    else
        pc_next = pc_add4;
end
endmodule
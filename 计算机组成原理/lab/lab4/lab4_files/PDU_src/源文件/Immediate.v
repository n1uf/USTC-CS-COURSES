`timescale 1ns / 1ps

module Immediate(
input [31:0] inst,
input [2:0] imm_type,
output reg [31:0] imm
);

always@(*)
begin
    case(imm_type)
    3'b001: // I (andi)
      imm = {{20{inst[31]}},inst[31:20]};
    
    3'b010: // Ishamt (slli, srli, srai)
      imm = {{26{inst[25]}},inst[25:20]};

    3'b011: // B
      imm = {{20{inst[31]}},inst[7],inst[30:25],inst[11:8],1'b0};

    3'b100: // S
      imm = {{20{inst[31]}},inst[31:25],inst[11:7]};

    3'b101: // U
      imm = {inst[31:12],{12{1'b0}}};

    3'b110: // J
      imm = {{12{inst[31]}},inst[19:12],inst[20],inst[30:21],1'b0};

    3'b000: // NAN
      imm = 0;
    endcase
end
endmodule
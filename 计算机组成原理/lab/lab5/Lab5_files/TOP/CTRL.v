`timescale 1ns / 1ps

module CTRL(
input [31:0] inst,
output reg jal,
output reg jalr,
output reg [1:0] br_type,
output reg wb_en,
output reg [1:0] wb_sel,
output reg alu_op2_sel, alu_op1_sel,
output reg [3:0] alu_ctrl,
output reg [2:0] imm_type,
output reg mem_write_en,
output reg rf_re0, rf_re1
);

always@(*)
begin
	if (inst[6:0] == 7'b0010011)//addi
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 1;
		wb_sel = 0;
		alu_ctrl = 0;
		imm_type = 0;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		rf_re1 = 0;
	end
	else if (inst[6:0] == 7'b0110011)//add
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 0;
		wb_sel = 0;
		alu_ctrl = 0;
		imm_type = 5;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		if (inst[24:20] == 3'b000) rf_re1 = 0;
		else rf_re1 = 1;
	end
	else if (inst[6:0] == 7'b0110111)//lui
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 0;
		wb_sel = 3;
		alu_ctrl = 8;
		imm_type = 3;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		rf_re0 = 0;
		rf_re1 = 0;
	end
	else if (inst[6:0] == 7'b0010111)//auipc
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 1;
		alu_op2_sel = 1;
		wb_sel = 0;
		alu_ctrl = 0;
		imm_type = 3;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		rf_re0 = 0;
		rf_re1 = 0;
	end
	else if (inst[6:0] == 7'b1101111)//jal
	begin
		jal = 1;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 1;
		alu_op2_sel = 1;
		wb_sel = 1;
		alu_ctrl = 0;
		imm_type = 4;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		rf_re0 = 0;
		rf_re1 = 0;
	end
	else if (inst[6:0] == 7'b1100111)//jalr
	begin
		jal = 0;
		jalr = 1;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 1;
		wb_sel = 1;
		alu_ctrl = 0;
		imm_type = 0;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		rf_re1 = 0;
	end
	else if (inst[6:0] == 7'b1100011 && inst[14:12] == 3'b000)//beq
	begin
		jal = 0;
		jalr = 0;
		br_type = 1;
		alu_op1_sel = 1;
		alu_op2_sel = 1;
		wb_sel = 0;
		alu_ctrl = 0;
		imm_type = 2;
		mem_write_en = 0;
		wb_en = 0;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		if (inst[24:20] == 3'b000) rf_re1 = 0;
		else rf_re1 = 1;
	end
	else if (inst[6:0] == 7'b1100011 && inst[14:12] == 3'b100)//blt
	begin
		jal = 0;
		jalr = 0;
		br_type = 2;
		alu_op1_sel = 1;
		alu_op2_sel = 1;
		wb_sel = 0;
		alu_ctrl = 0;
		imm_type = 2;
		mem_write_en = 0;
		wb_en = 0;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		if (inst[24:20] == 3'b000) rf_re1 = 0;
		else rf_re1 = 1;
	end
	else if (inst[6:0] == 7'b0000011)//lw
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 1;
		wb_sel = 2;
		alu_ctrl = 0;
		imm_type = 0;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		rf_re1 = 0;
	end
	else if (inst[6:0] == 7'b0100011)//sw
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 1;
		wb_sel = 0;
		alu_ctrl = 0;
		imm_type = 1;
		mem_write_en = 1;
		wb_en = 0;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		if (inst[24:20] == 3'b000) rf_re1 = 0;
		else rf_re1 = 1;
	end
	else 
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		wb_en = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 0;
		wb_sel = 0;
		alu_ctrl = 8;
		imm_type = 5;
		mem_write_en = 0;
		wb_en = 0;
		rf_re0 = 0;
		rf_re1 = 0;
	end
end
endmodule
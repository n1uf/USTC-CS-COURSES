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
output reg rf_re0, rf_re1,
output reg [2:0] l_type, s_type
);

//操作码的不同情况区分指令
parameter op1_U_lui=7'b0110111;
parameter op1_U_auipc=7'b0010111;
parameter op1_J_jal=7'b1101111;
parameter op1_I_jalr=7'b1100111;
parameter op1_I_type1=7'b0000011;
parameter op1_I_type2=7'b0010011;
parameter op1_B=7'b1100011;
parameter op1_S=7'b0100011;
parameter op1_R=7'b0110011;

parameter op2_I_type1_lw=3'b010;
parameter op2_I_type1_lb=3'b000;
parameter op2_I_type1_lbu=3'b100;
parameter op2_I_type1_lh=3'b001;
parameter op2_I_type1_lhu=3'b101;
parameter op2_I_type2_addi=3'b000;
parameter op2_I_type2_slti=3'b010;
parameter op2_I_type2_sltiu=3'b011;
parameter op2_I_type2_xori=3'b100;
parameter op2_I_type2_ori=3'b110;
parameter op2_I_type2_andi=3'b111;
parameter op2_Ishamt_slli=3'b001;
parameter op2_Ishamt_srli=3'b101;
parameter op2_Ishamt_srai=3'b101;
parameter op2_B_beq=3'b000;
parameter op2_B_bne=3'b001;
parameter op2_B_blt=3'b100;
parameter op2_B_bge=3'b101;
parameter op2_B_bltu=3'b110;
parameter op2_B_bgeu=3'b111;
parameter op2_S_sw=3'b010;
parameter op2_S_sh=3'b001;
parameter op2_S_sb=3'b000;
parameter op2_R_add=3'b000;
parameter op2_R_sub=3'b000;
parameter op2_R_sll=3'b001;
parameter op2_R_slt=3'b010;
parameter op2_R_sltu=3'b011;
parameter op2_R_xor=3'b100;
parameter op2_R_srl=3'b101;
parameter op2_R_sra=3'b101;
parameter op2_R_or=3'b110;
parameter op2_R_and=3'b111;

parameter op3_Ishamt_srli=7'b0000000;
parameter op3_Ishamt_slli=7'b0000000;
parameter op3_Ishamt_srai=7'b0100000;
parameter op3_R_add=7'b0000000;
parameter op3_R_sub=7'b0100000;
parameter op3_R_srl=7'b0000000;
parameter op3_R_sra=7'b0100000;
parameter op3_R_else=7'b0000000;

always@(*)
begin
	if (inst[6:0] == op1_I_type2 && inst[14:12] == op2_I_type2_addi)//addi
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
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_R && inst[14:12] == op2_R_add && inst[31:25] == op3_R_add)//add
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
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_U_lui)//lui
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
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_U_auipc)//auipc
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
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_J_jal)//jal
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
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_I_jalr)//jalr
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
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_B && inst[14:12] == op2_B_beq)//beq
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
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_B && inst[14:12] == op2_B_blt)//blt
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
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_B && inst[14:12] == op2_B_bne)//bne
	begin
		jal = 0;
		jalr = 0;
		br_type = 3;
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
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_B && inst[14:12] == op2_B_bge)//bge
	begin
		jal = 0;
		jalr = 0;
		br_type = 4;
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
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_B && inst[14:12] == op2_B_bltu)//bltu
	begin
		jal = 0;
		jalr = 0;
		br_type = 5;
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
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_B && inst[14:12] == op2_B_bgeu)//bgeu
	begin
		jal = 0;
		jalr = 0;
		br_type = 6;
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
		l_type = 0;
		s_type = 0;
	end	
	else if (inst[6:0] == op1_I_type1 && inst[14:12] == op2_I_type1_lw)//lw
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
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_I_type1 && inst[14:12] == op2_I_type1_lb)//lb
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
		l_type = 1;
		s_type = 0;
	end
	else if (inst[6:0] == op1_I_type1 && inst[14:12] == op2_I_type1_lbu)//lbu
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
		l_type = 2;
		s_type = 0;
	end
	else if (inst[6:0] == op1_I_type1 && inst[14:12] == op2_I_type1_lh)//lh
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
		l_type = 3;
		s_type = 0;
	end
	else if (inst[6:0] == op1_I_type1 && inst[14:12] == op2_I_type1_lhu)//lhu
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
		l_type = 4;
		s_type = 0;
	end
	else if (inst[6:0] == op1_S && inst[14:12] == op2_S_sw)//sw
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
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_S && inst[14:12] == op2_S_sb)//sb
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
		l_type = 0;
		s_type = 1;
	end
	else if (inst[6:0] == op1_S && inst[14:12] == op2_S_sh)//sh
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
		l_type = 0;
		s_type = 2;
	end
	else if (inst[6:0] == op1_I_type2 && inst[14:12] == op2_I_type2_slti)//slti
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 1;
		wb_sel = 0;
		alu_ctrl = 9;
		imm_type = 0;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		rf_re1 = 0;
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_R && inst[14:12] == op2_R_slt)//slt
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 0;
		wb_sel = 0;
		alu_ctrl = 9;
		imm_type = 5;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		if (inst[24:20] == 3'b000) rf_re1 = 0;
		else rf_re1 = 1;
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_I_type2 && inst[14:12] == op2_I_type2_sltiu)//sltiu
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 1;
		wb_sel = 0;
		alu_ctrl = 10;
		imm_type = 0;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		rf_re1 = 0;
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_R && inst[14:12] == op2_R_sltu)//sltu
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 0;
		wb_sel = 0;
		alu_ctrl = 10;
		imm_type = 5;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		if (inst[24:20] == 3'b000) rf_re1 = 0;
		else rf_re1 = 1;
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_R && inst[14:12] == op2_R_sub && inst[31:25] == op3_R_sub)//sub
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 0;
		wb_sel = 0;
		alu_ctrl = 1;
		imm_type = 5;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		if (inst[24:20] == 3'b000) rf_re1 = 0;
		else rf_re1 = 1;
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_I_type2 && inst[14:12] == op2_I_type2_xori)//xori
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 1;
		wb_sel = 0;
		alu_ctrl = 7;
		imm_type = 0;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		rf_re1 = 0;
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_R && inst[14:12] == op2_R_xor)//xor
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 0;
		wb_sel = 0;
		alu_ctrl = 7;
		imm_type = 5;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		if (inst[24:20] == 3'b000) rf_re1 = 0;
		else rf_re1 = 1;
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_I_type2 && inst[14:12] == op2_I_type2_ori)//ori
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 1;
		wb_sel = 0;
		alu_ctrl = 6;
		imm_type = 0;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		rf_re1 = 0;
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_R && inst[14:12] == op2_R_or)//or
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 0;
		wb_sel = 0;
		alu_ctrl = 6;
		imm_type = 5;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		if (inst[24:20] == 3'b000) rf_re1 = 0;
		else rf_re1 = 1;
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_I_type2 && inst[14:12] == op2_I_type2_andi)//andi
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 1;
		wb_sel = 0;
		alu_ctrl = 5;
		imm_type = 0;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		rf_re1 = 0;
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_R && inst[14:12] == op2_R_and)//and
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 0;
		wb_sel = 0;
		alu_ctrl = 5;
		imm_type = 5;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		if (inst[24:20] == 3'b000) rf_re1 = 0;
		else rf_re1 = 1;
		l_type = 0;
		s_type = 0;
	end	
	else if (inst[6:0] == op1_I_type2 && inst[14:12] == op2_Ishamt_slli && inst[31:25] == op3_Ishamt_slli)//slli
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 1;
		wb_sel = 0;
		alu_ctrl = 11;
		imm_type = 6;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		rf_re1 = 0;
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_R && inst[14:12] == op2_R_sll)//sll
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 0;
		wb_sel = 0;
		alu_ctrl = 11;
		imm_type = 5;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		if (inst[24:20] == 3'b000) rf_re1 = 0;
		else rf_re1 = 1;
		l_type = 0;
		s_type = 0;
	end	
	else if (inst[6:0] == op1_I_type2 && inst[14:12] == op2_Ishamt_srli && inst[31:25] == op3_Ishamt_srli)//srli
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 1;
		wb_sel = 0;
		alu_ctrl = 12;
		imm_type = 6;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		rf_re1 = 0;
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_R && inst[14:12] == op2_R_srl && inst[31:25] == op3_R_srl)//srl
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 0;
		wb_sel = 0;
		alu_ctrl = 12;
		imm_type = 5;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		if (inst[24:20] == 3'b000) rf_re1 = 0;
		else rf_re1 = 1;
		l_type = 0;
		s_type = 0;
	end	
	else if (inst[6:0] == op1_I_type2 && inst[14:12] == op2_Ishamt_srai && inst[31:25] == op3_Ishamt_srai)//srai
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 1;
		wb_sel = 0;
		alu_ctrl = 13;
		imm_type = 6;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		rf_re1 = 0;
		l_type = 0;
		s_type = 0;
	end
	else if (inst[6:0] == op1_R && inst[14:12] == op2_R_sra && inst[31:25] == op3_R_sra)//sra
	begin
		jal = 0;
		jalr = 0;
		br_type = 0;
		alu_op1_sel = 0;
		alu_op2_sel = 0;
		wb_sel = 0;
		alu_ctrl = 13;
		imm_type = 5;
		mem_write_en = 0;
		if (inst[11:7] == 3'b000) wb_en = 0;
		else wb_en = 1;
		if (inst[19:15] == 3'b000) rf_re0 = 0;
		else rf_re0 = 1;
		if (inst[24:20] == 3'b000) rf_re1 = 0;
		else rf_re1 = 1;
		l_type = 0;
		s_type = 0;
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
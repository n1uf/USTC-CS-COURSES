`timescale 1ns / 1ps

module SEG_REG(
	input clk,flush,stall,

	input [31:0] pc_cur_in,inst_in,
	input [4:0] rf_ra0_in,rf_ra1_in,
	input rf_re0_in,rf_re1_in,
	input [31:0] rf_rd0_raw_in,rf_rd1_raw_in,rf_rd0_in,rf_rd1_in,
	input [4:0] rf_wa_in,
	input [1:0] rf_wd_sel_in,
	input rf_we_in,
	input [2:0] imm_type_in,
	input [31:0] imm_in,
	input alu_src1_sel_in,alu_src2_sel_in,
	input [31:0] alu_src1_in,alu_src2_in,
	input [3:0] alu_func_in,
	input [31:0] alu_ans_in,pc_add4_in,pc_br_in,pc_jal_in,pc_jalr_in,
	input jal_in,jalr_in,br_in,dm_we_in,
	input [1:0] br_type_in,pc_sel_in,
	input [31:0] pc_next_in,dm_addr_in,dm_din_in,dm_dout_in,
	input [2:0] l_type_in,s_type_in,
	
	output reg [31:0] pc_cur_out,inst_out,
	output reg [4:0] rf_ra0_out,rf_ra1_out,
	output reg rf_re0_out,rf_re1_out,
	output reg [31:0] rf_rd0_raw_out,rf_rd1_raw_out,rf_rd0_out,rf_rd1_out,
	output reg [4:0] rf_wa_out,
	output reg [1:0] rf_wd_sel_out,
	output reg rf_we_out,
	output reg [2:0] imm_type_out,
	output reg [31:0] imm_out,
	output reg alu_src1_sel_out,alu_src2_sel_out,
	output reg [31:0] alu_src1_out,alu_src2_out,
	output reg [3:0] alu_func_out,
	output reg [31:0] alu_ans_out,pc_add4_out,pc_br_out,pc_jal_out,pc_jalr_out,
	output reg jal_out,jalr_out,br_out,dm_we_out,
	output reg [1:0] br_type_out,pc_sel_out,
	output reg [31:0] pc_next_out,dm_addr_out,dm_din_out,dm_dout_out,
	output reg [2:0] l_type_out,s_type_out	
    );
always @(posedge clk)
if (stall == 0)
if (flush)
begin
	pc_cur_out = 0;
  	inst_out = 0;
  	rf_ra0_out = 0;
  	rf_ra1_out = 0;
  	rf_re0_out = 0;
  	rf_re1_out = 0;
  	rf_rd0_raw_out = 0;
  	rf_rd1_raw_out = 0;
	rf_rd0_out = 0;
	rf_rd1_out = 0;
	rf_wa_out = 0;
	rf_wd_sel_out = 0;
	rf_we_out = 0;
	imm_type_out = 0;
	imm_out = 0;
	alu_src1_sel_out = 0;
	alu_src2_sel_out = 0;
	alu_src1_out = 0;
	alu_src2_out = 0;
	alu_func_out = 0;
	alu_ans_out = 0;
	pc_add4_out = 0;
	pc_br_out = 0;
	pc_jal_out = 0;
	pc_jalr_out = 0;
	jal_out = 0;
	jalr_out = 0;
	br_out = 0;
	dm_we_out = 0;
	br_type_out = 0;
	pc_sel_out = 0;
	pc_next_out = 0;
	dm_addr_out = 0;
	dm_din_out = 0;
	dm_dout_out = 0;
	l_type_out = 0;
	s_type_out = 0;
end
else 
begin
	pc_cur_out = pc_cur_in;
  	inst_out = inst_in;
  	rf_ra0_out = rf_ra0_in;
  	rf_ra1_out = rf_ra1_in;
  	rf_re0_out = rf_re0_in;
  	rf_re1_out = rf_re1_in;
  	rf_rd0_raw_out = rf_rd0_raw_in;
  	rf_rd1_raw_out = rf_rd1_raw_in;
	rf_rd0_out = rf_rd0_in;
	rf_rd1_out = rf_rd1_in;
	rf_wa_out = rf_wa_in;
	rf_wd_sel_out = rf_wd_sel_in;
	rf_we_out = rf_we_in;
	imm_type_out = imm_type_in;
	imm_out = imm_in;
	alu_src1_sel_out = alu_src1_sel_in;
	alu_src2_sel_out = alu_src2_sel_in;
	alu_src1_out = alu_src1_in;
	alu_src2_out = alu_src2_in;
	alu_func_out = alu_func_in;
	alu_ans_out = alu_ans_in;
	pc_add4_out = pc_add4_in;
	pc_br_out = pc_br_in;
	pc_jal_out = pc_jal_in;
	pc_jalr_out = pc_jalr_in;
	jal_out = jal_in;
	jalr_out = jalr_in;
	br_out = br_in;
	dm_we_out = dm_we_in;
	br_type_out = br_type_in;
	pc_sel_out = pc_sel_in;
	pc_next_out = pc_next_in;
	dm_addr_out = dm_addr_in;
	dm_din_out = dm_din_in;
	dm_dout_out = dm_dout_in;
	l_type_out = l_type_in;
	s_type_out = s_type_in;
end

endmodule

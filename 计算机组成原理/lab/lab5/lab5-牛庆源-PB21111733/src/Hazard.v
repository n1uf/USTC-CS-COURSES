`timescale 1ns / 1ps

module Hazard(
	input [4:0] rf_ra0_ex,rf_ra1_ex,rf_wa_mem,rf_wa_wb,
	input rf_re0_ex,rf_re1_ex,rf_we_mem,rf_we_wb,
	input [1:0] rf_wd_sel_mem,pc_sel_ex,
	input [31:0] alu_ans_mem,pc_add4_mem,imm_mem,rf_wd_wb,
	output reg [31:0] rf_rd0_fd,rf_rd1_fd,
	output reg rf_rd0_fe,rf_rd1_fe,stall_if,stall_id,stall_ex,flush_if,flush_id,flush_ex,flush_mem 
    );
    
wire [31:0] wd_res_mem;

initial begin
	rf_rd0_fd = 0;
	rf_rd1_fd = 0;
	rf_rd0_fe = 0;
	rf_rd1_fe = 0;
	stall_if = 0;
	stall_id = 0;
	stall_ex = 0;
	flush_if = 0;
	flush_id = 0;
	flush_ex = 1;
	flush_mem = 0;
end
   			    
Mux2 mem_write_sel(
   			    .src0(alu_ans_mem),
   			    .src1(pc_add4_mem),
   			    .src2(32'h0),
   			    .src3(imm_mem),
   			    .sel(rf_wd_sel_mem),
   			    .res(wd_res_mem)
   			    );

always @(*)
begin
		if (pc_sel_ex != 0) // 控制冒险
		begin
			flush_id = 1;
			flush_ex = 1;
		end
		else
		begin
			flush_id = 0;
			flush_ex = 0;
		end
		if (rf_re0_ex) // EX段寄存器0读使能非零
			if (rf_we_mem == 1) // MEM段写使能为1
			begin
			if (rf_ra0_ex == rf_wa_mem) // MEM段写地址等于寄存器读地址
			begin
				if (rf_wd_sel_mem == 2)
				begin
					flush_mem = 1;
					flush_if = 1;
					stall_if = 1;
					stall_id = 1;
					stall_ex = 1;
					rf_rd0_fd = 0;
					rf_rd0_fe = 0;
				end
				else
				begin
					flush_mem = 0;
					flush_if = 0;
					stall_if = 0;
					stall_id = 0;
					stall_ex = 0;
					rf_rd0_fd = wd_res_mem;
					rf_rd0_fe = 1;
				end
			end
			end
			else if (rf_we_wb == 1) // WB段写使能为1
			begin
			if (rf_ra0_ex == rf_wa_wb) // WB段写地址等于寄存器读地址
			begin
				flush_mem = 0;
				flush_if = 0;
				stall_if = 0;
				stall_id = 0;
				stall_ex = 0;
				rf_rd0_fd = rf_wd_wb;
				rf_rd0_fe = 1;
			end
			else 
			begin
				flush_mem = 0;
				flush_if = 0;
				stall_if = 0;
				stall_id = 0;
				stall_ex = 0;
				rf_rd0_fd = 0;
				rf_rd0_fe = 0;
			end
			end
		else // 寄存器0写使能为0
		begin
			flush_mem = 0;
			flush_if = 0;
			stall_if = 0;
			stall_id = 0;
			stall_ex = 0;
			rf_rd0_fd = 0;
			rf_rd0_fe = 0;
		end
		if (rf_re1_ex) // EX段寄存器1非0，以下同上寄存器0的情况
			if (rf_we_mem == 1)
			begin
				if (rf_ra1_ex == rf_wa_mem)
				begin
					if (rf_wd_sel_mem == 2)
					begin
						flush_mem = 1;
						flush_if = 1;
						stall_if = 1;
						stall_id = 1;
						stall_ex = 1;
						rf_rd1_fd = 0;
						rf_rd1_fe = 0;
					end
					else
					begin
						flush_mem = 0;
						flush_if = 0;
						stall_if = 0;
						stall_id = 0;
						stall_ex = 0;
						rf_rd1_fd = wd_res_mem;
						rf_rd1_fe = 1;
					end
				end
			end
			else if(rf_we_wb == 1)
			begin
				if (rf_ra1_ex == rf_wa_wb)
				begin
					flush_mem = 0;
					flush_if = 0;
					stall_if = 0;
					stall_id = 0;
					stall_ex = 0;
					rf_rd1_fd = rf_wd_wb;
					rf_rd1_fe = 1;
				end
				else 
				begin
					flush_mem = 0;
					flush_if = 0;
					stall_if = 0;
					stall_id = 0;
					stall_ex = 0;
					rf_rd1_fd = 0;
					rf_rd1_fe = 0;
				end
			end
		else // 寄存器1写使能为0
		begin
			rf_rd1_fd = 0;
			rf_rd1_fe = 0;
		end
		if (rf_re0_ex == 0 && rf_re1_ex == 0) // 两个寄存器写使能均为0
		begin
			stall_if = 0;
			stall_id = 0;
			stall_ex = 0;
			flush_if = 0;
			flush_mem = 0;
		end
end

endmodule
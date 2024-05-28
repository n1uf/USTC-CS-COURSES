`timescale 1ns / 1ps

/* 
 *   Author: YOU
 *   Last update: 2023.04.20
 */

module CPU(
    input clk, 
    input rst,

    // MEM And MMIO Data BUS
    output [31:0] im_addr,      // Instruction address (The same as current PC)
    input [31:0] im_dout,       // Instruction data (Current instruction)
    output [31:0] mem_addr,     // Memory read/write address
    output mem_we,              // Memory writing enable		            
    output [31:0] mem_din,      // Data ready to write to memory
    input [31:0] mem_dout,	    // Data read from memory

    // Debug BUS with PDU
    output [31:0] current_pc, 	        // Current_pc, pc_out
    output [31:0] next_pc,              // Next_pc, pc_in    
    input [31:0] cpu_check_addr,	    // Check current datapath state (code)
    output reg [31:0] cpu_check_data    // Current datapath state data
);
    
    
    // Write your CPU here!
    // You might need to write these modules:
    //      ALU、RF、Control、Add(Or just add-mode ALU)、And(Or just and-mode ALU)、PCReg、Imm、Branch、Mux、...
//CTRL
wire jal;
wire jalr;
wire [2:0] br_type;
wire wb_en;
wire [1:0] wb_sel;
wire [1:0] alu_op1_sel;
wire alu_op2_sel;
wire [3:0] alu_ctrl;
wire [2:0] imm_type;
wire mem_write_en;
//RF
wire [31:0] rd0;
wire [31:0] rd1;
wire [31:0] rd2;
//Branch
wire br;
//PC
wire [31:0] pc_next;
wire [31:0] pc_current;
//ADD_PC
wire [31:0] pc_add4;
//imm
wire [31:0] imm;
//ALU
wire [31:0] alu_op1;
wire [31:0] alu_op2;
wire [31:0] alu_res;
//write_back
wire [31:0] write_back_res;
//pc_jalr
wire [31:0] pc_jalr;

wire [31:0] cpu_check_data_ck1;
wire [31:0] cpu_check_data_wire;

PC PC(
    .clk(clk),
    .rst(rst),
    .pc_next(pc_next),
    .pc_cur(pc_current)
);

CTRL CTRL(
    .inst(im_dout),
    .jal(jal),
    .jalr(jalr),
    .br_type(br_type),
    .wb_en(wb_en),
    .wb_sel(wb_sel),
    .alu_op1_sel(alu_op1_sel),
    .alu_op2_sel(alu_op2_sel),
    .imm_type(imm_type),
    .mem_write_en(mem_we),
    .alu_ctrl(alu_ctrl)
);

RF RF(
    .clk(clk),
    .we(wb_en),
    .ra0(im_dout[19:15]),
    .ra1(im_dout[24:20]),
    .wa(im_dout[11:7]),
    .wd(write_back_res),
    .rd0(rd0),
    .rd1(rd1),
    .ra2(cpu_check_addr[4:0]),
    .rd2(cpu_check_data_ck1)
);

Immediate Immediate(
    .inst(im_dout),
    .imm_type(imm_type),
    .imm(imm)
);
Branch Branch(
    .br_type(br_type),
    .op1(rd0),
    .op2(rd1),
    .br(br)
);

MUX_op1_sel MUX_op1_sel(
    .sel(alu_op1_sel),
    .src0(rd0),
    .src1(pc_current),
    .res(alu_op1)
);

MUX_op2_sel MUX_op2_sel(
    .sel(alu_op2_sel),
    .src0(rd1),
    .src1(imm),
    .res(alu_op2)
);

ALU ALU(
    .alu_op1(alu_op1),
    .alu_op2(alu_op2),
    .alu_ctrl(alu_ctrl),
    .alu_res(alu_res)
);

ADD_PC ADD_PC(
    .rhs(pc_current),
    .res(pc_add4)
);

MUX_write_back_sel MUX_write_back_sel(
    .sel(wb_sel),
    .src0(alu_res),
    .src1(pc_add4),
    .src2(mem_dout),
    .res(write_back_res)
);

AND_jalr AND_jalr(
    .rhs(alu_res),
    .res(pc_jalr)
);

PC_sel PC_sel(
    .jal(jal),
    .jalr(jalr),
    .br(br),
    .pc_add4(pc_add4),
    .pc_jal_br(alu_res),
    .pc_jalr(pc_jalr),
    .pc_next(pc_next)
);

CPU_debug CPU_debug(
    .cpu_check_data_ck1(cpu_check_data_ck1),
    .cpu_check_addr(cpu_check_addr),
    .pc_cur(pc_current),
    .pc_next(pc_next),
    .inst(im_dout),
    .ra0(im_dout[19:15]),
    .ra1(im_dout[24:20]),
    .wa(im_dout[11:7]),
    .rd0(rd0),
    .rd1(rd1),
    .we(wb_en),
    .imm(imm),
    .alu_op1(alu_op1),
    .alu_op2(alu_op2),
    .alu_ctrl(alu_ctrl),
    .alu_res(alu_res),
    .mem_addr(mem_addr),
    .mem_din(mem_din),
    .mem_dout(mem_dout),
    .mem_we(mem_we),
    .check_data(cpu_check_data_wire)
);

always@(*)
begin
    cpu_check_data <= cpu_check_data_wire;
end

assign im_addr=pc_current;

assign mem_we=mem_write_en;
assign mem_addr=alu_res;
assign mem_din=rd1;
assign current_pc=pc_current;
assign next_pc=pc_next;

endmodule
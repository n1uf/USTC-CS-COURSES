`timescale 1ns / 1ps

module CPU_debug(
    input [31:0] cpu_check_addr,
    input [31:0] pc_cur,
    input [31:0] pc_next,
    input [31:0] inst,
    input [4:0] ra0,
    input [4:0] ra1,
    input [31:0] rd0,
    input [31:0] rd1,
    input [4:0] wa,
    input  we,
    input [31:0] imm,
    input [31:0] alu_op1,
    input [31:0] alu_op2,
    input [31:0] alu_ctrl,
    input [31:0] alu_res,
    input [31:0] mem_addr,
    input [31:0] mem_din,
    input [31:0] mem_dout,
    input  mem_we,
    input [31:0] cpu_check_data_ck1,
    output reg [31:0] check_data
);
always@(*)
begin
    if(cpu_check_addr[12] == 0)
        case(cpu_check_addr[7:0])
            8'h01:check_data = pc_cur;
            8'h02:check_data = pc_next;
            8'h03:check_data = inst;
            8'h04:check_data[4:0] = ra0;
            8'h05:check_data[4:0] = ra1;
            8'h06:check_data = rd0;
            8'h07:check_data = rd1;
            8'h08:check_data[4:0] = wa;
            8'h09:check_data[0] = we;
            8'h0a:check_data = imm;
            8'h0b:check_data =alu_op1;
            8'h0c:check_data = alu_op2;
            8'h0d:check_data = alu_ctrl;
            8'h0e:check_data = alu_res;
            8'h0f:check_data = alu_res;
            8'h10:check_data = mem_addr;
            8'h11:check_data = mem_din;
            8'h12:check_data = mem_dout;
            8'h13:check_data [0] = mem_we;
            default:check_data = 0;
        endcase
    else if(cpu_check_addr[12] == 1)
        check_data = cpu_check_data_ck1;
    else 
        check_data = 0;
end
endmodule
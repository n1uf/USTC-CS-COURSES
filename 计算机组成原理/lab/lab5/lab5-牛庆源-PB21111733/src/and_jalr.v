`timescale 1ns / 1ps

module and_jalr(
	input [31:0] alu_res,
	output [31:0] pc_jalr
    );
    assign pc_jalr = alu_res & 32'hFFFFFFFE;
endmodule

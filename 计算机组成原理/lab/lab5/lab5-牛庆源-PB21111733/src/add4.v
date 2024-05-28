`timescale 1ns / 1ps

module add4(
	input [31:0] pc_cur,
	output [31:0] pc_add4
    );
    assign pc_add4 = pc_cur + 4;
endmodule
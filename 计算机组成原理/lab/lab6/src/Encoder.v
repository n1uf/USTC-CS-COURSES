`timescale 1ns / 1ps

module Encoder(
	input jal,jalr,br,
	output reg [1:0] pc_sel
    );

always @(*)
begin
	if (jalr) pc_sel = 2'b01;
	else if (jal || br) pc_sel = 2'b10;
	else pc_sel = 2'b00;
end

endmodule

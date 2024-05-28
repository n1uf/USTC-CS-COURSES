`timescale 1ns / 1ps

module IMMediate(
	input [31:0] inst,
	input [2:0] imm_type,
	output reg [31:0] imm
    );

always @(*)
begin
	if (imm_type == 0)//I type
	begin
		imm = {{21{inst[31]}}, inst[30:20]};
	end
	else if (imm_type == 1)//S type
	begin
		imm = {{21{inst[31]}}, inst[30:25], inst[11:7]};
	end
	else if (imm_type == 2)//B type
	begin
		imm = {{20{inst[31]}}, inst[7] ,inst[30:25], inst[11:8], 1'b0};
	end
	else if (imm_type == 3)//U type
	begin
		imm = {inst[31:12],12'h000};
	end
	else if (imm_type == 4)//J type
	begin
		imm = {{12{inst[31]}}, inst[19:12], inst[20], inst[30:21], 1'b0};
	end
	else
	begin
		imm = 0;
	end
end

endmodule

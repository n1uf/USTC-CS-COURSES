`timescale 1ns / 1ps

module S_types(
	input [31:0] din,dout,
	input [2:0] s_type,
	output reg [31:0] new_din
    );
    
always @(*)
begin
	if (s_type == 1)//sb
	begin
		new_din = {dout[31:8],din[7:0]};
	end
	else
	if (s_type == 2)//sh
	begin
		new_din = {dout[31:16],din[15:0]};
	end
	else
	begin
		new_din = din;
	end
end
endmodule
`timescale 1ns / 1ps

module l_types(
	input [31:0] dm,
	input [2:0] l_type,
	output reg [31:0] new_dm
    );

always @(*)
begin
	if (l_type == 1)//lb
	begin
		new_dm = {{25{dm[7]}},dm[6:0]};		
	end
	else if (l_type == 2)//lbu
	begin
		new_dm = {24'b0,dm[7:0]};
	end
	else if (l_type == 3)//lh
	begin
		new_dm = {{17{dm[15]}},dm[14:0]};
	end
	else if (l_type == 4)//lhu
	begin
		new_dm = {16'b0,dm[15:0]};
	end	
	else
	begin
		new_dm = dm;
	end
end
endmodule
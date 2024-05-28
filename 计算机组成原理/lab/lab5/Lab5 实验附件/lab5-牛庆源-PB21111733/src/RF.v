`timescale 1ns / 1ps

module RF  
( 
  input clk, 
  input we, 
  input [4 : 0] ra0,
  input [4 : 0] ra1, 
  input [4: 0] ra2,
  input [4 : 0] wa, 
  input [31 : 0] wd, 
  output reg [31 : 0] rd0, 
  output reg [31 : 0] rd1,
  output [31 : 0] rd2
);

reg [31:0] Regfile [0 : 31];

integer i;
initial begin
i = 0;
while (i < 32) begin
Regfile[i] = 32'b0;
i = i + 1;
end
Regfile [2] = 32'h2ffc;
Regfile [3] = 32'h1800;
end

always @(*) // 写优先
begin
  if (we) 
	begin 
		if (wa == 0)
		begin
			if (ra0 == 0) 
        rd0 = 0;
			else 
        rd0 = Regfile[ra0];
			if (ra1 == 0) 
        rd1 = 0;
			else 
        rd1 = Regfile[ra1];
		end
		else
		begin
			if (ra0 == wa) 
        rd0 = wd;
			else 
        rd0 = Regfile[ra0];
			if (ra1 == wa) 
        rd1 = wd;
			else 
        rd1 = Regfile[ra1];
		end
	end
	else
	begin
		rd0 = Regfile[ra0];
		rd1 = Regfile[ra1];
	end
end

always @ (posedge clk) begin
if (we) 
    if (wa == 0) 
      Regfile[wa] <= 0;
    else 
      Regfile[wa] <= wd;
else
Regfile[0] <= 0;
end

endmodule

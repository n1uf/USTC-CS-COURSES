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
  output [31 : 0] rd0, 
  output [31 : 0] rd1,
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


assign rd0 = (ra0 == 0 ? 0 : Regfile[ra0]);
assign rd1 = (ra1 == 0 ? 0 : Regfile[ra1]);
assign rd2 = (ra2 == 0 ? 0 : Regfile[ra2]);

always @ (posedge clk)
  begin
    if (we)
    Regfile[wa] <= wd;
  end
endmodule

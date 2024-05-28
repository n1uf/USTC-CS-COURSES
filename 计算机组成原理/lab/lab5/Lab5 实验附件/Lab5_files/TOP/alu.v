`timescale 1ns / 1ps

module alu #(parameter WIDTH = 32)(
input [WIDTH-1:0] a, b, 
input [3:0] func, 
output [WIDTH-1:0] y
);
reg [WIDTH-1:0] result;
assign y = result;

always @(*)
begin
    if (func == 4'b0000)
    begin
        result = a + b;
    end
    else
    if (func == 4'b0001)
    begin
        result = a - b;
    end
    else
    if (func == 4'b0010)
    begin
        result = a == b;
    end
    else
    if (func == 4'b0011)
    begin
        result = a < b;
    end
    else
    if (func == 4'b0101)
    begin
        result = a & b;
    end
    else
    if (func == 4'b0110)
    begin
        result = a | b;
    end
    else
    if (func == 4'b0111)
    begin
        result = a ^ b;
    end
    else
    begin
        result = 0;
    end
end
endmodule
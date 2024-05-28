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
    else if (func == 4'b0001)
    begin
        result = a - b;
    end
    else if (func == 4'b0010)
    begin
        result = a == b;
    end
    else if (func == 4'b0011)
    begin
        result = a < b;
    end
    else if (func == 4'b0101)
    begin
        result = a & b;
    end
    else if (func == 4'b0110)
    begin
        result = a | b;
    end
    else if (func == 4'b0111)
    begin
        result = a ^ b;
    end
    else if (func == 4'b1001)
    begin
    	if (a[WIDTH-1] == b[WIDTH-1])
    		if (a[WIDTH-2:0] < b[WIDTH-2:0])
    			result = 32'b1;
    		else
    			result = 32'b0;
   	    else if (a[WIDTH-1] == 1 && b[WIDTH-1] == 0)
   	    		result = 32'b1;
   	    	else 
   	    		result = 32'b0;
    end
    else if (func == 4'b1010)
    begin
    	if (a < b) result = 32'b1;
    	else result = 32'b0;
    end
    else if (func == 4'b1011)
    begin
        result = a << b[4:0];
    end
    else if (func == 4'b1100)
    begin
        result = a >> b[4:0];
    end
    else if (func == 4'b1101)
    begin
        result = ($signed(a)) >>> b[4:0];
    end    
    else
    begin
        result = 0;
    end
end
endmodule
`timescale 1ns / 1ps

module Branch(
	input [31:0] rd0,rd1,
	input [1:0] br_type,
	output reg br
    );
    always @(*)
    begin
    	if (br_type == 1)//beq
    		if (rd0 == rd1)
    			br = 1;
    		else
    			br = 0;
    	else if (br_type == 2)//blt
    		if (rd0[31] == rd1[31])
    			if (rd0[30:0] < rd1[30:0])
    				br = 1;
    			else
    				br = 0;
   	    	else if (rd0[31] == 1 && rd1[31] == 0)
   	    			br = 1;
   	    		else 
   	    			br = 0;
    	else br = 0;
    end
endmodule

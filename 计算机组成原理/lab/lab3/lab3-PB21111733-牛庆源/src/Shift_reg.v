`timescale 1ns / 1ps

module Shift_reg(
    input rst,
    input clk,          // Work at 100MHz clock

    input [31:0] din,   // Data input  
    input [3:0] hex,    // Hexadecimal code for the switches
    input add,          // Add signal
    input del,          // Delete signal
    input set,          // Set signal
    
    output reg [31:0] dout  // Data output
);

    always@(posedge clk or posedge rst)
    begin
        if(rst)
            dout<=din;
        else if(set) // 置数
            dout<=din;
        else if(add) // 左移四位，低四位置hex
            dout<={dout[27:0],hex};
        else if(del) // 删除低四位，高四位置0
            dout<={4'b0,dout[31:4]};
    end

endmodule


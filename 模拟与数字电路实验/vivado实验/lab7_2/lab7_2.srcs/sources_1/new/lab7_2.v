`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/11/24 10:07:26
// Design Name: 
// Module Name: lab7_2
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module lab7_2(
    input clk,
    input [7:0] sw,
    output [7:0] led,
    reg [3:0] data,
    reg [2:0] an
    );
    reg [3:0] count;
    reg temp = 1'b0;
    always @ (posedge clk) begin
        count <= count + 1;
    end
    always @ (*) begin
        if(count == 4'b1111)
            temp = ~temp;
    end
    always @ (*) begin
        if(temp) begin
            an <= 3'b001;
            data <= sw[7:4];
        end
        else begin
            an <= 3'b000;
            data <= sw[3:0];
        end
    end
dist_mem_gen_0 dist_mem_gen_0(
.a(data),
.spo(led));
endmodule

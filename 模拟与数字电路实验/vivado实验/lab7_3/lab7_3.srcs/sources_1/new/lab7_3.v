`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/11/24 13:11:44
// Design Name: 
// Module Name: lab7_3
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


module lab7_3(
    input clk, rst,
    output [7:0] led,
    output reg [3:0] data,
    output reg [2:0] an
    );
    reg [23:0] timer;
    reg [3:0] clk_0_1;
    reg [3:0] clk_1;
    reg [3:0] clk_10;
    reg [3:0] clk_60;
    reg [3:0] count;
    reg temp = 2'b00;
    always@(posedge clk) begin
        if(rst) begin clk_60 <= 4'h1; clk_10 <= 4'h2; clk_1 <= 4'h3; clk_0_1 <= 4'h4; end
        else begin
        timer <= 24'h0; 
        if(timer>=9999999) begin
            if(clk_0_1 > 8) begin
                clk_0_1 <= 4'b0000;
                clk_1 <= clk_1 + 1;
                if(clk_1 > 8) begin
                    clk_1 <= 4'b0000;
                    clk_10 <= clk_10 + 1;
                    if(clk_10 > 4) begin
                        clk_10 <= 4'b0000;
                        clk_60 <= clk_60 + 1;
                        if(clk_60 > 8) begin
                            clk_60 <= 4'b0000;
                        end
                        else clk_60 <= clk_60 + 1;
                    end
                    else clk_10 <= clk_10 + 1;
                end
                else clk_1 <= clk_1 + 1;
            end
            else clk_0_1 <= clk_0_1 + 1;
            timer <= 24'h0; 
        end
        else 
            timer <= timer + 24'h1;
        end 
    end
    always@(posedge clk)
    begin
        count = count + 1;
        an = count[3:2];
        case (count[3:2])
            2'b00 : data <= clk_0_1;
            2'b01 : data <= clk_1;
            2'b10 : data <= clk_10;
            2'b11 : data <= clk_60;
        endcase
    end
dist_mem_gen_0 dist_mem_gen_0(
.a(data),
.spo(led));
endmodule
`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/12/01 11:14:27
// Design Name: 
// Module Name: lab8_3
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


module lab8_3(
    input clk, rst, sw, btn,
    output reg [2:0] hexplay_an,
    output reg [3:0] hexplay_data);
    // 按钮信号转为持续一个周期的脉冲信号
    reg temp1, temp2;
    wire btn_pulse;
    always @(posedge clk) temp1 <= btn;
    always @(posedge clk) temp2 <= temp1;
    assign btn_pulse = temp1 & (~temp2);
    // 计数
    reg [7:0] count;
    always @(posedge clk) begin
        if (rst)
            count <= 8'h1f;
        else if (btn_pulse) begin
            if (sw)
                count <= count + 1;
            else
                count <= count - 1;
        end
    end
    // 分时复用
    reg [2:0] cnt;
    always @(posedge clk) begin
        cnt <= cnt + 1;
        case (cnt)
            3'b011: begin
                hexplay_an <= 3'b000;
                hexplay_data <= count[3:0];
            end
            3'b111: begin
                hexplay_an <= 3'b001;
                hexplay_data <= count[7:4];
            end
        endcase
    end
endmodule

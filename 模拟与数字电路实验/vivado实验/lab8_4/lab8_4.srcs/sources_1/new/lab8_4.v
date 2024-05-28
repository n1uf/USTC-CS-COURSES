`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/12/01 11:33:14
// Design Name: 
// Module Name: lab8_4
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


module lab8_4(
input clk, rst, sw, btn,
output reg [2:0] hexplay_an,
output reg [3:0] hexplay_data);
// 第一部分：生成次态
reg [2:0] cur, next;
always @(*) begin
    if (sw)
    case (cur)
        3'b000: next = 1;
        3'b001: next = 2;
        3'b010: next = 2;
        3'b011: next = 1;
        3'b100: next = 1;
        default: next = 0;
    endcase
    else
    case (cur)
        3'b010: next = 3;
        3'b011: next = 4;
        default: next = 0;
    endcase
end
// 第二部分：时序逻辑状态转换
reg temp1, temp2;
wire btn_pulse;
always @(posedge clk) temp1 <= btn;
always @(posedge clk) temp2 <= temp1;
assign btn_pulse = temp1 & (~temp2);
reg [3:0] recent;
always @(posedge clk) begin
    if (rst) begin
        cur <= 0;
        recent <= 0;
    end
    else if (btn_pulse) begin
        cur <= next;
        recent <= recent << 1;
        recent[0] <= sw;
    end
    else begin
        cur <= cur;
        recent <= recent;
    end
end
// 第三部分：输出
reg state1, state2;
wire state_pulse;
always @(posedge clk) state1 <= cur[2];
always @(posedge clk) state2 <= state1;
assign state_pulse = state1 & (~state2);
reg [3:0] out;
always @(posedge clk) begin
    if (rst)
        out <= 0;
    else if (state_pulse)
        out <= out + 1;
    else
        out <= out;
end
reg [4:0] cnt;
always @(posedge clk) begin
    if (cnt == 5'b10111)
        cnt <= 5'b0;
    else
        cnt <= cnt + 1;
    case (cnt[4:2])
        0: begin
            hexplay_an <= 3'b000;
            hexplay_data <= {1'b0, cur};
        end
        1: begin
            hexplay_an <= 3'b010;
            hexplay_data <= out;
        end
        2: begin
            hexplay_an <= 3'b100;
            hexplay_data <= {3'b0, recent[0]};
        end
        3: begin
            hexplay_an <= 3'b101;
            hexplay_data <= {3'b0, recent[1]};
        end
        4: begin
            hexplay_an <= 3'b110;
            hexplay_data <= {3'b0, recent[2]};
        end
        5: begin
            hexplay_an <= 3'b111;
            hexplay_data <= {3'b0, recent[3]};
        end
        default: hexplay_data <= 4'b0;
    endcase
end
endmodule

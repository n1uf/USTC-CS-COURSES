module fifo (
input clk, rst, //时钟（上升沿有效）、同步复位（高电平有效）
input enq, //入队列使能，高电平有效
input [3:0] in, //入队列数据
input deq, //出队列使能，高电平有效
output [3:0] out, //出队列数据
output full,empty, //队列满和空标志
output [2:0] an, //数码管选择
output [3:0] seg //数码管数据
);

wire [3:0] rd0,rd1,wd;
wire we;
wire [2:0] wa,ra0,ra1;
wire [7:0] valid;

LCU ll(clk,rst,enq,deq,in,rd0,out,wd,full,empty,we,wa,ra0,valid);
register_file rf(clk,ra0,rd0,ra1,rd1,wa,we,wd);
SDU ss(clk,rst,valid,rd1,empty,ra1,an,seg);

endmodule
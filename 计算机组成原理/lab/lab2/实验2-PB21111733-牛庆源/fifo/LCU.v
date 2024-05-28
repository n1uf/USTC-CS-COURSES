module LCU(
    input clk,rst,enq,deq,
    input [3:0] in,rd0,
    output [3:0] out,wd,
    output full,emp,
    output we,
    output [2:0] wa,ra0,
    output [7:0] valid
    );
wire enq1,deq1; // sedg后的入队出队使能信号
reg [7:0] cur_valid,n_valid;
reg [2:0] cur_wp,cur_rp,n_wp,n_rp,n_wa,cur_wa;
reg [2:0] wpp,rpp,rpm; // 便于代码书写
reg cur_full,cur_empty,n_full,n_empty,n_we,cur_we;
reg [1:0] cur_state,n_state;//0=IDLE 1=ENQU 2=DEQU

always @(posedge clk) 
    if (rst)    // 同步复位
    begin
        cur_rp <= 0;
        cur_wp <= 0;
        cur_full <= 0;
        cur_empty <= 1;
        cur_state <= 0;
        cur_valid <= 0;
        cur_wa <= 0;
        cur_we <= 0;
    end
    else    // 当前态赋值
    begin
        cur_rp <= n_rp;
        cur_wp <= n_wp;
        cur_full <= n_full;
        cur_empty <= n_empty;
        cur_state <= n_state;
        cur_valid <= n_valid;
        cur_wa <= n_wa;
        cur_we <= n_we;
    end

always @(*)
begin
    if (enq1 & !cur_full) // 队列不满且入队使能有效
    begin   // 入队
            n_rp = cur_rp;
            n_wp = cur_wp + 1;
            n_valid = cur_valid | (1 << cur_wp);
            n_full = (wpp == cur_rp);
            n_wa = cur_wp; 
            n_empty = 0;
            n_state = 1;
            n_we = 1;
    end
    else if (deq1 & !cur_empty) // 队列非空且出队使能有效
    begin   // 出队
            n_rp = cur_rp + 1;
            n_wp = cur_wp;
            n_valid = cur_valid - (1 << cur_rp);
            n_empty = (cur_wp == rpp);
            n_wa = 0;
            n_full = 0;
            n_state = 2;
            n_we = 0;
    end
    else // 其他情况
    begin // 状态不变
        n_rp = cur_rp;
        n_wp = cur_wp;
        n_full = cur_full;
        n_empty = cur_empty;
        n_state = cur_state;
        n_valid = cur_valid;
        n_wa = 0;
        n_we = 0;
    end
end

always @(*)
begin
 	wpp = cur_wp + 1;
 	rpp = cur_rp + 1;
 	rpm = cur_rp - 1;
end

assign we = cur_we;
assign ra0 = rpm;
assign wa = cur_wa;
assign valid = cur_valid;
assign wd = in;
assign out = rd0;
assign full = cur_full;
assign emp = cur_empty;

sedg edge1(clk,enq,enq1);
sedg edge2(clk,deq,deq1);

endmodule

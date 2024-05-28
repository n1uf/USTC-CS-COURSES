module SDU(
    input clk,rst,
    input [7:0] valid,
    input [3:0] rd1,
    input empty,
    output [2:0] ra1,
    output [2:0] an,
    output [3:0] seg
    );
reg [4:0] cnt;
reg [2:0] n_cnt1,cur_cnt1; // 八位，为下一个（当前）数据的地址
reg [2:0] n_an,cur_an;
reg [3:0] n_seg,cur_seg;

always @(posedge clk or posedge rst)
begin
    if (rst) cnt <= 0;
    else cnt <= cnt + 1;
end


always @(posedge clk or posedge rst)
begin
	if (rst) // 复位
	begin
		cur_an <= 0;
		cur_seg <= 0;
		cur_cnt1 <= 0;
	end
	else // 赋值
	begin
		cur_cnt1 <= n_cnt1;
		cur_an <= n_an;
		cur_seg <= n_seg;
    end
end

always @(*)
begin
	if (cnt == 1) // rst后第一个输入的数据
	begin
		n_cnt1 = cur_cnt1 + 1;
		if (empty) // 队列空
		begin 	// 按照要求写出的an和seg均为0
			n_an = 0;
			n_seg = 0;
		end
		else if (valid[cur_cnt1]) // 当前位数据有效
		begin 	// 读出当前数码管位置和数据给下一位
			n_an = cur_cnt1;
		    n_seg = rd1;
		end
		else // 队列非空且当前数据无效
		begin 
			n_an = cur_an;
			n_seg = cur_seg;
		end
	end
	else // 其他数据
	begin
		n_cnt1 = cur_cnt1;
		n_an = cur_an;
		n_seg = cur_seg;
	end
end

assign ra1 = cur_cnt1;
assign an = cur_an;
assign seg = cur_seg;

endmodule
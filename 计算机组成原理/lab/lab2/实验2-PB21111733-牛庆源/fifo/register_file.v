module register_file //三端口32 xWIDTH寄存器堆
#(parameter WIDTH = 4) //数据宽度和存储器深度
(   input clk, //时钟（上升沿有效）
    input[2 : 0] ra0, //读端口0地址
    output[WIDTH - 1 : 0] rd0, //读端口0数据
    input[2: 0] ra1, //读端口1地址
    output[WIDTH - 1 : 0] rd1, //读端口1数据
    input[2 : 0] wa, //写端口地址
    input we, //写使能，高电平有效
    input[WIDTH - 1 : 0] wd //写端口数据
);

    reg [WIDTH - 1 : 0] regfile[0 : 7];
    assign rd0 = regfile[ra0];
    assign rd1 = regfile[ra1];

always @ (posedge clk) begin
    if (we) 
        if (wa == 0) 
            regfile[wa] <= 0;
        else 
            regfile[wa] <= wd;
    else
        regfile[0] <= 0;
end
endmodule
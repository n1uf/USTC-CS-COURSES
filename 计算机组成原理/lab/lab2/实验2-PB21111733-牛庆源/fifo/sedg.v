module sedg(
    input clk, in,
    output out
    );
    reg out1, out2;
    
    always@(posedge clk)
    begin
        out1 <= in;
        out2 <= out1;
    end
    
    assign out = out1 && ~out2;
    
endmodule
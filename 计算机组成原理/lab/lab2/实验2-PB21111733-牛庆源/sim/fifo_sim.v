module fifo_sim(

    );
    
    reg clk,rst,enq,deq;
    reg [3:0] in;
    
    wire [3:0] out;
    wire full,empty;
    wire [2:0] an;
    wire [3:0] seg;
    //reg [2:0] an;
    //reg [3:0] seg;
    
    fifo ff(clk,rst,enq,in,deq,out,full,empty,an,seg);
    initial begin
        clk = 0;
        forever #5 clk = ~ clk; 
    end
            
    initial begin
        #10000 $finish;
    end
    
    initial begin
        rst = 0;
        enq = 0;
        deq = 0;
        in = 3;
        #5 rst = 1;
        #5 rst = 0;
        #2 enq = 1;
        #20 enq = 0;
        #5 enq = 1;
        #20 enq = 0;
        #2 in = 7;
        #10 enq = 1;
        #20 enq = 0;
        #10 enq = 1;
        #20 enq = 0;
        #10 enq = 1;
        #20 enq = 0;
        #10 enq = 1;
        #20 enq = 0;
        #10 enq = 1;
        #20 enq = 0;
        #10 enq = 1;
        #20 enq = 0;
        #10 enq = 1;
        #20 enq = 0;      
        
        #100 deq = 1;
        #20 deq = 0;
        
        
        #10 deq = 1;
        #20 deq = 0;
        #10 deq = 1;
        #20 deq = 0;
        #10 deq = 1;
        #20 deq = 0;
        #10 deq = 1;
        #20 deq = 0;
        #10 deq = 1;
        #20 deq = 0;
 		#10 deq = 1;
		#20 deq = 0;
        #10 deq = 1;
 		#20 deq = 0;
        #10 deq = 1;
        #20 deq = 0;
        #10 deq = 1;
        #20 deq = 0;
        #10 deq = 1;
        #20 deq = 0;
        
    end
endmodule
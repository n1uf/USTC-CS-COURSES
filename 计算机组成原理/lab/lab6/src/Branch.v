`timescale 1ns / 1ps

module Branch(
input [31:0] op1,
input [31:0] op2,
input [2:0] br_type,
output reg br
);

parameter beq=3'd1;
parameter blt=3'd2;
parameter bne=3'd3;
parameter bge=3'd4;
parameter bltu=3'd5;
parameter bgeu=3'd6;
parameter NAN=3'd0;

always@(*)
begin
    case(br_type)
    beq:
    begin
    if(op1 == op2)
       br = 1;
    else
       br = 0;
    end

    bne:
    begin
    if(op1 != op2)
       br = 1;
    else
       br = 0;    
    end

    blt:
    begin
    if($signed(op1) < $signed(op2))
      br = 1;
    else
      br = 0;
    end

    bge:
    begin
    if($signed(op1) > $signed(op2))
      br = 1;
    else
      br = 0;
    end

    bltu:
    begin
    if(op1 < op2)
      br = 1;
    else
      br = 0;
    end

    bgeu:
    begin
     if(op1 > op2)
      br = 1;
    else
      br = 0;
    end

    NAN:
    begin
      br = 0;
    end
    
    endcase
end
endmodule

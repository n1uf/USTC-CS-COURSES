`timescale 1ns / 1ps

module CTRL(
input [31:0] inst,
output reg jal,
output reg jalr,
output reg [2:0] br_type,
output reg wb_en,
output reg [1:0] wb_sel,
output reg [1:0] alu_op1_sel,
output reg alu_op2_sel,
output reg [3:0] alu_ctrl,
output reg [2:0] imm_type,
output reg mem_write_en
);

//ALU计算方式的选择
parameter alu_add=4'd0;
parameter alu_sub=4'd1;
parameter alu_and=4'd2;
parameter alu_or=4'd3;
parameter alu_xor=4'd4;
parameter alu_compare=4'd5;
parameter alu_compare_u=4'd6;
parameter alu_left_logic=4'd7;
parameter alu_right_logic=4'd8;
parameter alu_left_count=4'd9;
parameter alu_right_count=4'd10;
parameter alu_wrong_input=4'd11;

//写入寄存器堆的内容的选择
parameter write_back_choose_NAN=2'd0;
parameter write_back_choose_pc_add4=2'd1;
parameter write_back_choose_alu_res=2'd2;
parameter write_back_choose_mem_read_data=2'd3;

//ALUop1的选择
parameter op1_choose_rd0=2'd0;
parameter op1_choose_pc=2'd1;
parameter op1_choose_zero=2'd3;

//ALUop2的选择
parameter op2_choose_rd1=1;
parameter op2_choose_imm=0;

//imm种类的选择
parameter imm_type_I=4'd1;
parameter imm_type_Ishamt=4'd2;
parameter imm_type_B=4'd3;
parameter imm_type_S=4'd4;
parameter imm_type_U=4'd5;
parameter imm_type_J=4'd6;
parameter imm_type_NAN=4'd0;

//br种类的选择
parameter br_type_NAN=3'd0;
parameter br_type_beq=3'd1;
parameter br_type_bne=3'd2;
parameter br_type_blt=3'd3;
parameter br_type_bge=3'd4;
parameter br_type_bltu=3'd5;
parameter br_type_bgeu=3'd6;

//操作码的不同情况区分指令
parameter op1_U_lui=7'b0110111;
parameter op1_U_auipc=7'b0010111;
parameter op1_J_jal=7'b1101111;
parameter op1_I_jalr=7'b1100111;
parameter op1_I_type1=7'b0000011;
parameter op1_I_type2=7'b0010011;
parameter op1_B=7'b1100011;
parameter op1_S=7'b0100011;
parameter op1_R=7'b0110011;

parameter op2_I_type1_lw=3'b010;
parameter op2_I_type2_addi=3'b000;
parameter op2_I_type2_slti=3'b010;
parameter op2_I_type2_sltiu=3'b011;
parameter op2_I_type2_xori=3'b100;
parameter op2_I_type2_ori=3'b110;
parameter op2_I_type2_andi=3'b111;
parameter op2_Ishamt_slli=3'b001;
parameter op2_Ishamt_srli=3'b101;
parameter op2_Ishamt_srai=3'b101;
parameter op2_B_beq=3'b000;
parameter op2_B_bne=3'b001;
parameter op2_B_blt=3'b100;
parameter op2_B_bge=3'b101;
parameter op2_B_bltu=3'b110;
parameter op2_B_bgeu=3'b111;
parameter op2_S_sw=3'b010;
parameter op2_R_add=3'b000;
parameter op2_R_sub=3'b000;
parameter op2_R_sll=3'b001;
parameter op2_R_slt=3'b010;
parameter op2_R_sltu=3'b011;
parameter op2_R_xor=3'b100;
parameter op2_R_srl=3'b101;
parameter op2_R_sra=3'b101;
parameter op2_R_or=3'b110;
parameter op2_R_and=3'b111;

parameter op3_Ishamt_srli=6'b000000;
parameter op3_Ishamt_srai=6'b010000;
parameter op3_R_add=7'b0000000;
parameter op3_R_sub=7'b0100000;
parameter op3_R_srl=7'b0000000;
parameter op3_R_sra=7'b0100000;
parameter op3_R_else=7'b0000000;

always@(*)
begin
    //jal赋值
    begin
        if(inst[6:0]==op1_J_jal)
        jal = 1;
        else
        jal = 0;
    end

    //jalr赋值
    begin
        if(inst[6:0]==op1_I_jalr)
        jalr = 1;
        else
        jalr = 0;
    end
    //br_type赋值
    begin
    if(inst[6:0]==op1_B)
    begin
        case(inst[14:12])
        op2_B_beq:br_type = br_type_beq;
        op2_B_bge:br_type = br_type_bge;
        op2_B_blt:br_type = br_type_blt;
        op2_B_bne:br_type = br_type_bne;
        op2_B_bltu:br_type = br_type_bltu;
        op2_B_bgeu:br_type = br_type_bgeu;
        endcase
    end
    else 
    br_type = br_type_NAN;
    end

    //wb_en赋值
    begin
      if(inst[6:0]==op1_B|inst[6:0]==op1_S)
      wb_en = 0;
      else
      wb_en = 1;
    end

    //wb_sel赋值
    begin
      case(inst[6:0])
      op1_B:wb_sel = write_back_choose_NAN;
      op1_S:wb_sel = write_back_choose_NAN;
      op1_U_lui:wb_sel = write_back_choose_alu_res;
      op1_U_auipc:wb_sel = write_back_choose_alu_res;
      op1_J_jal:wb_sel = write_back_choose_pc_add4;
      op1_I_jalr:wb_sel = write_back_choose_pc_add4;
      op1_I_type1:wb_sel = write_back_choose_mem_read_data;
      op1_I_type2:wb_sel = write_back_choose_alu_res;
      op1_R:wb_sel = write_back_choose_alu_res;
      default:wb_sel = write_back_choose_NAN;
      endcase
    end

    //alu_op1_sel赋值
    begin
    case(inst[6:0])
    op1_I_jalr:alu_op1_sel = op1_choose_rd0;
    op1_I_type1:alu_op1_sel = op1_choose_rd0;
    op1_I_type2:alu_op1_sel = op1_choose_rd0;
    op1_R:alu_op1_sel = op1_choose_rd0;
    op1_S:alu_op1_sel = op1_choose_rd0;
    op1_B:alu_op1_sel = op1_choose_pc;
    op1_U_auipc:alu_op1_sel = op1_choose_pc;
    op1_U_lui:alu_op1_sel = op1_choose_zero;
    op1_J_jal:alu_op1_sel = op1_choose_pc;
    default:alu_op1_sel = op1_choose_zero;
    endcase  
    end

    //alu_op2_sel赋值
    begin
    if(inst[6:0]==op1_R)
    alu_op2_sel = op2_choose_rd1;
    else
    alu_op2_sel = op2_choose_imm;
    end

    //alu_ctrl赋值
    begin
      case(inst[6:0])
      op1_U_lui:alu_ctrl = alu_add;
      op1_U_auipc:alu_ctrl = alu_add;
      op1_J_jal:alu_ctrl = alu_add;
      op1_I_jalr:alu_ctrl = alu_add;
      op1_B:alu_ctrl = alu_add;
      op1_I_type1:alu_ctrl = alu_add;
      op1_S:alu_ctrl = alu_add;
      op1_I_type2:
        begin
        case(inst[14:12])
        op2_I_type2_addi:alu_ctrl = alu_add;
        op2_I_type2_slti:alu_ctrl = alu_compare;
        op2_I_type2_sltiu:alu_ctrl = alu_compare_u;
        op2_I_type2_xori:alu_ctrl = alu_xor;
        op2_I_type2_ori:alu_ctrl = alu_or;
        op2_I_type2_andi:alu_ctrl = alu_and;
        op2_Ishamt_slli:alu_ctrl = alu_left_logic;
        op2_Ishamt_srli:
        begin
            if(inst[31:26]==op3_Ishamt_srli)
            alu_ctrl = alu_right_logic;
            else if(inst[31:26]==op3_Ishamt_srai)
            alu_ctrl = alu_right_count;
            else 
            alu_ctrl = alu_wrong_input;
        end
        default:alu_ctrl = alu_wrong_input;
        endcase
        end
      op1_R:
        begin
        case(inst[14:12])
        op2_R_add:
        begin
         if(inst[31:25]==op3_R_add)
          alu_ctrl = alu_add;
          else
        alu_ctrl = alu_sub;
        end
        op2_R_sll:alu_ctrl = alu_left_logic;
        op2_R_slt:alu_ctrl = alu_compare;
        op2_R_sltu:alu_ctrl = alu_compare_u;
        op2_R_xor:alu_ctrl = alu_xor;
        op2_R_srl:
        begin
            if(inst[31:25]==op3_R_srl)
            alu_ctrl = alu_right_logic;
            else if(inst[31:25]==op3_R_sra)
            alu_ctrl = alu_right_count;
            else
            alu_ctrl = alu_wrong_input;
        end
        op2_R_or:alu_ctrl = alu_or;
        op2_R_and:alu_ctrl = alu_and;
        default:alu_ctrl = alu_wrong_input;
        endcase
        end
      default:alu_ctrl = alu_wrong_input;
      endcase
    end

    //imm_type赋值
    begin
    case(inst[6:0])
    op1_I_jalr:imm_type = imm_type_I;
    op1_I_type1:imm_type = imm_type_I;
    op1_I_type2:
    begin
      if(inst[14:12]==op2_Ishamt_slli|inst[14:12]==op2_Ishamt_srai|inst[14:12]==op2_Ishamt_srli)
      imm_type = imm_type_Ishamt;
      else
      imm_type = imm_type_I;
    end
    op1_B:imm_type = imm_type_B;
    op1_S:imm_type = imm_type_S;
    op1_U_lui:imm_type = imm_type_U;
    op1_U_auipc:imm_type = imm_type_U;
    op1_J_jal:imm_type = imm_type_J;
    default:imm_type = imm_type_NAN;        
    endcase
    end

    //mem_write_en赋值
    begin
      if(inst[6:0]==op1_S)
      mem_write_en = 1;
      else
      mem_write_en = 0;
    end

end
endmodule
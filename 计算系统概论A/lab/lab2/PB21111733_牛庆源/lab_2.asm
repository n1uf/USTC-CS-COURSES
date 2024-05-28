        .ORIG x3000
        LD    R0, #255      ;将p存入R0
        LD    R1, #255      ;将q存入R1
        LD    R2, #255      ;将N存入R2
        NOT   R0, R0
        ADD   R0, R0, #1    ;-p的补码
        NOT   R1, R1      
        ADD   R1, R1, #1    ;-q的补码
        ADD   R3, R3, #1    ;R3为F(N-1)，初始化为1
        ADD   R4, R4, #1    ;R4为F(N-2)，初始化为1
        ADD   R2, R2, #-2   ;N变为N-2(已经赋值了F(1)和F(2))
STAR0   ADD   R5, R3, #0
STAR1   ADD   R6, R5, #0    ;R6中存F(N-1) % q
        ADD   R5, R5, R1  
        BRn   STAR2
        ADD   R6, R5, #0
        BRzp  STAR1
STAR2   ADD   R5, R4, #0    ;R7中存F(N-2) % p
        ADD   R7, R5, #0
STAR3   ADD   R5, R5, R0
        BRn   STAR4
        ADD   R7, R5, #0
        BRzp  STAR3
STAR4   ADD   R5, R6, R7    ;R5记录计算得到的F(N)
        ADD   R4, R3, #0    ;F(N-1)赋给F(N-2)
        ADD   R3, R5, #0    ;F(N)赋给F(N-1)
        ADD   R2, R2, #-1   ;循环次数递减
        BRzp  STAR0       
        ST    R5, #231
        HALT
        .END
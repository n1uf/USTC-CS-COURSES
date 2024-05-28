        .ORIG x3000
        LD    R0, #255    ;将p存入R0
        LD    R1, #255    ;将q存入R1
        LD    R2, #255    ;将N存入R2
        NOT   R0, R0
        ADD   R0, R0, #1  ;p的补码
        NOT   R1, R1      
        ADD   R1, R1, #1  ;q的补码
        ADD   R3, R3, #1  ;R3为F(N-1)，初始化为1
        ADD   R4, R4, #1  ;R4为F(N-2)，初始化为1
        ADD   R2, R2, #-2 ;这里将N减2是因为初始化已经计入两次
        ADD   R5, R3, #0
        BRnzp STAR1
STAR0   ADD   R4, R3, #0  ;将上次的F(N)赋给这次的F(N-1)
        ADD   R3, R6, #0  ;将上次的F(N-1)赋给这次的F(N-2)
        ADD   R5, R3, #0  
STAR1   ADD   R6, R5, #0  ;对F(N-1)取模q，结果存在R6中
        ADD   R5, R5, R1  
        BRn   STAR2
        ADD   R6, R5, #0
        BRzp  STAR1
STAR2   ADD   R5, R4, #0  ;对F(N-2)取模p，结果存在R7中
        ADD   R7, R5, #0
STAR3   ADD   R5, R5, R0
        BRn   STAR4
        ADD   R7, R5, #0
        BRzp  STAR3
STAR4   ADD   R6, R6, R7  ;R6记录当前F(N)
        ADD   R2, R2, #-1 ;循环次数递减
        BRzp  STAR0       
        ST    R6, #229
        HALT
        .END

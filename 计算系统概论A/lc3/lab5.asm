.ORIG x800
        ; (1) Initialize interrupt vector table.
        LD R0, VEC
        LD R1, ISR
        STR R1, R0, #0

        ; (2) Set bit 14 of KBSR.
        LDI R0, KBSR
        LD R1, MASK
        NOT R1, R1
        AND R0, R0, R1
        NOT R1, R1
        ADD R0, R0, R1
        STI R0, KBSR

        ; (3) Set up system stack to enter user space.
        LD R0, PSR
        ADD R6, R6, #-1
        STR R0, R6, #0
        LD R0, PC
        ADD R6, R6, #-1
        STR R0, R6, #0
        ; Enter user space.
        RTI
        
VEC     .FILL x0180
ISR     .FILL x1000
KBSR    .FILL xFE00
MASK    .FILL x4000
PSR     .FILL x8002
PC      .FILL x3000
        .END

        .ORIG x3000
        ; *** Begin user program code here ***
LOOP    LD R0, ADDR ;
        LDR R1, R0, #1
        ADD R1, R1, #0
        BRz PRINT;若R1为合法输入(数字)则继续，否则跳转到输出学号
        LDR R1, R0, #0;R1为数字
        AND R3, R3, #0;R3 = 0
        JSR HANOI;//
        LEA R0, OUT3
        TRAP x22
        JSR OUTPUT
        LEA R0, OUT4
        TRAP x22
        HALT
        
PRINT   LEA R0, idOUT
        TRAP x22
        JSR DELAY;先经过delay例程避免循环输出过快
        BR LOOP;输出学号后继续跳转到循环过程
        
HANOI   STR R7, R6, #0
        ADD R1, R1, #-1;R1为从键盘读入的合法数字
        BRn RECURSIVE
        STR R1, R6, #-1
        ADD R6, R6, #-2
        JSR HANOI
        ADD R6, R6, #1
        LDR R7, R6, #0
        ADD R3, R3, R3
        ADD R3, R3, #1
        
RECURSIVE ADD R6, R6, #1;指针移动
        LDR R1, R6, #0;取R1
        RET
        
OUTPUT  ST R0, SAVER0
        ST R1, SAVER1
        ST R2, SAVER2
        ADD R2, R3 #0
        LD R1, NUM100
        NOT R1, R1
        ADD R1, R1, #1
        AND R0, R0, #0
        
MINUS1  ADD R0, R0, #1
        ADD R2, R2, R1
        BRzp MINUS1
        NOT R1, R1
        ADD R1, R1, #1
        ADD R2, R2, R1
        ADD R0, R0, #-1;循环多了一次
        BRnz JUMP;跳过百位
        LD R1, zero
        ADD R0, R0, R1
        TRAP x21
        
JUMP    LD R1 NUM10
        AND R0, R0, #0
        NOT R1, R1
        ADD R1, R1, #1
        
MINUS2  ADD R0, R0, #1
        ADD R2, R2, R1
        BRzp MINUS2
        NOT R1, R1
        ADD R1, R1, #1
        ADD R2, R2, R1
        ADD R0, R0, #-1
        BRnz JUMP2;跳过十位
        LD R1, zero
        ADD R0, R0, R1
        TRAP x21
        
JUMP2   ADD R0, R2 #0
        LD R1, zero
        ADD R0, R0, R1
        TRAP x21
        LD R0, SAVER0
        LD R1, SAVER1
        LD R2, SAVER2
        RET
        
DELAY   ST R1, SAVER1
        LD R1, COUNT;每次延迟count后输出一次
REP     ADD R1, R1, #-1
        BRp REP
        LD R1, SAVER1
        RET

idOUT .STRINGZ "PB21111733 "
OUT3 .STRINGZ "Tower of hanoi needs "
OUT4 .STRINGZ " moves.\n"
ADDR .FILL x3FFF
SAVER0 .FILL x0000
SAVER1 .FILL x0000
SAVER2 .FILL x0000
COUNT .FILL x2500;延迟量
NUM100 .FILL #100
NUM10 .FILL #10
zero .FILL x30
.END
; *** End user program code here ***

        .ORIG x3FFF
        ; *** Begin honoi data here ***
HONOI_N .FILL xFFFF
        ; *** End honoi data here ***
        .END

        .ORIG x1000
        ; *** Begin interrupt service routine code here ***
        LDI R1, KBSR1;检查是否从键盘读入内容
        LD R2, MASK_1;xc000
        AND R1, R1, R2
        BRz EXIT
        
        LDI R1, KBDR1;读入了内容
        LD R2, MASK_2;x00ff
        AND R1, R1, R2;取后8位 
        LD R2, NUM0;数字0的ASCII码
        ADD R2, R1, R2;判断是否大于0的ASCII码
        BRn OUTPUT2;从键盘读取的内容不进入汉诺塔例程
        LD R2, NUM9;数字9的ASCII码
        ADD R2, R1, R2;判断是否小于9的ASCII码
        BRp OUTPUT2
        LD R0, LF;是合法的数字输入，则存到Honoi_n并且更新
        TRAP x21
        ADD R0, R1, #0; R0 = R1
        TRAP x21
        LEA R0, OUT2
        TRAP x22
        LD R3, ADDR1;汉诺塔输入存放
        LD R2, NUM0
        ADD R1, R1, R2;// R1 = R1 - 48此时从ASCII码转化为数字
        STR R1, R3, #0
        LDR R1, R3, #1;以下将number都设为1
        ADD R1, R1, #1
        STR R1, R3, #1
        RET

OUTPUT2 LD R0, LF
        TRAP x21
        ADD R0, R1, #0;R0 = R1
        TRAP x21;
        LEA R0, OUT1
        TRAP x22
        BR EXIT
EXIT
        RTI
        
MASK_1  .FILL xc000
MASK_2  .FILL x00ff
NUM0    .FILL #-48
NUM9    .FILL #-57
NUMADD .FILL x30
LF      .STRINGZ "\n"
OUT1    .STRINGZ " is not a decimal number!\n"
OUT2    .STRINGZ " is a decimal number!\n"
KBSR1   .FILL xFE00
KBDR1   .FILL xFE02
ADDR1   .FILL x3FFF
; *** End interrupt service routine code here ***
.END

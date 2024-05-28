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
LOOP LD R0 ADDR ;
LDR R1 R0 #1
ADD R1 R1 #0
BRz PRINT;//若为0 则就执行打印学号 若存入数字说明已经存在合格的汉诺塔输入值
LDR R1 R0 #0;//R1 = number
AND R3 R3 #0;//R3 = 0
JSR HANOI;//
LEA R0 OUT3
TRAP x22
JSR OUTPUT ;//
LEA R0 OUT4
TRAP x22
HALT
PRINT LEA R0 idOUT
TRAP x22
JSR DELAY
BR LOOP
HANOI STR R7 R6 #0
ADD R1 R1 #-1;//R1为输入后的转换值
BRn RECURSIVE;//栈
STR R1 R6 #-1
ADD R6 R6 #-2
JSR HANOI
ADD R6 R6 #1
LDR R7 R6 #0
ADD R3 R3 R3
ADD R3 R3 #1
RECURSIVE ADD R6 R6 #1;//将栈指针回退一位
LDR R1 R6 #0;//回到可取的那一位 取入R1
RET
OUTPUT ST R0, SAVER0;//有点参考网络上的对数字和相对应ASCII码的转化
ST R1 SAVER1
ST R2 SAVER2
ADD R2 R3 #0
LD R1 neg;//R1赋为-100
AND R0 R0 #0
MINUS ADD R0 R0 #1
ADD R2 R2 R1
BRzp MINUS;//举例说明200 200-100=100 1 100-100=0 2 0-100=-100<0 3跳出
NOT R1 R1
ADD R1 R1 #1
ADD R2 R2 R1
ADD R0 R0 #-1;//因为循环本身大了1 所以减一
BRnz #3;//若为0或负 则可以跳过百位的打印
LD R1 zero
ADD R0 R0 R1
TRAP x21
AND R1 R1 #0
ADD R1 R1 #-10;//和上面的LD R1 neg类似 不过本处较小所以直接计算得出
AND R0 R0 #0
MINUS2 ADD R0,R0,#1
ADD R2,R2,R1
BRzp MINUS2
NOT R1 R1
ADD R1 R1 #1
ADD R2 R2 R1
ADD R0 R0  #-1
BRnz #3
LD R1 zero
ADD R0 R0 R1
TRAP x21
ADD R0 R2 #0
LD R1 zero
ADD R0 R0 R1
TRAP x21;//后面的处理分别为十位 个位与百位相似，就是每次递减10 1 然后打印出来
LD R0 SAVER0
LD R1 SAVER1
LD R2 SAVER2
RET
DELAY
ST R1 SaveR1;//将R1保存在saveR1中
LD R1 COUNT;//R1用作计数器
REP ADD R1 R1 #-1
BRp REP
LD R1 SaveR1
RET

idOUT .STRINGZ "PB21111733 "
OUT3 .STRINGZ "Tower of hanoi needs "
OUT4 .STRINGZ " moves.\n"
ADDR .FILL x3FFF
SAVER0 .FILL x0000
SAVER1 .FILL x0000
SAVER2 .FILL x0000
COUNT .FILL x2500;//修改延迟量
NUM100 .FILL #100
neg .FILL #-100
zero .FILL x30;0的ASCII码
; *** End user program code here ***
.END

        .ORIG x3FFF
        ; *** Begin honoi data here ***
HONOI_N .FILL xFFFF
        ; *** End honoi data here ***
        .END

.ORIG x1000
; *** Begin interrupt service routine code here ***
LDI R1 KBSR1;//键盘中断后 存入ASCII码
LDI R1 KBDR1
LD R2 MASK_2;0000 0000 1111 1111 
AND R1 R1 R2;取后8位 
LD R2 NUM0
ADD R2 R1 R2; //判断0--9
BRn OUTPUT2
LD R2 NUM9;//意思为 a<9&&a>0 否则继续
ADD R2 R1 R2; 
BRp OUTPUT2;//判断0--9
LD R0 LF
TRAP x21
ADD R0 R1 #0; R0 = R1
TRAP x21
LEA R0 OUT2
TRAP x22
LD R3 ADDR1;//若合格打印后 汉诺塔有效值存放处
LD R2 NUM0
ADD R1 R1 R2;// R1 = R1 - 48此时从ASCII码转化为数字
STR R1 R3 #0;//且如此后则再不会执行打印学号操作
LDR R1 R3 #1
ADD R1 R1 #1
STR R1 R3 #1
RET

OUTPUT2 LD R0 LF
TRAP x21
ADD R0 R1 #0;R0 = R1
TRAP x21;//因为此时仍非合法输入，所以回到主程序继续
LEA R0 OUT1
TRAP x22
BRnzp EXIT
EXIT
RTI
MASK_1 .FILL xC000
MASK_2 .FILL x00ff
NUM0 .FILL #-48
NUM9 .FILL #-57
NUMADD .FILL x30
LF .STRINGZ "\n"
OUT1 .STRINGZ " is not a decimal number!\n"
OUT2 .STRINGZ " is a decimal number!\n"
KBSR1 .FILL xFE00
KBDR1 .FILL xFE02
ADDR1 .FILL x3FFF
; *** End interrupt service routine code here ***
.END

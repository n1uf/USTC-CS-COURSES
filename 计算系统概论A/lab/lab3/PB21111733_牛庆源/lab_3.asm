        .ORIG   x3000
        LDI     R0, NUM             ;R0初始化为N
        LD      R1, DATA            ;R1为指针，初始化为DATA首地址
        LDR     R2, R1, #0          ;R2为R1指向的字符
        
TEST    ADD     R0, R0, #-1         ;每次检测char之后，N--
        BRz     OUTPUT              ;如果减到0则跳转到输出
        
GETCHAR ADD     R1, R1, #1          ;移动指针位置
        LDR     R3, R1, #0          ;获取下一个字符
        NOT     R2, R2
        ADD     R2, R2, R3          ;如果R2和R3相同，则R2结果为xffff
        NOT     R2, R2              ;如果R2和R3相同，则R2结果为x0000
        BRnp    FALSE               ;如果不相同
        
        ADD     R6, R6, #1          ;存储当前连续相同字符长度结果的R6++
        NOT     R5, R6
        ADD     R5, R5, #1          ;得到-R6的补码存在R5中
        ADD     R5, R7, R5          ;R7-R6存在R5中
        BRnz    UPDATE              ;如果R7<R6
        BRnzp   MOVE                ;更新当前字符和检查是否到字符串尾部
        
FALSE   AND     R6, R6, #0          ;否则R6清零
        BRnzp   MOVE                ;更新当前字符和检查是否到字符串尾部
        
UPDATE  ADD     R7, R6, #0          ;将当前R7更新为最大的长度
        BRnzp   MOVE                ;更新当前字符和检查是否到字符串尾部
        
MOVE    LDR     R2, R1, #0          ;R2赋值为当前指针所指的字符（R3）
        BRnzp   TEST                ;检查是否到字符串尾部
        
OUTPUT  ADD     R7, R7, #1          ;最终结果+1（因为从0开始计数的）
        STI     R7, RESULT          ;存在指定位置
        TRAP    x25                 ;HALT
        
        RESULT  .FILL x3050
        NUM     .FILL x3100
        DATA    .FILL x3101
        .END
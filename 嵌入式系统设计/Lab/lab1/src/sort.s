    AREA    |.text|, CODE, READONLY

    EXPORT sort_strings

sort_strings
    STMFD   sp!, {r4-r11, lr}   ; 保存寄存器
    
    MOV     r4, r0              ; 保存数组指针
    MOV     r5, r1              ; 保存数组长度

outer_loop
    MOV     r6, #0              ; i = 0
    SUB     r7, r5, #1          ; limit = length - 1
    MOV     r8, #0              ; swapped = false

inner_loop
    CMP     r6, r7
    BGE     inner_loop_end

    ; 加载相邻字符串指针
    LDR     r9, [r4, r6, LSL #2]    ; str1
    ADD     r10, r6, #1
    LDR     r10, [r4, r10, LSL #2]  ; str2

    ; 找到薪水部分并转换为整数
    MOV     r0, r9
    BL      find_salary_asm
    MOV     r11, r0             ; salary1

    MOV     r0, r10
    BL      find_salary_asm     ; salary2 在 r0 中

    ; 比较薪水
    CMP     r11, r0
    BLT     swap                ; 如果 salary1 < salary2, 交换 (高薪在前)
    BNE     no_swap             ; 如果不相等, 无需比较姓名

    ; 薪水相等，逐字符比较姓名
    MOV     r0, r9
    MOV     r1, r10
    BL      compare_name_asm
    CMP     r0, #0
    BLE     no_swap             ; 如果 str1 <= str2, 不交换

swap
    ; 交换字符串指针
    STR     r10, [r4, r6, LSL #2]
    ADD     r10, r6, #1
    STR     r9, [r4, r10, LSL #2]
    MOV     r8, #1              ; swapped = true

no_swap
    ADD     r6, r6, #1          ; i++
    B       inner_loop

inner_loop_end
    CMP     r8, #0              ; 检查是否发生了交换
    BNE     outer_loop          ; 如果发生了交换，继续外层循环

    LDMFD   sp!, {r4-r11, pc}   ; 恢复寄存器并返回

; 查找并转换薪水部分为整数的函数
find_salary_asm
    STMFD   sp!, {r4, r5, lr}   ; 保存寄存器
    MOV     r4, r0              ; 保存字符串指针
    MOV     r5, #0              ; 初始化薪水值为0

salary_loop
    LDRB    r1, [r4], #1
    CMP     r1, #'-'            ; 查找 '-' 符号
    BNE     salary_loop

    ; 读取并转换薪水部分
convert_loop
    LDRB    r1, [r4], #1
    CMP     r1, #'0'            ; 检查是否为数字字符
    BLT     convert_end
    CMP     r1, #'9'
    BGT     convert_end

    ; 计算薪水的整数值: salary = salary * 10 + (r1 - '0')
    SUB     r1, r1, #'0'        ; 将 ASCII 字符转换为整数
    MOV     r2, r5, LSL #3      ; r2 = r5 * 8（左移 3 位相当于乘以 8）
    ADD     r5, r2, r5, LSL #1  ; r5 = r2 + (r5 * 2) = r5 * 10
    ADD     r5, r5, r1          ; r5 = r5 + 当前数字
    B       convert_loop

convert_end
    MOV     r0, r5              ; 返回薪水整数值
    LDMFD   sp!, {r4, r5, pc}   ; 恢复寄存器并返回

; 比较姓名的函数
compare_name_asm
    STMFD   sp!, {r4, r5, r6, lr} ; 保存寄存器
    MOV     r4, r0              ; 保存 str1 指针
    MOV     r5, r1              ; 保存 str2 指针

name_compare_loop
    LDRB    r1, [r4], #1
    LDRB    r2, [r5], #1
    CMP     r1, r2              ; 比较字符
    BNE     name_compare_end

    ; 检查是否到达字符串末尾
    CMP     r1, #0
    BEQ     name_compare_equal   ; 如果两者相等且结束，返回相等

    B       name_compare_loop

name_compare_end
    ; r1 - r2 的结果用于比较
    SUB     r0, r1, r2
    B       compare_exit

name_compare_equal
    MOV     r0, #0              ; 字符串相等

compare_exit
    LDMFD   sp!, {r4, r5, r6, pc} ; 恢复寄存器并返回

    END

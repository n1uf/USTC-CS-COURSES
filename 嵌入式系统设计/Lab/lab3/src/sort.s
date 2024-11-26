    .section .text
    .global sort_strings

sort_strings:
    push {r4-r11, lr}           @ 保存寄存器

    mov r4, r0                  @ 保存数组指针
    mov r5, r1                  @ 保存数组长度

outer_loop:
    mov r6, #0                  @ i = 0
    sub r7, r5, #1              @ limit = length - 1
    mov r8, #0                  @ swapped = false

inner_loop:
    cmp r6, r7
    bge inner_loop_end

    @ 加载相邻字符串指针
    ldr r9, [r4, r6, lsl #2]    @ str1
    add r10, r6, #1
    ldr r10, [r4, r10, lsl #2]  @ str2

    @ 找到薪水部分并转换为整数
    mov r0, r9
    bl find_salary_asm
    mov r11, r0                 @ salary1

    mov r0, r10
    bl find_salary_asm          @ salary2 在 r0 中

    @ 比较薪水
    cmp r11, r0
    blt swap                    @ 如果 salary1 < salary2, 交换 (高薪在前)
    bne no_swap                 @ 如果不相等, 无需比较姓名

    @ 薪水相等，逐字符比较姓名
    mov r0, r9
    mov r1, r10
    bl compare_name_asm
    cmp r0, #0
    ble no_swap                 @ 如果 str1 <= str2, 不交换

swap:
    @ 交换字符串指针
    str r10, [r4, r6, lsl #2]
    add r10, r6, #1
    str r9, [r4, r10, lsl #2]
    mov r8, #1                  @ swapped = true

no_swap:
    add r6, r6, #1              @ i++
    b inner_loop

inner_loop_end:
    cmp r8, #0                  @ 检查是否发生了交换
    bne outer_loop              @ 如果发生了交换，继续外层循环

    pop {r4-r11, pc}            @ 恢复寄存器并返回

@ 查找并转换薪水部分为整数的函数
find_salary_asm:
    push {r4, r5, lr}           @ 保存寄存器
    mov r4, r0                  @ 保存字符串指针
    mov r5, #0                  @ 初始化薪水值为0

salary_loop:
    ldrb r1, [r4], #1
    cmp r1, #'-'                @ 查找 '-' 符号
    bne salary_loop

    @ 读取并转换薪水部分
convert_loop:
    ldrb r1, [r4], #1
    cmp r1, #'0'                @ 检查是否为数字字符
    blt convert_end
    cmp r1, #'9'
    bgt convert_end

    @ 计算薪水的整数值: salary = salary * 10 + (r1 - '0')
    sub r1, r1, #'0'            @ 将 ASCII 字符转换为整数
    mov r2, r5, lsl #3          @ r2 = r5 * 8（左移 3 位相当于乘以 8）
    add r5, r2, r5, lsl #1      @ r5 = r2 + (r5 * 2) = r5 * 10
    add r5, r5, r1              @ r5 = r5 + 当前数字
    b convert_loop

convert_end:
    mov r0, r5                  @ 返回薪水整数值
    pop {r4, r5, pc}            @ 恢复寄存器并返回

@ 比较姓名的函数
compare_name_asm:
    push {r4, r5, r6, lr}       @ 保存寄存器
    mov r4, r0                  @ 保存 str1 指针
    mov r5, r1                  @ 保存 str2 指针

name_compare_loop:
    ldrb r1, [r4], #1
    ldrb r2, [r5], #1
    cmp r1, r2                  @ 比较字符
    bne name_compare_end

    @ 检查是否到达字符串末尾
    cmp r1, #0
    beq name_compare_equal      @ 如果两者相等且结束，返回相等

    b name_compare_loop

name_compare_end:
    @ r1 - r2 的结果用于比较
    sub r0, r1, r2
    b compare_exit

name_compare_equal:
    mov r0, #0                  @ 字符串相等

compare_exit:
    pop {r4, r5, r6, pc}        @ 恢复寄存器并返回


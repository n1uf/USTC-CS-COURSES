
.text
add  t5, zero, zero
add  a0, zero,zero
li   a2, 32512 # 0x7f00，输入状态寄存器地址
li   a3, 32516 # 0x7f04，输入数据寄存器地址
li   s3, 48    # 0x0030，数字0的ascii码
li   s4, 69    # 0x0041, 字母E的ascii码 表示end
addi s1, zero, 1
TMP:
lw   s2, 0(a2) # 取输入状态
beq  s2, zero, TMP # 为0则等待输入（，1则继续）
lw   s5, 0(a3) # 取输入的数据
beq  s5, s4, GETN # 为A则输入结束，跳转到取n的环节
sub  s5, s5, s3 # 得到输入的数值
sw   s5, 0(a0) # 写入地址a0
addi a0, a0, 4 # 地址指针移动
addi t5, t5, 1 # t5为n的位数
addi t6, t5, 0 # t6 = t5
j    TMP

GETN:
addi a0, a0, -4 # a0前移一次
lw   s2, 0(a0) # 取a0内容到s2
li   a5, 10 # a5 = 10，为十位
sub  s5, t6, t5 #判断当前n在第几位
GETNUM:
beq  zero, s5, MUL #如果是个位
add  s1, s1, s7 #循环10次
addi a5, a5, -1
blt  zero, a5, GETNUM

MUL:
add  s6, s1, s6 # beq进入s6记录个位，之后记录10*十位
addi s2, s2, -1
blt  zero, s2, MUL 
add  t0, s6, t0 # 由beq进入的MUL中t0为个位的数值，之后为n
addi s6, zero, 0
addi s7, s1, 0 
addi s1, zero, 0 # s1 = 0
addi t5, t5, -1 # 位数--
blt  zero, t5, GETN # 判断是否取完整个n

FIB:    # 这里已经得到t0为n
addi t5, t0, 0 # t5为n
addi t1, zero, 0
addi t2, zero, 1
addi t3, zero, 1
sw   t2, 0(t1)
addi t1, t1, 4
sw   t3, 0(t1)
addi t0, t0, -2 # 已经录入了前两个数据

LOOP:
add  t4, t2, t3 # 得到下一个数据
addi t2, t3, 0 # t2 = t3
addi t3, t4, 0 # t3 = t4
addi t1, t1, 4 # 地址指针移动
sw   t4, 0(t1) # 录入下一个数据
addi t0, t0, -1 # 又录入了一个数据
blt  zero, t0, LOOP # 直到把n个数据录入完毕结束

li   s0, 32524 # 0x7f0c Display
li   s1, 10 # 0x0a # 10 换行 \n
li   s2, 13 # 0x0d # 回车 \r
li   s3, 48 # 0x30 # 数字0
li   s4, 87 # 0x57 # 
addi t0, zero, 0

PRINT:
addi t2, zero, 0
addi t3, zero, 0
lw   t1, 0(t0) # 取第一个数据
addi t2, t1, 0

SLL:
addi t3, t3, 1 # t3++
srli t2, t2, 1 # t2右移一位
blt  zero, t2, SLL # 直到取到0，t3记录该数字的位数

STAR:
addi t3, t3, -1  #t3--
blt  t3, zero, COMPARE # 直到小于0
addi t2, t1, 0 # t2仍然为第一个数据
srl  t2, t2, t3 # t2右移t3位
sll  t2, t2, t3 # t2左移t3位，只保留最高位的数
sub  t1, t1, t2 
srl  t4, t2, t3 # t4为t2右移t3位
blt  t4, s1, PRINT_NUM1 # 小于10则打印
add  t4, s4, t4 # 大于10则用字母输出
sw   t4, 0(s0) # 写入地址
jal  STAR # 跳转

PRINT_NUM1:
add  t4, s3, t4 # t4转化为ascii码的数字
sw   t4, 0(s0) # 写入地址
jal  STAR # 跳转

COMPARE:
sw   s1, 0(s0) # 换行
sw   s2, 0(s0) # 回车
addi t0, t0, 4 # 地址指针移动
addi t5, t5, -1 # t5为n--
blt  zero, t5, PRINT # 直到t5 < 0结束
ecall
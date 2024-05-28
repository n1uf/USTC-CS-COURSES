# Author: 2023_COD_TA
# Last_edit: 20230416
# ============================== 单周期 CPU 正确性测试程序 ==============================
# global pointer gp 为 x3 寄存器
# 在文件中 gp 指示当前进行的测试
# 若连续运行后pc的值为 0x0000301c 到 0x00003034，代表FAIL，这时gp指示第一个未通过的测试
# 上板可以看到 led[1] 亮起，此时程序执行异常

# 若连续运行后pc的值为 0x0000324c 到 0x00003264，代表全部测试通过
# 上板可以看到 led[0] 亮起，此时程序执行正常

# !!!!!!!!!!!!!!!! 请不要修改本测试程序的代码 !!!!!!!!!!!!!!!!!!!!!!!
# ======================================================================================


# TEST 0 addi & beq test
# 建议在此测试时单步运行 正确进入TEST1 后再连续运行
.text
	addi gp, x0, 0		# gp = 0 检测addi实现与x0设为0
	addi x5, x0, 2		# x5 = 2
	addi x6, x5, -3		# x6 = 0xffffffff
	addi x8, x6, 1000	# x8 = 0x3e7
	addi x7, x0, 999 	# x7 = 0x3e7
	beq x5, x6, FAIL	# 不应跳转
	beq x8, x7, TEST1	# 应跳转
	
FAIL:	
	lui x7 7
	addi x7 x7 0x700
	addi x7 x7 0x700
	addi x7 x7 0x100	# x7 = 7f00
	addi x8 x0 1
	sw x8 16(x7)		# led[1] = 0
	beq x0, x0, FAIL	# 失败时会在此处死循环
	
TEST1:	# add test	
	addi gp, x0, 1		# gp = 1
	addi x5, x0, 2		# x5 = 2
	addi x5, x5, 2		# x5 = 4
	add x6, x5, x5		# x6 = 8
	add x6, x6, x6		# x6 = 0x10
	addi x7, x0, 16		# x7 = 0x10
	beq x6, x7, TEST2
	beq x0, x0, FAIL
	
TEST2:	# add test II	
	addi gp, x0, 2		# gp = 2
	addi x8, x0, 9 		# x8 = 9
	add x9, x8, x0		# x9 = 9
	addi x10, x0, -9	# x10 = 0xfffffff7
	add x10, x9, x10	# x10 = 0
	beq x10, x0, TEST3
	beq x0, x0, FAIL
	
TEST3:	# lui test	
	addi gp, x0, 3		# gp = 3 
	lui x5, 3		# x5 = 0x3000
	lui x6, -2		# x6 = 0xfffffe000
	addi x7, x0, 0x400	# x7 = 0x0400
	add x5, x5, x6		# x5 = 0x1000
	add x7, x7, x7		# x7 = 0x0800
	add x7, x7, x7		# x7 = 0x1000
	beq x5, x7, TEST4
	beq x0, x0, FAIL
	
TEST4:	# auipc test	
	addi gp, x0, 4		# gp = 4
	auipc x5, 3		# x5 = 0x609c
	auipc x6, -4		# x6 = 0xfffff0a0
	add x7, x5, x6		# x7 = 0x513c
	lui x8, 5		# x8 = 0x5000
	addi x8, x8, 0x13c 	# x8 = 0x513c
	beq x7, x8, TEST5
	beq x0, x0, FAIL
	
TEST5:	# lw sw test	
	addi gp, x0, 5		# gp = 5
	lui x5, 0x12345		# x5 = 0x12345000
	addi x5, x5, 0x789	# x5 = 0x12345789
	sw x5, 40(x0)
	addi x6, x0, 32		# x6 = 0x20
	lw x7, 8(x6)		# x7 = 0x12345789
	beq x5, x7, TEST6
	beq x0, x0, FAIL
	
TEST6:	# x0 test	
	addi gp, x0, 6		# gp = 6
	addi x5, x0, 3		# x5 = 3
	addi x0, x0, 3
	beq x0, x5, FAIL
	sub x0, x0, x5 
	addi x5, x0, 2		# x5 = 2
	addi x6, x0, -1		# x6 = 0xffffffff
	beq x5, x6, FAIL
	sw x6, 8(x0)
	lw x0, 8(x0)
	addi x1, x0, 2		# x1 = 2
	beq x1, x5, TEST7
	beq x0, x0, FAIL
	
TEST7:	# lw sw test II	
	addi gp, x0, 7		# gp = 7
	addi x10, x0, 12	# x10 = 0x0c
	sw x10, 4(x10)
	addi x8, x0, 16		# x8 = 0x10
	lw x8, 0(x8)		# x8 = 0x0c
	beq x8, x10, TEST8
	beq x0, x0, FAIL
	
TEST8:	# blt test	
	addi gp, x0, 8		# gp = 8
	addi x5, x0, 1		# x5 = 1
	addi, x6, x0, 2		# x6 = 2
	addi x28, x0, 1 	# x28 = 1 可通过x28确定哪个分测试时失败
	blt x6, x5, FAIL
	addi x5, x5, 1		# x5 = 2
	addi x28, x0, 2 	# x28 = 2
	blt x6, x5, FAIL
	addi x7, x0, -1		# x7 = 0xffffffff
	addi x8, x0, -2		# x8 = 0xfffffffe
	addi x28, x0, 3 	# x28 = 3
	blt x7, x8, FAIL
	addi x9, x0, 0		# x9 = 0
	addi x28, x0, 4 	# x28 = 4
	blt x9, x7, FAIL
	addi x28, x0, 5 	# x28 = 5
	blt x5, x9, FAIL
	addi x28, x0, 6 	# x28 = 6
	blt x7, x5, TEST9
	beq x0, x0, FAIL
	
TEST9:	# jal test	
	addi gp, x0, 9		# gp = 9
	addi x5, x0, 0		# x5 = 0
L0:	jal x0, L2
	beq x0, x0, FAIL	
L1:	beq x5, x0, L3
	beq x0, x0, FAIL
L2:	jal x0, L1
	beq x0, x0, FAIL
L3:	addi x5, x0, 1		# x5 = 1
	jal x5, L4		# x5 = 0x31a0
	beq x0, x0, FAIL
L4:	auipc x6, 0		# x6 = 0x31a4
	addi x6, x6, -4		# x6 = 0x31a0
	beq x5, x6, TEST10
	beq x0, x0, FAIL
	
TEST10:	# jalr test	
	addi gp, x0, 10		# gp = 0x0a
	jal x1, L5		
	beq x0, x0, FAIL
	jalr x0, x12, 8
	beq x0, x0, FAIL
L5:	jalr x12, x1, 4		
	beq x0, x0, FAIL
	beq x0, x0, FAIL
	auipc x6, 0		# x6 = 0x31d4
	addi x6, x6, 16		# x6 = 0x31e4
	jalr x0, x6, 0
	beq x0, x0, FAIL	

FINAL:	# final test	
	addi gp, x0, 11		# gp = 0x0b
	addi x8, x0, 100	# x8 = 100
	addi x5, x0, 0		# x5 = 0
	addi x30, x30, 0	# x30 = 0
LOOP:	beq x5, x8, JMP
	add x6, x5, x5
	add x6, x6, x6		# x6 = 4 * x5
	sw x5, 0(x6)	
	addi x5, x5, 1		# 数据段前100个位置存0到99
	jal x7, LOOP		
	beq x0, x0, FAIL
JMP:	jalr x0, x7, 12		# 跳至COUNT前一句
	beq x0, x0, FAIL
	addi x10, x0, 0
COUNT:	add x11, x10, x10
	add x11, x11, x11	# x11 = 4 * x10
	lw x12, 0(x11)
	add x30, x30, x12
	addi x10, x10, 1
	blt x10, x8, COUNT	# x30 储存0到99的和 0x1356
	auipc x31, 0		# x310x3234
	lui x29, -2		# x29 = 0xffffe000
	add x28, x29, x31	# x28 = 0x1234
	addi x27, x28, 0x122	# x27 = 0x1356
	beq x27, x30, TEST11
	beq x0, x0, FAIL
	
TEST11:  #TEST sll,slli
        addi gp, x0, 12         #gp=0x0c
        addi x5, x0, 3
        addi x6, x0, 6
        slli x5, x5, 1
        beq  x5, x6, TEST12
        jal  x7, FAIL
         
TEST12: 
        addi gp, x0, 13         #gp=0x0d       
        addi x5, x0, 3
        addi x6, x0, 6
        addi x8, x0, 1
        sll  x5, x5, x8
        beq  x5, x6, TEST13
        jal  x7, FAIL

TEST13: #TEST srl,srli,srai
        addi gp, x0, 14        #gp=0x0e
        addi x5, x0, 6
        addi x6, x0, 3
        srli x5, x5, 1
        beq  x5, x6, TEST14
        jal  x7, FAIL
        
TEST14:#TEST srli
        addi gp, x0, 15        
        addi x5, x0, -1
        srli x5, x5, 31
        addi x6, x0, 1
        beq  x5, x6, TEST15
        jal  x7, FAIL
        
 TEST15:#TEST srai
        addi gp, x0, 16
        addi x5, x0, -1
        srai x5, x5, 1
        addi x6, x0, -1
        beq  x5, x6, TEST16
        jal  x7, FAIL
      
TEST16: #TEST and
        addi gp, x0, 17     
        addi x5, x0, 7
        addi x6, x0, 6
        and  x5, x5, x6
        beq  x5, x6, TEST17
        jal  x7, FAIL
       
TEST17:#TEST or
        addi gp, x0, 18       
        addi x5, x0, 7
        addi x6, x0, 6
        or  x6, x5, x6
        beq  x5, x6, TEST18
        jal  x7, FAIL
        
TEST18:#TEST xor
        addi gp, x0, 19       
        addi x5, x0, 7
        addi x6, x0, 6
        xor  x5, x5, x6
        addi x6, x0, 1
        beq  x5, x6, TEST19
        jal  x7, FAIL

TEST19:#TEST bne
        addi gp, x0, 20  
        addi x5, x0, 1
        addi x6, x0, 2
        bne  x5, x6, TEST20
        jal  x7, FAIL

TEST20:#TEST bge
        addi gp, x0, 21
        addi x5, x0, 3
        addi x6, x0, -1
        bge  x5, x6, TEST21
        jal  x7, FAIL

TEST21:#TEST bltu
        addi gp, x0, 22
        addi x5, x0, 3
        addi x6, x0, -1
        bltu x5, x6, TEST22
        jal  x7, FAIL

TEST22:#TEST bgeu
        addi gp, x0, 22
        addi x5, x0, -1
        addi x6, x0, 3
        bgeu x5, x6, WIN
        jal  x7, FAIL

WIN:	
	lui x7 7
	addi x7 x7 0x700
	addi x7 x7 0x700
	addi x7 x7 0x100	# x7 = 7f00
	addi x8 x0 1
	sw x8 12(x7)		# led[0] = 0
	beq x0, x0, WIN
	
.text
andi x1, x1, 0
addi x2, x0, 1
sw   x2, 0(x1)
addi x1, x1, 4
addi x3, x0, 1
sw   x3, 0(x1)
addi x1, x1, 4
addi x4, x0, 23
FLS:
add x5, x2, x3
sw  x5, 0(x1)
addi x1, x1, 4
addi x2, x3, 0
addi x3, x5, 0
addi x4, x4, -1
beq  x4, x0, WIN
jal  x7, FLS

WIN:
	lui x7 7
	addi x7 x7 0x700
	addi x7 x7 0x700
	addi x7 x7 0x100	# x7 = 7f00
	addi x8 x0 1
	sw x8 12(x7)		# led[0] = 0
	beq x0, x0, WIN

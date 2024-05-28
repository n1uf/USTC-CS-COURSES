	   .ORIG	x3000 		
	    LD	    R1, SCORE   ;R1为指针，指向初始的分数地址
	    LD      R2, StuNUM  ;R2为学生人数（16）
	    LD	    R7, RESULT  ;R7为指针，指向要存放的分数初始地址

;复制到指定位置
COPY	LDR	    R3, R1, #0	;R3存成绩
	    STR	    R3, R7, #0	;成绩存入结果
	    ADD	    R1, R1, #1	;移向下一个成绩
	    ADD	    R7, R7, #1	;结果成绩指针移向下一个
	    ADD	    R2, R2, #-1	;R2减1
	    BRp	    COPY		;全部复制
	    
;排序
        AND     R2, R2, #0
	    ADD     R2, R2, #1	;R2从1开始，代表i
LOOPout	
		 LD      R7, RESULT	;R7重新移动到指向要存放的分数初始地址
		 AND     R3, R3, #0	;R3清零
		 ADD     R1, R2, #-16	;R1=-(n-i)
	LOOPin	    
	            LDR	    R4, R7, #0  ;R4存SCORE[j]
		        LDR	    R5, R7, #1	;R5存SCORE[j + 1]
		        NOT	    R6, R5	
		        ADD	    R6, R6, #1	;R6 = -R5
		        ADD	    R6, R6, R4	;R6 = R4 - R5
		        BRnz	FLAG	;如果R4 <= R5
		        STR	    R5, R7, #0 
		        STR	    R4, R7, #1	;交换R4, R5
	FLAG
		        ADD	    R7, R7, #1		;指向下一成绩
		        ADD	    R3, R3, #1		
		        ADD	    R6, R3, R1	
		        BRn	LOOPin
	    ADD	    R2, R2, #1	
	    ADD	    R6, R2, #-16;
	    BRn	    LOOPout


	LD	    R2, A    ;R2 = -85
	LD	    R3, B     ;R3 = -75
	AND	    R1, R1,#0		;R1清零
	AND	    R5, R5,#0		;R5清零存A人数
	AND	    R6, R6,#0		;B人数
	LD	    R7, LAST		;R7存放成绩结果末地址

;计数A
CountA	LDR 	R4, R7, #0	
    	ADD	    R4, R4, R2	;R4=score-85
    	BRn	    CountB		;如果score<85，开始计数B
	    ADD	    R5, R5, #1	;人数增加
	    ADD	    R7, R7, #-1	;移向下一分数
	    ADD	    R1, R1, #1	;计数加1
	    ADD	    R0, R1, #-4	;R0=计数-4
    	BRn	    CountA		;计数小于4，还在前25%继续判断A人数
    	
;计数B
CountB	LDR	    R4, R7, #0	
    	ADD	    R4, R4, R3	;R4=score-75
	    BRn	    STORE		;如果score<75，跳出B计数，进行保存
	    ADD	    R6, R6, #1	;人数增加
	    ADD	    R7, R7, #-1	;移向下一分数
	    ADD	    R1, R1, #1	;计数加1
	    ADD	    R0, R1, #-8	;R0=计数-8
	    BRn	    CountB		;计数小于8，还在前50%继续判断B人数
	
STORE	STI	    R5, Anum    ;保存A，B人数
	    STI	    R6, Bnum
        HALT

SCORE	.FILL	x4000		;成绩存放起始地址
RESULT	.FILL	x5000		;成绩结果起始地址
StuNUM	.FILL	#16		    ;学生人数
A	    .FILL	#-85		;
B	    .FILL	#-75	    ;
LAST	.FILL	x500F		;成绩结果末地址
Anum	.FILL	x5100		;存放A地址
Bnum	.FILL	x5101       ;存放B地址
	    .END
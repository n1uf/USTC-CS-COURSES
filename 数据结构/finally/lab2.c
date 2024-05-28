#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 可以使用宏定义来规定精度
#define INTE_MAX 1000
#define DECI_MAX 1000
// 输出精度
#define PRINT_MAX 50

typedef struct num{	// 高精度数的存储结构
	int negative;	// 正负，正号为0，负号为1
	int data[INTE_MAX + DECI_MAX];	// 存储数据
	int *number;	// 令number = data + DECI_MAX 则 num = ... + number[-1] * base^-1 + number[0] * base^0 + number[1] * base^1 +...
	int base;
}num;

num* initNUM();
num* ReadFromString(char * str, int base);	// 从一个数字字符串读取生成高精度数
void printnum(num* N);					// 输出高精度数
num* baseConversion(num* N, int base);	// return A转化为 base进制下的数
num * add(num * A, num* B);		// return A + B
num * minus(num * A, num* B);	// return A - B
num * multi(num* A,num* B);		// return A * B
num * calculate(char * fx,char * x, int inbase, int outbase);	// 仅含有 数字 字母 加减乘 的多项式计算

int main(){
	num * tmp,* t1, * t2;
	printf("测试读取字符串：\n");
	tmp = ReadFromString("-204.2", 10);
	printnum(tmp);

	printf("测试进制转化：\n");
	t1 = baseConversion(tmp, 2);
	printnum(t1);
	t2 = baseConversion(tmp, 10);
	tmp = ReadFromString("-11001100.00110011001100110011001100110011001100110011001100", 2);
	t2 = baseConversion(tmp, 10);
	printnum(t2);

	printf("测试加减乘：\n");
	t1 = ReadFromString("1.14514",10);
	t2 = ReadFromString("-1.919810",10);
	printnum(add(t1,t2));
	printnum(minus(t1,t2));
	printnum(multi(t1,t2));
	printf("上述转化为7进制：\n");
	printnum(baseConversion(add(t1,t2),7));
	printnum(baseConversion(minus(t1,t2),7));
	printnum(baseConversion(multi(t1,t2),7));

	printf("多项式测试：\n");
	printf("测试进制转化：\n");
	tmp = calculate("-204.2","0",10,2);printnum(tmp); // 将10进制的204.2转2进制
	tmp = calculate("x","-11001100.00110011001100110011001100110011001100110011001100",2,10);printnum(tmp);	// 将2进制的-11001100.00110011转10进制.可以看到，常数多项式可以考虑这两种输入方式
	printf("测试加减乘：\n");
	tmp = calculate("1.14514+-1.919810","8008208820",10,10);printnum(tmp);	// 符号优先级同一般机器语言 http://home.ustc.edu.cn/~ziheng/pic/test.png
	tmp = calculate("1.14514--1.919810","8008208820",10,10);printnum(tmp);
	tmp = calculate("1.14514*-1.919810","8008208820",10,10);printnum(tmp);
	printf("上述转化为7进制：\n");
	tmp = calculate("1.14514+-1.919810","0",10,7);printnum(tmp);
	tmp = calculate("1.14514--1.919810","0",10,7);printnum(tmp);
	tmp = calculate("1.14514*-1.919810","0",10,7);printnum(tmp);
	printf("含有变量的多项式测试：\n");
	tmp = calculate("12.31379131*x*x+x+8.2137619836821388","1.612368921371923122414",10,10);printnum(tmp);
	tmp = calculate("-12.31379131*x*x+-x+-8.2137619836821388","1.612368921371923122414",10,10);printnum(tmp);	// 测试负号
	tmp = calculate("x*-12.31379131*x-x-8.2137619836821388","1.612368921371923122414",10,10);printnum(tmp);		// 测试负号
	return 0;
}

num* initNUM(){
	num* tmp = (num*)malloc(sizeof(num));
	tmp->base = 0;
	tmp->negative = 0;
	tmp->number = tmp->data + DECI_MAX;
	for(int i = -DECI_MAX; i < INTE_MAX; ++i)
		tmp->number[i] = 0;
	return tmp;
}

num* baseConversion(num* N, int base){	// return A转化为 base进制下的数
	num* tmp = initNUM();
	if(N->base == base){
		*tmp = *N;
		tmp->number = tmp->data + DECI_MAX;
		return tmp;
	}
	tmp->base = base;				// 进制
	tmp->negative = N->negative;	// 正负与原来一致
	// 整数部分
	for(int i = 0; i < INTE_MAX; ++i){
		for(int j = 0; j < INTE_MAX; ++j)
			tmp->number[j] *= N->base;
		tmp->number[0] += N->number[INTE_MAX - 1 - i];
		for(int j = 0; j < INTE_MAX - 1; ++j)
			if(tmp->number[j] >= base){
				tmp->number[j + 1] += tmp->number[j] / base;
				tmp->number[j] = tmp->number[j] % base;
			}
	}
	// 小数部分
	int deci[DECI_MAX];
	for(int i = 1; i < DECI_MAX; ++i)	deci[i] = N->number[-i];	// 保存N的小数部分
	for(int i = 1; i < DECI_MAX; ++i) {
		deci[0] = 0;
		for (int j = 1; j < DECI_MAX; ++j)
			deci[j] *= base;
		for (int j = DECI_MAX - 1;j > 0; --j) {
			deci[j - 1] += deci[j] / N->base;
			deci[j] = deci[j] % N->base;
		}
		tmp->number[-i] = deci[0];
	}
	return tmp;
}

int abscompare(num * A, num* B){	// 比较 abs(A) 与 abs(B) 的大小
	A = baseConversion(A, B->base);
	for(int i = INTE_MAX - 1; i >= -DECI_MAX; --i)	// 从高位比较
		if(A->number[i] != B->number[i]){
			int tmp = A->number[i] - B->number[i];
			free(A);
			return tmp > 0 ? 1 : -1;
		}
	free(A);
	return 0;	
}

num * minus(num * A, num* B){	// return A - B
	if(A->negative != B->negative){		// AB符号不同
		B->negative = 1 - B->negative;	// 将AB符号改为一致
		num* tmp = add(A,B);
		B->negative = 1 - B->negative;
		return tmp;
	}
	if(abscompare(A,B) < 0){	// |A| > |B|， 则 A - B 变号，return -(B - A)
		num* tmp = minus(B,A);
		tmp->negative = 1 - tmp->negative;
		return tmp;
	}
	// AB同号，且|A| > |B| , A - B 
	num* tmp = baseConversion(A,B->base);	// tmp = A ，且与B进制一样
	// 借位
	for(int i = -DECI_MAX; i < INTE_MAX; ++i){	// 从低位向高位遍历
		tmp->number[i] -= B->number[i];
		if(tmp->number[i] < 0){
			tmp->number[i + 1] --;
			tmp->number[i] += tmp->base;
		}
	}
	return tmp;
}

num * add(num * A, num* B){	// return A + B
	if(A->negative != B->negative){		// AB符号不同
		B->negative = 1 - B->negative;	// 将AB符号改为一致
		num* tmp = minus(A,B);
		B->negative = 1 - B->negative;
		return tmp;
	}
	// AB同号
	num* tmp = baseConversion(A,B->base);	// tmp = A ，且与B进制一样
	// 进位
	for(int i = -DECI_MAX; i < INTE_MAX; ++i){ // 从低位向高位遍历
		tmp->number[i] += B->number[i];
		if(tmp->number[i] >= tmp->base){
			tmp->number[i + 1] ++;
			tmp->number[i] -= tmp->base;
		}
	}
	return tmp;
}

num * multi(num* A,num* B){		// A * B 
	num* tmp = initNUM();
	A = baseConversion(A,B->base);	// 令A转化到与B一个进制
	tmp->negative = A->negative == B->negative ? 0 : 1;	// 同号得正，异号为负
	tmp->base = B->base;
	// 我们知道 (a0 + a1*p^1 + a2*p^2 ...) * (b0 + b1*p^1 + .... ) =  sum_i (sum_k+j=i ak + bj )*p^i
	for(int i = -DECI_MAX; i < INTE_MAX; ++i){
		for(int j = -DECI_MAX; j < INTE_MAX; ++j)
			if(i - j >= -DECI_MAX && i - j < INTE_MAX)	// i - j 也需要满足在精度范围内
				tmp->number[i] += A->number[j] * B->number[i - j];	//  sum_i (sum_k+j=i ak + bj ) * p^i 其中 k是i-j 
		// 进位
		if(tmp->number[i] >= tmp->base){
			tmp->number[i + 1] = tmp->number[i] / tmp->base;
			tmp->number[i] = tmp->number[i] % tmp->base;
		}
	}
	return tmp;
}

void printnum(num* N){
	if(N->negative)	printf("-");
	int i;
	for(i = INTE_MAX - 1;i >= 1 && !N->number[i]; --i);	// 从高位到低位找到非0位
	for( ; i >= -PRINT_MAX; --i){
		if(N->number[i] < 10) 	 printf("%d",N->number[i]);
		else if(N->number[i] < 36) printf("%c",'a' + N->number[i]-10);
		if(i == 0)	printf(".");
	}
	printf("\n");
}

num* ReadFromString(char * str, int base){	// 从一个数字字符串读取生成高精度数
	// 如 ReadFromString("123546.2321", 10) 返回一个10进制下的高精度数
	num* tmp = initNUM();
	tmp->base = base;
	if(str[0] == '-'){	// 处理负号
		tmp->negative = 1;
		str++;
	}
	int dot;
	for(dot = 0; str[dot] && str[dot]!= '.'; ++dot);	// 找到小数点所在位置
	for(int i = 0; i < dot; ++i)			// 整数
		tmp->number[i] = (str[dot - i - 1] >= '0' && str[dot - i - 1] <= '9') ?  str[dot - i - 1] - '0' : str[dot - i - 1] - 'a' + 10;	// 数字 or 字母 
	for(int i = -1; str[dot - i]; --i )	// 小数
		tmp->number[i] = (str[dot - i] >= '0' && str[dot - i] <= '9') ?  str[dot - i] - '0' : str[dot - i] - 'a' + 10;	// 数字 or 字母 
	return tmp;
}

// 提供了一种大一统的输入，可处理所有样例，基本上实现单变量多项式就可以实现所有样例（毕竟常数也是多项式
// 当然也可以自行设计其他类型的输入
/***
 * fx是多项式字符串
 * x是多项式自变量的值
 * inbase是输入多项式与自变量的进制
 * outbase是最终结果的进制
***/
num *calculate(char * fx,char * x, int inbase, int outbase){	// fx仅存在 数字 字母 +-*
	int i , j;
	char fx1[999] = {0};
	for(i = 0; fx[i] && fx[i] != '+'; ++i);	// 检测第一个加法
	if(fx[i]){		// 形如 A + B
		strncpy(fx1 ,fx , i);
		num * t1 = calculate(fx1, x, inbase, outbase);
		num * t2 = calculate(fx + i + 1, x, inbase, outbase);
		num * tmp = add(t1,t2); free(t1);free(t2);
		t1 = baseConversion(tmp,outbase); free(tmp);
		return t1;
	}

	for(i = j = 0; fx[j]; ++j)			// 检测最后一个减法
		if(j > 0 && fx[j] == '-' && fx[j - 1] != '*' && fx[j - 1] != '-')	// 需要排除负数的 -
			i = j;
	if(i > 0){	// 形如 A - B 且 B中全是乘法
		strncpy(fx1 ,fx , i);
		num * t1 = calculate(fx1, x, inbase, outbase);
		num * t2 = calculate(fx + i + 1, x, inbase, outbase);
		num * tmp = minus(t1,t2); free(t1);free(t2);
		t1 = baseConversion(tmp,outbase); free(tmp);
		return t1;
	}

	for(i = 0; fx[i] && fx[i] != '*'; ++i);	// 检测第一个乘法
	if(fx[i]){
		strncpy(fx1 ,fx , i);
		num * t1 = calculate(fx1, x, inbase, outbase);
		num * t2 = calculate(fx + i + 1, x, inbase, outbase);
		num * tmp = multi(t1,t2); free(t1);free(t2);
		t1 = baseConversion(tmp,outbase); free(tmp);
		return t1;
	}
	// 单独一个数
	int negative = 0;
	if(*fx == '-'){
		fx++;
		negative = 1;
	}
	num * tmp = ReadFromString(*fx == 'x' ? x : fx,inbase);
	tmp->negative = negative;
	num * t1 = baseConversion(tmp,outbase); free(tmp);
	return t1;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct num
{	// 高精度数的存储结构 
	int negative;	// 正负，正为0，负为1 
	int inte[MAX];	// 绝对值下的整数部分
	int deci[MAX];	// 绝对值下的小数部分
	int base;
	int length1;	// 整数长度 
	int length2;	// 小数长度 
}num;

num* initNUM()
{	// 初始化结构体 
	num* tmp = (num*)malloc(sizeof(num));
	tmp->base = 0;
	tmp->negative = 0;
	tmp->length1 = 0; 
	tmp->length2 = 0;
	for(int i = 0; i < MAX; i ++)
	{
		tmp->inte[i] = 0;
		tmp->deci[i] = 0;
	}
	return tmp;
}

char *initCHAR(char *str)
{	// 初始化字符数组 
	for(int i = 0; i < MAX; i ++)
		str[i] = '\0';
	return str;
}

int *initINT(int *p)
{	// 初始化整形数组 
	for(int i = 0; i < MAX; i ++)
		p[i] = 0;
	return p;
}

num* Copy(num *IN, num *OUT)
{	// 复制高精度数，每个结构体内定义的变量都复制过去 
	OUT->base = IN->base;
	OUT->length1 = IN->length1;
	OUT->length2 = IN->length2;
	OUT->negative = IN->negative;
	for(int i = 0; i < MAX; i ++)
	{
		OUT->inte[i] = IN->inte[i];
		OUT->deci[i] = IN->deci[i];
	}
	return OUT;
}

num* ReadFromString(char *str, int base)
{	// 读取字符串生成base进制下的高精度数 
	num* tmp = initNUM();		// 初始化 
	tmp->base = base;			// 进制一致 
	int i;
	if(str[0] == '-')
	{	// 读到负号 
		tmp->negative = 1;
		for(i = 0; i < MAX; i ++)
		{	// 之后的前移一位 
			str[i] = str[i + 1];
		}
	}
	for(i = 0; str[i] != '.' && str[i] != '\0'; i ++);		// 移到最高位 
	int j = i - 1;
	int k = 0;
	for(; j >= 0; j --, k ++)
	{	// 依次读取整数部分，并增加整数部分长度 
		tmp->inte[k] = str[j] - 48;
		tmp->length1 ++;
	}
	if(i != MAX)
	{	// 没读完，则有小数 
		k ++;
		int l = 0;
		for(; str[k] != '\0'; k ++, l ++)
		{	// 依次读取小数部分，并增加小数部分长度 
			tmp->deci[l] = str[k] - 48;
			tmp->length2 ++;
		}
	}
	return tmp;
}

num* baseConversion(num *N, int base)
{	// 将高精度数转化为base进制数 
	num* tmp = initNUM();
	tmp->base = base;				// 进制
	tmp->negative = N->negative;	// 正负一致 
	// 整数部分
	for(int i = 0; i < MAX; i ++)
	{
		for(int j = 0; j < MAX; j ++)
			tmp->inte[j] *= N->base;			// 预处理base进制的整数 

		tmp->inte[0] += N->inte[MAX - 1 - i];

		for(int j = 0; j < MAX - 1; j ++)
		{	// 遍历整数部分 
			if(tmp->inte[j] >= base)
			{	// 有超过base的数，则采取base进制的进位 
				tmp->inte[j + 1] += tmp->inte[j] / base;
				tmp->inte[j] = tmp->inte[j] % base;
			}
		}		
	}
	// 小数部分
	int i, j, k = 0;
	int tmpp[MAX];
	for(i = 0; i < MAX; i ++)
	{	// tmpp存tmp的小数部分 
		tmpp[i] = N->deci[i];
		tmp->deci[i] = 0;
	}
	for(k = 0; k < MAX; k ++)
	{	// 输出每一位 
		for(i = MAX - 1; tmpp[i] == 0; i --);	// 移动到小数的最低位（去掉后继0） 
		for(; i >= 0; i --)
		{	// 对小数的最后一位开始，从后往前进行按位的操作 
			int temp = tmpp[i] * base + j;		// 预处理成为base进制 
			for(j = 0; j <= base; j ++)
			{	// 找到temp/初始进制的整数部分，并记录余数 
				if(temp - j * N->base < 0)
				{
					j --;
					tmpp[i] = temp - j * N->base;
					break;
				}
			}
		}
		tmp->deci[k] = j;						// 该整数部分即为转换进制后该位的数字 
		j = 0;									// 重置j 
	}
}

void printnum(num *N)
{	// 打印出结构体存储的数 
	int flag = 0;
	int i;
	if(N->negative == 1)
		printf("-");		// 打印符号 
	for(i = MAX - 1;! N->inte[i] && i >= 0; i --);		//移动到整数部分最高位 
	if(i < 0)
		printf("0");		// 没有整数部分则整数部分打印0 
	for(; i >= 0; i --)
	{	// 逐项打印 
		if(N->inte[i] < 10)
			printf("%d", N->inte[i]);
		else if(N->inte[i] < 36)
			printf("%c", 'a' + N->inte[i] - 10);
	}
		
	for(i = 0; i < MAX; i ++)				 
	{	// 判断是否有小数
		if(N->deci[i] != 0)
			flag = 1;
	}
	if(flag)
	{	// 有小数部分 
		printf(".");
		for(i = MAX - 1;! N->deci[i]; i --);			// 移动到小数部分最低位（去掉后继0） 
		int j;
		for(j = 0; j <= i; j ++)
		{	// 逐项打印 
			if(N->deci[j] < 10) 	 printf("%d",N->deci[j]);
			else if(N->deci[j] < 36) printf("%c",'a' + N->deci[j] - 10);
		}
	}
	printf("\n");
}

int max(int a, int b)
{	// 求整形数字的较大值 
    return (a > b ? a : b);
}

int CompareAbs(num *A, num *B) 
{	// 比较绝对值大小，A大则返回1，否则为0 
    if (A->length1 > B->length1)
        return 1;							// A整数部分长，A大 
    if (A->length1 == B->length1)
    {	// 整数部分长度一样 
        for (int i = A->length1 - 1; i >= 0; i--)
        {	// 逐项判断整数部分大小 
            if (A->inte[i] > B->inte[i])
                return 1;
            if (A->inte[i] < B->inte[i])
                return 0;
        }
        for (int i = 0; i < max(A->length2, B->length2) - 1; i++)
        {	// 逐项判断小数部分大小 
            if (A->deci[i] > B->deci[i])
                return 1;
            if (A->deci[i] < B->deci[i])
                return 0;
        }
    }
    return 0;
}

num *AddAbs(num *A, num *B) 
{	// 进行绝对值A + B
    num *C = initNUM();
    int k = 0;				// k代表进位 
    for (int i = max(A->length2, B->length2) - 1; i >= 0; i--) 
    {	// 小数部分加法 
        C->deci[i] = (A->deci[i] + B->deci[i] + k) % A->base;		// 两数相加并加进位再对进制取余得到该位 
        k = (A->deci[i] + B->deci[i] + k) / A->base;				// 进位 
    }
    for (int i = 0; i <= max(A->length1, B->length1); i++)  
    {	// 整数部分加法
        C->inte[i] = (A->inte[i] + B->inte[i] + k) % A->base;		// 两数相加并加进位再对进制取余得到该位 
        k = (A->inte[i] + B->inte[i] + k) / A->base;				// 进位 
    }
    
    k = MAX - 1;
    for (; C->inte[k] == 0 && k > 0;)
        k--;					// k为整数最高位 
    C->length1 = k + 1; 		// 整数部分长度
    k = MAX - 1;
    for (; C->deci[k] == 0 && k > 0;)
        k--;					// k为小数最低位（去掉后继0） 
    C->length2 = k + 1; 		// 小数部分长度
	C->negative = A->negative;	// 保持正负 
    return C;
}

num *SubAbs(num *A, num *B) 
{	// 进行绝对值A - B
    num *C = initNUM();
    int k = 0;				// k代表借位 
    for (int i = max(A->length2, B->length2) - 1; i >= 0; i--) 
    {	// 小数部分减法，一位一位减 
        if (A->deci[i] + k >= B->deci[i])
        {	// 如果减法结果为正， 则直接减 
            C->deci[i] = A->deci[i] + k - B->deci[i];
            k = 0;
        }
        else
        {	// 否则借位减，借位标识为-1 
            C->deci[i] = A->deci[i] + k + A->base - B->deci[i];
            k = -1;
        }
    }

    for (int i = 0; i <= max(A->length1, B->length1) - 1; i++) 
    {	// 整数部分减法，一位一位减 
        if (A->inte[i] + k >= B->inte[i])
        {	// 如果减法结果为正， 则直接减 
            C->inte[i] = A->inte[i] + k - B->inte[i];
            k = 0;
        }
        else
        {	// 否则借位减，借位标识为-1 
            C->inte[i] = A->inte[i] + k + A->base - B->inte[i];
            k = -1;
        }
    }

    k = MAX - 1;
    for (; C->inte[k] == 0 && k > 0;)
        k--;					// 移动k的位置到整数最高位 
    C->length1 = k + 1;			// 赋值整数长度 
    k = MAX - 1;
    for (; C->deci[k] == 0 && k > 0;)
        k--;					// 移动k的位置到小数最低位（去掉后继0） 
    C->length2 = k + 1;			// 赋值小数长度 
    C->negative = A->negative;	// 正负保持一致 
    return C;
}

num *SubOrder(num *A, num *B) 
{	// 改变加减顺序使得输出正确结果 
    if (CompareAbs(A, B)) // 若A绝对值大于B 就A-B
        return SubAbs(A, B);
    else
        return SubAbs(B, A); // 否则B-A
}

num *Add(num *A, num *B) 
{	// 加法 
	num *C = initNUM();				// 初始化 
	
    if (A->negative == B->negative)
    {	// 符号相同 
    	C = AddAbs(A, B);			// 绝对值加法 
    	C->base = 10;				// 进制为10 
    	return C;
	}

    else
    {	// 符号不同 
    	C = SubOrder(A, B);			// 绝对值减法 
    	C->base = 10;				// 进制为10 
    	return C;
	}
}

num *Sub(num *A, num *B) 
{	// 减法 
	num *C = initNUM();				// 初始化 
	C = SubOrder(A, B);				// 正确顺序的减法 
	
    if (A->negative != B->negative)
    {	// 符号不同则调用绝对值加法 
    	C = AddAbs(A, B);			// 绝对值加法 
    	C->base = 10;				// 注意需要把进制也赋给结果 
    	return C;
	}
    else if(!CompareAbs(A, B))
    {	// 结果是负数 
    	C->negative = 1;			// 符号为负 
    	C->base = 10;				// 进制保持10 
    	return C;
	}
    else
    {	// 结果是正数 
    	C->base = 10;				// 进制保持10 
    	return C;
	}
}

// 存储形式为 a[0]:数字长度len，a[MAX-1]:符号位，a[MAX-2]:整数位数
// 数字从高位到低位，存储在len..1 
char *output(int a[], int M, char str[])
{	// 将整形存储的高精度数转变为字符型存储并输出 
	int i, j, k = 0;		
	int strp = 0;			// str字符串的第几个字符 
	if(a[M - 1] < 0)
	{	// 符号位的判断 
		str[strp] = '-';
		strp ++;
	}
	 
	for(i = 1; i < a[0] - a[M - 2]; i ++)
	{	// 处理小数点后的没有用的0
		if(a[i] == 0)
		{
			for(j = i + 1; j <= a[0]; j ++)
				a[j - 1] = a[j];
			a[0] --;
			i --; 			// 防止移动过来的也是0 
		}
		else
			break;
	}
	
	for(i = a[0]; i > 1; i --)
	{	// 处理计算产生的无效0 
		if(a[i] == 0 && a[M - 2] > 1)
		{
			a[0] --;
			a[M - 2] --;
		}		
		else
			break;
	}	
	
	for(i = a[0]; i >= 1; i --)
	{
		// k记录已经输出的位数
		if(k == a[M - 2])
		{	// 输出到小数点，则录入小数点 
			str[strp] = '.';
			strp ++;
		}
		str[strp] = a[i] + '0';			// 录入数字 
		strp ++;
		k ++;		
	}
	return str;
}

int allDigit(char *s) 
{	// 判断字符串是否可以被正确读取 
	int flag = 1;// 标志读取的是否第一个字符 
	int pointFlag = 1; // 标志读取到第一个小数点 
	while(*s) 
	{
		if(flag) 
		{	// 如果是第一个字符，可以是+或者-
			flag = 0; 
			if(*s == '+' || *s == '-')
			{
				s ++;
				continue;
			}								
		}
		
		if(! (*s >= '0' && *s <= '9'))
		{	// 不是数字字符且不是第一个小数点，return 0;
			if(*s == '.' && pointFlag == 1)
			{	// 只允许一个小数点
				pointFlag = 0;				
			}
			else
				return 0;
		}
		s ++;		// 判断下一个字符 
	}
	return 1;
}

void input(char s[],int p[])
{	// 将字符数组存放的高精度数放在整形数组中用于计算乘法 
	int sign = 1;// 符号位 
	int len = strlen(s), i = 0, j, k;	// len是s的长度 
	 
	// 检测s中第一个是否是符号 
	if(s[0] == '+')
	{
		i = 1;
		len --;			
	}
	if(s[0] == '-')
	{
		i = 1;
		len --;
		sign = -1;
	}		
	
	
	if(s[i] == '.')
	{	// 处理小数点在第一位或符号位之后的情况
		// 如：+.12345或.12345 
		for(j = len + 1; j >= i; j --)		// 后移 
			s[j + 1] = s[j];

		s[i] = '0';							// 在.前补0 
		len ++;
	} 
	
	j = i;
	
	while(s[j] && s[j] != '.')
		j ++;
	if(s[j])
		// 有小数点 
		len --;	 	
	p[MAX - 2] = j - i; // 整数位数
	
	while(s[i] == '0' && len > 1 && p[MAX - 2] > 1)
	{	// 跳过符号位之后的所有的无效0，如需要则保留小数点前的一个0 
		i ++;
		len --;
		p[MAX - 2] --; 
	}	// 此时i为第一个非0字符的下标，特别的如果均为0，则i为最后一个0的下标 
	 
	j = 0;
	
	for(; j < len; j ++)
	{	// 将处理后的字符数组存储变为整形数组存储 
		if(s[i] == '.')						// 跳过小数点 
			j --;
		else								//存储 
			p[len - j] = s[i] - '0';
		i ++;		
	}
	
	p[0] = len;								// 记录长度 
	p[MAX - 1] = sign;						// 记录符号位 
} 

void multiply(int a[],int b[],int c[]) 
{	// c = a * b
	int i, j, k;
	
	// a,b中的小数位数 
	int len1 = a[0] - a[MAX - 2];
	int len2 = b[0] - b[MAX - 2];
	
	// a,b的符号
	int signa = a[MAX - 1];      
	int signb = b[MAX - 1];	 
	
	c[0] = a[0] + b[0]; 					// 积的长度 
	for(j = 1; j <= b[0]; j ++)
	{
		for(i = 1; i <= a[0]; i ++)			
			c[i + j - 1] += a[i] * b[j];	// 先乘完，再处理进位
		
		for(k = 1; k <= c[0]; k ++) 
			if(c[k] >= 10)
			{	// 如果进位则处理，否则留下 
				c[k + 1] += c[k] / 10;
				c[k] = c[k] % 10;
			}				
	}
	
	// 结果可能是m + n - 1位 
	if(c[c[0]] == 0) 
		c[0] --;
		
	// 处理积的符号
	if(signa > 0 && signb > 0 || signa < 0 && signb < 0) 
		c[MAX - 1] = 1;
	else
		c[MAX - 1] = -1;
		 
	// 积的整数位数 
	c[MAX - 2] = c[0] - len1 - len2;
}

int main()
{
P:	printf("---------------------------------\n");
	printf("0.退出\n1.随意转换进制\n2.10进制转2进制\n3.2进制转10进制\n4.10进制转N进制\n");
	printf("5.10进制数高精度数加减乘运算并输出10进制和N进制结果\n6.单变量多项式\n");
	int flag;
	
	// 选择功能 
	printf("输入数字选择功能：");
	scanf("%d", &flag);
	printf("---------------------------------\n");
	
	// 初始化可能用到的结构体  
	num *A = initNUM();
	num *B = initNUM();
	num *C = initNUM();
	num *D = initNUM();
	num *E = initNUM();
	num *F = initNUM();
	
	switch(flag)
	{
		case(0):
		{
			break; 
		}
		case(1):
		{	// 进制转换部分 
			int baseM, baseN;				// 初始进制与输出进制 
			char str1[MAX];
			initCHAR(str1);					// 初始化字符串 
			printf("输入初始进制；");
			scanf("%d", &baseM);			// 初始进制 
			
			printf("输入初始数字；");
			scanf("%s", str1);				// 初始数字 
			
			A = ReadFromString(str1, baseM);			// 初始数字写入结构体 
			printf("输入的%d进制数字为；", baseM);
			printnum(A);					// 输出输入的数字检验前面是否有误 
			
			printf("输入需要转换的进制："); 
			scanf("%d", &baseN);			// 输出进制 
			printnum(baseConversion(A, baseN));			// 输出转换进制后的数字 
			goto P;
		}
		
		case(2):
		{	// 十进制转二进制 
			char str2[MAX];
			initCHAR(str2);					// 初始化字符串 
			printf("输入10进制数字：");
			scanf("%s", str2);				// 初始数字 
			
			A = ReadFromString(str2, 10);	// 写入结构体 
			printf("输入的10进制数字为；");
			printnum(A);					// 输出输入的数字 
			printf("转换为2进制数字为：");
			printnum(baseConversion(A, 2));	// 输出转换为二进制后的数字 
			goto P;
		}
		
		case(3):
		{	// 二进制转十进制 
			char str3[MAX];
			initCHAR(str3);					// 初始化字符串 
			printf("输入2进制数字：");
			scanf("%s", str3);				// 初始数字 
			
			A = ReadFromString(str3, 2);	// 写入结构体 
			printf("输入的2进制数字为；");
			printnum(A);					// 输出输入的数字 
			printf("转换为10进制数字为：");
			printnum(baseConversion(A, 10));// 输出转换为十进制后的数字 
			goto P;
		}
		
		case(4):
		{	// 十进制转N进制 
			char str4[MAX];
			initCHAR(str4);					// 初始化字符串 
			int N;
			printf("输入10进制数字：");
			scanf("%s", str4);				// 初始数字 
			
			A = ReadFromString(str4, 10);	// 写入结构体 
			printf("输入的10进制数字为；");
			printnum(A);					// 输出输入的数字
			printf("输入需要转换到的进制：");
			scanf("%d", &N); 				// 输入转换后的进制 
			printf("转换为%d进制数字为：", N);
			printnum(baseConversion(A, N)); // 输出转换为N进制后的数字 
			goto P;
		}
		
		case(5):
		{	// 高精度数加减乘运算与结果进制转换 
			char str5[MAX], str6[MAX], mulres[MAX];
			initCHAR(str5);
			initCHAR(str6);
			initCHAR(mulres);				// 初始化字符串 
			
			int a[MAX] = {0}, b[MAX] = {0}, c[2 * MAX] = {0};
			
			int N;
			
			printf("输入数字a：\n");
			scanf("%s", str5);
			printf("输入数字b：\n");
			scanf("%s", str6);
			printf("输入进制N：\n");
			scanf("%d", &N);				// 输入数字和进制 
			
			// 乘法部分
			input(str5, a);
			input(str6, b);					// 字符串转整形数组，便于乘法 
			multiply(a, b, c);				// 乘法操作，结果存入c 
			printf("a * b结果为：");
			output(c, MAX, mulres);			// 结果再转化为字符串 
			printf("%s\n", mulres);			// 输出结果 
			E = ReadFromString(mulres, 10);	// 结果写入结构体 
			 
			printf("%d进制结果为：", N); 
			printnum(baseConversion(E, N));	// N进制结果 
			
			// 加减部分 
			A = ReadFromString(str5, 10);
			B = ReadFromString(str6, 10);	//写入结构体 
			
			C = Add(A, B);					// 加法操作 
			printf("a + b结果为：");
			printnum(C);					// 输出结果 
			printf("%d进制结果为：", N);
			printnum(baseConversion(C, N));	// 输出N进制结果 
			
			D = Sub(A, B);					// 减法操作 
			printf("a - b结果为；");
			printnum(D);					// 输出结果 
			printf("%d进制结果为：", N);
			printnum(baseConversion(D, N));	// 输出N进制结果 
			
			goto P;
		}
		
		case(6):
		{	// 单变量多项式计算 
			int term = 0, i, j;
			printf("输入项数：");
			scanf("%d", &term);				// 输入项数 
			
			// 设置变量与变量的初始化 
			char coe[10][MAX];
			int coeint[10][MAX];
			int ind[10] = {0}, restmp[10][MAX] = {0}, res[10][MAX] = {0};
			char x[MAX], reschar[10][MAX];
			int xint[MAX] = {0}; 
			for(i = 0; i < 10; i ++)
			{
				initCHAR(coe[i]);
				initCHAR(reschar[i]);
			}
			initCHAR(x);
			
			// 多项式的读入 
			printf("输入x的值："); 
			scanf("%s", x);					// 读入x
			input(x, restmp[0]);
			input(x, xint); 				// x转化为整形数组存储 
			
			for(i = 0; i < term; i ++)
			{	// 输入系数 
				printf("输入第%d项的系数：", i + 1);
				scanf("%s", coe[i]);
				input(coe[i], coeint[i]);
			}
				
			for(i = 0; i < term; i ++)
			{	//输入指数 
				printf("输入第%d项的指数：", i + 1);
				scanf("%d", &ind[i]);
			}
			
			// 每一项的计算 
			for(i = 0; i < term; i ++)
			{	// 每一项分别计算 
				for(int k = 0; k < 10; k ++)
					initINT(restmp[k]);		// 每一次计算都要重新初始化该整形数组 
				input(x, restmp[0]);		// 将x写入需要操作的数组 
				if(ind[i] == 0)				
				{	// 如果指数是0，直接输出系数即可 
					output(coeint[i], MAX, reschar[i]);
				}
				else
				{	// 否则 
					for(j = 0; j < ind[i] - 1; j ++)
					{	// 先通过循环计算x的幂次 
						multiply(restmp[j], xint, restmp[j + 1]);
					}
					multiply(restmp[j], coeint[i], res[i]);		// 计算系数与x幂次的乘积 
					output(res[i], MAX, reschar[i]);			// 输出每一项的计算结果 
				}
				printf("第%d项结果为：%s\n",i + 1, reschar[i]);
			}
			
			// 将各项相加 
			num *A = initNUM();
			num *RES = initNUM();
			num *TMP = initNUM();			// 初始化结构体 
			TMP = ReadFromString(reschar[0], 10);				// 读入 
			Copy(TMP, RES);					// 如果只有一项那直接输出就可 
			for(i = 1; i < term; i ++)
			{	// 如果多于一项，则用循环进行加法 
				RES = initNUM();
				A = initNUM();				// 每一次操作均需要重新初始化上次操作中改变过的失去作用的变量 
				A = ReadFromString(reschar[i], 10);
				RES = Add(TMP, A);			// 循环体内的加法 
				TMP = initNUM();			// 清空用过的已经完成使命的TMP 
				Copy(RES, TMP);				// 再把TMP赋值为上一次加法运算的结果 
			}
			
			printf("多项式计算结果为：");
			printnum(RES);					// 输出结果 

			goto P;
		}
	}
}

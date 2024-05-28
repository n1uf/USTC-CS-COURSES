//高精度小数的乘法 
#include<stdio.h> 
#include<string.h>

#define MAX 1000

//a[0]:数字长度len，a[M-1]:符号位，a[M-2]:整数位数
//数字从高位到低位，存储在len..1 
//a对应的数组长度可能不同，但符号位一定在最高位
//M:a对应数组的长度 
void output(int a[],int M)
{
	int i, j, k = 0;		
	 
	if(a[M - 1] < 0)
		printf("-");
		
	//处理小数点之后的后继0，如123.45000000, 0.000000
	for(i = 1; i < a[0] - a[M - 2]; i ++)
	{
		if(a[i] == 0)
		{
			for(j = i + 1; j <= a[0]; j ++)
				a[j - 1] = a[j];
			a[0] --;
			i --; //防止移动过来的也是0 
		}
		else
			break;
	}	
	
	//处理因计算出现的前导0，前面处理的有bug，未同时减去数字长度
	//可以不用标志，注意条件是i>1 
	for(i = a[0]; i > 1; i --)
	{
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
		//k记录已经输出的位数
		//整数位数至少为1，因此第一次循环一定不会输出. 
		if(k == a[M - 2]) 
			printf(".");
		printf("%d",a[i]);
		k ++;		
	}
	printf("\n");
}

//判断字符串是否为数字串，允许符号位和小数点，是返回1否返回0 
int allDigit(char *s) 
{
	int flag = 1;//标志读取的是否第一个字符 
	int pointFlag = 1; //标志读取到第一个小数点 
	while(*s) 
	{
		//如果是第一个字符，允许是 + - 
		if(flag) 
		{
			flag = 0; 
			if(*s == '+' || *s == '-')
			{
				s ++;
				continue;
			}								
		}
		
		//不是数字字符且不是第一个小数点，return 0; 
		if(! (*s >= '0' && *s <= '9'))
		{
			//允许一个小数点 
			if(*s == '.' && pointFlag == 1)
			{
				pointFlag = 0;				
			}
			else
				return 0;
		} 	
		s ++;
	}
	return 1;
}

//将数字串s拆分为单个数字保存在整型数组，从1号开始 
//整型数组0号元素记录数字长度 
//存储时去除所有的前导0 
//运行形如：+.12345的输入
void input(char s[],int p[])
{
	int sign = 1;//符号位 
	int len = strlen(s), i = 0, j, k;
	
	//len表示s中数字字符的个数 
	//检测s中第一个是否是符号 
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
	
	//处理小数点在第一位或符号位之后的情况
	//如：+.12345或.12345 
	if(s[i] == '.')
	{
		//从\0开始到i号逐个后移 
		for(j = len + 1; j >= i; j --)
			s[j + 1] = s[j];
		//在.前补0 
		s[i] = '0';
		len ++;
	} 
	
	j = i;
	
	while(s[j] && s[j] != '.')
		j ++;
	if(s[j])
		//有小数点 
		len --;	 	
	p[MAX - 2] = j - i; //整数位数
	
	//跳过符号位之后所有的前导0
	//无+号时，从0号开始检测 
	// p[MAX-2]>1 限制小数点前要保留一个0，若输入000.1234 
	while(s[i] == '0' && len > 1 && p[MAX - 2] > 1)
	{
		i ++;
		len --;
		p[MAX - 2] --; 
	}
	
	//i为s中除符号位第一个非0字符的下标 
	//若s中全0，i为最后一个0的下标 
	j = 0;
	//注意条件是j<len，不能是i<len 
	for(; j < len; j ++)
	{
		//若转换时遇到小数点，不转换 
		if(s[i] == '.')
			j --;		 
		else
			p[len - j] = s[i] - '0';
		i ++;		
	}
	
	//0位记录数字长度，1..len记录数字
	//MAX-1位记录符号1或-1
	//考虑运算时两个数可能不等长,符号位不能设置在len+1	
	p[0] = len;
	p[MAX - 1] = sign;
} 

// c=a*b a,b容量为MAX,c容量为2N 
void multiply(int a[],int b[],int c[]) 
{
	int i, j, k;
	int len1 = a[0] - a[MAX - 2]; //a中小数位数 
	int len2 = b[0] - b[MAX - 2]; //b中小数位数
	//a,b的符号位 
	int signa = a[MAX - 1];      
	int signb = b[MAX - 1];	 
	
	c[0] = a[0] + b[0]; //积的长度 
	for(j = 1; j <= b[0]; j ++)
	{
		for(i = 1; i <= a[0]; i ++)			
			c[i + j - 1] += a[i] * b[j]; //+=
			
		//先乘完，再统一处理进位 
		for(k = 1; k <= c[0]; k ++)
			if(c[k] >= 10)
			{
				c[k + 1] += c[k] / 10; //+=
				c[k] = c[k] % 10;
			}				
	}
	
	//结果可能是m+n-1位 
	if(c[c[0]] == 0) 
		c[0] --;
		
	//处理积的符号
	if(signa > 0 && signb > 0 || signa < 0 && signb < 0) 
		c[2 * MAX - 1] = 1;
	else
		c[2 * MAX - 1] = -1;
		 
	//积的整数位数 
	c[2 * MAX - 2] = c[0] - len1 - len2;
		
}

int main()
{
	char s[MAX];
	int a[MAX] = {0}, b[MAX] = {0}, c[2 * MAX] = {0};
	
	printf("请输入数字串1：\n");
	while(1)
	{
		scanf("%s", s);
		if(allDigit(s))
			break;
		printf("请输入数字串1：\n");
	}
	input(s, a);	
	
	printf("请输入数字串2：\n");
	while(1)
	{
		scanf("%s", s);
		if(allDigit(s))
			break;
		printf("请输入数字串2：\n");
	}		
	input(s, b);		

	multiply(a, b, c);
	
	output(c, 2 * MAX);	
	
	return 0; 
}


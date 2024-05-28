#include<stdio.h>
int main()
{
	/*题目可以分为两部分，左半部分和右半部分*/
	/*其中左半部分去掉A为B	BC	BCD	...右半部分为A 	BA	CBA	...*/ 
	/*用ASCII码去表示各个字母，A的ASCII码是65，所以数字65以字符形式表示出来就是A*/
	int i,j,n,a,b;
	char letter;
	scanf("%c",&letter);
	n = letter - 64;
	a = 65;//让数字a去表示字母A 
	 
	for(i = 1; i <= n; i ++)
	{
		
		
		/*输入每一行的A*/ 
		for(j = 1; j < n - i + 1; j ++)
		{
			printf(" ");
		}
		printf("%c",a);
		
		/*输入左半部分*/ 
		b = a; 
		for(j = 1; j < i; j ++)
		{
			b ++;//意思是b = b + 1，让b去表示后面的BCD... 
			printf("%c",b);
		}
		
		/*输入右半部分*/ 
		for(j = i - 1; j >= 1; j --)
		{
			b --;
			printf("%c",b);
		}
		
		/*每一行结束要换行*/ 
		printf("\n");
	}
	return 0;
} 

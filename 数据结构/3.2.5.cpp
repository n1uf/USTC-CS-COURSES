//入栈次数必须大于出栈次数 则I个数大于等于O的个数，且出栈时一定要有元素在栈内，合法的为
//A C D 

#include <stdio.h>
#include <stdlib.h>
#define LEN 100
int main()
{
	char A[LEN] = {'I','O','I','I','I','I','O','O'};				//已经确定好的字符数组 
	int i = 0, j = 0, k = 0;
	for(; A[k] != '\0'; k ++)				//顺序遍历所有有值的数组元素 
	{
		switch(A[k])
		{
			case'I' : i ++; break;				//I则i加，同时直接break掉判断下一个数组元素 
			case'O' : j ++;				//O则j加 
			if(i < j)				//如过程中有任何一步i小于j则序列不合法 
			{
				printf("不合法的序列");
				exit(0); 
			}
		}
	}
	printf("序列合法"); 				//判断完，序列合法 
	return 0;
} 

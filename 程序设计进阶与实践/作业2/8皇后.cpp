#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define QUEEN 8
#define MAX 1000

int result[MAX][QUEEN]; //所有结果 
int nowtry[QUEEN]; //正在尝试 
int cnt = 0; //结果个数 
void nqueen(int n) //判断皇后 
{
	if(n == QUEEN) //出口条件是判断到第QUEEN行 
	{
		memcpy(result[cnt], nowtry, sizeof(nowtry)); //把当前尝试的结果存在总结果的第cnt个结果 
		cnt ++; //下一个结果 
		return ;
	}
	int i;
	for(i = 0; i < QUEEN; i ++) //放第n行第i列 
	{
		int j;
		for(j = 0; j < n; ) //判断能否放置 
		{
			if(i == nowtry[j] || abs(i - nowtry[j]) == abs(n - j)) //有矛盾 
			{
				break;
			}
			j ++;//这一行没有矛盾，判断下一行 
		}
		if(j == n) //与之前摆放的每一行都不矛盾 
		{ 
			nowtry[n] = i; //第n行皇后放在i列 
			nqueen(n + 1); //判断下一行 
		}
	}
}

int main(void)
{
	int n;
	nqueen(0);
	scanf("%d", &n);//第n个解 
	for(int i = 0; i < QUEEN; i ++)
	{
		printf("%d ", result[n - 1][i] + 1);
	}
	printf("\n");	
}

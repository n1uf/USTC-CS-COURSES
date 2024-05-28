#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define MAX 10000
#define QUEENNUM 50

int result[MAX][QUEENNUM]; //所有结果 
int nowtry[QUEENNUM]; //正在尝试 

void nqueen(int n, int QUEEN) //判断皇后 
{
	if(n == QUEEN) //出口条件是判断到第QUEEN行 
	{
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
			nqueen(n + 1, QUEEN); //判断下一行 
		}
	}
}

int main(void)
{
	int n, queen; 
	
	printf("输入皇后个数：");
	scanf("%d", &queen);
	
	clock_t start,end;
	start = clock();
	
	nqueen(0, queen);//计算 
	if(n == QUEEN) //出口条件是判断到第QUEEN行 
	{
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
			nqueen(n + 1, QUEEN); //判断下一行 
		}
	}
	end = clock();
	printf(" %d 皇后问题的计算时间为 %f s\n", queen, (double)(end-start)/CLK_TCK);
	
	for(int i = 0; i < queen; i ++)
	{
		printf("%d ", nowtry[i] + 1);
	}
	printf("\n");	
}

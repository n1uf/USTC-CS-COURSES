#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define MAX 1000000
#define QUEENNUM 50

int nowtry[QUEENNUM]; //正在尝试 
int cnt = 0; //结果个数 

void nqueen(int n, int QUEEN) //判断皇后 
{
	srand((unsigned)time(NULL)); 
	if(n == QUEEN) //出口条件是判断到第QUEEN行 
	{
		return;
	}
	int i;
	for(i = 0; i < QUEEN; i ++) //放第n行第i列 
	{
		int j;
		for(j = 0; j < n; j ++) //判断能否放置 
		{
			if(i == nowtry[j] || abs(i - nowtry[j]) == abs(n - j)) //有矛盾 
			{
				break;
			}
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
	FILE * fp;
	int n, queen; 
	
	printf("输入皇后个数：");
	scanf("%d", &queen);
	
	clock_t start,end;
	start = clock();
	
	nqueen(0, queen);//计算 
	
	end = clock();
	printf(" %d 皇后问题的计算时间为 %f s\n", queen, (double)(end-start)/CLK_TCK);
	
	fp = fopen("result.txt", "w");
	for(int i = 0; i < queen; i ++)
	{
		printf("%d ", nowtry[i] + 1);
		fprintf(fp, "%d ", nowtry[i] + 1);
	}
	printf("\n输出完成");
}

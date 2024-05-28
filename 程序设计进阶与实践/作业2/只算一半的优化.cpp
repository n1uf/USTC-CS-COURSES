#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define MAX 1000000
#define QUEENNUM 50

int nowtry[QUEENNUM]; //���ڳ��� 
int cnt = 0; //������� 

void nqueen(int n, int QUEEN) //�жϻʺ� 
{
	srand((unsigned)time(NULL)); 
	if(n == QUEEN) //�����������жϵ���QUEEN�� 
	{
		return;
	}
	int i;
	for(i = 0; i < QUEEN; i ++) //�ŵ�n�е�i�� 
	{
		int j;
		for(j = 0; j < n; j ++) //�ж��ܷ���� 
		{
			if(i == nowtry[j] || abs(i - nowtry[j]) == abs(n - j)) //��ì�� 
			{
				break;
			}
		}
		if(j == n) //��֮ǰ�ڷŵ�ÿһ�ж���ì�� 
		{ 
			nowtry[n] = i; //��n�лʺ����i�� 
			nqueen(n + 1, QUEEN); //�ж���һ�� 
		}
	}
	
}

int main(void)
{ 
	FILE * fp;
	int n, queen; 
	
	printf("����ʺ������");
	scanf("%d", &queen);
	
	clock_t start,end;
	start = clock();
	
	nqueen(0, queen);//���� 
	
	end = clock();
	printf(" %d �ʺ�����ļ���ʱ��Ϊ %f s\n", queen, (double)(end-start)/CLK_TCK);
	
	fp = fopen("result.txt", "w");
	for(int i = 0; i < queen; i ++)
	{
		printf("%d ", nowtry[i] + 1);
		fprintf(fp, "%d ", nowtry[i] + 1);
	}
	printf("\n������");
}

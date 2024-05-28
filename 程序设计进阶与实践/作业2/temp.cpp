#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define MAX 10000
#define QUEENNUM 50

int result[MAX][QUEENNUM]; //���н�� 
int nowtry[QUEENNUM]; //���ڳ��� 

void nqueen(int n, int QUEEN) //�жϻʺ� 
{
	if(n == QUEEN) //�����������жϵ���QUEEN�� 
	{
		return ;
	}
	int i;
	for(i = 0; i < QUEEN; i ++) //�ŵ�n�е�i�� 
	{
		int j;
		for(j = 0; j < n; ) //�ж��ܷ���� 
		{
			if(i == nowtry[j] || abs(i - nowtry[j]) == abs(n - j)) //��ì�� 
			{
				break;
			}
			j ++;//��һ��û��ì�ܣ��ж���һ�� 
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
	int n, queen; 
	
	printf("����ʺ������");
	scanf("%d", &queen);
	
	clock_t start,end;
	start = clock();
	
	nqueen(0, queen);//���� 
	if(n == QUEEN) //�����������жϵ���QUEEN�� 
	{
		return ;
	}
	int i;
	for(i = 0; i < QUEEN; i ++) //�ŵ�n�е�i�� 
	{
		int j;
		for(j = 0; j < n; ) //�ж��ܷ���� 
		{
			if(i == nowtry[j] || abs(i - nowtry[j]) == abs(n - j)) //��ì�� 
			{
				break;
			}
			j ++;//��һ��û��ì�ܣ��ж���һ�� 
		}
		if(j == n) //��֮ǰ�ڷŵ�ÿһ�ж���ì�� 
		{ 
			nowtry[n] = i; //��n�лʺ����i�� 
			nqueen(n + 1, QUEEN); //�ж���һ�� 
		}
	}
	end = clock();
	printf(" %d �ʺ�����ļ���ʱ��Ϊ %f s\n", queen, (double)(end-start)/CLK_TCK);
	
	for(int i = 0; i < queen; i ++)
	{
		printf("%d ", nowtry[i] + 1);
	}
	printf("\n");	
}

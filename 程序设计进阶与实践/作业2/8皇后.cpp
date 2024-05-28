#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define QUEEN 8
#define MAX 1000

int result[MAX][QUEEN]; //���н�� 
int nowtry[QUEEN]; //���ڳ��� 
int cnt = 0; //������� 
void nqueen(int n) //�жϻʺ� 
{
	if(n == QUEEN) //�����������жϵ���QUEEN�� 
	{
		memcpy(result[cnt], nowtry, sizeof(nowtry)); //�ѵ�ǰ���ԵĽ�������ܽ���ĵ�cnt����� 
		cnt ++; //��һ����� 
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
			nqueen(n + 1); //�ж���һ�� 
		}
	}
}

int main(void)
{
	int n;
	nqueen(0);
	scanf("%d", &n);//��n���� 
	for(int i = 0; i < QUEEN; i ++)
	{
		printf("%d ", result[n - 1][i] + 1);
	}
	printf("\n");	
}

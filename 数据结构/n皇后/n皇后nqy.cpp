#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define MAX 1000000
#define QUEENNUM 50

int result[MAX][QUEENNUM]; //���н�� 
int nowtry[QUEENNUM]; //���ڳ��� 
int cnt = 0; //������� 
int line = 0;//����ʱ
 
void nqueen(int n, int QUEEN) //�жϻʺ� 
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
	
	printf("������Ҫ�ڼ����⣺����Χ��1 ~ %d)\n", cnt);
	scanf("%d", &n); //��n���� 
	fp = fopen("resultnqy.txt", "w");
	fprintf(fp, "%d;", queen);
	for(int i = 0; i < queen; i ++)
	{
		fprintf(fp, "%d,", result[n - 1][i] + 1);
		printf("%d ", result[n - 1][i] + 1); 
	}
	printf("\n������\n");
	
	fclose(fp);
}

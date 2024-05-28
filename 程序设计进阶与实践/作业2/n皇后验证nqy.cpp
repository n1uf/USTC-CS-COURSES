#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define QUEENNUM 50
 
int checkans(int oneans[QUEENNUM], int QUEEN)
{
	int t = 0, k = 0;
	for(t = 0; t < QUEEN; t ++)
	{
		int j;
		for(j = t + 1; j < 	QUEEN; j ++) //�ж��ܷ���� 
		{
			if(oneans[t] == oneans[j] || abs(oneans[t] - oneans[j]) == abs(t - j)) //��ì�� 
			{
				return false;
			}
		}
	}
	return true;
}

int main() 
{
	FILE * fp;
	fp = fopen("result.txt", "r");
	
	int queen;
	fscanf(fp, "%d;", &queen);
	int check[queen];
	
	for(int i = 0; i < queen; i ++)
	{
		fscanf(fp, "%d,", &check[i]);
	}
	if(checkans(check, queen))
	{
		printf("ͨ����֤");
	}
	else
	{
		printf("��֤ʧ��");
	}
	
	fclose(fp);
}

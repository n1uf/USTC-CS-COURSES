#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
int main()
{
	int deci[MAX], tmp[MAX], decigoal[MAX];
	int baseori = 8;
	int i, j = 0;
	for(i = 0; i < MAX; i ++)
	{
		deci[i] = 0;
		tmp[i] = 0;
		decigoal[i] = 0;
	}
	deci[0] = 7;
	deci[1] = 3;
	for(i = 0; i < MAX; i ++)
	{
		tmp[i] = deci[i];
	}
	int basegoal;
	printf("将八进制0.73转化为需要的进制(10以内)，精度为1000\n");
	printf("输入需要的进制：");
	scanf("%d", &basegoal);
	int k;
	for(k = 0; k < MAX; k ++)
	{
		for(i = MAX - 1; tmp[i] == 0; i --);
		for(; i >= 0; i --)
		{
			int temp = tmp[i] * basegoal + j;
			for(j = 0; j <= basegoal; j ++)
			{
				if(temp - j * baseori < 0)
				{
					j --;
					tmp[i] = temp - j * baseori;
					break;
				}
			}
		}
		decigoal[k] = j;
		j = 0;
	}
	for(i = MAX; decigoal[i] == 0; i --);
	printf("进制转换后的数字为：0.");
	for(j = 0; j <= i; j ++)
	{
		printf("%d", decigoal[j]);
	}
}

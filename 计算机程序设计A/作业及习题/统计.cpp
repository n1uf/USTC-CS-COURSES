#include <stdio.h>

float aver(float *q);

int fals(float *q);

int well(float *q);

int main(void)
{
	float stu[5][4];
	int i, j;
	for(i = 0; i < 5; i ++)
	{
		for(j = 0; j < 4; j ++)
		{
			scanf("%f",&stu[i][j]);
		}
	}
	float *p;
	p = stu[0];
	float ans1 = aver(p);
	int ans2, ans3;
	ans2 = fals(p);
	ans3 = well(p);
	printf("%.1f %d %d", ans1, ans2, ans3);
}

float aver(float *q)
{
	int i;
	float a = 0.0;
	for(i = 0; i < 5; i ++, q += 4)
	{
		a += *q;
	}
	return (a/5);
}

int fals(float *q)
{
	int i, j, flag = 0, a = 0;
	for(i = 0; i < 5; i ++)
	{
		for(j = 0; j < 4; j ++, q ++)
		{
			if(*q < 60)
			{
				flag ++;
			}
		}
		if(flag >= 2)
		{
			a ++;
			flag = 0;
		}
	}
	return a;
}

int well(float *q)
{
	int i, j, flag = 0, k = 0;
	float a = 0.0;
	for(i = 0; i < 5; i ++)
	{
		for(j = 0; j < 4; j ++, q ++)
		{
			a += *q;
		}
		if(a >= 360)
		{
			flag ++;
		}
		else
		{
			q -= 4;
			for(j = 0; j < 4; j ++, q ++)
			{
				if(*q >= 85)
				{
					k ++;
				}
			}
			if(k == 4)
			{
				flag ++;
			}
			k = 0;
		}
		a = 0;
	}
	return flag;
}

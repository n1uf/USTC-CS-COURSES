/*ÆæÊý±¶Êý*/ 
#include <stdio.h>
#define LEN 10000

int check(int *t)
{
	int j, k = 0;
	int a[LEN];
	while(*t)
	{
		a[k] = *t % 10;
		*t /= 10;
		k ++;
	}
	for(j = 0; j < k; j ++)
	{
		if(a[j] % 2 == 0)
		{
			break;
		}
	}
	if(a[j] % 2 == 0)
	{
		return 1;
	}
	if(a[j] % 2 != 0)
	{
		return 0;
	}
};

int main()
{
	int x[LEN], y[LEN], z[LEN];
	int i, j = 0;
	x[0] = 2019; 
	int *p = x;
	for(i = 1; check(p); i ++)
	{
		x[0] = 2019 * (i + 1);
		y[0] = x[0];
		while(x[0] != 0)
		{
			x[0] /= 10;
			j ++;
		}
		z[0] = j;
		j = 0;
		x[0] = y[0];
		p = x;
	}
	printf("%d", x[i]);
}

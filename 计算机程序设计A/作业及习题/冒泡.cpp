/*ж╠╫сп╢еепРак*/

#include <stdio.h>

int main()
{
	int n;
	scanf("%d", &n);
	int i, j;
	float a[n], b[n], m;
	int num[n];
	for(i = 0; i < n; i ++)
	{
		scanf("%f", &a[i]);
	}
	for(i = 0; i < n; i ++)
	{
		b[i] = a[i];
	}
	for(i = 0; i <= 9; i ++)
	{
		for(j = 0; j <= 9; j ++)
		{
			if(a[j] < a[j + 1])
			{
				m = a[j];
				a[j] = a[j + 1];
				a[j + 1] = m;
			}
		}
	}
	for(i = 0; i < n; i ++)
	{
		printf("%f ", a[i]);
	}
	putchar(10);
	for(i = 0; i < n; i ++)
	{
		for(j = 0; j < n; j ++)
		{
			if(b[i] == a[j])
			{
				num[i] = n - j;
				printf("%d ",num[i]);
			}
		}
	}
}

#include <stdio.h>
int main()
{
	int n,i,j;
	scanf("%d",&n);
	int a[n][n];
	for(i = 0; i <= n - 1; i ++)
	{
		for(j = 0; j <= n - 1; j ++)
		{
			a[i][j] = 0;
		}
	}
	
	/*放第一个数字*/ 
	i = 0;
	j = n / 2;
	a[i][j] = 1;
	
	/*从第二个开始放数字*/ 
	int t;
	for(t = 2; t <= n * n; t ++)
	{
		/*各种情况*/ 
		if(i == 0 && j != n - 1)
		{
			i = n - 1;
			j = j + 1; 
			if(a[i][j] == 0) a[i][j] = t;
			else
			{
				i = 1;
				j = j - 1;
				a[i][j] = t;
			}
		}
 
		else if(i != 0 && j == n-1)
		{
			i = i - 1;
			j = 0;
			if(a[i][j] == 0) a[i][j] = t;
			else
			{
				i = i + 1;
				j = n - 1;
				a[i][j] = t;
			}
		}
 
	   else if(i == 0 && j == n-1)
		{
			i = n - 1;
			j = 0;
			if(a[i][j] == 0) a[i][j] = t;
			else
			{
				i = 1;
				j = n - 1;
				a[i][j] = t;
			}
		}
 
		else
		{
			i = i - 1;
			j = j + 1;
			if(a[i][j] == 0) a[i][j] = t;
			else
			{
				i = i + 2;
				j = j - 1;
				a[i][j] = t;
			}
		}
	}
	
	/*输出*/ 
	for(i = 0; i <= n - 1; i ++)
	{
		for(j = 0; j <= n - 1; j ++)
		{
			printf("%5d",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}

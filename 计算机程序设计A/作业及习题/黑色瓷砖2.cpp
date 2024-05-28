#include<stdio.h>
/*定义全局变量*/ 
int m, n, x, y;
int map[101][101];
void check(int a, int b);

int main()
{
	int i,j,sum;
	scanf("%d %d %d %d",&m, &n, &x, &y);
	for (i = 0; i < m; i ++)
	{
		for (j = 0; j < n; j ++)
		{
			scanf("%d", &map[i][j]);
		}
	}
	check(x, y);
	for (i = 0; i <= m - 1; i ++)
	{
		for (j = 0; j < n; j ++)
		{
			if (map[i][j] == 2)
			{
				sum ++;
			}
		}
	}
	printf("%d", sum);
	return 0;
}

void check(int a, int b)
{
	if (map[a][b] == 0 && a >= 0 && b >= 0 && a < m && b < n)
	{ 
			map[a][b] = 2;
		    check(a + 1,b);
			check(a,b + 1);
			check(a - 1,b);
			check(a,b - 1); 
	}
}



#include <stdio.h>
#include <string.h>

int min(int a, int b);

int main()
{
    int n, a[101], sum = 0, m[101][101];
    scanf("%d", &n);
    int i, j, k;
    for(i = 0; i < n; i ++)
    {
    	scanf("%d",&a[i]);
	}
    memset(m, 0, sizeof(m));
    for(i = 0; i < n; i ++)
    {
    	m[i][i] = a[i];
	}
    for(i = n - 1; i >= 0; i --)
    {
        for(j = i + 1; j < n; j ++)
        {
            sum = 0;
            for(k = i; k <= j; k ++)
            {
            	sum += a[k];
			}
            m[i][j] = sum - min(m[i + 1][j], m[i][j - 1]);
        }
    }
    sum = 0;
    for(k = 0; k <= n - 1; k ++)
    {
    	sum += a[k];
	}
	int x, y;
	x = m[0][n - 1];
	y = sum - x;
    printf("%d %d", x, y);
}

int min(int a, int b)
{
	if(a >= b)
	{
		return b;
	}
	else
	{
		return a;
	}
}

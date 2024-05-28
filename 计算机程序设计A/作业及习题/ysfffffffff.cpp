#include <stdio.h>
int main()
{
    int n,s,m;
    int i = -1,p,q;
    scanf("%d %d %d",&n,&s,&m);
    int a[1024]; 
    i = s - 2;
    for (p = 0; p <= n - 1; p ++)
    {
        a[p] = 1;
        //printf("%d ",a[i]);
    }
    for (p = 0; p < n - 1; p ++)
    {
        for (q = 0; q < m; q ++)
        {
            i ++;
            if (i == n)
            {
                i = 0;
            }
            if (a[i] == 0)
            {
                q--;
            }
        }
        a[i] = 0;
        printf("%d ", i + 1);
    }
    for (p = 0; p < n; p ++)
    {
        if (a[p] == 1)
		{
			printf("%d", p + 1);
    	}
	}
    return 0;
}

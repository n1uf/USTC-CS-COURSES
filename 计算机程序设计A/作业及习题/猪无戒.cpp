#include <stdio.h>
int main()
{
	/*ÊäÈë¾ØÕó*/ 
    int m, n;
    scanf("%d %d", &m, &n);
    int str[m][n];
    int a, b; 
    for (a = 0; a < m; a++)
    {
        for (b = 0; b < n; b++)
        {
            scanf("%d", &str[a][b]);
        }
    }
    int M = 0;
    int c, d, x, y;       
    int e = 0, f = 0, g = 0, h = 0; 
    for (a = 0; a < m; a++)
    {
        for (b = 0; b < n; b++)
        {
            for (c = a; c < m; c++)
            {
                for (d = b; d < n; d++)
                {
                    int t = 0;
                    for (x = a; x <= c; x++)
                    {
                        for (y = b; y <= d; y++)
                        {
                            t = t + str[x][y];
                        }
                    }
                    if (t > M)
                    {
                        M = t;
                        e = a;
                        f = b;
                        g = c;
                        h = d;
                    }
                }
            }
        }
    }
    int A, B, C, D;
    A = e + 1;
    B = f + 1;
    C = g + 1;
    D = h + 1;
    printf("(%d, %d) (%d, %d) %d", A, B, C, D, M);
    return 0;
} 

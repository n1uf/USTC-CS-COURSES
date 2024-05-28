#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 201
#define MAXC 1001

int dp[MAXN][MAXN];
int sum[MAXN];
int c[MAXN];

int main()
{

    memset(dp, 0x3f, sizeof(dp));

    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &c[i]);
        sum[i] = sum[i - 1] + c[i];
        dp[i][i] = 0;
    }
    for (int len = 2; len <= n; len ++)
    {
        for (int i = 1; i <= n - len + 1; i ++)
        {
            int j = i + len - 1;
            for (int k = i; k < j; k++)
            {
                if(dp[i][j] > dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1])
                    dp[i][j] = dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1];
            }
        }
    }

    printf("%d\n", dp[1][n]);
    return 0;
}

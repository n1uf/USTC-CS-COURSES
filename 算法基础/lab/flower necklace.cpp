#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10001

int main()
{
    int n, m;
    char s[MAXN], t[MAXN];
    scanf("%d%s", &n, s);
    scanf("%d%s", &m, t);

    int **dp;
    dp = (int**)malloc(sizeof(int*) * (n + 1));
    for(int i = 0; i <= n; i ++)
        dp[i] = (int*)malloc(sizeof(int) * (m + 1));

    for(int i = 0; i <= n; i ++)
        for(int j = 0; j < m; j ++)
            dp[i][j] = 0;

        
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            if(s[i - 1] == t[j - 1])
                dp[i][j]=dp[i - 1][j - 1] + 1;
            else if(dp[i][j - 1] > dp[i - 1][j])
                dp[i][j] = dp[i][j-1];
            else
                dp[i][j] = dp[i-1][j];
    printf("%d\n", dp[n][m]);
    return 0;
}

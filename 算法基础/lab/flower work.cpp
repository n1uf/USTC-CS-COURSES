#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000001
#define MAXA 10001

int main()
{
    int n;
    scanf("%d", &n);
    int *a;
    a = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i ++)
        scanf("%d", &a[i]);

    int *dp;
    dp = (int*)malloc(sizeof(int) * (n + -1));

    dp[0] = 0;
    dp[1] = a[0];

    for(int i = 2; i <= n; i ++)
        if(dp[i - 1] > (dp[i - 2] + a[i - 1]))
            dp[i] = dp[i - 1];
        else 
            dp[i] = dp[i - 2] + a[i - 1];

    printf("%d\n", dp[n]);
    return 0;
}

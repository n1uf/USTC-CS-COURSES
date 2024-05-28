#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

void multiply(long long A[2][2], long long B[2][2], long long C[2][2])
{
    int i, j, k;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < 2; k++)
            {
                C[i][j] = (C[i][j] + (A[i][k] * B[k][j]) % MOD) % MOD;
            }
        }
    }
}

void matrixPow(long long A[2][2], int n, long long result[2][2])
{
    int i, j;
    long long temp[2][2];

    // 初始化结果矩阵为单位矩阵
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            result[i][j] = (i == j) ? 1 : 0;
        }
    }

    while (n > 0)
    {
        if (n % 2 == 1)
        {
            multiply(result, A, temp);
            for (i = 0; i < 2; i++)
            {
                for (j = 0; j < 2; j++)
                {
                    result[i][j] = temp[i][j];
                }
            }
        }
        multiply(A, A, temp);
        for (i = 0; i < 2; i++)
        {
            for (j = 0; j < 2; j++)
            {
                A[i][j] = temp[i][j];
            }
        }
        n /= 2;
    }
}

long long fibonacci(int n)
{
    long long base[2][2] = {{1, 1}, {1, 0}};
    long long result[2][2];

    matrixPow(base, n - 1, result);
    return result[0][0] % MOD;
}

int main()
{
    int n;
    scanf("%d", &n);

    long long result = fibonacci(n);
    printf("%lld\n", result);

    return 0;
}

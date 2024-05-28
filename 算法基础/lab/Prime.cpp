#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int countPrimes(int L, int R)
{
    int size = R - L + 1;
    int *isPrime = (int *)malloc(size * sizeof(int)); // 动态分配标记数组，初始都为素数
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        isPrime[i] = 1; // 初始化为素数
    }

    int limit = sqrt(R); // 素数筛法的上限
    for (int i = 2; i <= limit; i++)
    {
        for (int j = fmax(i * i, (L + i - 1) / i * i); j <= R; j += i)
        {
            isPrime[j - L] = 0; // 将区间内i的倍数标记为非素数
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (isPrime[i])
        {
            count++;
        }
    }

    free(isPrime); // 释放动态分配的内存
    return count;
}

int main()
{
    int L, R;
    scanf("%d %d", &L, &R);

    int result = countPrimes(L, R);
    printf("%d\n", result);

    return 0;
}

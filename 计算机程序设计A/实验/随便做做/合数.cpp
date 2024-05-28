#include <stdio.h> 
#include <math.h>

int main() 
{
    int i, n, count = 0;
    for (n = 2; n <= 2021; n++) 
	{
        int sqrtn = sqrt(n);
        for (i = 2; i <= sqrtn; i++) 
		{ 
            // 判断是否为素数
            if (n % i == 0) 
                break;
        }
        if (i == sqrtn + 1) 
		{
            continue; // n 为素数
        }
        // 为合数，输出
        printf("%d ", n); // 1 point
        count++;
        if (count % 5 == 0) 
		{ // 每输出 5 个数换一行
            printf("\n");
        }
    }
    return 0;
}


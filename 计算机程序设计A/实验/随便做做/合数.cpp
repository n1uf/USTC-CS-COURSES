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
            // �ж��Ƿ�Ϊ����
            if (n % i == 0) 
                break;
        }
        if (i == sqrtn + 1) 
		{
            continue; // n Ϊ����
        }
        // Ϊ���������
        printf("%d ", n); // 1 point
        count++;
        if (count % 5 == 0) 
		{ // ÿ��� 5 ������һ��
            printf("\n");
        }
    }
    return 0;
}


/*ð������*/

#include <stdio.h>
int main(void)
{
	int len;
	scanf("%d", &len);
	int i, a[len];
	for(i = 0; i < len; i ++)
	{
		scanf("%d", &a[i]);
	}
	int j;
	for(i = 0; i < len; i ++)// ���� len-1 �ε���
	{
		for(j = 0; j < len - i; j ++)// len-i-1 �� len-1��i��Ԫ���Ѿ�����
		{
			/*��С��������*/ 
			if(a[j] >= a[j + 1])// ������ڵ�Ԫ�ش�������н���
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	for(i = 0; i < len; i ++)
	{
		printf("%d ", a[i]);
	}
}

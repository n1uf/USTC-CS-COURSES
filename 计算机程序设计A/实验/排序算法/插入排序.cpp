/*��������*/
#include <stdio.h>
int main()
{
	int len;
	scanf("%d", &len);
	int i, a[len];
	for(i = 0; i < len; i ++)
	{
		scanf("%d", &a[i]);
	}
	int j;
	for(i = 1; i < len; i ++)// ���� len-1 �ε���
	{
		int temp = a[i];
		for(j = i - 1; j >= 0 && temp < a[j]; j --)// ��iǰ���Ԫ�ز��ϵ�������Ų
		{
			a[j + 1] = a[j];
		}
		a[j + 1] = temp;// ����i��Ԫ�ز��뵽��ȷ��λ��
	}
	for(i = 0; i < len; i ++)
	{
		printf("%d ", a[i]);
	}
} 

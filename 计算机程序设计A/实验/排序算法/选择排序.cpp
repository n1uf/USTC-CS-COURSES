/*ѡ������*/

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
	for(i = 0; i < len; i ++)//len�ε��� 
	{
		int min = i;
		for(j = i; j < len; j ++)//�ҵ�i��len����Сֵ 
		{
			if(a[min] > a[j])
			{
				min = j;
			}
		}
		if(i != min)//��ǰλ�ò�����С���򽻻� 
		{
			int temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
	}
	for(i = 0; i < len; i ++)
	{
		printf("%d ", a[i]);
	}
} 

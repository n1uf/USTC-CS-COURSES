/*选择排序法*/

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
	for(i = 0; i < len; i ++)//len次迭代 
	{
		int min = i;
		for(j = i; j < len; j ++)//找到i到len的最小值 
		{
			if(a[min] > a[j])
			{
				min = j;
			}
		}
		if(i != min)//当前位置不是最小的则交换 
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

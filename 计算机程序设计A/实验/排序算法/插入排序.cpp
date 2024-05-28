/*插入排序法*/
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
	for(i = 1; i < len; i ++)// 进行 len-1 次迭代
	{
		int temp = a[i];
		for(j = i - 1; j >= 0 && temp < a[j]; j --)// 将i前面的元素不断的往后面挪
		{
			a[j + 1] = a[j];
		}
		a[j + 1] = temp;// 将第i个元素插入到正确的位置
	}
	for(i = 0; i < len; i ++)
	{
		printf("%d ", a[i]);
	}
} 

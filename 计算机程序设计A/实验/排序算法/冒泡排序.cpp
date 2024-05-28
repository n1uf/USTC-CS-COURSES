/*冒泡排序法*/

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
	for(i = 0; i < len; i ++)// 进行 len-1 次迭代
	{
		for(j = 0; j < len - i; j ++)// len-i-1 到 len-1这i个元素已经有序
		{
			/*从小到大排序*/ 
			if(a[j] >= a[j + 1])// 如果相邻的元素错序则进行交换
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

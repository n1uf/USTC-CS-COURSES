/*顺序查找*/

#include <stdio.h>

int search(int *a, int key);

int main()
{
	int n;
	printf("输入数组大小:\n");
	scanf("%d", &n);
	int num[n];
	int i;
	printf("输入数字:\n");
	for(i = 0; i < n; i ++)
	{
		scanf("%d", &num[i]);
	}
	int goal;
	printf("输入要查找的数字:\n");
	scanf("%d", &goal);
	int place = search(num, goal);
	printf("位置为%d.", place);
} 

int search(int *a, int key)
{
	int i;
	for(i = 0; a != NULL; i ++)
	{
		if(a[i] == key)
		{
			return (i);
		}
	}
	return -1;
}

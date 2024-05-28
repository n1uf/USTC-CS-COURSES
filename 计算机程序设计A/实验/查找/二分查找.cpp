/*二分查找*/
#include <stdio.h>

int main(void)
{
	printf("输入数字个数:\n");
	int len;
	scanf("%d", &len);
	
	printf("输入从小到大的一组数:\n");
	int i, a[len];
	for(i = 0; i < len; i ++)
	{
		scanf("%d", &a[i]);
	}
	
	int key;
	printf("输入要查找的数字:\n");
	scanf("%d", &key);
	
	/*查找*/ 
	int low = 0, high = len - 1;
	while(low <= high)
	{
		int mid = (high + low) / 2;
		if(a[mid] == key)
		{
			printf("%d" ,mid);
			break;
		}
		else if(a[mid] > key)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
} 

/*���ֲ���*/
#include <stdio.h>

int main(void)
{
	printf("�������ָ���:\n");
	int len;
	scanf("%d", &len);
	
	printf("�����С�����һ����:\n");
	int i, a[len];
	for(i = 0; i < len; i ++)
	{
		scanf("%d", &a[i]);
	}
	
	int key;
	printf("����Ҫ���ҵ�����:\n");
	scanf("%d", &key);
	
	/*����*/ 
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

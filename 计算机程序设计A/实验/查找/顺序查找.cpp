/*˳�����*/

#include <stdio.h>

int search(int *a, int key);

int main()
{
	int n;
	printf("���������С:\n");
	scanf("%d", &n);
	int num[n];
	int i;
	printf("��������:\n");
	for(i = 0; i < n; i ++)
	{
		scanf("%d", &num[i]);
	}
	int goal;
	printf("����Ҫ���ҵ�����:\n");
	scanf("%d", &goal);
	int place = search(num, goal);
	printf("λ��Ϊ%d.", place);
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

/*	�㷨������a[]��ų�ʼ���У�b[]��������кͣ�b[i]����a[i]Ϊβ�������кͣ�
	�Ҳ��ϸ���b[i]����ֵʹ���Ϊ��a[i]Ϊβʱ����������кͣ����ѡ��b[]�е������	*/ 

#include <stdio.h>
#define max 1000

int main()
{
	int a[max], b[max], i, n;
	
	scanf("%d", &n);
	
	for(i = 0; i < n; i ++)
	{
		scanf("%d", &a[i]);
	}
	
	b[0] = a[0];
	
	for(i = 1; i < n; i ++)						//n 
	{
		if(a[i] > a[i] + b[i - 1])
		{
			b[i] = a[i];
		}
		else b[i] = a[i] + b[i - 1];
	}
	
	int p = b[0];
	
	for(i = 1; i < n; i ++)						//n
	{
		if(b[i] > p)
		{
			p = b[i];
		}
	}
	printf("%d", p);
	return 0;
}												//ʱ�临�Ӷ�ΪO(n) 

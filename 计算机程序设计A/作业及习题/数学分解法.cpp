#include<stdio.h>
int main()
{
	int num;
	int a[10];
	int i,j,l,k;
	
	/*��ʼ��*/ 
	i=0;
	
	/*����*/
	scanf("%d",&num);
	
	/*�������*/
	while(num > 0)
	{
		a[i] = num % 10;
		num /= 10;
		i ++;
	}
	
	/*��С����*/ 
	for(j = 0; j < i - 1; j ++)
	{
		for(k = j; k < i; k ++)
		{
			if(a[j] < a[k])
			{
				l = a[j];
				a[j] = a[k];
				a[k] = l;
			}
		}	
	}
	/*����*/ 
	for(j = 0; j < i; j ++)
	printf("%d ",a[j]);
	
	return 0; 
 } 

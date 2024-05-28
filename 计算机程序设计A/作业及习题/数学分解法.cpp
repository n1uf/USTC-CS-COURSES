#include<stdio.h>
int main()
{
	int num;
	int a[10];
	int i,j,l,k;
	
	/*初始化*/ 
	i=0;
	
	/*输入*/
	scanf("%d",&num);
	
	/*拆解数字*/
	while(num > 0)
	{
		a[i] = num % 10;
		num /= 10;
		i ++;
	}
	
	/*大小排序*/ 
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
	/*排序*/ 
	for(j = 0; j < i; j ++)
	printf("%d ",a[j]);
	
	return 0; 
 } 

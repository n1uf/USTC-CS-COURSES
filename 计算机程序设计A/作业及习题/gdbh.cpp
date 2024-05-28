#include<stdio.h>
int prime(int m);
int main()
{
	int a,b,c;
	scanf("%d %d",&a,&b);
	for(; a <= b ; a += 2)
	{
		for(c = 3; c <= b ; c += 2)
		{
			if(prime(c)&&prime(a-c))
			{
				printf("%d=%d+%d\n",a,c,a-c);break;
			}
		}
	}
	return 0;
 } 
 
int prime(int m){
	int i;
	for(i = 2; i < m; i++)
	{
		if(m%i == 0)
		{
			return 0;
		}
	} 
	return m;	
} 

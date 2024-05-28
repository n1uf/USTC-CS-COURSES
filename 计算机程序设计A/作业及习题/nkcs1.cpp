#include<stdio.h>
int main()
{
	int n,N,a,s,k,i;
	scanf("%d",&n);
	N=n*n*n;
	if(N % 2 == 0)
	{
		a = N - 1;	
	}
	else
	{
		a = N - 2;
	}
	i=0;
	while (!(s==N))
	{
	for(s = 0,k = 0;s <= N;a -= 2)
	{
		s = a + s;
		k += 1;
		i += 1;
		if (s==N)
		{
			printf("%d %d",a,k);break;
		}
	}
	a += 2*k-2;
	}
	return 0;
}

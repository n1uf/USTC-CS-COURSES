#include <stdio.h>
int main()
{
	int i=100,a,b,c;
	for( ; i<1000; i++)
	{
		a=i%10;
		b=i/10%10;
		c=i/100%10;
		if(i==(a*a*a+b*b*b+c*c*c))
		printf("%d\t", i);
	}
	return 0;
}

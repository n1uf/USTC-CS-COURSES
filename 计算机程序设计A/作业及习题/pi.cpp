#include<stdio.h>
#include<math.h>
int main()
{
	double pi,a,b,c,d,k;
	k = 0.0;
	pi = 0.0;
	b = 16.0;
	scanf("%le",&a);
	c = 1/pow(b,k);
	d = (c*(4/(8*k+1)-2/(8*k+4)-1/(8*k+5)-1/(8*k+6)));
	pi += d;
	while(d>=a)
	{
		k = k+1.0;
		c = 1/pow(b,k);
		d = c*(4/(8*k+1)-2/(8*k+4)-1/(8*k+5)-1/(8*k+6));
		pi += d;
	}
	printf("%.0lf\n",k);
	printf("%lf",pi);
	return 0;
} 

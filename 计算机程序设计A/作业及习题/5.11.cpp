#include<stdio.h>
int main()
{
	int i;
	double s=100,a=100,b=0;
	for(i=1;i<=10;i++)
	{
		s=s+b;
		a=a/2;
		b=a;
	}
	printf("共经过%lf米。\n第十次反弹%lf米。\n",s,a);
	return 0;
}

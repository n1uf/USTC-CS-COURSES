#include<stdio.h>
int main()
{
	int max(int x,int y,int z);
	int a,b,c,d;
	scanf("%d,%d,%d",&a,&b,&c);
	d=max(a,b,c);
	printf("max=%d\n",d);
	return 0;
 } 
 int max(int x,int y,int z)
 {
 	int p;
 	if(x>y)
 	{
 		if(x>z)
 		p=x;
 		else
 		p=z;
	 }
	else
	{
		if(y>z)
		p=y;
		else
		p=z;
	}
	return(p);
 }

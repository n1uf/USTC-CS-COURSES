#include<stdio.h>
#define PI 3.1415926
int main()
{
	float r,h,a,b,c,d,e;
	scanf("r=%f,h=%f",&r,&h);
	a=2*PI*r;
	b=PI*r*r;
	c=4*PI*r*r;
	d=(4/3)*PI*r*r*r;
	e=b*h;
	printf("圆周长为%.2f.\n圆面积为%.2f.\n圆球表面积为%.2f.\n圆球体积为%.2f.\n圆柱体积为%.2f.\n",a,b,c,d,e);
	return 0;
}

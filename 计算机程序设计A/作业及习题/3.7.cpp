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
	printf("Բ�ܳ�Ϊ%.2f.\nԲ���Ϊ%.2f.\nԲ������Ϊ%.2f.\nԲ�����Ϊ%.2f.\nԲ�����Ϊ%.2f.\n",a,b,c,d,e);
	return 0;
}

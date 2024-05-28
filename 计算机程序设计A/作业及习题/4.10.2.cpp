#include<stdio.h>
int main()
{
	int I;
	float a;
	scanf("%d",&I);
	printf("应发奖金为");
	switch((I-1)/100000)
	{
	case 0:a=I*0.1,printf("%.3f.",a);break;
	case 1:a=100000*0.1+(I-100000)*0.075,printf("%.3f.",a);break;
	case 2:
	case 3:a=100000*0.1+100000*0.075+(I-200000)*0.05,printf("%.3f.",a);break;
	case 4:
	case 5:a=100000*0.1+100000*0.075+200000*0.05+(I-400000)*0.03,printf("%.3f.",a);break;
	case 6:
	case 7:
	case 8:
	case 9:a=100000*0.1+100000*0.075+200000*0.05+200000*0.03+(I-600000)*0.015,printf("%.3f.",a);break;
	default:a=100000*0.1+100000*0.075+200000*0.05+200000*0.03+400000*0.015+(I-1000000)*0.01,printf("%.3f.",a);
	}
	return 0;
 } 

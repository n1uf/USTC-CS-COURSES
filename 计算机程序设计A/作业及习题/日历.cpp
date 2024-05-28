#include<stdio.h>
int main()
{
    int y,c,m,d,w,Y,M,a,i,k,n;
    n=0; 
    scanf("%d %d", &Y, &M);
    printf("Sun   Mon   Tur   Wed   Thu   Fri   Sat   \n");
    y = Y%100;
  	c = Y/100;
    m = M;d = 1; 
    if (m == 1||m == 2) 
	{ 
        y--;
        m +=12;
    }
    w =(y+y/4+c/4-2*c+13*(m+1)/5+d+6)%7;
	if (M==2)
	/*注意，此时y不是真实的年份，判断时应该+1*/ 
	{
		if (y+1==0&&c%4==0) i=29; 
		else if (!(y+1==0)&&Y%4==0) i=29;
		else i=28;
	}
    else if (M==1||M==3||M==5||M==7||M==8||M==10||M==12) i=31;
    else i=30;
    if(Y%1000==0) w=w-1;
    for (k=w;k>0;k--)
	{
    printf("      ");
	n++;
	}
    for (a=1;a<=i;a++)
	{
      printf("%2.d    ",a);
      n++;
      if(n%7==0) printf("\n");
	}
	return 0;
}

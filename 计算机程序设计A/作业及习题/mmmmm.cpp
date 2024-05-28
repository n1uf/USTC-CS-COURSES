#include<stdio.h>
int main()
{
	int j,i,t,l,s,a,sign;
	char op[4] = {'+','-','*','/'};
	int p[4]; 
	int cal[6];
    for (j = 0; j <= 5 ; j ++)
        scanf("%d",&cal[j]);
	for(i = 0;i <= 255;i ++)
	{
	    sign = 1;
		l = 0;
		s = cal[0];
		a = 0;
		p[3] = i / 64 % 4;
		p[2] = i / 16 % 4;
		p[1] = i / 4 % 4;
		p[0] = i / 1 % 4;
		for(t = 3;t >= 0;t --,a ++)
		{
			switch(p[t])
			{
				case 0:
				    l = l + sign * s;
				    sign = 1;
					s = cal[a + 1];
					break; 
				case 1:
				    l = l + sign * s;
				    sign = -1;
				    s = cal[a + 1];
				    break;
				case 2:
					s = s * cal[a + 1];
					break;
				case 3:
					s = s / cal[a + 1];
					break;
			}
		}
		if(l + s * sign == cal[5])
		{
		    printf("%c %c %c %c",op[p[3]],op[p[2]],op[p[1]],op[p[0]]);break;
		}
		if(l + s * sign == cal[5])	break;	
	}
	if(l + s * sign != cal[5])
	{
	printf("No solution"); 
	}
	return 0;  
}

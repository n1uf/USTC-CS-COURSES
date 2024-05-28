#include<stdio.h>
#include<math.h>
int main(void)
{
	int a, b;
	
	/*存商和余数*/
	int m[1024], n[1024];
	int i, j, s = 0, t;
	
	/*输入*/ 
	scanf("%d %d",&a, &b);
	m[0] = a * 10 / b;//商 
	n[0] = a * 10 - m[0] * b;//余数 
	for(i = 0; i < 500; i ++)
	{
	    m[i + 1] = n[i] * 10 / b;//每次计算 
	    
	    
	    if(m[i + 1] == 0) 
		{
			n[i + 1] = n[i] * 10;
		} 
	    else
	    {
	    	n[i + 1] = n[i] *10 - m[i + 1] * b;
		}
		
	    /*可以整除则break*/ 
	    if(n[i] == 0) 
		{
	    	s = 1;
	    	break;
		}
		for(j = i; j >= 0; j --) 
		{
			if(n[i + 1] == n[j])
			{
				if(m[i + 1] == m[j])//相等分为两种情况，余数和商都相等或余数和商只有一个相等，对应两种输出方式 
				{
					printf("0.");
				    for(t = 0; t <= i ; t ++)
				    {
						printf("%d",m[t]);
				    }
					printf("(");
					for(t = j ; t <= i ; t ++) 
					{
						printf("%d",m[t]);
					}
					printf(")");
					s = 2;
					break;
				}
				else
				{
					printf("0.");
					for(t = 0; t <= i + 1; t ++)
					{
						printf("%d",m[t]);
					}
					printf("(");
					for(t = j + 1; t <= i + 1; t ++) 
					{
					printf("%d",m[t]);
					}
					printf(")");
					s = 2;
					break;
				}
			}
		}
		if(s == 2)
		{
			break;
		}
	}
	
	
	if(s == 1)
	{
		printf("0.");
		for(t = 0; t < i + 1; t ++)
		{
			printf("%d",m[t]);
		}
	}
}

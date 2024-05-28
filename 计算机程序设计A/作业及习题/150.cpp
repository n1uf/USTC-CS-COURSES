#include<stdio.h>
int cal(int l,int r,int o);
int main()
{
	int a,b,c,d,e,s;
	scanf("%d %d %d %d %d %d",&a,&b,&c,&d,&e,&s);
	int ans1 = 0,ans2 = 0,ans3 = 0,ans4 = 0;
	int i1,i2,i3,i4;
	char ope_[4]={'+','-','*','/'};
	for(ans1 = 0,i1 = 0; i1 <= 3; i1 ++)
	{
		ans1 = cal(a,b,i1);
		for(ans2 = 0,i2 = 0; i2 <= 3; i2 ++)
		{
			ans2 = cal(ans1,c,i2);
			for(ans3 = 0,i3 = 0; i3 <= 3; i3 ++)
			{
				ans3 = cal(ans2,d,i3);
				for(ans4 = 0,i4 = 0; i4 <= 3; i4 ++)
				{
					ans4 = cal(ans3,e,i4);
					if(ans4 == s)
					{
						printf("%c %c %c %c",ope_[i1],ope_[i2],ope_[i3],ope_[i4]); goto end;
					}
				}
			}
		}
	}
end:if(!(ans4 == s))
	{
		printf("No solution");
	}
  	return 0;
} 

/*定义一个三个数字运算的函数*/ 
int cal(int m,int n,int ans)
{
	switch(ans)
	{
		case 0:return m + n;
		case 1:return m - n;
		case 2:return m * n;
		case 3:return m / n;
	}
 	return 0;
}

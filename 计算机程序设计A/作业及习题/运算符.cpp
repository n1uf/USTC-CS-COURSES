#include<stdio.h>
int cal(int l,int r,int o);
int main()
{
	int a,b,c,d,e,s;
	scanf("%d %d %d %d %d %d",&a,&b,&c,&d,&e,&s);
	int ans1 = 0,ans2 = 0,ans3 = 0,ans4 = 0;
	int i1,i2,i3,i4;
	char ope_[5]={'0','+','-','*','/'};
	for(ans1 = 0,i1 = 1;i1 <= 4;i1 ++)
	{
		ans1 = cal(a,b,i1);
		//printf("%d ans1\n",ans1);
		for(ans2 = 0,i2 = 1;i2 <= 4;i2 ++)
		{
			ans2 = cal(ans1,c,i2);
			//printf("%d ans2\n",ans2);
			for(ans3 = 0,i3 = 1;i3 <= 4;i3 ++)
			{
				ans3 = cal(ans2,d,i3);
				//printf("%d ans3\n",ans3);
				for(ans4 = 0,i4 = 1;i4 <= 4;i4 ++)
				{
					ans4 = cal(ans3,e,i4);
					//printf("%d ans4\n",ans4);
					if(ans4 == s)
					{
						printf("%c %c %c %c",ope_[i1],ope_[i2],ope_[i3],ope_[i4]);goto end;
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

int cal(int l,int r,int o)
{
	switch(o)
	{
		case 1:return l + r;
		case 2:return l - r;
		case 3:return l * r;
		case 4:return l / r;
	}
  	return 0;
}

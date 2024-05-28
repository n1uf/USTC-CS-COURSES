#include<stdio.h>

int main()
{
 	int n,s,m,i,j,k,p,q,t;
 	int a[1024];
 	scanf("%d %d %d",&n,&s,&m);
 	for(i=0;i<=n-1;i++)
 	{
 		a[i]=i+1;
 		//printf("%d",a[i]);
	}
	for(j=s+m-2,k=1;k<=n;k++)
	{
		a[j]=0;
		printf("%d ",j+1);
		j+=m;
		t=j;
		if(t<=n-1)
		{
			for(p=t-m;p<=t;p++)
			{
				if(a[p]==0)
				{
					j++; 
				}
			}
		}
		else
		{
			for(p=t-m;p<=n-1;p++)
			{
				if(a[p]==0)
				{
					j++; 
				}
			}
			for(p=0;p<=j-n;p++)
			{
				if(a[p]==0)
				{
					j++; 
				}
			}
		} 
		if(j>=n)
		{
			j-=n;
		}
		//printf("%d %d %d %d %d\n",a[0],a[1],a[2],a[3],a[4]);
	}
	return 0;
 }

#include<stdio.h>

int main()
{
 	int n,s,m,i,j,k,p,q,t;
 	int a[n];
 	scanf("%d %d %d",&n,&s,&m);
 	for(i=0;i<=n-1;i++)
 	{
 		a[i]=i+1;
 		//printf("%d",a[i]); a[5]={1,2,3,4,5}
	}
	for(j=s+m-2,k=1;k<=n;k++)
	{
		a[j]=0;
		printf("%d\t",j+1);
		j+=m;
		if(j>=n)
		{
			j-=n;
		}
		printf("%d %d %d %d %d\n",a[0],a[1],a[2],a[3],a[4]);
	}
	return 0;
 }

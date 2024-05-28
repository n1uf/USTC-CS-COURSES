#include<stdio.h>

int in(int n,int num[],int b[]);

int _do(int num[],int n); 

int out(int num[],int n) ;

int main()
{
	int a[10001],length,i;
	scanf("%d",&length);
	int b[length];
	for(i = 0; i < length; i ++)
	{
		scanf("%d",&a[i]);
	}
	in(length,a,b);
    _do(b,length);
    out(b,length);
}



int in(int n,int num[],int b[]) 
{
	int i;
	for(i = 0;i <= n - 1;i ++)
	{
		b[i] = num[i]; 
	}
}



int _do(int num[],int n)
{
	int i,j,k,vnum;
	for(i = 0; i < n; i ++)
	{
		for(j = 0; j < i; j ++)
		{
			if(num[i] < num[j])
			{
				vnum = num[i];
				for(k = i - 1; k >= j; k --)
				{
					num[k + 1] = num[k];
				}
				num[j] = vnum;
			}
		}
	}
}



int out(int num[],int n)
{
	int i;
	for(i = 0;i < n;i ++)
	{
	    printf("%d\n",num[i]);
	}
}

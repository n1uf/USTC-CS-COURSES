#include<stdio.h>
int main()
{
	int length;
	scanf("%d",&length);
	int num[length],a;
	for(a = 0; a < length; a ++)
	{
		scanf("%d",&num[a]);
	}
	int i,j,k,vnum;
	for(i = 0; i < length; i ++)
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
	for(a = 0; a < length; a ++)
	{
		printf("%d\n",num[a]);
	}
	return 0;
}

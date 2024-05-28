#include<stdio.h>
int main()
{
	char a[2048];
	int i,j;
	for(i = 0; i <= 2048; i ++)
	{
		for(j = 0; j <= 3; j ++, i ++)
		{
			scanf("%c",&a[i]);
			printf("%c\n",a[i]);
		}
	}
	return 0;
}

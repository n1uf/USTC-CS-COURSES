#include<stdio.h>
int main()
{
	char input[3],a[5],b[5];
	int i,j,k;
	for(i = 0; i <= 4; i ++)
	{
		scanf("%s",input);
		a[i] = input[0];
		b[i] = input[1];
	}
	for(k = 0; k <= 4; k ++)
	{
		printf("%c%c ",a[k],b[k]);
	}
	return 0;
}

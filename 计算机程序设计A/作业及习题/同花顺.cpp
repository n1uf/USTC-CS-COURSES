#include<stdio.h>
int main()
{
	int i,j;
	char a[5][2];
	for(i = 0; i < 5; i ++)
	{
		for(j = 0; j < 2; j ++)
		{
			scanf("%c%c %c%c %c%c %c%c %c%c\r\n",a[i][j]);
		}
	}
	printf("%c%c %c%c %c%c %c%c %c%c\r\n");
}

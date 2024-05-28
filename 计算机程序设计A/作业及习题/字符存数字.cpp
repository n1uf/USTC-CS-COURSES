#include<stdio.h>
int main()
{
	char a[4];
	int k;
	k = 5;
	a[0] = (char)&k;
	printf("%s",a);
}

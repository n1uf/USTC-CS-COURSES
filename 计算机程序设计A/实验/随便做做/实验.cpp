#include <stdio.h>
int main(void)
{
	int i = 2;
	i*=(i--)+(++i)*(++i)%(i--);
	printf("%d", i);
}

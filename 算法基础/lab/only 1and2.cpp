#include <stdio.h>
#include <stdlib.h>

int main()
{
	int N = 0;
	scanf("%d", &N);
	int *Fib = (int *)malloc((N + 1) * sizeof(int));
	
	Fib[0] = 1;
	Fib[1] = 1;
	
	for(int i = 2; i <= N; i ++)
	{
		Fib[i] = Fib[i - 1] + Fib[i - 2];
	}
	
	printf("%d", Fib[N]);
	return 0;
}

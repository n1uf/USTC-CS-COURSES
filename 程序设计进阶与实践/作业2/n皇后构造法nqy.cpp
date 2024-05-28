#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

int anans[10000000];
int k = 0;

void ans(int bgn, int end) 
{
	for(int i = bgn; i <= end; i += 2) 
	{
		anans[k] = i - 1;
		k ++;
	}
}

int QUEEN(int n)
{
	const int mod = n % 6;
	if(mod != 2 && mod != 3)
	{
		if(n % 2 == 1) 
		{
			ans(2, n - 1);
			ans(1, n);
		} 
		else 
		{
			ans(2, n);
			ans(1, n - 1);
		}
	} 
	else 
	{
		int half = n / 2;
		if(n % 2 == 1) 
		{
			if(half % 2 == 1) 
			{
				ans(half, n - 2);
				ans(1, half - 2);
				ans(half + 3, n - 1);
				ans(2, half + 1);
				ans(n, n);
			} 
			else 
			{
				ans(half, n - 1);
				ans(2, half - 2);
				ans(half + 3, n - 2);
				ans(1, half + 1);
				ans(n, n);
			}
		} 
		else
		{
			if(half % 2 == 1) 
			{
				ans(half, n - 1);
				ans(1, half - 2);
				ans(half + 3, n);
				ans(2, half + 1);
			} 
			else
			{
				ans(half, n);
				ans(2, half - 2);
				ans(half + 3, n - 1);
				ans(1, half + 1);
			}
		}
	}
}

int main(void)
{
	int queennum = 0;
	scanf("%d", &queennum);
	QUEEN(queennum);
	for(int i = 0; i < k; i ++)
	{
		printf("%d ", anans[i] + 1);
	}
}

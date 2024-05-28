#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#define MAXN 100009

int N = 0, M = 0;
int stone[MAXN];

bool Judge(int ans)
{
	int now_s = 0;
	int move_count = 0;
	for(int i = 1; i <= N + 1; i ++)
	{
		if(stone[i] - now_s < ans)
			move_count ++;
		else
			now_s = stone[i];
	}
	if(move_count > M)
		return false;
	return true;
}

int main()
{
	int L = 0;
	scanf("%d" ,&L);
	scanf("%d %d", &N, &M);
	stone[0] = 0;	// S岸距离记为0
	// 中间石头赋值给stone[1]到stone[N]
	for(int i = 1; i < N + 1; i ++)
	{
		stone[i] = 0;
		scanf("%d", &stone[i]);
	}
	stone[N + 1] = L;	// E岸距离记为L
	int left = 1, right = L;
	int ans = 1;
	while(left <= right)
	{
		int mid = (left + right)/2;
		if(Judge(mid))
		{
			left = mid + 1;
			ans = mid;
		}
		else
			right = mid - 1;
	}
	printf("%d", ans);
	return 0;
}

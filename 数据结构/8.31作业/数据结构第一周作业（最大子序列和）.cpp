/*	算法描述：a[]存放初始序列，b[]存放子序列和（b[i]是以a[i]为尾的子序列和）
	且不断更新b[i]的数值使其成为以a[i]为尾时的最大子序列和，最后选出b[]中的最大数	*/ 

#include <stdio.h>
#define max 1000

int main()
{
	int a[max], b[max], i, n;
	
	scanf("%d", &n);
	
	for(i = 0; i < n; i ++)
	{
		scanf("%d", &a[i]);
	}
	
	b[0] = a[0];
	
	for(i = 1; i < n; i ++)						//n 
	{
		if(a[i] > a[i] + b[i - 1])
		{
			b[i] = a[i];
		}
		else b[i] = a[i] + b[i - 1];
	}
	
	int p = b[0];
	
	for(i = 1; i < n; i ++)						//n
	{
		if(b[i] > p)
		{
			p = b[i];
		}
	}
	printf("%d", p);
	return 0;
}												//时间复杂度为O(n) 

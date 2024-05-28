#include <stdio.h>
#include <string.h>
int t = 0;
void _do(char s[201][1001],int n);
char str[201][1001];
int main()
{
	int i, n;
	scanf("%d",&n);
	i = 0;
	/* ‰»Î*/ 
	while(i < n)
	{
		for(i = 0; i < n; i ++)
		{
			scanf("%s",str[i]);
		}
	}
	
	_do(str, n);
	
	/* ‰≥ˆ*/ 
	for(i = 0; i < n; i ++)
	{
		printf("%s\n",str[i]);
	}
}


/*≈≈–Ú≤Ÿ◊˜*/
void _do(char s[201][1001], int n)
{
	int i, j, k;
	char vs[1001];
	for(i = 0; i < n; i ++)
	{
		for(j = 0; j < i; j ++)
		{
			if(strcmp(s[i], s[j]) < 0)
			{
				strcpy(vs, s[i]);
				for(k = i - 1; k >= j; k --)
				{
					strcpy(s[k + 1], s[k]);
				}
				strcpy(s[j], vs);
			}
		}
	}
}	

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
	int n, m;
	while(1)
	{
		scanf("%d%d", &n, &m);
		if(n * m <= 54)
		{
			printf("输入有效。\n"); 
			break;
		}
		else
		{
			printf("重新输入n，m：\n");
		}
	}
	
	char level[13][3] = {{"2"}, {"3"}, {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"}, {"10"}, {"J"}, {"Q"}, {"K"}, {"A"}};
	char flow[4][5] = {{6}, {3}, {5}, {4}};
	srand(time(NULL));
	while(1)
	{ 
		int i, j;
		int person_level[n][m];
		int person_flow[n][m];
		int a, b;
here:	for(i = 0; i < n; i ++)
		{
			for(j = 0; j < m; j ++)
			{
				a = rand() % 13;
				b = rand() % 4;
				person_level[i][j] = a;
				person_flow[i][j] = b;
				printf("%d %d	", person_flow[i][j], person_level[i][j]);
			}
			printf("\n");
		}
		char person[n][m][100] = {}, person2[n][m][100] = {};
		for(i = 0; i < n; i ++)
		{
			printf("player %d:", i + 1);
			for(j = 0; j < m; j ++)
			{
				strcat(person[i][j], flow[person_flow[i][j]]);
				strcat(person[i][j], level[person_level[i][j]]);
				strcpy(person2[i][j], person[i][j]);
				printf("%s ", person[i][j]);
			}
			printf("\n");
		}
		int k, l;
		for(i = 0; i < n; i ++)
		{
			for(j = 0; j < m; j ++)
			{
				for(k = 0; k < n; k ++)
				{
					for(l = 0; l < m; l ++)
					{
						if(strcmp(person[i][j], person[k][l]) == 0 && (k != i || l != j))
						{
							goto here;
						}
					}
				}
			}
		}
		int p;
		for(i = 0; i < n; i ++)
		{
			for(j = 0; j < m; j ++)
			{
				for(k = 0; k < m; k ++)
				{
					if(person_level[i][k] < person_level[i][k + 1])
					{
						p = person_level[i][k];
						person_level[i][k] = person_level[i][k + 1];
						person_level[i][k + 1] = p;
					}
				}
			}
		}
		int rank[n], rank2[n];
		for(i = 0; i < n; i ++)
		{
			rank[i] = person_level[i][0];
			printf("%d", rank[i]);
			printf("\n");
			rank2[i] = rank[i];
		}
		for(i = 0; i < n; i ++)
		{
			for(j = 0; j < n; j ++)
			{
				if(rank[j] < rank[j + 1])
				{
					p = rank[j];
					rank[j] = rank[j + 1];
					rank[j + 1] = p;
				}
			}
		}
		/*重复等级牌的处理*/ 
		for(i = 0; i < n; i ++)
		{
			for(j = i + 1; j < n; j ++)
			{
				if(rank[i] == rank[j])
				{
					
				}
			}
		}
		int s[n];
		for(i = 0; i < n; i ++)
		{
			for(j = 0; j < n; j ++)
			{
				if(rank2[j] == rank[i])
				{
					s[i] = j;
					break;
				}
			}
		}
		for(i = 0; i < n; i ++)
		{
			if(i != n - 1)
				printf("player %d >", s[i] + 1);
			else
				printf("player %d", s[i] + 1);
		}
		putchar(10);
		int flag = 0;
		scanf("%d", &flag);
		if(flag == 0)
		{
			break;
		}
	}//while结束 
}

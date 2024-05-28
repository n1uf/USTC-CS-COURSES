#include<stdio.h>
int main()
{
	char NUM[13] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
	char color[100][5] = {"0000"},num[100][5] = {"0000"},input[3] = {"00"};
	int n[100][5];
	int i,j;
	
	/*输入并分别存储花色和数字*/
	for(i = 0; ; i ++)
	{
		for(j = 0; j <= 4; j ++)
		{
			scanf("%s",input);
			if(input[0] == '0')
			{
				break;
			}
			color[i][j] = input[0];
			num[i][j] = input[1];
		}
		if(input[0] == '0')
		{
			break;
		}
	}
	
	/*给每一手牌的数字赋予等级并排序*/ 
	int k,s,r,p,q;
	for(s = 0; s <= i; s ++)
	{
		k = 0;
		for(p = 0; p <= 12 ; p ++)
		{
			for(q = 0; q <= 4; q ++)
			{
				if(NUM[p] == num[s][q])
				{
					n[s][k] = p + 1;
					k ++;
				}
			}
		}
	}
	
	/*操作*/ 
	s = -1;
	int flag;
begin:
	flag = 0;	
	s ++;
	for(; s <= i - 1; s ++)
	{
		/*判断非法*/
		for(r = 0; r <= 4; r ++)
		{
			if(color[s][r] != 'D' && color[s][r] != 'C' && color[s][r] != 'H' && color[s][r] != 'S')
			{
				printf("Invalid\n"); goto begin;
			}
			else if(num[s][r] != 'A' && num[s][r] != '2' && num[s][r] != '3' && num[s][r] != '4' &&
			        num[s][r] != '5' && num[s][r] != '6' && num[s][r] != '7' && num[s][r] != '8' && 
			        num[s][r] != '9' && num[s][r] != 'T' && num[s][r] != 'J' && num[s][r] != 'Q' && num[s][r] != 'K')
			{
				printf("Invalid\n"); goto begin;
			}
			else if((r <= 3 && num[s][r] == num[s][r + 1] && color[s][r] == color[s][r + 1]) ||
			        (r <= 2 && num[s][r] == num[s][r + 2] && color[s][r] == color[s][r + 2]) ||
			        (r <= 1 && num[s][r] == num[s][r + 3] && color[s][r] == color[s][r + 3]) ||
			        (r <= 0 && num[s][r] == num[s][r + 4] && color[s][r] == color[s][r + 4]))
			{
				printf("Invalid\n"); goto begin;
			}
		}
		/*判断同花顺*/
		for(r = 0; r < 4; r ++)
		{
			if(color[s][r] == color[s][r + 1] && n[s][r] + 1 == n[s][r + 1])
			{
				flag ++;
			}
			if (flag == 4)
			{
				printf("Straight Flush\n"); goto begin;
			}
		}
		flag = 0;
		/*判断四张*/
		for(r = 0; ; )
		{
			if((n[s][r] == n[s][r + 1] && n[s][r] == n[s][r + 2] && n[s][r] == n[s][r + 3]) ||
			    (n[s][r + 1] == n[s][r + 2] && n[s][r + 1] == n[s][r + 3] && n[s][r + 1] == n[s][r + 4]))
			{
				printf("Four of A Kind\n"); goto begin;
			}
			else break;
		}
		/*判断三带二*/
		for(r = 0; ; )
		{
			if((n[s][r] == n[s][r + 1] && n[s][r] == n[s][r + 2] && n[s][r + 3] == n[s][r + 4]) ||
			(n[s][r] == n[s][r + 1] && n[s][r + 2] == n[s][r + 3] && n[s][r + 2] == n[s][r + 4]))
			{
				printf("Full House\n"); goto begin;
			}
			else break;
		}
		/*判断同花*/
		for(r = 0; ; )
		{
			if(color[s][r] == color[s][r + 1] && color[s][r] == color[s][r + 2] && 
			   color[s][r] == color[s][r + 3] && color[s][r] == color[s][r + 4])
			{
				printf("Flush\n"); goto begin;
			}
			else break;
		}
		/*判断顺子*/
		for(r = 0; r < 4; r ++)
		{
			if(n[s][r] + 1 == n[s][r + 1])
			{
				flag ++;
			}
			if(flag == 4)
			{
				printf("Straight\n"); goto begin;
			}
		}
		/*判断三张*/
		for(r = 0; ; )
		{
			if((n[s][r] == n[s][r + 1] && n[s][r] == n[s][r + 2]) || 
			   (n[s][r + 1] == n[s][r + 2] && n[s][r + 1] == n[s][r + 3]) ||
			   (n[s][r + 2] == n[s][r + 3] && n[s][r + 2] == n[s][r + 4])) 
			{
				printf("Three of A Kind\n"); goto begin;
			}
			else break;
		}
		/*判断双对*/
		for(r = 0; ; )
		{
			if((n[s][r] == n[s][r + 1] && n[s][r + 2] == n[s][r + 3]) ||
			   (n[s][r] == n[s][r + 1] && n[s][r + 3] == n[s][r + 4]) ||
			   (n[s][r + 1] == n[s][r + 2] && n[s][r + 3] == n[s][r + 4]))
			{
				printf("Two Pairs\n");goto begin; 	
			}
			else break;
		}
		/*判断对子*/
		for(r = 0; ; )
		{
			if(n[s][r] == n[s][r + 1] || n[s][r + 1] == n[s][r + 2] || 
			   n[s][r + 2] == n[s][r + 3] || n[s][r + 3] == n[s][r + 4])
			{
				printf("Pair\n");goto begin;
			}
			else break;
		}
		/*剩余情况*/
		printf("Other\n");goto begin;
	}
	return 0;
}

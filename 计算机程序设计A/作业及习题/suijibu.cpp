#include<stdio.h>
#include<stdlib.h>

int main()
{
	int i,j,k;
	char str[10][10],letter[26];
	
	/*��ʼ��*/
	for(i = 0; i < 10; i ++)
	{
		for(j = 0; j < 10; j ++)
		{
			str[i][j] = '.';
		}
	}
	for(k = 0; k < 26; k ++)
	{
		letter[k] = 65 + k;
	}
	
	/*�����*/
	int x,y,a,t;
	scanf("%d %d",&x,&y);
	str[x][y] = letter[0];//����һ��λ�õ�Ԫ�ظ�ΪA 
	srand(x + 10 * y);
	for(a = 1; a <= 25; a ++)
	{
		t = 0;
		int dir = rand() % 4;//������ɷ��� 
		/*�Է�����߷�����ѡ��*/ 
begin:	switch(dir)
		{
			case 0:
			{
				if(t >= 4) goto end;
				else
				{
					if(x - 1 < 0 || str[x - 1][y] != '.')
					{
						dir ++;
						t ++;
						goto begin;
					}
					else
					{
						x = x - 1;
						str[x][y] = letter[a];break;
					}
				}
			}
			case 1:
			{
				if(t >= 4) goto end;
				else
				{
					if(y + 1 > 9 || str[x][y + 1] != '.')
					{
						dir ++;
						t ++;
						goto begin;
					}
					else
					{
						y = y + 1;
						str[x][y] = letter[a];break;
					}
				}
			}
			case 2:
			{
				if(t >= 4) goto end;
				else
				{
					if(x + 1 > 9 || str[x + 1][y] != '.')
					{
						dir ++;
						t ++;
						goto begin;
					}
					else
					{
						x = x + 1;
						str[x][y] = letter[a];break;
					}
				}
			}
			case 3:
			{
				if(t >= 4) goto end;
				else
				{
					if(y - 1 < 0 || str[x][y - 1] != '.')
					{
						dir = 0;
						t ++;
						goto begin;
					}
					else
					{
						y = y - 1;
						str[x][y] = letter[a];break;
					}
				}
			}
		}
	}
	
	/*���*/
end:for(i = 0; i < 10; i ++)
	{
		for(j = 0; j < 10; j ++)
		{
			printf("%c ",str[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}

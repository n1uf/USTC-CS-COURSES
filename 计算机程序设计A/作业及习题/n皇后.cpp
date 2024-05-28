#include<stdio.h>
void queen(int i,int j,int line);
int check(int i,int j,int line);
int cas = 0;
int i = 0,j = 0;
int xx,yy;

int main()
{
	int line;
	scanf("%d",&line);
	queen(0,0,line);
	printf("%d\n",cas);	
	return 0;
}

void queen(int i,int j,int line)
{
	int chess[line][line];
	/*出口*/ 
	if(j >= line)
	{
		return ;
	}
	
	/*如果可以放*/ 
	if(check(i,j,line) == 1)
	{
		/*放*/ 
		chess[i][j] = 1;
		/*如果是最后一行，解法+1*/
		if(i == line - 1)
		{
			cas ++;
		}
		/*否则分析下一行*/
		else
		{
			queen(i + 1,0,line);
		}
	}
	
	/*如果不能放*/ 
	chess[i][j] = 0;//置为0 
	/*试旁边的位置*/ 
	queen(i,j + 1,line);
}

int check(int i,int j,int line)
{
	int k;
	int chess[line][line];
	/*横竖*/ 
	for(k = 0; k < line; k ++)
	{
		if(chess[i][k] == 1) return 0;
	}
	for(k = 0; k < line; k ++)
	{
		if(chess[k][j] == 1) return 0;
	}
	
	/*两对角*/
	for(k = - line; k <= line; k ++)
	{
		/*左上右下*/ 
		if(i + k >= 0 && i + k < line && j + k >= 0 && j + k < line)
		{
			if(chess[i + k][j + k] == 1) return 0;
		} 
		
		/*右上左下*/ 
		if(i - k >= 0 && i - k < line && j + k >= 0 && j + k < line)
		{
			if(chess[i - k][j + k] == 1) return 0;
		}
	}
	return 1;
}

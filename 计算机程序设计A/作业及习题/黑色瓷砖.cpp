#include<stdio.h>

int check(int m,int n,int x,int y,int A[]);
int move(int x,int y,int A[]);
int main()
{
	
	/*����*/ 
	int m,n;
	scanf("%d %d",&m,&n);
	int area[m][n];
	int x,y;
	scanf("%d %d",&x,&y);
	int i,j;
	for(i = 0; i < m; i ++)
	{
		for(j = 0; j < n; j ++)
		{
			scanf("%d",&area[i][j]);
		}
	}
	printf("\n");
	
	/*���������Ƿ���ȷ�����鿴�ж��ٺڴ�ש*/ 
	int sum;
	for(i = 0; i < m; i ++)
	{
		for(j = 0; j < n; j ++)
		{
			//printf("%d ",area[i][j]);
			
			if(area[i][j] == 0)
			{
				sum ++;
			}
		}
		//printf("\n");
	}
	//printf("%d",sum);
	
	/*��area��һά�����ŷ���д�뺯��*/
	int s = m * n, t = 0;
	int A[s] = {0};
	for(i = 0; i < m ; i ++)
	{
		for(j = 0; j < n; j ++)
		{
			A[t] = area[i][j];
			t ++;
		}
	}
	check(m,n,x,y,A);
	
	
	return 0;
}

int check(int m,int n,int x,int y,int A[])
{
	int area[m][n] = {0};
	int i,j,t = 0;
	for(i = 0; i < m ; i ++)
	{
		for(j = 0; j < n; j ++)
		{
			area[i][j] = A[t];
			t ++;
			//printf("%d",area[i][j]);
		}
		//printf("\n");
	}
	int step = 1,flag = 0;
	/*��,��,��,��,1,2,3,4,*/ 
	if(area[x - 1][y] == 0)
	{
		flag = 1;
	}
	if(area[x + 1][y] == 0)
	{
		flag = 2;
	}
	if(area[x][y - 1] == 0)
	{
		flag = 3;
	}
	if(area[x][y + 1] == 0)
	{
		flag = 4;
	}
}

#include<stdio.h>
#define line 4
void queen(int i,int j);
int check(int i,int j);
int chess[line][line];
int cas = 0;
int xx,yy;

int main()
{
	queen(0,0);
	printf("%d\n",cas);	
	return 0;
}

void queen(int i,int j)
{
	
	/*����*/ 
	if(j >= line)
	{
		return ;
	}
	
	/*������Է�*/ 
	if(check(i,j) == 1)
	{
		/*��*/ 
		chess[i][j] = 1;
		printf("%d",j + 1);
		/*��������һ�У��ⷨ+1*/
		if(i == line - 1)
		{
			cas ++;
			printf("\n");
		}
		
		/*���������һ��*/
		else
		{
			queen(i + 1,0);
		}
	}
	
	/*������ܷ�*/ 
	chess[i][j] = 0;//��Ϊ0 
	/*���Աߵ�λ��*/ 
	queen(i,j + 1);
}

int check(int i,int j)
{
	int k;
	
	/*����*/
	for(k = 0; k < line; k ++)
	{
		if(chess[i][k] == 1) return 0;
	}
	for(k = 0; k < line; k ++)
	{
		if(chess[k][j] == 1) return 0;
	}
	
	/*���Խ�*/
	for(k = - line; k <= line; k ++)
	{
		/*��������*/ 
		if(i + k >= 0 && i + k < line && j + k >= 0 && j + k < line)
		{
			if(chess[i + k][j + k] == 1) return 0;
		} 
		
		/*��������*/ 
		if(i - k >= 0 && i - k < line && j + k >= 0 && j + k < line)
		{
			if(chess[i - k][j + k] == 1) return 0;
		}
	}
	return 1;
}


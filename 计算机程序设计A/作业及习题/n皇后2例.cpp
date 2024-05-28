#include <stdio.h>
#include <stdlib.h>

/*查阅资料发现可以用一维数组解答
行冲突可以省掉
列冲突看已放置的列和需要放置的列数组下标不同就可
关于对角线冲突的判断：它们所在的行列互减的绝对值相等，即| 上一次放置的列 –上一次放置的行 | = | 要放置的列 –要放置的行 |
*/
 
/*设全局变量以便于统计所有解，以及解的个数*/ 

int chess[10];//棋盘足够大
int ans = 0;//统计解的个数
int a[1024];//存放每一个解 
int p = 0;

/*放置皇后到棋盘上*/
void place(int k,int n);

/*检验第i行的k列上是否可以摆放皇后*/
int check(int i,int k);

/*输出一组解*/
void print(int n);


int main()
{
	int n;
	scanf("%d",&n);
	place(1,n);
	printf("%d\n",ans);
	int i,j;
	for(i = 0; i < ans * n; )
	{
		for(j = 0; j < n; j ++,i ++)
		{
			printf("%d",a[i]);
		}
		printf("\n");
	}
	return 0;
}

void place(int k,int n) 
{
	int j;
	
	/*出口*/ 
	if(k > n)
	{
		print(n);
	}
	
	else
	{
		/*对k行的每一列都进行检查*/ 
		for(j = 1; j <= n; j ++)
		{
			/*若成立则记录并递归*/ 
            if(check(k,j))
            {
            	chess[k] = j;
                place(k + 1,n);
            }
        }
	}
}

int check(int i,int k) 
{
	int j = 1;
	while(j < i)//j=1~i-1是已经放置了皇后的行
	{
		/*第j行的皇后是否在k列或(j,chess[j])与(i,k)是否在斜线上*/
		if(chess[j] == k || abs(j - i) == abs(chess[j] - k))
		{
			return 0;
		}
    	j ++;
	}
	return 1;
}

void print(int n)
{
	int i;
	for(i = 1; i <= n; i ++)
	{
		a[p] = chess[i];
		p ++;
	}
	ans ++;
}

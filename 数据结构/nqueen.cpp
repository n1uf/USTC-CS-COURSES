#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *solution; 		// solution[col]=row,表示第col列的皇后在row行
int len;			// 棋盘大小参量 

int initSolution();
void restart();
void swap(int, int);
int traverseNeighbors();
int evaluate();

int main()
{
	srand(int(time(0)));	// 把时间作为随机种子 

	printf("请输入皇后个数：");
	scanf("%d",&len);     	// 棋盘大小 
	
	initSolution();			// 初始化
	
	int flag = traverseNeighbors();
	
	while(flag != 0)		// 冲突数不为0则重新操作进行搜索 
	{
		restart();
		flag = traverseNeighbors();
		if(flag)
			printf("冲突数为：%d，重新搜索\n",flag);
	}
	
	// 找到解，打印解 
	printf("找到一组解，解为：\n");
	for(int i = 0; i < len; i ++)
		printf("%d ",solution[i] + 1);
		
	free(solution);
	return 0;
}

// 交换棋盘的第i列和第j列
void swap(int i, int j)
{
	int temp = solution[i];
	solution[i] = solution[j];
	solution[j] = temp;
}


// 初始化棋盘
int initSolution()
{
	solution = (int *)malloc(sizeof(int)*len);	// 分配空间  
	if (!solution)  return 0; 
	// 随机给初始布局或给定某个初始布局
	for(int i = 0; i < len; i ++)    
		solution[i]=i;
	for(int i = 0; i < len; i ++)	// 对棋盘进行随机交换
		swap(rand()%len, rand()%len);
}

// 当前棋盘的冲突数value 
int evaluate()
{
	int value=0;
	for(int i = 0; i < len; i ++)
		for(int j = i + 1; j < len; j ++)
			if(solution[i] == solution[j] || abs(solution[i] - solution[j]) == abs(i - j))
				value ++;
	return value;
}



// 检查邻居棋盘冲突数，更优则替换
int traverseNeighbors()
{
	int min_value = evaluate();     // 当前棋盘的所有邻居的最小评价函数值 
	int col1 = -1, col2 = -1;		// 交换前的列下标和交换后的列下标  
	
    //遍历邻居，评估每个邻居冲突皇后对的个数，找到最小冲突对数的邻居
	int i, j, value;
	for(i = 0; i < len; i ++)
	{
		for(j = i + 1; j < len; j ++)
		{
			swap(i, j);				// 得到邻居 
			value = evaluate();		// 邻居的冲突数 
			swap(i, j);				// 换回来 
			if(value < min_value)	// 更优则更新  
			{
				min_value = value;
				col1 = i; 
				col2 = j;
			}
		}
	}
	
    if (col1 == -1) 
	{  //如果遍历了所有的邻居节点，也找不到更好的移动方式，那么就需要重新启动算法，初始棋局改变一下
    	printf("找不到解，重新搜索\n");
    	return -1;
    }
    swap(col1, col2);	// 找到更好的移动方式，那么就以这个邻居进行下一次爬山
    return min_value;
}

void restart()
{	// 随机交换列，重新搜索 
	int times = 10; 
	for(int i = 0; i < times; i ++)
		swap(rand()%len, rand()%len);
	printf("restart()被调用\n");
}


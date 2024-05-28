//n-皇后问题的随机搜索算法，找到解即可
//用一维数组来存放每一列皇后的行号

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//采用堆分配存储的方式实现
int *solution; //每列一个皇后，solution[col]=row,表示第col列的皇后在row行
int len;            //皇后数量，len*len的棋盘
int size;      //每个棋盘邻居棋盘的数量 size=(len-1)*len/2记录数组最大容量

//函数声明
void swap(int , int);
void restart();
void initSolution();
int traverseNeighbors();
int evaluate();

int main(){
	long seed = 820;  //随机数种子，如果这个数不改变，那么每次算法运行的结果都是一样的
	// seed = rand(); //这一句注释掉，等于每次的随机数种子都一样
	srand(seed);  
	// printf("请输入皇后个数：");
	// scanf("%d",&len);     	// 键盘读入棋盘的大小
	len = 6;	// 棋盘大小
	solution = (int *)malloc(sizeof(int)*len);
	if (!solution)  return 0; //分配空间失败
	
	initSolution();			// 初始化一个棋盘布局
	
	int flag;
	clock_t t0 = clock();
	while ((flag = traverseNeighbors())!=0)
		if (flag<0)	restart();
	clock_t t1 = clock();
	printf("冲突数为：%d\n得到的解为：",evaluate());
	printf("所花费的时间为：%5f 秒\n", 1.0*(t1 - t0)/1000);	
	for(int i=0;i<len;++i)
		printf("%d,",solution[i]);
	free(solution);
	return 0;
}

/***  将棋盘的第i列和第j列交换  ***/
void swap(int i, int j){
	if(i == j) return;
	int tmp = solution[j];
	solution[j] = solution[i];
	solution[i] = tmp;
}


/***  初始化一个棋盘布局,将邻居数组准备好  ***/
void initSolution(){
	// 随机给初始布局或给定某个初始布局
	// int a[6] = {0,5,2,1,3,4};
	for(int i=0;i<len;++i)    
		solution[i]=i;
	for(int i = 0; i < 2*len; ++i)	// 对棋盘进行2*len次随机交换
		swap(rand()%len,rand()%len);
}

/***  计算棋盘的评价函数（棋盘的价值: value=可相互攻击到的皇后对数）
 ***  当皇后相互攻击不到时，目标函数的值value==0
 ***   solution[i]==solution[j], (solution[i]-solution[j])/(i-j)==1或-1时（C语言实现会有bug），两个皇后彼此能攻击到，value++
 ***  棋盘编码方式能保证不会出现 solution[i]==solution[j]，故该条件可以不用判断
 ***  思考：该函数的时间性能是否能提高？
 ***  答案：利用前一个value，生成邻居的value
 int evaluate(int prevalue, int col1, int col2) {
	int value = 0;
	int i, j;
	if (prevalue == 0) {
		for (i = 0;i < len;i++)
			for (j = i + 1;j < len;j++)
				if (j - i == abs(*(solution + i) - *(solution + j)))
					value++;
	}
	else {
		value = prevalue;
		for (i = 0;i < len;i++) {
			if (i != col1 && i != col2) {
				if (abs(i - col1) == abs(*(solution + i) - *(solution + col2)))
					value--;
				if (abs(i - col2) == abs(*(solution + i) - *(solution + col1)))
					value--;
				if (abs(i - col1) == abs(*(solution + i) - *(solution + col1)))
					value++;
				if (abs(i - col2) == abs(*(solution + i) - *(solution + col2)))
					value++;
			}
		}

	}
	return value;
}
 ***/
int evaluate(){
	int value=0;
	//todo
	for(int i = 0; i < len; ++i)
		for(int j = i + 1; j < len; ++j)
			if(solution[i] - solution[j] == i - j || solution[i] - solution[j] == j - i)
				value++;

	return value;
}

/***  随机置换 randShuffle() ，无放回的均匀随机采样（被采样集合在不断缩小，直至为0，算法停止）
 ***  对数组 neighbors 进行随机置换操作
 ***  用到的数据：size= neighbors的长度
 ***  best found 策略用不着该函数
 ***/
void randShuffle(){ //每次随机挑选第k个元素出来,然后存放在数组“当前末尾”
    //todo
}


/***  检查当前解（棋盘）的邻居棋盘（交换solution[i]和solution[j],i和j随机选择，共有n(n-1)/2种不同的可能）
 ***  保留冲突最小的棋盘，将它视为新的解（best found策略）, 返回构建新解时交换而来的邻居编号current
 ***  若返回-1,表示没有找到更好的邻居，需要重启 restart() ,返回0表示找到所求的解，
 ***  返回大于0的值表示需要更新当前解solution后要继续遍历新解的邻居
 ***/
int traverseNeighbors(){
	int min_value = evaluate();     // 当前棋盘的所有邻居的最小评价函数值
	int min_col = -1,min_row = -1;	// 上述对应的邻居
	
    //遍历邻居，评估每个邻居冲突皇后对的个数，找到最小冲突对数的邻居
	for(int i = 0; i < len; ++i)
		for(int j = i + 1; j < len; ++j){
			swap(i,j);	// 生成邻居棋盘
			if(evaluate() < min_value){
				min_value = evaluate();
				min_col = i; min_row = j;
			}
			swap(i,j);	// 还原棋盘
		}

    if (min_col == -1) {  //如果遍历了所有的邻居节点，也找不到更好的移动方式，那么就需要重新启动算法，初始棋局改变一下
    	printf("找不到解，正在重新生成初始解和运行搜索算法中...\n");
    	return -1;
    }
    swap(min_col,min_row);	// 找到更好的移动方式，那么就以这个邻居进行下一次爬山
    return min_value;
}


/***  当遍历完所有邻居，也没有找到y==0的棋盘布局，
 ***  那么随机重置solution，然后再用爬山法搜索
 ***  随机重启：邻居是邻域内的“微小”的扰动，增加扰动范围，比如随机交换times=20次
 ***/
void restart(){
	int times = 20;  // 随机交换解的次数，扰动大小,设置times>1即可
	for(int i = 0; i < times; ++i)
		swap(rand()%len,rand()%len);
	puts("restart()被调用！");
}


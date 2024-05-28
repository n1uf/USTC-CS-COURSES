#include<stdio.h>//主函数 
int main()//定义主函数 
{//主函数主体开始 
	int max(int x,int y);//对max声明 
	int a,b,c;//定义变量a,b,c 
	scanf("%d,%d",&a,&b);//输入变量a，b 
	c=max(a,b);//调用max函数，将得到的值赋给c 
	printf("max=%d\n",c);//输出c 
	return 0;//主函数结束 
}//函数主体结束
//求两个整数中较大的max函数 
int max(int x,int y)//定义max函数：函数值为整形，形式参数x，y为整形 
{//定义max函数开始 
	int z;//max函数声明：定义所用到的z为整形 
		if(x>y)z=x;//若x>y成立，将x值赋给变量z 
		else z=y;//否则，将y赋给z 
		return(z);//将z的值作为max函数值，返回到调用max函数的位置 
}

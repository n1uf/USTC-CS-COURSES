#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<math.h>

char op[5] = { '#', '+', '-', '*', '/', };

float cal(float x, float y, int op)
{
	switch (op)									//将运算符初始化为1,2,3,4四个数字
	{
	case 1:return x + y;
	case 2:return x - y;
	case 3:return x * y;
	case 4:return x / y;
	}
}

int main()
{
	float a, b;
	scanf("%f %f", &a, &b);
	float c = cal(a, b, 1);
	printf("%f", c);
}

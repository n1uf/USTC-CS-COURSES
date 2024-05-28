#include <stdio.h> 

typedef int apple;
typedef int plate;

int putapple(apple a, plate d);

int main(void)
{
	apple x;
	plate y;
	printf("苹果的数量是：");
	scanf("%d", &x);
	printf("盘子的数量是：");
	scanf("%d", &y);
	int z;
	z = putapple(x, y);
	printf("放置的方法数为%d.", z);
}

int putapple(apple a, plate d)
{
	if(d == 1 || a == 0)
	{
		return 1;
	}
	if(d > a)
	{
		return putapple(a,a);
	}
	else
	{
		return putapple(a, d - 1) + putapple(a - d, d);
	}
}

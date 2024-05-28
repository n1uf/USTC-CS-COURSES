/*
include <stdio.h>
void swap(int a, int b);
int main()
{
	int x = 0, y = 1;
	printf("%d %d\n", x, y);
	swap(x, y);
	printf("%d %d", x, y);
}

void swap(int a, int b)
{
	int c;
	c = a;
	a = b;
	b = c;
}*/

#include <stdio.h>
void swap(int *p1, int *p2);
int main()
{
	int x = 0, y = 1;
	int *s1, *s2;
	s1 = &x;
	s2 = &y;
	printf("%d %d\n", *s1 ,*s2);
	swap(s1, s2);
	printf("%d %d", *s1, *s2);
}

void swap(int *p1, int *p2)
{
	int c;
	c = *p1;
	*p1 = *p2;
	*p2 = c;
}

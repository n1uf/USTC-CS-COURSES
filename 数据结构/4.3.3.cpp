#include <stdio.h>
#include <stdlib.h>

void insert(char *s, char *t, int pos)
{
	int i = 0, j = 0, k = 0;
	char *p = s;
	char *q = t;			//用p和q分别处理s和t 
	if(pos < 1)				//插入位置不合法 
	{
		printf("插入位置非法\n");
		exit(0);
	}
	while(*p != '\0' && i < pos)			//是否能找到插入的位置 
	{
		p ++;
		i ++;
	}
	if(*p == '\0')			//没有找到，则位置同样不合法 
	{
		printf("插入位置超过了s的长度\n");
		exit(0);
	}
	while(*p != '\0')			//找到后，p指针指向s字符串尾的'\0'，得到s长度i 
	{
		p ++;
		i ++;
		printf("字符串s的长度为%d", i);
	}
	while(*q != '\0')			//遍历t，得到t长度j，q指针指向t字符串尾的'\0'
	{
		q ++;
		j ++;
		printf("字符串t的长度为%d", j);
	}
	for(k = i; k >= pos; k --)			//从字符串尾开始，将pos后的元素一一后移j个位置 
	{
		*(p + j) = *p;			//将p元素移到p+j的位置 
		p --;			//p从后向前移动指向前一个元素 
	}			//结束后p的位置是pos位置 
	q --;			//q从串尾移动到串的最后一个非'\0'的元素 
	p = p + j;			//p从pos位置后移到需要插入q最后一个元素的位置即pos + j的位置 
	for(k = 1; k <= j; k ++)			//从后往前依次将q中元素插入p中 
		*p -- = *q --;
}

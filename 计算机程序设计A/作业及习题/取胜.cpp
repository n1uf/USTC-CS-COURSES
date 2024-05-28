#include <stdio.h>
#define MAX 100

int sum(int data[], int head, int tail);

int best(int data[], int head, int tail)
{
	int temp1, temp2;
	if(head == tail)
	{
		return head;
	}
	temp1 = *(data + head) + sum(data, head + 1, tail);
	temp2 = *(data + tail) + sum(data, head, tail - 1);
	/*返回指针*/
	if(temp1 > temp2)
	{
		return head;
	}
	else
	{
		return tail;
	}
}

int sum(int data[], int head, int tail)
{
	int temp;
	/*有0个数据*/
	if(head == tail)
	{
		return 0;
	}
	/*取小的那一个*/
	if(tail == head + 1)
	{
		return (*(data + head) < *(data + tail)) ? head : tail;
	}
	/*改变工作指针，让对方选一个最好值*/
	if(best(data, head, tail) == head)
	{
		head ++;
	}
	else
	{
		tail --;
	}
	temp = best(data, head, tail);
	if(temp == head)
	{
		return *(data + temp) + sum(data, head + 1, tail);
	}
	else
	{
		return *(data + temp) + sum(data, head, tail - 1);
	}
}

int main(void)
{
	int data[MAX], head, tail, n, i, total1, total2, temp;
	scanf("%d", &n);
	for(i = 0; i < n; i ++)
	{
		scanf("%d", data + i);
	}
	total1 = total2 = 0;
	head = 0;
	tail = n-1;
	for(i = 0; i < n; i ++)
	{
		temp = best(data, head, tail);
    	if((i + 1) % 2 != 0)
    	{
    		total1 = total1 + *(data + temp);
		}
		else
		{
			total2 = total2 + *(data + temp);
		}
		if(temp == head)
		{
			head = head + 1;
		}
    	else
    	{
    		tail = tail - 1;
		}
	}
	printf("%d %d\n", total1, total2);
	return 0;
}


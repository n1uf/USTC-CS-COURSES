#include <stdio.h>
#include <stdlib.h>

int *solution;
int len;

void swap(int i, int j)
{
	int temp = solution[i];
	solution[i] = solution[j];
	solution[j] = temp;
}

int main()
{
	len = 10;
	solution = (int *)malloc(sizeof(int)*len);
	int i;
	for(i = 0; i < len; i ++)
	{
		solution[i] = i;
	}
	
	swap(1, 5);
	
	for(i = 0; i < len; i ++)
	{
		printf("%d", solution[i]);
	}
}

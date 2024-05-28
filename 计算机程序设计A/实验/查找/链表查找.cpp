/*链表顺序查找*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int num;
	struct node * next;
}NODE;

int search(NODE* head, int key);

int main()
{
	int n;
	scanf("%d", &n);
	NODE *head, *p, *q;
	head = NULL;
	int i;
	for(i = 0; i < n;i ++)
	{
		p = (NODE *)malloc(sizeof(NODE));
		p->next = head;
		head = p;
		scanf("%d", &p->num);
	}
	int goal;
	scanf("%d", &goal);
	int place = search(head, goal);
	printf("位置为%d", n - place);
} 

int search(NODE* head, int key)
{
	int i;
	for(NODE *q = head; q != NULL; q = q->next)
	{
		i ++;
		if(q->num == key)
		{
			return (i);
		}
	}
	return -1;
}

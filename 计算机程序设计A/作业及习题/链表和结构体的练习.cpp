/*��̬����
 
#include <stdio.h>
struct stu
{
	int num;
	float score;
	struct stu *next;
};

int main()
{
	struct stu a, b, c, *head, *p;
	a.num = 10101; a.score = 89.5;
	b.num = 10103; b.score = 90.0;
	c.num = 10107; c.score = 85.0;
	head = &a;
	a.next = &b;
	b.next = &c;
	c.next = NULL;
	p = head;
	do
	{
		printf("%ld %5.1f\n", p -> num, p -> score);
		p = p -> next;
	}
	while(p != NULL);
	return 0;
}*/

/*��̬����
#include <stdio.h>
#include <stdlib.h>
#define LEN sizeof(struct Student)
struct Student
{
	long num;
	float score;
	struct Student * next;
};
int n;
struct Student * creat(void)
{
	struct Student * head;
	struct Student *p1, *p2;
	n = 0;
	p1 = p2 = (struct Student *)malloc(LEN);
	scanf("%ld,%f",&p1 -> num, &p1 -> score);
	head = NULL;
	while(p1 -> num != 0)
	{
		n ++;
		if(n == 1)
		{
			head = p1;
		}
		else
		{
			p2 -> next = p1;
		}
		p2 = p1;
		p1 = (struct Student *)malloc(LEN);
		scanf("%ld,%f",&p1 -> num, &p1 -> score);
	}
	p2 -> next = NULL;
	return(head);
}

int main(void)
{
	struct Student *pt;
	pt = creat();
	printf("\nnum:%ld\nscore:%5.1f\n",pt -> num, pt -> score);
}*/

/*��̬����Ľ����Ͳ���*/
#include <stdio.h>
#include <stdlib.h>
/*������̬����*/ 
struct Node
{
	int task_num;
	struct Node * next;
}
/*��������*/
struct Node *lookup(struct Node *head, int k)
{ 
	struct Node *q;
	q = head;
	while (q != NULL && q -> num != k)
	q = q -> next;
	if (q == NULL) return(NULL);
	else return(q);
}
int main(void)
{
	struct 	Node *head, *p;
	
	/*�����ʼ��*/ 
	head = NULL;
	
	/*������һ���ڵ�*/ 
	p = (struct Node *)malloc(sizeof(struct Node));
	p -> next = head;
	head = p;
	
	/*ͷ�巨����ڵ�*/
	int i;
	struct 	Node *a;
	for(i = 0; i < 10; i ++)
	{
		a = (struct Node *)malloc(sizeof(struct Node));
		a -> next = head;
		head = a;
	} 
	/*��������*/
	struct Node *p, *q;
	p = (struct Node *) malloc(sizeof(struct Node));
	p -> next = q -> next;
	q -> next = p; 
}
 

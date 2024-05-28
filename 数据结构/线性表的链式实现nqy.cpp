#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct Lnode				//����ṹ�� 
{
	ElemType data;
	struct Lnode * next;
} LinkNode, *LinkList;


LinkNode *first;					//˳����ͷָ�� 


LinkNode *initList()				//��ʼ������ 
{
	LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));				//����ռ� 
	if(!p)				//����ռ�ʧ�� 
	{
		printf("��ʼ������ͷ���ʧ�� \n");
		exit(0);
	}
	p -> next = NULL;				//���������ÿ� 
	return p;
}

int ListLength(LinkList p)				//����Ľ����� 
{
	int count = 0;
	while(p -> next != NULL)				//������һ�������count���ӣ������� 
	{
		count ++;
		p = p -> next;
	}
	return count;
}

int ListEmpty(LinkList p)				//�ж��Ƿ�Ϊ�ձ� 
{
	if(p -> next != NULL)
		return 1;
	return 0;
}

void ClearList(LinkList p)				//ɾ����������Ԫ�� 
{
	LinkNode *q;
	while(p -> next != NULL)			//������Ԫ�� 
	{
		q = p -> next;
		p -> next = q -> next;
		free(q);				//�ͷ����ڴ���������Ԫ�ص���ʱָ�� 
	}
}

void DestroyList(LinkList p)			//ɾ������ 
{
	ClearList(p);
	free(p);
}

int ElemGet(LinkList p, int i, ElemType *e)				//�������л�ȡ��i������Ԫ�� 
{
	int k = 0;
	while(p = p -> next)				//ѭ��������ָ����ָ��� 
	{
		k ++;
		if(k == i)				//�ҵ��ýڵ� 
		{
			*e = p -> data;				//ȡ��Ԫ�� 
			return k;
		}
	}
	return 0;
}

LinkNode *LocateElem(LinkList p, ElemType e)				//���������ҵ��ض�Ԫ�أ��������е�һ�γ��֣������ؽ��ָ�� 
{
	while(p = p -> next)				//ѭ��������ָ����ָ��� 
	{
		if(p -> data == e)				//�ҵ���Ԫ�� 
		{
			return p;				//���ؽ��ָ�� 
		}
	}
	return NULL;
}




LinkNode *PriorElem(LinkList p, LinkNode *cur_e)				//��������ĳ����ǰ�������ǵ�һ��Ԫ�أ� 
{
	for(; p -> next; p = p -> next)				//��ǰ����������� 
	{
		if(p -> next == cur_e)				//�ҵ��ý���ǰ�� 
			return p;
	}
	return NULL;
}

LinkNode *NextElem(LinkList p, LinkNode *cur_e)				//��������ĳ���ĺ�̣��������һ��Ԫ�أ� 
{
	return cur_e -> next;
}

LinkNode *ListInsert(LinkList p, int i, ElemType e)				//�������е�i��������Ԫ��e 
{
	if(i < 1)				//���λ�ò��Ϸ� 
		return NULL;
	for(; p; p = p -> next)				//�������� 
	{
		if(--i < 1)				//�ҵ�˳���ŷ�λ��Ϊ��i-1���Ľ��p
		{
			LinkNode *q = (LinkNode *)malloc(sizeof(LinkNode));				//����ָ����������Ԫ��e 
			if(!q)
			{
				printf("����ڵ�ʱ������ռ�ʧ��. \n");
				exit(0);
			}
			q -> next = p -> next;				//ʹqָ��p���ĺ�� 
			p -> next = q;				//p����һ������Ϊq ��q��ʱΪ��i����㣩 
			q -> data = e;				//��ֵ 
			return q;
		}
	}
	return NULL;
}

int ListDelete(LinkList p, int i, ElemType *e)				//��������ɾ����i����� 
{
	if(i < 1)				//���λ�ò��Ϸ� 
		return 0;
	LinkNode *q = p;				//qָ��p 
	for(p = p -> next; p; p = p -> next)				//�������� 
	{
		if(--i < 1)				//�ҵ�i-1���p 
		{
			q -> next = p -> next;				//qָ��p�ĺ�� ����ʱΪ��i����㣩 
			*e = p -> data;				//ȡp�е�Ԫ�� 
			free(p);				//ɾ���ý�� 
			return 1;
		}
		q = p;				//����q��λ����p��ͬ 
	}
	return 0;
}

void PrintLinkNode(LinkNode *p)				//��ӡp�������� 
{
	printf("%d\n", p -> data);
}

void ListTraverse(LinkList p, LinkNode *q)				//������ʽ������ÿ����㣨����ӡ��ÿһ����㣩 
{
	int i = 1;
	while(p = p -> next)
	{
		q = p;
		printf("���%dΪ��", i);
		PrintLinkNode(q);
		i ++;
	}
	printf("\n");
}

int main()
{
	LinkNode *p;				//Traverse��������ָ�� 
	first = initList();				//��ʼ������ 
	ListInsert(first, 1, 2);				//�������������в������� 
	ListInsert(first, 1, 3);
	ListInsert(first, 1, 4);
	ListInsert(first, 1, 5);
	ListInsert(first, 1, 6);
	ListInsert(first, 1, 7);
	ListInsert(first, 1, 8);
	ListInsert(first, 1, 9);
	ListInsert(first, 2, 13);
	ListInsert(first, 5, 15);
	ListInsert(first, 8, 17);
	ListTraverse(first, p);				//����������ӡ 
	
	printf("----------------------------\n");
	
	ElemType e;
	ElemGet(first, 10, &e);				//ȡ������ĳ�������� 
	printf("��ȡ������Ϊ %d \n", e);
	
	LinkNode *q = LocateElem(first, 6);				//��ǰ���ͺ�� 
	if(!q)
		printf("û���ҵ�ֵ��Ӧ�Ľ��\n");
	else
	{
		q = PriorElem(first, q);
		printf("�ҵ�����ǰ��Ϊ %d -- ", q -> data);
		printf("�ҵ����Ϊ %d -- ", q -> next -> data);
		if(q -> next -> next)
			printf("�ҵ����ĺ��Ϊ %d ", NextElem(first, NextElem(first, q)) -> data);
		printf("\n");
	}
	
	if(ListDelete(first, 3, &e) > 0)				//����ɾ������ 
		printf("ɾ����ֵΪ %d \n", e);
	else
		printf("ɾ��ʧ�� %d \n", e);
		
	printf("----------------------------\n");
	
	ListTraverse(first, p);					//��ӡɾ����Ľ�� 
	
	DestroyList(first);				//ɾ������ 
	
	return 0;
}

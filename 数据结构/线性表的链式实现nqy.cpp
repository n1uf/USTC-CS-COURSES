#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct Lnode				//链表结构体 
{
	ElemType data;
	struct Lnode * next;
} LinkNode, *LinkList;


LinkNode *first;					//顺序表的头指针 


LinkNode *initList()				//初始化链表 
{
	LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));				//分配空间 
	if(!p)				//分配空间失败 
	{
		printf("初始化分配头结点失败 \n");
		exit(0);
	}
	p -> next = NULL;				//创建链表并置空 
	return p;
}

int ListLength(LinkList p)				//链表的结点个数 
{
	int count = 0;
	while(p -> next != NULL)				//存在下一个结点则count增加，结点后移 
	{
		count ++;
		p = p -> next;
	}
	return count;
}

int ListEmpty(LinkList p)				//判断是否为空表 
{
	if(p -> next != NULL)
		return 1;
	return 0;
}

void ClearList(LinkList p)				//删除表内所有元素 
{
	LinkNode *q;
	while(p -> next != NULL)			//表内有元素 
	{
		q = p -> next;
		p -> next = q -> next;
		free(q);				//释放用于处理链表结点元素的临时指针 
	}
}

void DestroyList(LinkList p)			//删除链表 
{
	ClearList(p);
	free(p);
}

int ElemGet(LinkList p, int i, ElemType *e)				//从链表中获取第i个结点的元素 
{
	int k = 0;
	while(p = p -> next)				//循环并更新指针所指结点 
	{
		k ++;
		if(k == i)				//找到该节点 
		{
			*e = p -> data;				//取出元素 
			return k;
		}
	}
	return 0;
}

LinkNode *LocateElem(LinkList p, ElemType e)				//从链表中找到特定元素（在链表中第一次出现），返回结点指针 
{
	while(p = p -> next)				//循环并更新指针所指结点 
	{
		if(p -> data == e)				//找到该元素 
		{
			return p;				//返回结点指针 
		}
	}
	return NULL;
}




LinkNode *PriorElem(LinkList p, LinkNode *cur_e)				//求链表中某结点的前驱（不是第一个元素） 
{
	for(; p -> next; p = p -> next)				//从前往后遍历链表 
	{
		if(p -> next == cur_e)				//找到该结点的前驱 
			return p;
	}
	return NULL;
}

LinkNode *NextElem(LinkList p, LinkNode *cur_e)				//求链表中某结点的后继（不是最后一个元素） 
{
	return cur_e -> next;
}

LinkNode *ListInsert(LinkList p, int i, ElemType e)				//在链表中第i个结点插入元素e 
{
	if(i < 1)				//结点位置不合法 
		return NULL;
	for(; p; p = p -> next)				//遍历链表 
	{
		if(--i < 1)				//找到顺序排放位置为第i-1个的结点p
		{
			LinkNode *q = (LinkNode *)malloc(sizeof(LinkNode));				//分配指针用来插入元素e 
			if(!q)
			{
				printf("插入节点时，分配空间失败. \n");
				exit(0);
			}
			q -> next = p -> next;				//使q指向p结点的后继 
			p -> next = q;				//p的下一个结点变为q （q此时为第i个结点） 
			q -> data = e;				//赋值 
			return q;
		}
	}
	return NULL;
}

int ListDelete(LinkList p, int i, ElemType *e)				//在链表中删除第i个结点 
{
	if(i < 1)				//结点位置不合法 
		return 0;
	LinkNode *q = p;				//q指向p 
	for(p = p -> next; p; p = p -> next)				//遍历链表 
	{
		if(--i < 1)				//找到i-1结点p 
		{
			q -> next = p -> next;				//q指向p的后继 （此时为第i个结点） 
			*e = p -> data;				//取p中的元素 
			free(p);				//删除该结点 
			return 1;
		}
		q = p;				//更新q的位置与p相同 
	}
	return 0;
}

void PrintLinkNode(LinkNode *p)				//打印p结点的数据 
{
	printf("%d\n", p -> data);
}

void ListTraverse(LinkList p, LinkNode *q)				//遍历链式表，访问每个结点（并打印出每一个结点） 
{
	int i = 1;
	while(p = p -> next)
	{
		q = p;
		printf("结点%d为：", i);
		PrintLinkNode(q);
		i ++;
	}
	printf("\n");
}

int main()
{
	LinkNode *p;				//Traverse遍历所用指针 
	first = initList();				//初始化链表 
	ListInsert(first, 1, 2);				//以下是向链表中插入数字 
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
	ListTraverse(first, p);				//遍历链表并打印 
	
	printf("----------------------------\n");
	
	ElemType e;
	ElemGet(first, 10, &e);				//取链表中某结点的数据 
	printf("读取的数据为 %d \n", e);
	
	LinkNode *q = LocateElem(first, 6);				//找前驱和后继 
	if(!q)
		printf("没有找到值对应的结点\n");
	else
	{
		q = PriorElem(first, q);
		printf("找到结点的前驱为 %d -- ", q -> data);
		printf("找到结点为 %d -- ", q -> next -> data);
		if(q -> next -> next)
			printf("找到结点的后继为 %d ", NextElem(first, NextElem(first, q)) -> data);
		printf("\n");
	}
	
	if(ListDelete(first, 3, &e) > 0)				//测试删除功能 
		printf("删除的值为 %d \n", e);
	else
		printf("删除失败 %d \n", e);
		
	printf("----------------------------\n");
	
	ListTraverse(first, p);					//打印删除后的结果 
	
	DestroyList(first);				//删除链表 
	
	return 0;
}

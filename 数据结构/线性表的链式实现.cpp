#include <stdio.h>
#include <stdlib.h>

#define ElemType int

#define _DEBUG_ 1


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

#ifdef _DEBUG_

LinkNode head;


void initList1(LinkNode *p)
{
	p = (LinkNode *)malloc(sizeof(LinkNode));
	if(!p)
	{
		printf("初始化分配头结点失败 \n");
		exit(0);
	}
	p -> next = NULL;
}

void initList2()
{
	first = &head;
	first -> next = NULL;
}

#endif

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

LinkNode *LocateElem(LinkList p, ElemType e)				//从链表中找到特定元素，返回结点指针 
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




LinkNode *PriorElem(LinkList p, LinkNode *cur_e)				//求链表中某结点的前驱 
{
	for(; p -> next; p = p -> next)				//从前往后遍历链表 
	{
		if(p -> next == cur_e)				//找到该结点的前驱 
			return p;
	}
	return NULL;
}

LinkNode *NextElem(LinkList p, LinkNode *cur_e)				//求链表中某结点的后继 
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
	printf("%d,", p -> data);
}

void Add2(LinkNode *p)				
{
	p -> data += 2;
	printf("+2,");
}

void DebugLinkNode(LinkNode *p)
{
	printf("结点 - (*addr) = value : ");
	printf("(*%lx) = %d\n", p, p -> data);
}

void ListTraverse(LinkList p, void (*ptrFunc)(LinkNode *ptr))
{
	printf("链表(表长 = %d): ", ListLength(p));
	while(p = p -> next)
		(*ptrFunc)(p);
	printf("\n");
}

int main()
{
	
	void (*ptrFunc)(LinkNode *p) = DebugLinkNode;
	
	
	first = initList();
	
	ListTraverse(first, ptrFunc);
	ListInsert(first, 1, 2);
	ListInsert(first, 1, 3);
	ListInsert(first, 1, 4);
	ListInsert(first, 1, 5);
	ListTraverse(first, ptrFunc);
	ListInsert(first, 1, 6);
	ListInsert(first, 1, 7);
	ListInsert(first, 1, 8);
	ListInsert(first, 1, 9);
	ListTraverse(first, ptrFunc);
	ListInsert(first, 3, 666);
	ListInsert(first, 5, 777);
	ListInsert(first, 7, 888);
	ListInsert(first, 9, 999);
	ListTraverse(first, ptrFunc);
	
	ElemType ei;
	printf("取数据之前 %d -- ", ei);
	ElemGet(first, 10, &ei);
	printf("读取的数据为 %d \n", ei);
	
	LinkNode *q = LocateElem(first, 888);
	if(!q)
		printf("没有找到值对应的结点\n");
	else
	{
		q = PriorElem(first, q);
		printf("找到结点的前驱为 %d -- ", q -> data);
		printf("找到结点为 %d -- ", q -> next ->data);
		if(q -> next -> next)
			printf("找到结点的后继为 %d ", NextElem(first, NextElem(first, q)) -> data);
		printf("\n");
	}
	
	
	printf("删除前的值 %d -- ", ei);
	if(ListDelete(first, 15, &ei) > 0)
		printf("删除的值为 %d \n", ei);
	else
		printf("删除失败 %d \n", ei);
	
	ListTraverse(first, ptrFunc);
	printf("删除前的值 %d -- ", ei);
	if(ListDelete(first, 10, &ei) > 0)
		printf("删除的值为 %d \n", ei);
	else
		printf("删除失败 %d \n", ei);
	
	printf("删除前的值 %d -- ", ei);
	if(ListDelete(first, 6, &ei) > 0)
		printf("删除的值为 %d \n", ei);
	else
		printf("删除失败 %d \n", ei);
	ListTraverse(first, ptrFunc);
	
	ptrFunc = Add2;
	printf("每个数据元素准备+2\n");
	ListTraverse(first, ptrFunc);
	printf("完成+2后，新的链表：");
	ListTraverse(first, PrintLinkNode); 
	
	
	
	
	DestroyList(first);
	
	return 0;
}

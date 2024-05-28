#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX 10

typedef struct				//队列结构体 
{
	ElemType *base;
	int front, rear;
	int tag;
}SqQueue;

void InitQueue(SqQueue *Q)				//初始化循环队列 
{
	Q->base = (ElemType *)malloc(MAX * sizeof(ElemType));				//为队列分配空间 
	if(!Q->base)
	{
		printf("存储分配失败\n");
		exit(0);
	}
	Q->front = Q->rear = 0;				//头尾置0使得队列为空 
	Q->tag = 0;				//初始化状态队列为空，tag初始化为0 
}

void EnQueue(SqQueue *Q, ElemType e)				//给队尾插入元素e 
{
	if((Q->tag == 1) && (Q->rear == Q->front))				//队满无法插入 
	{
		printf("队满\n");
		exit(0);
	}
	Q->base[Q->rear] = e;				//将e插入队尾 
	Q->rear = (Q->rear + 1) % MAX;				//循环队列，取模可以得到循环，队尾指针+1 
	if(Q->tag == 0)				//此时队列非空 
		Q->tag == 1;
}

ElemType DeQueue(SqQueue *Q)				//删除队头元素e并且返回e 
{
	ElemType e;
	if((Q->tag == 0) && (Q->rear == Q->front))				//队空则无法删除 
	{
		printf("队空\n");
		exit(0);
	}
	e = Q->base[Q->front];				//取出队头元素 
	Q->front = (Q->front + 1) % MAX;				//队头指针+1 
	if(Q->tag == 1)				//此时队列非满 
		Q->tag == 0;
	return e;
}

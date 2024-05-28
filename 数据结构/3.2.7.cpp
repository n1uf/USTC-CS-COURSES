#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX 10

typedef struct				//���нṹ�� 
{
	ElemType *base;
	int front, rear;
	int tag;
}SqQueue;

void InitQueue(SqQueue *Q)				//��ʼ��ѭ������ 
{
	Q->base = (ElemType *)malloc(MAX * sizeof(ElemType));				//Ϊ���з���ռ� 
	if(!Q->base)
	{
		printf("�洢����ʧ��\n");
		exit(0);
	}
	Q->front = Q->rear = 0;				//ͷβ��0ʹ�ö���Ϊ�� 
	Q->tag = 0;				//��ʼ��״̬����Ϊ�գ�tag��ʼ��Ϊ0 
}

void EnQueue(SqQueue *Q, ElemType e)				//����β����Ԫ��e 
{
	if((Q->tag == 1) && (Q->rear == Q->front))				//�����޷����� 
	{
		printf("����\n");
		exit(0);
	}
	Q->base[Q->rear] = e;				//��e�����β 
	Q->rear = (Q->rear + 1) % MAX;				//ѭ�����У�ȡģ���Եõ�ѭ������βָ��+1 
	if(Q->tag == 0)				//��ʱ���зǿ� 
		Q->tag == 1;
}

ElemType DeQueue(SqQueue *Q)				//ɾ����ͷԪ��e���ҷ���e 
{
	ElemType e;
	if((Q->tag == 0) && (Q->rear == Q->front))				//�ӿ����޷�ɾ�� 
	{
		printf("�ӿ�\n");
		exit(0);
	}
	e = Q->base[Q->front];				//ȡ����ͷԪ�� 
	Q->front = (Q->front + 1) % MAX;				//��ͷָ��+1 
	if(Q->tag == 1)				//��ʱ���з��� 
		Q->tag == 0;
	return e;
}

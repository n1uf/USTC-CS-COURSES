/*ѡ�����Ϊ
	CCDAA DABCD DDBCB */
	
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ElemType char
#define MAX 20

typedef struct SqStack			//ջ 
{
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;

void InitStack(SqStack *q)			//��ʼ��ջ 
{
	q->base = (ElemType*)malloc(MAX * sizeof(ElemType));
	if(!q->base)
		printf("����洢ʧ��");
	q->top = q->base;
	q->stacksize = MAX;
}

void PushStack(SqStack *q, ElemType e)			//��ջ 
{
	if(q->top - q->base >= q->stacksize)
		printf("ջ��");
	*q->top ++ = e;
}

bool EmptyStack(SqStack *q)			//�ж�ջ�Ƿ�Ϊ�� 
{
	if(q->top == q->base)
		return true;
	return false;
}

char PopStack(SqStack *q)			//��ջ�����س�ջ��Ԫ�� 
{
	if(!EmptyStack(q))
	{
		char e = *--q->top;
		return e;
	}
}

int IsPalindrome(char *t)			//�ж��Ƿ�Ϊ���� 
{
	SqStack *S;
	InitStack(S);			//��ʼ�� 
	int i;
	int len = strlen(t);
	for(i = 0; i < len / 2; i ++)			//һ��Ԫ�ؽ�ջ 
		PushStack(S, t[i]);
	if(len % 2 != 0)			//�ж��Ƿ������ַ����м�Ԫ�� 
		i ++;
	char temp;
	while(!EmptyStack(S))			//��ջԪ��һһ��ջ�����ַ���ʣ�µ���ĸһһ�Ա� 
	{
		temp = PopStack(S);
		if(temp != t[i])
			return 0;
		else
			i ++;
	}
	return 1;			//�Ա������ȷ���ǻ��� 
}

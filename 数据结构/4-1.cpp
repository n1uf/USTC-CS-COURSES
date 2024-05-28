/*选择题答案为
	CCDAA DABCD DDBCB */
	
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ElemType char
#define MAX 20

typedef struct SqStack			//栈 
{
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;

void InitStack(SqStack *q)			//初始化栈 
{
	q->base = (ElemType*)malloc(MAX * sizeof(ElemType));
	if(!q->base)
		printf("分配存储失败");
	q->top = q->base;
	q->stacksize = MAX;
}

void PushStack(SqStack *q, ElemType e)			//入栈 
{
	if(q->top - q->base >= q->stacksize)
		printf("栈满");
	*q->top ++ = e;
}

bool EmptyStack(SqStack *q)			//判断栈是否为空 
{
	if(q->top == q->base)
		return true;
	return false;
}

char PopStack(SqStack *q)			//出栈，返回出栈的元素 
{
	if(!EmptyStack(q))
	{
		char e = *--q->top;
		return e;
	}
}

int IsPalindrome(char *t)			//判断是否为回文 
{
	SqStack *S;
	InitStack(S);			//初始化 
	int i;
	int len = strlen(t);
	for(i = 0; i < len / 2; i ++)			//一半元素进栈 
		PushStack(S, t[i]);
	if(len % 2 != 0)			//判断是否跳过字符串中间元素 
		i ++;
	char temp;
	while(!EmptyStack(S))			//将栈元素一一出栈，与字符串剩下的字母一一对比 
	{
		temp = PopStack(S);
		if(temp != t[i])
			return 0;
		else
			i ++;
	}
	return 1;			//对比完均正确，是回文 
}

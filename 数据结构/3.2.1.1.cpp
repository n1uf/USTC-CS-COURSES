#include <stdio.h>
#include <stdlib.h>

#define SElemType int

typedef struct
{
	int top[2], bot[2];				//栈顶和栈底指针 
	SElemType *V;					//栈数组 
	int m;							//栈最大可容纳元素个数 
}DblStack;

DblStack *InitDblStack(DblStack *S, int m)
{
	S -> V = (SElemType *)malloc(m * sizeof(SElemType));
	S -> bot[0] = -1;
	S -> bot[1] = m;
	S -> top[0] = -1;
	S -> top[1] = m;
	return S;
}

int IsEmpty(DblStack S, int i)
{
	if(S.top[i] == S.bot[i])
		return 1;
	return 0;
}

int IsFull(DblStack S)
{
	if(S.top[0] + 1 == S.top[1])
		return 1;
	return 0;
}

DblStack DblPush(DblStack S, int i, SElemType x)
{
	if(IsFull(S))
		printf("栈满");
		return S;
	if(i == 0)
		S.V[++ S.top[0]] = x;
	else
		S.V[-- S.top[1]] = x;
	return S;
}

SElemType DblOut(DblStack S, int i, SElemType x)
{
	if(IsEmpty(S, i))
		return false;
	if(i == 0)
		x = S.V[S.top[0] --];
	else
		x = S.V[S.top[0] ++];
	return x;
}


int main()
{
	DblStack *St;
	InitDblStack(St, 10);
	return 0;
}


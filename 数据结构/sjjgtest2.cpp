#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

typedef struct node
{
	char ele;
	struct node *next;
}LinkNode, *LinkList;

LinkList InitList()
{	// 初始化链表 
	LinkList p = (LinkList)malloc(sizeof(LinkNode));
	p->next = p;
	return p;
}

void AddEles(LinkList L, char *str)
{	// 向每个结点加入字符串中的字符 
	LinkList p = L;
    for(int i = 0; str[i] != '\0'; i ++)
    {	// 字符串的每个值依次进入每一个结点 
    	
    	// 为新结点赋值 
        LinkList q = (LinkList)malloc(sizeof(LinkNode));
        q->ele = str[i];
        
        // 插入到之前结点的后继 
        p->next = q;
        p = q;
    }
    
    p->next = L;
}

int IsPalindrome(LinkList p, char *str, int size)
{	// 判断是否中心对称 

    char temp[MAXSIZE];
    for(int j = 0; j < size; j++)
    {
        temp[j] = str[size - j - 1];
    }
    for(int j = 0; j < size; j++)
    {
        if(temp[j] != str[j])
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
	LinkList L = InitList();
    char str[MAXSIZE];
    printf("输入字符串:\n");
    scanf("%s", str);
    
    int size = strlen(str);
    AddEles(L, str);
    
    if(IsPalindrome(L, str, size))
        printf("中心对称\n");
    else
        printf("不中心对称\n");
    return 0;
}

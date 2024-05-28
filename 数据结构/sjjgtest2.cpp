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
{	// ��ʼ������ 
	LinkList p = (LinkList)malloc(sizeof(LinkNode));
	p->next = p;
	return p;
}

void AddEles(LinkList L, char *str)
{	// ��ÿ���������ַ����е��ַ� 
	LinkList p = L;
    for(int i = 0; str[i] != '\0'; i ++)
    {	// �ַ�����ÿ��ֵ���ν���ÿһ����� 
    	
    	// Ϊ�½�㸳ֵ 
        LinkList q = (LinkList)malloc(sizeof(LinkNode));
        q->ele = str[i];
        
        // ���뵽֮ǰ���ĺ�� 
        p->next = q;
        p = q;
    }
    
    p->next = L;
}

int IsPalindrome(LinkList p, char *str, int size)
{	// �ж��Ƿ����ĶԳ� 

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
    printf("�����ַ���:\n");
    scanf("%s", str);
    
    int size = strlen(str);
    AddEles(L, str);
    
    if(IsPalindrome(L, str, size))
        printf("���ĶԳ�\n");
    else
        printf("�����ĶԳ�\n");
    return 0;
}

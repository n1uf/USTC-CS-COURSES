/*用链表的方式存储从键盘输入的 1958 个 int 类型数字，并用插入排序法将链表中的数从大到小排列后输出。
插入排序： 前m个数已排好序，将第m+1个数插入到合适位置。
链表形式的插入排序：每次插入链表时，需要保证链表从大到小连接*/


#include <stdio.h>
#include <stdlib.h>

typedef struct link 
{
    int val; // 需要排序的值
    struct link *next; // 指向下一个节点
} LINK;

LINK *createLink(int val);
LINK *insertLink(LINK *head, int val);
void printLink(LINK *head);

LINK *createLink(int val) 
{
    // 创建一个链表节点并设定其 val
    LINK *res = (LINK*)malloc(sizeof(LINK));
    res->val = val;
    res->next = NULL; // 1 point
    return res;
}
LINK *insertLink(LINK *head, int v) 
{
    // 向 head 链表插入值为 v 的链表节点，保持 head 链表是从大到小排序的
    // 并返回链表的头部
    LINK *p = createLink(v);
    if (head == NULL) 
	{
        // head 中没有元素，直接插入
        head = p;
        return head;
    }
    if (v >= head->val) 
	{
        // v 为 head 中最大的值
        p->next = head;
        head = p; // 更新 head
        return head;
    }

}

void printLink(LINK *head) 
{
    LINK *p = head;
    while (p != NULL) 
	{
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
    return ;
}
int main() 
{
    int i, j, n = 1958, v = 0;
    // 在输入的时候直接保证链表有序
    LINK *head = NULL, *p;
    for (i = 0; i < n; i++) 
	{
        scanf("%d", &v);
        head = insertLink(head, v);
        // printLink(head);
    }
    printLink(head);

    p = head; // 释放空间
    while (p != NULL) 
	{
        LINK *f = p;
        p = p->next;
        free(f);
    }
    return 0;
}

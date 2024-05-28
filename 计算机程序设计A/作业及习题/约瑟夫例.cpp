#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int number;
    struct node * next;
}Person;
Person * InitList(int n)
{
    Person * head=(Person*)malloc(sizeof(Person));
    /*准备一个头结点*/
    head->number=1;
    head->next=NULL;
    Person * cyclic=head;
    /*循环创建*/
    for (int i=2; i<=n; i++) 
    {
        /*申请空间存储数据*/
        Person * body=(Person*)malloc(sizeof(Person));
        body->number=i;
        body->next=NULL; 
        /*连接*/
        cyclic->next=body;
        /*cyclic继续用作循环变量*/
        cyclic=cyclic->next;
    }
    /*首尾相连*/
    cyclic->next=head;
    return head;
}

void FindAndKillK(Person * head,int s,int m)
{
 
    Person * tail=head;
    /*找到链表第一个结点的上一个结点，为删除操作做准备*/
    while (tail->next!=head) 
    {
        tail=tail->next;
    }
    Person * p=head;
    /*找到编号为s的人*/
    while (p->number!=s)
    {
        tail=p;
        p=p->next;
    }
    /*从编号为s的人开始，只有符合p->next==p时，说明链表中除了p结点，所有编号都出列了*/
    while (p->next!=p) 
    {
        /*找到从p报数1开始，报m的人，并且还要知道数m-1的人的位置tail，方便做删除操作*/
        for (int i=1; i<m; i++) 
        {
            /*存储下上一个位置*/
            tail=p;
            p=p->next;
        }
        /*从链表上将p结点摘下来*/
        tail->next=p->next;
        printf("%d ",p->number);
        free(p);
        /*继续使用p指针指向出列编号的下一个编号，游戏继续*/
        p=tail->next;
    }
    printf("%d",p->number);
    free(p);
}

int main()
{
    int n,s,m;
    scanf("%d %d %d",&n,&s,&m);
    Person * head=InitList(n);
    FindAndKillK(head, s, m);
    return 0;
} 

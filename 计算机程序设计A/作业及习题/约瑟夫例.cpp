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
    /*׼��һ��ͷ���*/
    head->number=1;
    head->next=NULL;
    Person * cyclic=head;
    /*ѭ������*/
    for (int i=2; i<=n; i++) 
    {
        /*����ռ�洢����*/
        Person * body=(Person*)malloc(sizeof(Person));
        body->number=i;
        body->next=NULL; 
        /*����*/
        cyclic->next=body;
        /*cyclic��������ѭ������*/
        cyclic=cyclic->next;
    }
    /*��β����*/
    cyclic->next=head;
    return head;
}

void FindAndKillK(Person * head,int s,int m)
{
 
    Person * tail=head;
    /*�ҵ������һ��������һ����㣬Ϊɾ��������׼��*/
    while (tail->next!=head) 
    {
        tail=tail->next;
    }
    Person * p=head;
    /*�ҵ����Ϊs����*/
    while (p->number!=s)
    {
        tail=p;
        p=p->next;
    }
    /*�ӱ��Ϊs���˿�ʼ��ֻ�з���p->next==pʱ��˵�������г���p��㣬���б�Ŷ�������*/
    while (p->next!=p) 
    {
        /*�ҵ���p����1��ʼ����m���ˣ����һ�Ҫ֪����m-1���˵�λ��tail��������ɾ������*/
        for (int i=1; i<m; i++) 
        {
            /*�洢����һ��λ��*/
            tail=p;
            p=p->next;
        }
        /*�������Ͻ�p���ժ����*/
        tail->next=p->next;
        printf("%d ",p->number);
        free(p);
        /*����ʹ��pָ��ָ����б�ŵ���һ����ţ���Ϸ����*/
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

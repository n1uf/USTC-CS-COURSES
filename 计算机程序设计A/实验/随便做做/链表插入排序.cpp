/*������ķ�ʽ�洢�Ӽ�������� 1958 �� int �������֣����ò������򷨽������е����Ӵ�С���к������
�������� ǰm�������ź��򣬽���m+1�������뵽����λ�á�
������ʽ�Ĳ�������ÿ�β�������ʱ����Ҫ��֤����Ӵ�С����*/


#include <stdio.h>
#include <stdlib.h>

typedef struct link 
{
    int val; // ��Ҫ�����ֵ
    struct link *next; // ָ����һ���ڵ�
} LINK;

LINK *createLink(int val);
LINK *insertLink(LINK *head, int val);
void printLink(LINK *head);

LINK *createLink(int val) 
{
    // ����һ������ڵ㲢�趨�� val
    LINK *res = (LINK*)malloc(sizeof(LINK));
    res->val = val;
    res->next = NULL; // 1 point
    return res;
}
LINK *insertLink(LINK *head, int v) 
{
    // �� head �������ֵΪ v ������ڵ㣬���� head �����ǴӴ�С�����
    // �����������ͷ��
    LINK *p = createLink(v);
    if (head == NULL) 
	{
        // head ��û��Ԫ�أ�ֱ�Ӳ���
        head = p;
        return head;
    }
    if (v >= head->val) 
	{
        // v Ϊ head ������ֵ
        p->next = head;
        head = p; // ���� head
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
    // �������ʱ��ֱ�ӱ�֤��������
    LINK *head = NULL, *p;
    for (i = 0; i < n; i++) 
	{
        scanf("%d", &v);
        head = insertLink(head, v);
        // printLink(head);
    }
    printLink(head);

    p = head; // �ͷſռ�
    while (p != NULL) 
	{
        LINK *f = p;
        p = p->next;
        free(f);
    }
    return 0;
}

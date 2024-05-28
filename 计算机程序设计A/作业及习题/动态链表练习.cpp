#include <stdio.h> 
#include <stdlib.h>
/*建立链表*/ 
struct books
{
    char name[101];
    char sentence[1001];
    struct books *next;
};
struct books *creat(int n)//返回指针的指针函数
{
    struct books *head, *p_last, *p_new;
    int i;
    for (i = 0; i < n; i ++)
    {
        p_new = (struct books*)malloc(sizeof(struct books));//指针pb指向结构体指针函数
        printf("%dth input Name and Age:\n", i + 1);
        scanf("%s %s", &p_new -> name, &p_new -> sentence);//结构体成员赋值
        if (i == 0)
            p_last = head = p_new;//复制地址
        else
            p_last->next = p_new;//将地址赋给上一个地址的next
        p_new->next = NULL;//清空
        p_last = p_new;//更新
    }
    return(head);//返回头地址 
}
int main(void)
{
    puts("please input the number:");
    int n;//几个节点
    scanf("%d", &n);
    struct books *p = creat(n);//创建指向链表头的指针
    for (int i = 0; i < n; i++)
    {
        printf("%s %s\n", p -> name, p -> sentence);
        p = p -> next;
    }
}

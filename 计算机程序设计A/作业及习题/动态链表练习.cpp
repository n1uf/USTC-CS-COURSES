#include <stdio.h> 
#include <stdlib.h>
/*��������*/ 
struct books
{
    char name[101];
    char sentence[1001];
    struct books *next;
};
struct books *creat(int n)//����ָ���ָ�뺯��
{
    struct books *head, *p_last, *p_new;
    int i;
    for (i = 0; i < n; i ++)
    {
        p_new = (struct books*)malloc(sizeof(struct books));//ָ��pbָ��ṹ��ָ�뺯��
        printf("%dth input Name and Age:\n", i + 1);
        scanf("%s %s", &p_new -> name, &p_new -> sentence);//�ṹ���Ա��ֵ
        if (i == 0)
            p_last = head = p_new;//���Ƶ�ַ
        else
            p_last->next = p_new;//����ַ������һ����ַ��next
        p_new->next = NULL;//���
        p_last = p_new;//����
    }
    return(head);//����ͷ��ַ 
}
int main(void)
{
    puts("please input the number:");
    int n;//�����ڵ�
    scanf("%d", &n);
    struct books *p = creat(n);//����ָ������ͷ��ָ��
    for (int i = 0; i < n; i++)
    {
        printf("%s %s\n", p -> name, p -> sentence);
        p = p -> next;
    }
}

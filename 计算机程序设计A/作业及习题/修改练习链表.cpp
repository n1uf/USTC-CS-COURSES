#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
int flag = 0;
/*��������*/ 
typedef struct books
{
    char name[101];
    char info[1001];
    struct books *next;
}library;

/*���ĵ���*/
char book[20];

/*����ָ�������ָ��*/ 
struct books *head, *p_last, *p_new, *p, *p1, *p2;

/*����ָ���ָ�뺯��*/
struct books *creat(char str[10]);

int main(void)
{
	/*�����ʼ��*/ 
	head = NULL;
	
	/*ָ���ַ�����*/ 
	char imple[100][10];
	
	int i, j, k = 0;
	for(i = 0; strcmp(imple[i - 1], "QUIT") != 0; i ++)
	{
		scanf("%s",imple[i]);
		p = creat(imple[i]);
	}
	for (j = 0; j < flag; j ++)
    {
        printf("%s %s\n", p -> name, p -> info);
        p = p -> next;
    }
}


struct books *creat(char str[10])
{
	if(strcmp(str, "INSERT") == 0)
	{
		p_new = (struct books *)malloc(sizeof(struct books));//ָ��pbָ��ṹ��ָ�뺯��
		
    	scanf("%s %[^c\n]", &p_new -> name, &p_new -> info);//�ṹ���Ա��ֵ,info�пո����Խ��������ǻس��������ǿո���� 
    	/*��һ�β���*/ 
    	if (flag == 0)
    	{
    		p_last = head = p_new;//���Ƶ�ַ
    		printf("Insert: Success!\n");
    		flag ++;
		} 
    	for(int j = 0; p != NULL; j ++)
    	{
    		if(strcmp(p_new -> name, p -> name) == 0)
    		{
    			printf("Insert Error: This book already exists.\n");
			}
			else if(j + 1 == flag)
			{
				printf("Insert: Success!\n");
				/*��������*/
				p_last -> next = p_new;//���µ�ַ������һ����ַ����һ�� 
				flag ++;
    			p_new -> next = NULL;//���
    			p_last = p_new;//����
			}
			p = p -> next;
		}
		p = head;//��λ 
	}
	if(strcmp(str, "QUERY") == 0)
	{
		scanf("%s", book);
		for (int j = 0; p != NULL; j ++)
    	{
    		if(strcmp(p -> name, book) == 0)
    		{
    			printf("%s\n", p -> info); 
    			break; 
			}
			else if(j + 1 == flag)
			{
				printf("Query Error: This book does not exist.\n");
			}
			p = p -> next;
    	}
    	p = head;//ָ�븴λ 
	}
	if(strcmp(str, "DELETE") == 0)
	{
		scanf("%s", book);
		for (int j = 0; p != NULL; j ++)
    	{
    		if(strcmp(p -> name, book) == 0)
    		{
    			p1 = (struct books *)malloc(sizeof(struct books));
			}
		}
		flag --;
	}
	return (head);
}

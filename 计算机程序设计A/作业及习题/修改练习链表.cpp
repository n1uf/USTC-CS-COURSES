#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
int flag = 0;
/*建立链表*/ 
typedef struct books
{
    char name[101];
    char info[1001];
    struct books *next;
}library;

/*查阅的书*/
char book[20];

/*声明指向链表的指针*/ 
struct books *head, *p_last, *p_new, *p, *p1, *p2;

/*返回指针的指针函数*/
struct books *creat(char str[10]);

int main(void)
{
	/*链表初始化*/ 
	head = NULL;
	
	/*指令字符数组*/ 
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
		p_new = (struct books *)malloc(sizeof(struct books));//指针pb指向结构体指针函数
		
    	scanf("%s %[^c\n]", &p_new -> name, &p_new -> info);//结构体成员赋值,info有空格，所以结束必须是回车，不能是空格结束 
    	/*第一次操作*/ 
    	if (flag == 0)
    	{
    		p_last = head = p_new;//复制地址
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
				/*后续操作*/
				p_last -> next = p_new;//将新地址赋给上一个地址的下一个 
				flag ++;
    			p_new -> next = NULL;//清空
    			p_last = p_new;//更新
			}
			p = p -> next;
		}
		p = head;//复位 
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
    	p = head;//指针复位 
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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*定义结构体数组，NAME表示书名*/
typedef struct NAME
{ 
	char name[20];
	struct NAME *next;
}NAME;

/*INFO表示书籍信息*/
typedef struct INFO
{
	char info[1024];
	struct INFO *next;
}INFO;
int main()
{
	/*存放操作指令的字符数组*/ 
	char /*插入，删除之类的指令*/in1[1024][7], /*书籍名字*/in2[1024][20];
	char /*书籍信息*/in3[1024][1024]; 
	int i, t, m, k, j;
	
	/*输入*/ 
	for(i = 0; ; i ++)
	{
		scanf("%s", in1[i]);
		
		/*结束输出*/ 
		if(in1[i][0] == 'Q' && in1[i][1] == 'U' && in1[i][2] == 'I' && in1[i][3] == 'T') break;
		/*输入书名*/ 
		scanf("%s", in2[i]);
		
		scanf("%[^\n]", in3[i]);
	}
	for(j = 0; j < 1024; j ++)
	{
		if(in3[j][0] = ' ')
		{
			for(i = 0; i < 1024; i ++)
			{
				in3[j][i] = in3[j][i + 1]
			}
		}
	}
	NAME * pn = NULL;//创建头指针并初始化 
	INFO * pi = NULL;
	NAME * temp1 = (NAME *)malloc(sizeof(NAME));
	INFO * temp2 = (INFO *)malloc(sizeof(INFO));
	
	/*INSERT操作*/ 
	if(in1[0][0] == 'I')//处理首节点 
	{
		memcpy(temp1, in2[0], 20);
		temp1 -> next = NULL;
		pn = temp1;
		memcpy(temp2, in3[0], 1024);
		temp2 -> next = NULL;
		pi = temp2;
		printf("Insert: Success!\n");
	}
	else 
	{
		temp1 -> next = NULL;
		temp2 -> next = NULL;
		pn = temp1;
		pi = temp2;
	    printf("Query Error: This book does not exist.\n");
	} 
	for(t = 1; t < i; t ++)//处理后续的指令 
	{ 
		k = 0;//k初值为0代表没有，有的话k赋为1 
		j = 1;
	    if(in1[t][0] == 'I')
	    {
	    	NAME * p1 = pn;
			int s = 0;
			
			/*遍历链表*/
			while(p1 != NULL)
			{
				j = strcmp(p1 -> name, in2[t]);
				if(j == 0)
				{
				    k = 1;//有相同为1 
				    break;
				}
				p1 = p1 -> next;
			    s ++; 
			}
			
			if(k == 1) printf("Insert Error: This book already exists.\n");//若果有相同的就error
			
			else//没有相同的就插入 
			{
				NAME * a1 = (NAME *)malloc(sizeof(NAME));
				INFO * a2 = (INFO *)malloc(sizeof(INFO));
	    		memcpy(a1, in2[t], 20);
	    		memcpy(a2, in3[t], 1024);
	    		a1 -> next = NULL;
	    		a2 -> next = NULL;
	    		temp1 -> next = a1;
	    		temp1 = temp1 -> next;
	    		temp2 -> next = a2;
	    		temp2 = temp2 -> next;
	    		printf("Insert: Success!\n");
	        }
		}
		
		/*DELETE操作*/ 
		if(in1[t][0] == 'D')//删除和插入一样
		{
		    NAME * p1 = pn;
			int s = 0;
			
			/*遍历链表*/ 
			while(p1 != NULL)
			{
			
			    if(temp1 == NULL) break;
				j = strcmp(p1 -> name,in2[t]);
				if(j == 0)
				{
				    k = 1;
				    break;
				}
				p1 = p1->next;
			    s ++; 
			}
			
			if(k == 0)	printf("Delete Error: This book does not exist.\n");//没有相同的就error 
			
			else//有相同的就删除 
			{
				temp1 = pn;
				for(m = 1; m < s; m ++)
				{
					temp1 = temp1 -> next;
				}
				if(temp1 -> next == NULL) temp1 = NULL;
				else
				{
					temp1 = temp1 -> next; 
			    }
				temp2 = pi;
				for(m = 1; m < s; m ++)
				{
					temp2 = temp2 -> next;
				}
				if(temp2 -> next == NULL) temp2 = NULL;
				else
				{
					temp2 = temp2 -> next;	
			    }
				printf("Delete: Success!\n");
			}
		}
		
		/*QUERY操作*/ 
		if(in1[t][0] == 'Q' && in1[t][1] == 'U' && in1[t][2] == 'E' && in1[t][3] == 'R' && in1[t][4] == 'Y')
		{
			NAME * p1 = pn;
			int s = 0;
			while(p1 != NULL)
			{
				j = strcmp(p1->name,in2[t]);
				if(j == 0)
				{
				    k = 1;
				    break;
				}
				p1 = p1->next;
			    s++; 
			}
			if(k == 1)//相同书名输出信息 
			{
				INFO * p2 = pi;
				for(m = 1; m <= s; m++)
				{
					p2 = p2->next;
				}
				printf("%s\n",p2->info);
			}
			else printf("Query Error: This book does not exist.\n");
		}
 	}
} 

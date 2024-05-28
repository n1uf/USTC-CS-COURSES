#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*����ṹ�����飬NAME��ʾ����*/
typedef struct NAME
{ 
	char name[20];
	struct NAME *next;
}NAME;

/*INFO��ʾ�鼮��Ϣ*/
typedef struct INFO
{
	char info[1024];
	struct INFO *next;
}INFO;
int main()
{
	/*��Ų���ָ����ַ�����*/ 
	char /*���룬ɾ��֮���ָ��*/in1[1024][7], /*�鼮����*/in2[1024][20];
	char /*�鼮��Ϣ*/in3[1024][1024]; 
	int i, t, m, k, j;
	
	/*����*/ 
	for(i = 0; ; i ++)
	{
		scanf("%s", in1[i]);
		
		/*�������*/ 
		if(in1[i][0] == 'Q' && in1[i][1] == 'U' && in1[i][2] == 'I' && in1[i][3] == 'T') break;
		/*��������*/ 
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
	NAME * pn = NULL;//����ͷָ�벢��ʼ�� 
	INFO * pi = NULL;
	NAME * temp1 = (NAME *)malloc(sizeof(NAME));
	INFO * temp2 = (INFO *)malloc(sizeof(INFO));
	
	/*INSERT����*/ 
	if(in1[0][0] == 'I')//�����׽ڵ� 
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
	for(t = 1; t < i; t ++)//���������ָ�� 
	{ 
		k = 0;//k��ֵΪ0����û�У��еĻ�k��Ϊ1 
		j = 1;
	    if(in1[t][0] == 'I')
	    {
	    	NAME * p1 = pn;
			int s = 0;
			
			/*��������*/
			while(p1 != NULL)
			{
				j = strcmp(p1 -> name, in2[t]);
				if(j == 0)
				{
				    k = 1;//����ͬΪ1 
				    break;
				}
				p1 = p1 -> next;
			    s ++; 
			}
			
			if(k == 1) printf("Insert Error: This book already exists.\n");//��������ͬ�ľ�error
			
			else//û����ͬ�ľͲ��� 
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
		
		/*DELETE����*/ 
		if(in1[t][0] == 'D')//ɾ���Ͳ���һ��
		{
		    NAME * p1 = pn;
			int s = 0;
			
			/*��������*/ 
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
			
			if(k == 0)	printf("Delete Error: This book does not exist.\n");//û����ͬ�ľ�error 
			
			else//����ͬ�ľ�ɾ�� 
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
		
		/*QUERY����*/ 
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
			if(k == 1)//��ͬ���������Ϣ 
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

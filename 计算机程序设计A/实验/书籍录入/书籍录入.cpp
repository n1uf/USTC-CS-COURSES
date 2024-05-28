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
	FILE *in, *out;
	if((in = fopen("input.txt","r")) == NULL || (out = fopen("output.txt","w")) == NULL)
	{
		printf("error: cant't open this file! \n");
		exit(0);
	}
	/*��Ų���ָ����ַ�����*/ 
	char /*���룬ɾ��֮���ָ��*/in1[1024][7], /*�鼮����*/in2[1024][20];
	char /*�鼮��Ϣ*/in3[1024][1024]; 
	int i, t, m, k, j;
	
	/*����*/ 
	for(i = 0; i < 100; i ++)
	{
		fscanf(in, "%s", in1[i]);
		
		/*��������*/ 
		fscanf(in, "%s", in2[i]);
		
		fscanf(in, "%[^\n]", in3[i]);
	}
	for(j = 0; j < 1024; j ++)
	{
		if(in3[j][0] == ' ')
		{
			for(i = 0; i < 1024; i ++)
			{
				in3[j][i] = in3[j][i + 1];
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
		fprintf(out, "Insert: Success!\n");
	}
	else
	{
		temp1 -> next = NULL;
		temp2 -> next = NULL;
		pn = temp1;
		pi = temp2;
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
			
			if(k == 1) fprintf(out, "Insert Error: This book already exists.\n");//��������ͬ�ľ�error
			
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
	    		fprintf(out, "Insert: Success!\n");
	        }
		}
		
		/*DELETE����*/ 
		if(in1[t][0] == 'D')//ɾ���Ͳ���һ��
		{
		    NAME * p1 = pn;
			int s = 0;
			while(p1 != NULL)
			{
			
			    if(temp1 == NULL) break;
				j = strcmp(p1->name,in2[t]);
				if(j == 0)
				{
				    k = 1;
				    break;
				}
				p1 = p1->next;
			    s++; 
			}
			if(k == 0)	fprintf(out, "Delete Error: This book does not exist.\n");
			else
			{
				temp1 = pn;
				for(m = 1; m < s; m ++)
				{
					temp1 = temp1 -> next;
				}
				if(temp1->next == NULL && temp1 == pn)
				{
					pn = NULL;
					temp1 = NULL;
					k = 2;
				}
				if(temp1 == pn && pn != NULL)
				{
					pn = temp1 -> next;
				}
				if(k == 2) ; 
				else if(temp1 -> next == NULL) temp1 = NULL;
				else
				{
					temp1 -> next = temp1 -> next -> next; 
			    }
				temp2 = pi;
				for(m = 1; m < s; m ++)
				{
					temp2 = temp2 -> next;
				}
				if(temp2-> next == NULL && temp2 == pi)
				{
					pi = NULL;
					temp2 = NULL;
				}
				if(temp2 == pi && pi != NULL)
				{
					pi = temp2 -> next;
				}
				if(k == 2) ;
				else if(temp2 -> next == NULL) temp2 = NULL;
				else
				{
					temp2 -> next = temp2 -> next -> next;	
			    }
				fprintf(out, "Delete: Success!\n");
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
			    s ++; 
			}
			if(k == 1)//��ͬ���������Ϣ 
			{
				INFO * p2 = pi;
				for(m = 1; m <= s; m++)
				{
					p2 = p2 -> next;
				}
				fprintf(out, "%s\n",p2 -> info);
			}
			else fprintf(out ,"Query Error: This book does not exist.\n");
		}
	}
	fprintf(out, "\n");
	
	//���� 
	char a[100][20];//��a���������ͬ������ 
	NAME *p1 = pn;
	INFO *p2 = pi;
	i = 0;
	while(p1 != NULL)
	{
		memcpy(a[i], p1 -> name,20);
		p1 = p1 -> next;
		i++;
	}
	int n, p, q, l;
	n= i;
	char str[1024];
    char *pstr[n];
    for(i = 0;i < n;i ++)
    {
    	pstr[i] = a[i];
	}
    char **s = pstr;
    for(p = 0; p < n - 1; p ++)
    {
    	for(q = 0; q < n - 1 - p; q ++)
    	{
    		l = strlen(a[p + q]);
    		for(k = 0; k < l; k ++)
    		{
    			m = *(*(s + q) + k) - *(*(s + q + 1) + k);
    		    if(m > 0) 
			    {
			        for(i = 0; i < 20; i ++)
			        {
						str[i] = a[q][i];
			        	a[q][i] = a[1 + q][i];
			        	a[1 + q][i] = str[i];
			        	str[i] = 0;
			        }
			        break;
    	        }
    	        if(m < 0) break; 
			}  
		}
	}
	//��� 
	for(i = 0;i < 100;i ++)
	{
		for(p1 = pn, p2 = pi; p1 != NULL; p1 = p1 -> next,p2 = p2 -> next)
		{
			if(strcmp(a[i],p1 -> name) == 0)
			{
				fprintf(out,"%s\n",p1 -> name);
				fprintf(out,"%s\n",p2 -> info);
				fprintf(out,"\n");
				break;
			}
		}
	}
	
	fclose(in);
	fclose(out);
} 

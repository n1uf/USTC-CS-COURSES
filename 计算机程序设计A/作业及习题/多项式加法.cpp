/*˼·��ͳһ����ʽ��չʾ��ʽΪ
������  ϵ��  x  ^  ָ�� ���������ģ�� 
����ϵ��������1��������double������λ����
����ٰ����µ�1ȥ��*/ 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
typedef struct nape
{
	int dim;
	double coe;
	struct nape *next;
} cal;
char k[2000];
int main(void)
{
	cal *head;
	cal *tail;
	head = NULL;
	tail = NULL;
	/*��������*/
	for(int a = 0; a < 1000; a++)
	{
		scanf("%c",&k[a]);
		if(k[a] == '\n')
		{
			break;
		}
	}
	/*��һ���������ַ����鳤��*/ 
	int u = strlen(k);
	
	/*������һ��0x^0�����ڽ�������������Ĵ��� ��\0�����ַ���*/
	k[u] = '+';
	k[u + 1] = '0';
	k[u + 2] = 'x';
	k[u + 3] = '^';
	k[u + 4] = '0';
	k[u + 5] = '\0';
	
	for(int a = 0; a < 1000; a++)
	{
		/*�ڶ�������ʽ*/
		if(k[a] == ' ')
		{
			/*�ж���������ʽ�Ĺ�ϵ��Ȼ����������*/
			if(k[a+1] == '-')
			{
				for(int y = a; y < 1000; y++)
				{
					k[y] = k[y+1];
				}
			}
			else
			{
				k[a] = '+';
			}
		}
	}
	/*��һ��ϵ����1�Ļ���1������ȥ*/ 
	if(k[0] == 'x')
	{
		for(int a = 1000; a > 0; a--)
		{
			k[a] = k[a - 1];
		}
		k[0] = '1';
	}
	/*���������������ϵ��1�������1*/
	for(int i=1; i < 1000; i++)
	{
		if(k[i] == 'x'&&(k[i - 1] == '-'||k[i - 1] == '+'))
		{
			for(int a = 1000; a>i; a--)
			{
				k[a] = k[a - 1];
			}
			k[i] = '1';
		}
	}
	
	
	
	/*��һ��֮ǰ��������*/ 
	if(k[0] != '-')
	{
		for(int a = 1000; a > 0; a--)
		{
			k[a] = k[a - 1];
		}
		k[0] = '+';
	}
	
	/*����Ϊһ������ϴ���*/
	for(int a=0; a < 1000; a++)
	{
		if(k[a] == 'x'&&k[a+1] != '^')
		{
			for(int n = 1000; n > a + 2; n --)
			{
				k[n] = k[n - 2];
			}
			k[a + 1] = '^';
			k[a + 2] = '1';
		}
	}
	
	int h[100];
	int r = 0;
	
	/*��¼�Ӽ���������λ��*/ 
	for(int a = 0; a < 1000; a ++)
	{
		if(k[a] == '+'||k[a] == '-')
		{
			h[r] = a;
			r++;
		}
	}
	
	/*�ó�����c���+cx^0��������ʽ*/ 
	for(int a = 0; a < r - 1; a++)
	{
		int t = 0;
		for(int q = h[a] ; q < h[a + 1]; q++)
		{
			if(k[q] == 'x') 
			{
				t++;
			}
		}
		if(t == 0) 
		{
			int c = h[a + 1];
			for(int y = 1000; y >= h[a + 1] + 3; y--) 
			{
				k[y] = k[y - 3];
			}
			k[c] = 'x';
			k[c + 1] = '^';
			k[c + 2] = '0';
		}
	}

	int j = 0;
	while(k[0] == '+'||k[0] == '-') 
	{
		/*��P���ÿһ��*/ 
		int i = 1;
		char P[50];
		memset(P, '\0', sizeof(P));
		P[0] = k[0];
		
		/*ֱ��ִ��*/ 
		while(1) 
		{
			if(k[i] == '+'||k[i] == '-'||k[i] == '\0') 
			{
				break;
			}
			P[i] = k[i];
			i++;
		}
		for(int a = 0; a <= 800-i; a++) 
		{
			k[a] = k[a + i];
		}

		int e;
		int di = 0;
		
		/*����ָ��*/ 
		for(e = 1; P[e] != 'x'; e ++);//������e��λ 
		for(int a = e + 2; a < strlen(P) ; a++)
		{
			di = di + (P[a] - 48)*pow(10,strlen(P) - a - 1);
		}
		
		/*�ַ���ת��������ʾϵ��*/ 
		double co; 
		co = atof(P);
		
		/*��������*/
		if(j == 0)//��Ԫ�ڵ� 
		{
			cal *p;
			p = (struct nape *)malloc(sizeof(struct nape));
			p -> coe = co;
			p -> dim = di;
			p -> next = head;
			head = tail = p;
			j ++;
		} 
		else//�����ڵ� 
		{
			cal *p;
			p = (struct nape *)malloc(sizeof(struct nape));
			p -> coe = co;
			p -> dim = di;
			cal *q;
			q = head;
			cal *t;
			t = (struct nape *)malloc(sizeof(struct nape));
			
			/*������������*/ 
			while(1) 
			{
				/*����*/ 
				if(q == NULL) 
				{
					p -> next = NULL;
					tail -> next = p;
					tail = p;
					break;
				}
				/*ָ����ͬ*/ 
				else if(p -> dim == q -> dim) 
				{
					q -> coe = q -> coe + p -> coe;
					break;
				}
				/*ǰ��ָ�����������ô�ѭ����ע��ָ��任����������ģ�����ͬ��ָ��*/ 
				else if((p -> dim) > (q -> dim)) 
				{
					if(q == head) 
					{
						p -> next =head;
						head = p;
						break;
					} 
					else
					{
						p -> next = q;
						t -> next = p;
						break;
					}
				} 
				else 
				{
					t = q;
					q = q -> next;
				}
			}
		}
	}
	
	/*���*/ 
	j = 0;
	cal *q = head;
	int a = 0;
	while(q != NULL)
	{
		/*ϵ������1*/ 
		if(fabs(q -> coe) >= 1e-6)
		{
			if(j != 0)
			{
				/*����0����*/ 
				if(q->coe > 1e-6)
				{
					printf("+");
					a ++;
				}
				/*�������������*/ 
				if((q -> dim == 0)||(q -> coe > 1 + 1e-3)||(q -> coe < -1 - 1e-3)||((q -> coe > -1 + 1e-3)&&(q -> coe < 1 - 1e-3)))
				{ 
					printf("%.3lf",q -> coe);
					a ++;
				}  
				else if(fabs(q -> coe + 1) < 1e-3)
				{
					printf("-");
				}
				/*ָ��Ϊ1*/ 
				if(q -> dim == 1)
				{
					printf("x");
				} 
				/*ָ��Ϊ0*/ 
				else if(q -> dim ==0) 
				{}
				/*ָ��Ϊ����д����������*/ 
				else
				{
					printf("x^%d",q -> dim);
					a ++;
				}
			} 
			else 
			{
				j ++;
				/*ͬ��*/ 
				if((q -> dim == 0)||(q -> coe > 1 + 1e-3)||(q -> coe < -1 - 1e-3)||((q -> coe > -1 + 1e-3)&&(q -> coe < 1 - 1e-3))) 
				{
					printf("%.3lf",q -> coe);
					a++;
				} 
				else if(fabs(q -> coe + 1) < 1e-3) 
				{
					printf("-");
				}
				if(q -> dim == 1) 
				{
					printf("x");
					a++;
				} 
				else if(q -> dim == 0) 
				{} 
				else 
				{
					printf("x^%d",q -> dim);
					a ++;
				}
			}
		}
		q = q -> next;
	}
	if(a == 0) 
	{
		printf("0.000");
	}
}

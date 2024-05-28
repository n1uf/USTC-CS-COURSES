/*思路是统一多项式的展示形式为
“正负  系数  x  ^  指数 ”这样多个模块 
其中系数除非是1，否则以double保留三位呈现
最后再把留下的1去掉*/ 

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
	/*输入数据*/
	for(int a = 0; a < 1000; a++)
	{
		scanf("%c",&k[a]);
		if(k[a] == '\n')
		{
			break;
		}
	}
	/*用一个变量存字符数组长度*/ 
	int u = strlen(k);
	
	/*在最后加一项0x^0，便于进行其他常数项的处理 ，\0结束字符串*/
	k[u] = '+';
	k[u + 1] = '0';
	k[u + 2] = 'x';
	k[u + 3] = '^';
	k[u + 4] = '0';
	k[u + 5] = '\0';
	
	for(int a = 0; a < 1000; a++)
	{
		/*第二个多项式*/
		if(k[a] == ' ')
		{
			/*判断两个多项式的关系，然后连接起来*/
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
	/*第一项系数是1的话把1补充上去*/ 
	if(k[0] == 'x')
	{
		for(int a = 1000; a > 0; a--)
		{
			k[a] = k[a - 1];
		}
		k[0] = '1';
	}
	/*其他项如果隐藏了系数1，则添加1*/
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
	
	
	
	/*第一项之前加上正负*/ 
	if(k[0] != '-')
	{
		for(int a = 1000; a > 0; a--)
		{
			k[a] = k[a - 1];
		}
		k[0] = '+';
	}
	
	/*次数为一的项加上次数*/
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
	
	/*记录加减法发生的位置*/ 
	for(int a = 0; a < 1000; a ++)
	{
		if(k[a] == '+'||k[a] == '-')
		{
			h[r] = a;
			r++;
		}
	}
	
	/*让常数项c变成+cx^0这样的形式*/ 
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
		/*用P存放每一项*/ 
		int i = 1;
		char P[50];
		memset(P, '\0', sizeof(P));
		P[0] = k[0];
		
		/*直接执行*/ 
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
		
		/*计算指数*/ 
		for(e = 1; P[e] != 'x'; e ++);//单纯将e移位 
		for(int a = e + 2; a < strlen(P) ; a++)
		{
			di = di + (P[a] - 48)*pow(10,strlen(P) - a - 1);
		}
		
		/*字符串转浮点数表示系数*/ 
		double co; 
		co = atof(P);
		
		/*创建链表*/
		if(j == 0)//首元节点 
		{
			cal *p;
			p = (struct nape *)malloc(sizeof(struct nape));
			p -> coe = co;
			p -> dim = di;
			p -> next = head;
			head = tail = p;
			j ++;
		} 
		else//其他节点 
		{
			cal *p;
			p = (struct nape *)malloc(sizeof(struct nape));
			p -> coe = co;
			p -> dim = di;
			cal *q;
			q = head;
			cal *t;
			t = (struct nape *)malloc(sizeof(struct nape));
			
			/*遍历链表并操作*/ 
			while(1) 
			{
				/*结束*/ 
				if(q == NULL) 
				{
					p -> next = NULL;
					tail -> next = p;
					tail = p;
					break;
				}
				/*指数相同*/ 
				else if(p -> dim == q -> dim) 
				{
					q -> coe = q -> coe + p -> coe;
					break;
				}
				/*前面指数大则跳出该次循环（注意指针变换）遍历后面的，找相同的指数*/ 
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
	
	/*输出*/ 
	j = 0;
	cal *q = head;
	int a = 0;
	while(q != NULL)
	{
		/*系数不是1*/ 
		if(fabs(q -> coe) >= 1e-6)
		{
			if(j != 0)
			{
				/*大于0则正*/ 
				if(q->coe > 1e-6)
				{
					printf("+");
					a ++;
				}
				/*输出浮点数数字*/ 
				if((q -> dim == 0)||(q -> coe > 1 + 1e-3)||(q -> coe < -1 - 1e-3)||((q -> coe > -1 + 1e-3)&&(q -> coe < 1 - 1e-3)))
				{ 
					printf("%.3lf",q -> coe);
					a ++;
				}  
				else if(fabs(q -> coe + 1) < 1e-3)
				{
					printf("-");
				}
				/*指数为1*/ 
				if(q -> dim == 1)
				{
					printf("x");
				} 
				/*指数为0*/ 
				else if(q -> dim ==0) 
				{}
				/*指数为可以写出来的数字*/ 
				else
				{
					printf("x^%d",q -> dim);
					a ++;
				}
			} 
			else 
			{
				j ++;
				/*同上*/ 
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

#include<stdio.h>
#include<math.h>
int main(void)
{
	int a, b;
	
	/*���̺�����*/
	int m[1024], n[1024];
	int i, j, s = 0, t;
	
	/*����*/ 
	scanf("%d %d",&a, &b);
	m[0] = a * 10 / b;//�� 
	n[0] = a * 10 - m[0] * b;//���� 
	for(i = 0; i < 500; i ++)
	{
	    m[i + 1] = n[i] * 10 / b;//ÿ�μ��� 
	    
	    
	    if(m[i + 1] == 0) 
		{
			n[i + 1] = n[i] * 10;
		} 
	    else
	    {
	    	n[i + 1] = n[i] *10 - m[i + 1] * b;
		}
		
	    /*����������break*/ 
	    if(n[i] == 0) 
		{
	    	s = 1;
	    	break;
		}
		for(j = i; j >= 0; j --) 
		{
			if(n[i + 1] == n[j])
			{
				if(m[i + 1] == m[j])//��ȷ�Ϊ����������������̶���Ȼ���������ֻ��һ����ȣ���Ӧ���������ʽ 
				{
					printf("0.");
				    for(t = 0; t <= i ; t ++)
				    {
						printf("%d",m[t]);
				    }
					printf("(");
					for(t = j ; t <= i ; t ++) 
					{
						printf("%d",m[t]);
					}
					printf(")");
					s = 2;
					break;
				}
				else
				{
					printf("0.");
					for(t = 0; t <= i + 1; t ++)
					{
						printf("%d",m[t]);
					}
					printf("(");
					for(t = j + 1; t <= i + 1; t ++) 
					{
					printf("%d",m[t]);
					}
					printf(")");
					s = 2;
					break;
				}
			}
		}
		if(s == 2)
		{
			break;
		}
	}
	
	
	if(s == 1)
	{
		printf("0.");
		for(t = 0; t < i + 1; t ++)
		{
			printf("%d",m[t]);
		}
	}
}

#include<stdio.h>
#include<string.h>

int udf_strcmp(char *s1, char *s2);
int s = 0;

int main()
{
	int k = 0, j = 0; 
	char ab[2048],a[1024], b[1024];
	char *p1, *p2; 
	/*��ab�洢����*/ 
	gets(ab); 
	
	/*�ֱ���a��b�洢�ո�ǰ�ͺ�*/ 
	for(k = 0; ; k ++)
	{
		if(ab[k] == ' ')
		{
			break;
		}
		a[k] = ab[k];
	}
	a[k] = '\0';
	k ++;
	for(j = 0; k <= sizeof(ab); k ++, j ++)
	{
		b[j] = ab[k];
	}
	b[j ++] = '\0';
	
	/*����ָ�����*/ 
	p1 = a; 
	p2 = b; 
	udf_strcmp(p1,p2); 
	printf("%d",s); 
}

int udf_strcmp(char *s1, char *s2)
{
	int i;
	for(i = 0; i <= 1024; i ++)
	{
		/*��⵽�����ַ�������������*/ 
		if(i != 0)
		{
			if(*(s1 - 1) == '\0' || *s2 == '\0')
			{
				break; 
			}
		}
		s += *s1 - *s2;
		s1 ++; 
		s2 ++; 
	}
	return (s);
}

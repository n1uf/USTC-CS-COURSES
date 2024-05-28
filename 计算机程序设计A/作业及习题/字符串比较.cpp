#include<stdio.h>
#include<string.h>

int udf_strcmp(char *s1, char *s2);
int s = 0;

int main()
{
	int k = 0, j = 0; 
	char ab[2048],a[1024], b[1024];
	char *p1, *p2; 
	/*用ab存储输入*/ 
	gets(ab); 
	
	/*分别用a和b存储空格前和后*/ 
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
	
	/*赋予指针变量*/ 
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
		/*检测到任意字符串结束就跳出*/ 
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

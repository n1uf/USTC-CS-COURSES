#include<stdio.h>
#include<string.h>
char *p1, *p2 ,*p3;
char del(char *s1, char *s2, char *s3);
char c[1024], ab[2048], a[1024], b[1024], _a[1024], _b[1024];
int main()
{
	int k = 0, i = 0, j = 0;  
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
	
	/*反着存储*/
	k = k - j - 1;
	_a[k + 1] = '\0';
	j = 0;
	for(; k >= 0 ; -- k, ++ j)
	{
		_a[j] = a[k];
		printf("%c",_a[j]);
	}
	printf("\n");
	k = j + 1;
	for(j ++; ab[j] != '\0'; j ++);
	j --;
	for(; j >= k ; j --, i ++)
	{
		_b[i] = ab[j];
		printf("%c",_b[i]);
	}
	_b[i] = '\0';
	
	
	/*赋予指针变量*/ 
	p1 = _a; 
	p2 = _b;
	
	del(p1, p2, p3);
	for(i = 0; a < p3; i ++)
	{
		c[i] = _a[i];
	}
	printf("%s",c);
	return 0;
}

char del(char *s1, char *s2, char *s3)
{
start:
	if(*s1 != '\0')
	{
		if(*s2 != '\0')
		{
			if(*s1 != *s2)
			{
				if(s1 != _a)
				{
					if(*(s1 - 1) != *(s2 - 1))
					{
						s1 ++;
					}
					s2 = _b;
					goto start;
				}
				else
				{
					s1 ++;
					goto start;
				}
			}
			else
			{
				if(*(s1 - 1) != *(s2 - 1))
				{
					s3 = s1;
				}
				s2 ++;
				s1 ++;
				goto start;
			}
		}
		else
		{
			goto end;
		}
	}
end:return 0;
}

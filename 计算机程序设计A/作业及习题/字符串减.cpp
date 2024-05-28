#include<stdio.h>
#include<string.h>
int main() 
{
	char str1[1024], str2[1024], str3[1024];
	char *p1 = &str1[0];
	char *p2 = &str2[0];
    char *p3 = &str3[0];
	int l1, l2 ,i ,t ,k ,m;
	k = 0;
	scanf("%s", str1);
	scanf("%s", str2);
	l1 = strlen(str1);
	l2 = strlen(str2);
	if(l2 > l1)
	{
		printf("%s",str1);
	}
	for(t = l1 - l2 ; t >= 0 ; t--)
	{
		k = 0;
		for(i = 0; i < l2 ; i++)
		{
			if (*(p1 + i + t) != *(p2 + i)) 
			{
			    k = 1;
				break; 
			}
		}
		if(k == 0)
		{
			for(i = 0,m = 0;i <= l1 - 1 ;i++,m++)
			{
				if(i == t) i = i + l2;
				*(p3 + m) = *(p1 + i);
			}
			break; 
		}
	}
	if(t == -1)
	{
		printf("%s",str1);
	}
	else
	{
		printf("%s",str3);
	}
}

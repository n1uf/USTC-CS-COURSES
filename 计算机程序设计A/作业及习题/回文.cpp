#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void A_a(char *p);//��Сдת��
int check(char s[]);//�жϴ���֮����ַ��Ƿ��ǻ���


int main()
{
    char a[1024],b[1024];
    int i,j = 0;
    gets(a);
	A_a(a);
	for(i = 0; i <= strlen(a); i ++)
	{
		if(a[i] >= 'A' && a[i] <= 'Z')
		{
			b[j] = a[i];
			j ++;
		}
	}
	j = check(b);
    printf("%d",j);
    return 0;
}

void A_a(char *p)
{
    int i;
    for(i = 0; p[i] != '\0'; i ++)
    {
    	if(p[i] >= 'a' && p[i] <= 'z')
		{
			p[i] -= 32;
		}
    }
}

int check(char s[])
{
    int k = strlen(s);
    int n = k;
    int i = 0;
    k = k - 1;
    while(i < strlen(s))
    {
        if(s[i] != s[k] )
		{
			break;
		}
        i ++;
        k --;
    }
    if(i >= strlen(s))
        return 1;   //����1������
    else
        return 0;   //����0������
}

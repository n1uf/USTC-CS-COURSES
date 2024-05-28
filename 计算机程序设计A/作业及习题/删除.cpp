#include <stdio.h>
#include <string.h>
void dele(char a[51], char b);

int main(void)
{
	char str[51], ch;
	gets(str);
	scanf("%c", &ch);
	dele(str, ch);
	puts(str);
}

void dele(char a[51], char b)
{
	int i, j;
	for(i = 0; i <= strlen(a); i ++)
	{
		if(b == a[i])
		{
			for(j = i; j <= strlen(a); j ++)
			{
				
				a[j] = a[j + 1];
			}
			i --;
		}
	}
	a[i] = '\0';
}

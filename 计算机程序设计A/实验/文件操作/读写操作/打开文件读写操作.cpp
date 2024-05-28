#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	FILE *fp;
	if (! (fp = fopen("¶ÁÐ´²Ù×÷.txt", "r+")))
	{ 
		printf("Cannot Open This File!\n");
		exit(0);
	}
	printf("You open This File!\n");
	char ch;
	ch = getchar();
	while(ch != '#')
	{
		fputc(ch, fp);
		putchar(ch);
		ch = getchar();
	}
	fclose(fp);
	putchar(10);
}

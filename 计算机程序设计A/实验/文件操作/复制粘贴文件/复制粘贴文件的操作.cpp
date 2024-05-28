#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	FILE *in, *out;
	char ch;
	if((in = fopen("C:\\Users\\niu\\Desktop\\文件操作\\复制粘贴文件\\读入文件.dat","r")) == NULL)
	{
		printf("无法打开此文件\n");
		exit(0);
	}
	if((out = fopen("C:\\Users\\niu\\Desktop\\文件操作\\复制粘贴文件\\输出文件.dat","w")) == NULL)
	{
		printf("找不到此文件\n");
		exit(0);
	}
	ch = fgetc(in);
	while(! feof(in))
	{
		fputc(ch, out);
		putchar(ch);
		ch = fgetc(in); 
	}
	putchar(10);
	fclose(in);
	fclose(out);
}

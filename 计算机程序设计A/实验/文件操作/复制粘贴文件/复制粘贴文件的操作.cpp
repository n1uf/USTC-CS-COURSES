#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	FILE *in, *out;
	char ch;
	if((in = fopen("C:\\Users\\niu\\Desktop\\�ļ�����\\����ճ���ļ�\\�����ļ�.dat","r")) == NULL)
	{
		printf("�޷��򿪴��ļ�\n");
		exit(0);
	}
	if((out = fopen("C:\\Users\\niu\\Desktop\\�ļ�����\\����ճ���ļ�\\����ļ�.dat","w")) == NULL)
	{
		printf("�Ҳ������ļ�\n");
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

#include<stdio.h>
int main()
{
	/*��Ŀ���Է�Ϊ�����֣���벿�ֺ��Ұ벿��*/
	/*������벿��ȥ��AΪB	BC	BCD	...�Ұ벿��ΪA 	BA	CBA	...*/ 
	/*��ASCII��ȥ��ʾ������ĸ��A��ASCII����65����������65���ַ���ʽ��ʾ��������A*/
	int i,j,n,a,b;
	char letter;
	scanf("%c",&letter);
	n = letter - 64;
	a = 65;//������aȥ��ʾ��ĸA 
	 
	for(i = 1; i <= n; i ++)
	{
		
		
		/*����ÿһ�е�A*/ 
		for(j = 1; j < n - i + 1; j ++)
		{
			printf(" ");
		}
		printf("%c",a);
		
		/*������벿��*/ 
		b = a; 
		for(j = 1; j < i; j ++)
		{
			b ++;//��˼��b = b + 1����bȥ��ʾ�����BCD... 
			printf("%c",b);
		}
		
		/*�����Ұ벿��*/ 
		for(j = i - 1; j >= 1; j --)
		{
			b --;
			printf("%c",b);
		}
		
		/*ÿһ�н���Ҫ����*/ 
		printf("\n");
	}
	return 0;
} 

//��ջ����������ڳ�ջ���� ��I�������ڵ���O�ĸ������ҳ�ջʱһ��Ҫ��Ԫ����ջ�ڣ��Ϸ���Ϊ
//A C D 

#include <stdio.h>
#include <stdlib.h>
#define LEN 100
int main()
{
	char A[LEN] = {'I','O','I','I','I','I','O','O'};				//�Ѿ�ȷ���õ��ַ����� 
	int i = 0, j = 0, k = 0;
	for(; A[k] != '\0'; k ++)				//˳�����������ֵ������Ԫ�� 
	{
		switch(A[k])
		{
			case'I' : i ++; break;				//I��i�ӣ�ͬʱֱ��break���ж���һ������Ԫ�� 
			case'O' : j ++;				//O��j�� 
			if(i < j)				//����������κ�һ��iС��j�����в��Ϸ� 
			{
				printf("���Ϸ�������");
				exit(0); 
			}
		}
	}
	printf("���кϷ�"); 				//�ж��꣬���кϷ� 
	return 0;
} 

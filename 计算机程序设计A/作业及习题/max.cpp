#include<stdio.h>//������ 
int main()//���������� 
{//���������忪ʼ 
	int max(int x,int y);//��max���� 
	int a,b,c;//�������a,b,c 
	scanf("%d,%d",&a,&b);//�������a��b 
	c=max(a,b);//����max���������õ���ֵ����c 
	printf("max=%d\n",c);//���c 
	return 0;//���������� 
}//�����������
//�����������нϴ��max���� 
int max(int x,int y)//����max����������ֵΪ���Σ���ʽ����x��yΪ���� 
{//����max������ʼ 
	int z;//max�����������������õ���zΪ���� 
		if(x>y)z=x;//��x>y��������xֵ��������z 
		else z=y;//���򣬽�y����z 
		return(z);//��z��ֵ��Ϊmax����ֵ�����ص�����max������λ�� 
}

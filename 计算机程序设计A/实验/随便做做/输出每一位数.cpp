#include<stdio.h>
void output(int n)
{
    int a[10];
    int l = 0;
    /*
    ѭ����ȡÿһλ��ֵ�����浽����a�С�
    ����l��ʾ�Ѿ���ȡ����λ����
    ����ÿ�λ�ȡ���Ǹ�λn%10�����Դ�������a�е��Ǹ���λ��������
    */
    while(n)
    {
        a[l++] = n%10;
        n/=10;
    }
    //�������ÿһλֵ��
    while(--l>=0) 
        printf("%d ", a[l]); 
}
int main()
{
    int n;
    scanf("%d",&n);//����nֵ��
    output(n);//�������λ��
    return 0;
}


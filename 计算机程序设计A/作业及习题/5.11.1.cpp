#include<stdio.h>
int main()
{
    double a=100,b=0,n,sum=100;
    printf("��������ش���n��\n");
    scanf("%lf",&n);
  
    for(int i=0;i<n;i++)
    {   
        sum=sum+2*b;
        a=a/2;
        b=a;
    }
    printf("С���100m�ߴ����%.0lf��ʱ��������%lf��\n��%.0lf����غ󷴵��ĸ߶�Ϊ%lf��\n",n,sum,n,a);
    return 0;
}

#include "stdio.h"
int main()
{
    int n,i,j;
    scanf("%d",&n);
    //上三角
    for(i=1;i<=n;i++)
    {
       for(j=1;j<=n-i;j++)//画空格
            printf(" ");
       for(j=1;j<=i;j++)
            printf("%d",j);//输出从1到n
       for(j=i-1;j>=1;j--)
            printf("%d",j);//输出从n-1到1
       printf("\n");   
    }
    //下三角
    for(i=n-1;i>=1;i--)
    {
       for(j=1;j<=n-i;j++)//画空格
            printf(" ");
       for(j=1;j<=i;j++)
            printf("%d",j);//输出从1到n
       for(j=i-1;j>=1;j--)
            printf("%d",j);//输出从n-1到1
       printf("\n"); 
    }
}

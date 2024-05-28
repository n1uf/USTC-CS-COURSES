#include<stdio.h>
void output(int n)
{
    int a[10];
    int l = 0;
    /*
    循环获取每一位的值，并存到数组a中。
    其中l表示已经获取到的位数。
    由于每次获取的是个位n%10，所以存在数组a中的是各个位数的逆序。
    */
    while(n)
    {
        a[l++] = n%10;
        n/=10;
    }
    //反序输出每一位值。
    while(--l>=0) 
        printf("%d ", a[l]); 
}
int main()
{
    int n;
    scanf("%d",&n);//输入n值。
    output(n);//输出各个位。
    return 0;
}


#include<stdio.h>
#include<string.h>
int main(void)
{
    int len_max,i;
    char m[999],n[999],temp[999];
    int a[999]={0},b[999]={0},c[999]={0};
    scanf("%s%s",m,n);
    if(strlen(m)>strlen(n))
        len_max=strlen(m);
    else
        len_max=strlen(n);
    if(strlen(n)>strlen(m)||(strlen(m)==strlen(n)&&strcmp(n,m)>0)){
       //ʹ���������ڼ�����������ͬʱ���ú���strcmp�жϴ�С
        strcpy(temp,m);
        strcpy(m,n);
        strcpy(n,temp);
       //��������
        printf("-");  //���Ϊ��
    }
    for(i=0;i<strlen(m);i++){
        a[i]=m[strlen(m)-1-i]-'0';
    }
    for(i=0;i<strlen(n);i++){
        b[i]=n[strlen(n)-1-i]-'0';
    }
    for(i=0;i<=len_max;i++){
        c[i]=a[i]-b[i];
        if(c[i]<0){
            c[i]+=10;    //���Ͻ�λ
            a[i+1]--;
        }
    }
    int flag=0;
    for(i=len_max;i>=0;i--){  //�����ӡ
        if(c[i])
            flag=1;
        if(flag)
            printf("%d",c[i]);
    }
    if(!flag) printf("0");  //���У�
    return 0;
}

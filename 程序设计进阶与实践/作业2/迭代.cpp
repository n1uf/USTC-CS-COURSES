#include <stdio.h>
#include <math.h>

int sum = 0;
int n;
 
void output(int  x[])
{
    int i;
    for(i=1;i<=n;i++)
	{
      printf("%d", x[i]);                              
    }
    printf("\n");
}
 
 
bool Place(int k,int  x[])
{
    int i;
    for(i=1;i<k;i++)
	{
    	if(abs(i-k)==abs(x[i]-x[k]) || x[i]==x[k])
        return false;                     
    }
    return true;
     
}
     
     
     
void Backtrack(int k,int  x[])
{
    x[k]=0;
    while(k>0)
	{
        x[k] += 1;
        while(x[k]<=n && !Place(k,x)) 
		{
			x[k]++;   //�ҵ���k������Լ����������һ�У��Ա���ӽ������������ 
		}
        if(x[k]<=n)
		{//�ҵ��������������ӽ�� 
             if(k==n)
			 {//��Ҷ��� 
                   output(x);
                   sum++;  
             }
			 else
			 {
                  k++;
                  x[k]=0; 
             }
                    
        }
		else
		{//�Ը��и����Ѿ������ 
             k--; 
        }  
    }
          
}
 
int main()
{
    int *x,i,n;    
    printf("����ʺ����: ");
    scanf("%d", &n);
    printf("\n");
    x=new int[n+1];
    for(i=0;i<=n;i++){
      x[i]=0;                
    }    
    Backtrack(1,x);
    printf("\n");
    printf("��ĸ�����%d", sum);
    return 0;
}

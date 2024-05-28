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
			x[k]++;   //找到第k行满足约束条件的那一列，以便对子结点继续深度搜索 
		}
        if(x[k]<=n)
		{//找到了满足条件的子结点 
             if(k==n)
			 {//是叶结点 
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
		{//对该行各列已经检查完 
             k--; 
        }  
    }
          
}
 
int main()
{
    int *x,i,n;    
    printf("输入皇后个数: ");
    scanf("%d", &n);
    printf("\n");
    x=new int[n+1];
    for(i=0;i<=n;i++){
      x[i]=0;                
    }    
    Backtrack(1,x);
    printf("\n");
    printf("解的个数：%d", sum);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

/*�������Ϸ��ֿ�����һά������
�г�ͻ����ʡ��
�г�ͻ���ѷ��õ��к���Ҫ���õ��������±겻ͬ�Ϳ�
���ڶԽ��߳�ͻ���жϣ��������ڵ����л����ľ���ֵ��ȣ���| ��һ�η��õ��� �C��һ�η��õ��� | = | Ҫ���õ��� �CҪ���õ��� |
*/
 
/*��ȫ�ֱ����Ա���ͳ�����н⣬�Լ���ĸ���*/ 

int chess[10];//�����㹻��
int ans = 0;//ͳ�ƽ�ĸ���
int a[1024];//���ÿһ���� 
int p = 0;

/*���ûʺ�������*/
void place(int k,int n);

/*�����i�е�k�����Ƿ���԰ڷŻʺ�*/
int check(int i,int k);

/*���һ���*/
void print(int n);


int main()
{
	int n;
	scanf("%d",&n);
	place(1,n);
	printf("%d\n",ans);
	int i,j;
	for(i = 0; i < ans * n; )
	{
		for(j = 0; j < n; j ++,i ++)
		{
			printf("%d",a[i]);
		}
		printf("\n");
	}
	return 0;
}

void place(int k,int n) 
{
	int j;
	
	/*����*/ 
	if(k > n)
	{
		print(n);
	}
	
	else
	{
		/*��k�е�ÿһ�ж����м��*/ 
		for(j = 1; j <= n; j ++)
		{
			/*���������¼���ݹ�*/ 
            if(check(k,j))
            {
            	chess[k] = j;
                place(k + 1,n);
            }
        }
	}
}

int check(int i,int k) 
{
	int j = 1;
	while(j < i)//j=1~i-1���Ѿ������˻ʺ����
	{
		/*��j�еĻʺ��Ƿ���k�л�(j,chess[j])��(i,k)�Ƿ���б����*/
		if(chess[j] == k || abs(j - i) == abs(chess[j] - k))
		{
			return 0;
		}
    	j ++;
	}
	return 1;
}

void print(int n)
{
	int i;
	for(i = 1; i <= n; i ++)
	{
		a[p] = chess[i];
		p ++;
	}
	ans ++;
}

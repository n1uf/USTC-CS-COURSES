#include <stdio.h>
 
int get_pos1(int* b, int x, int n)
{
    for(int i = x; i < n; i ++)    
    {
        if(b[i] == x) return i;
    }
    return 0;
}

int get_pos2(int* b, int x, int n)
{
    for(int i = x; i < n; i ++)    
    {
        if(b[i] == n - x) return i;
    }
    return 0;
}

/*升序*/ 
int swap1(int *array, int n)
{
    int b[50000];
    for(int i = 0; i < n; i ++)
        b[i] = array[i];
    int count = 0;
    int pos = 0;
    
    for(int i = 0; i < n; i ++ )
    {
        //数组值与其对应的下标值相等 
        if(i + 1 == b[i])  continue;
        else
        {
            //获得和下标值相等的数组值的索引(位置) 
            pos = get_pos1(b, i + 1, n);
            float v = b[i];
            b[i] = b[pos];
            b[pos] = v;
            count ++;
        }      
    }
    return count;
}

/*降序*/ 
int swap2(int *array, int n)
{
	int b[50000] = {0.0};
    for(int i = 0; i < n; i ++)
        b[i] = array[i];
    int count = 0;
    int pos = 0;
    
    for(int i = 0; i < n; i ++ )
    {
        //数组值与其对应的下标值相等 
        if(i + 1 == b[i])  continue;
        else
        {
            //获得和下标值相等的数组值的索引(位置) 
            pos = get_pos2(b, i + 1, n);
            int v = b[i];
            b[i] = b[pos];
            b[pos] = v;
            count ++;
        }      
    }
    return count;
}
 
int main(void)
{
	int n;
	scanf("%d",&n);
    float a[n], b[n], m;
    int i, j;
    int num[n];
    for(i = 0; i < n; i ++)
    {
    	scanf("%f", &a[i]);
	}
	for(i = 0; i < n; i ++)
	{
		b[i] = a[i];
	}
	for(i = 0; i < n; i ++)
	{
		for(j = 0; j < n; j ++)
		{
			if(a[j] < a[j + 1])
			{
				m = a[j];
				a[j] = a[j + 1];
				a[j + 1] = m;
			}
		}
	}
	/*for(i = 0; i < n; i ++)
	{
		printf("%f ", a[i]);
	}
	putchar(10);*/
	for(i = 0; i < n; i ++)
	{
		for(j = 0; j < n; j ++)
		{
			if(b[i] == a[j])
			{
				num[i] = n - j;
				//printf("%d ",num[i]);
			}
		}
	}
	//putchar(10);
	int k1 = swap1(num, n);
	int k2 = swap2(num, n);
	//printf("%d %d\n", k1, k2);
	if(k1 > k2)
	{
		printf("%d",k2);
	}
	else
	{
		printf("%d",k1);
	}
}

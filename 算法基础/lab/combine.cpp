#include <stdio.h>
int main()
{
    int N = 0, M = 0;
    scanf("%d %d", &N, &M);
    int A[N], B[M];
    int i = 0;
    for(i = 0; i < N; i ++)
    {
    	A[i] = 0;
        scanf("%d", &A[i]);
    }

    for(i = 0; i < M; i ++)
    {
    	B[i] = 0;
        scanf("%d", &B[i]);
    }
    
    int output[N + M];
    
    int j = 0, k = 0;
    i = 0;
    for(k = 0; k < N + M; k ++)
    {
    	output[k] = 0;
    	if(i < N && j < M)
    	{
    		if(A[i] < B[j])
    		{
    			output[k] = A[i];
    			i ++;
			}
			else
			{
				output[k] = B[j];
				j ++;
			}
		}
		else if(i >= N && j < M)
		{
			output[k] = B[j];
			j ++;
		}
		else if(i < N && j >= M)
		{
			output[k] = A[i];
			i ++;
		}
    	
		if(k < N + M - 1)
			printf("%d ", output[k]);
		else
			printf("%d", output[k]);
		
	}
    
    return 0;
}

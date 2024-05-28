#include <stdio.h>
#include <time.h>
#include "Strassenc.h"

int main(void)
{
	FILE *A, *B;
	FILE *norm_ans, *stra_ans;
    int MatrixSize = 0;
	printf("请输入矩阵大小(必须是2的幂指数值(2^n): ");
    scanf("%d", &MatrixSize);
    
    int ** MatrixA = (int **)malloc(sizeof(int*) * MatrixSize);  //存放矩阵A
    int ** MatrixB = (int **)malloc(sizeof(int*) * MatrixSize);  //存放矩阵B
    int ** MatrixC = (int **)malloc(sizeof(int*) * MatrixSize);  //存放朴素算法结果
    int ** MatrixD = (int **)malloc(sizeof(int*) * MatrixSize);  //存放Strassen算法结果 
    
     for (int i = 0; i < MatrixSize; i ++)
    {
        MatrixA[i] = (int *)malloc(sizeof(int) * MatrixSize);
        MatrixB[i] = (int *)malloc(sizeof(int) * MatrixSize);
        MatrixC[i] = (int *)malloc(sizeof(int) * MatrixSize);
        MatrixD[i] = (int *)malloc(sizeof(int) * MatrixSize);
    }
    
	//设置时钟 
	clock_t start_normal, end_normal;
    clock_t start_strassen, end_strassen;
    
    srand(time(0));
    int N = MatrixSize;
    FillMatrix(MatrixA, MatrixB, N);
    
	A = fopen("矩阵A,B及运算结果\\矩阵A.txt","w");
	for(int r = 0; r < N; r ++)
	{
    	for(int c = 0; c < N; c ++)
    	{
			fprintf(A, "%d ", MatrixA[r][c]);
    	}
    	fprintf(A, "\n");
	}
    
    B = fopen("矩阵A,B及运算结果\\矩阵B.txt","w");
	for(int r = 0; r < N; r ++)
	{
    	for(int c = 0; c < N; c ++)
    	{
			fprintf(B, "%d ", MatrixB[r][c]);
    	}
    	fprintf(B, "\n");
	}
    
	start_normal = clock();
    NOR(MatrixA,MatrixB,MatrixC,N);//朴素算法 
	end_normal = clock();
    
    norm_ans = fopen("矩阵A,B及运算结果\\朴素算法运算结果.txt","w");
    for(int r = 0; r < N; r ++)
	{
    	for(int c = 0; c < N; c ++)
    	{
			fprintf(norm_ans, "%d ", MatrixC[r][c]);
    	}
    	fprintf(norm_ans, "\n");
	}
	
    printf("朴素矩阵算法开始时钟:%d\n",start_normal);
    printf("朴素矩阵算法结束时钟:%d\n",end_normal);
    printf("运行时长:%.3lfs\n", (double)(end_normal - start_normal)/CLK_TCK);
    
	
	start_strassen = clock();
    Strassen(MatrixA, MatrixB, MatrixD, N); //strassen算法
	end_strassen = clock();
    
    stra_ans = fopen("矩阵A,B及运算结果\\Strassen算法运算结果.txt","w");
    for(int r = 0; r < N; r ++)
	{
    	for(int c = 0; c < N; c ++)
    	{
			fprintf(stra_ans, "%d ", MatrixD[r][c]);
    	}
    	fprintf(stra_ans, "\n");
	}
	
    printf("Strassen算法开始时钟:%d\n", start_strassen);
    printf("Strassen算法结束时钟:%d\n", end_strassen);
    printf("运行时长:%.3lfs\n", (double)(end_strassen - start_strassen)/CLK_TCK);
}

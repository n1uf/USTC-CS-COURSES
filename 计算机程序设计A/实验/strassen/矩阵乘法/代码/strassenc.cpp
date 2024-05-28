#include <stdio.h>
#include <time.h>
#include "Strassenc.h"

int main(void)
{
	FILE *A, *B;
	FILE *norm_ans, *stra_ans;
    int MatrixSize = 0;
	printf("����������С(������2����ָ��ֵ(2^n): ");
    scanf("%d", &MatrixSize);
    
    int ** MatrixA = (int **)malloc(sizeof(int*) * MatrixSize);  //��ž���A
    int ** MatrixB = (int **)malloc(sizeof(int*) * MatrixSize);  //��ž���B
    int ** MatrixC = (int **)malloc(sizeof(int*) * MatrixSize);  //��������㷨���
    int ** MatrixD = (int **)malloc(sizeof(int*) * MatrixSize);  //���Strassen�㷨��� 
    
     for (int i = 0; i < MatrixSize; i ++)
    {
        MatrixA[i] = (int *)malloc(sizeof(int) * MatrixSize);
        MatrixB[i] = (int *)malloc(sizeof(int) * MatrixSize);
        MatrixC[i] = (int *)malloc(sizeof(int) * MatrixSize);
        MatrixD[i] = (int *)malloc(sizeof(int) * MatrixSize);
    }
    
	//����ʱ�� 
	clock_t start_normal, end_normal;
    clock_t start_strassen, end_strassen;
    
    srand(time(0));
    int N = MatrixSize;
    FillMatrix(MatrixA, MatrixB, N);
    
	A = fopen("����A,B��������\\����A.txt","w");
	for(int r = 0; r < N; r ++)
	{
    	for(int c = 0; c < N; c ++)
    	{
			fprintf(A, "%d ", MatrixA[r][c]);
    	}
    	fprintf(A, "\n");
	}
    
    B = fopen("����A,B��������\\����B.txt","w");
	for(int r = 0; r < N; r ++)
	{
    	for(int c = 0; c < N; c ++)
    	{
			fprintf(B, "%d ", MatrixB[r][c]);
    	}
    	fprintf(B, "\n");
	}
    
	start_normal = clock();
    NOR(MatrixA,MatrixB,MatrixC,N);//�����㷨 
	end_normal = clock();
    
    norm_ans = fopen("����A,B��������\\�����㷨������.txt","w");
    for(int r = 0; r < N; r ++)
	{
    	for(int c = 0; c < N; c ++)
    	{
			fprintf(norm_ans, "%d ", MatrixC[r][c]);
    	}
    	fprintf(norm_ans, "\n");
	}
	
    printf("���ؾ����㷨��ʼʱ��:%d\n",start_normal);
    printf("���ؾ����㷨����ʱ��:%d\n",end_normal);
    printf("����ʱ��:%.3lfs\n", (double)(end_normal - start_normal)/CLK_TCK);
    
	
	start_strassen = clock();
    Strassen(MatrixA, MatrixB, MatrixD, N); //strassen�㷨
	end_strassen = clock();
    
    stra_ans = fopen("����A,B��������\\Strassen�㷨������.txt","w");
    for(int r = 0; r < N; r ++)
	{
    	for(int c = 0; c < N; c ++)
    	{
			fprintf(stra_ans, "%d ", MatrixD[r][c]);
    	}
    	fprintf(stra_ans, "\n");
	}
	
    printf("Strassen�㷨��ʼʱ��:%d\n", start_strassen);
    printf("Strassen�㷨����ʱ��:%d\n", end_strassen);
    printf("����ʱ��:%.3lfs\n", (double)(end_strassen - start_strassen)/CLK_TCK);
}

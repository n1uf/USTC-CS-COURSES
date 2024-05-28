#ifndef STRASSEN_HH
#define STRASSEN_HH
#include<stdio.h>
#include<stdlib.h> 

void FillMatrix( int ** MatrixA, int ** MatrixB, int length);//随机输入矩阵 
void ADD(int ** MatrixA, int ** MatrixB, int ** MatrixResult, int MatrixSize);//加法 
void SUB(int ** MatrixA, int ** MatrixB, int ** MatrixResult, int MatrixSize);//减法 
void NOR( int ** MatrixA, int ** MatrixB, int ** MatrixResult, int MatrixSize);//朴素算法 
void Strassen(int **MatrixA, int **MatrixB, int **MatrixC, int N);//strassen算法


//输入 
void FillMatrix(int **MatrixA, int **MatrixB, int length)
{
    for(int row = 0; row < length; row ++)
    {
        for(int column = 0; column < length; column ++)
        { 
            MatrixA[row][column] = rand() % 10;
            MatrixB[row][column] = rand() % 10;
        } 
    }
}

//加法 
void ADD(int **MatrixA, int **MatrixB, int **MatrixResult, int MatrixSize)
{
    for ( int i = 0; i < MatrixSize; i ++)
    {
        for ( int j = 0; j < MatrixSize; j ++)
        {
            MatrixResult[i][j] =  MatrixA[i][j] + MatrixB[i][j];
        }
    }
}

//减法 
void SUB(int **MatrixA, int **MatrixB, int **MatrixResult, int MatrixSize)
{
    for ( int i = 0; i < MatrixSize; i++)
    {
        for ( int j = 0; j < MatrixSize; j++)
        {
            MatrixResult[i][j] =  MatrixA[i][j] - MatrixB[i][j];
        }
    }
}

//朴素 
void NOR(int **MatrixA, int **MatrixB, int **MatrixResult, int MatrixSize)
{
    for (int i = 0;i < MatrixSize ; i ++)
    {
        for (int j = 0;j < MatrixSize ; j ++)
        {
            MatrixResult[i][j] = 0;
            for (int k = 0; k < MatrixSize; k ++)
            {
                MatrixResult[i][j] += MatrixA[i][k] * MatrixB[k][j];
            }
        }
    }
}

//strassen算法递归 
void Strassen(int **MatrixA, int **MatrixB, int **MatrixC, int N)
{
	int HalfSize = N/2;
    int newSize = N/2;
    /*出口*/ 
    if ( N <= 64 ) 
    {
        NOR(MatrixA, MatrixB, MatrixC, N);
    }
    else
    {
        int ** A11;
        int ** A12;
        int ** A21;
        int ** A22;
		    
        int ** B11;
        int ** B12;
        int ** B21;
        int ** B22;
          
        int ** C11;
        int ** C12;
        int ** C21;
        int ** C22;
          
        int ** M1;
        int ** M2;
        int ** M3;
        int ** M4;
        int ** M5;
        int ** M6;
        int ** M7;
        int ** AResult;
        int ** BResult;
 
        //开辟地址 
        A11 = (int **)malloc(sizeof(int*) * newSize);
        A12 = (int **)malloc(sizeof(int*) * newSize);
        A21 = (int **)malloc(sizeof(int*) * newSize);
        A22 = (int **)malloc(sizeof(int*) * newSize);
         
        B11 = (int **)malloc(sizeof(int*) * newSize);
        B12 = (int **)malloc(sizeof(int*) * newSize);
        B21 = (int **)malloc(sizeof(int*) * newSize);
        B22 = (int **)malloc(sizeof(int*) * newSize);
         
        C11 = (int **)malloc(sizeof(int*) * newSize);
        C12 = (int **)malloc(sizeof(int*) * newSize);
        C21 = (int **)malloc(sizeof(int*) * newSize);
        C22 = (int **)malloc(sizeof(int*) * newSize);
         
        M1 = (int **)malloc(sizeof(int*) * newSize);
        M2 = (int **)malloc(sizeof(int*) * newSize);
        M3 = (int **)malloc(sizeof(int*) * newSize);
        M4 = (int **)malloc(sizeof(int*) * newSize);
        M5 = (int **)malloc(sizeof(int*) * newSize);
        M6 = (int **)malloc(sizeof(int*) * newSize);
        M7 = (int **)malloc(sizeof(int*) * newSize);
 
        AResult = (int **)malloc(sizeof(int*) * newSize);
        BResult = (int **)malloc(sizeof(int*) * newSize);
 
        int newLength = newSize;
 
        //开辟地址 
        for ( int i = 0; i < newLength; i ++)
        {
            A11[i] = (int *)malloc(sizeof(int) * newLength);
            A12[i] = (int *)malloc(sizeof(int) * newLength);
            A21[i] = (int *)malloc(sizeof(int) * newLength);
            A22[i] = (int *)malloc(sizeof(int) * newLength);
             
            B11[i] = (int *)malloc(sizeof(int) * newLength);
            B12[i] = (int *)malloc(sizeof(int) * newLength);
            B21[i] = (int *)malloc(sizeof(int) * newLength);
            B22[i] = (int *)malloc(sizeof(int) * newLength);
             
            C11[i] = (int *)malloc(sizeof(int) * newLength);
            C12[i] = (int *)malloc(sizeof(int) * newLength);
            C21[i] = (int *)malloc(sizeof(int) * newLength);
            C22[i] = (int *)malloc(sizeof(int) * newLength);
 
            M1[i] = (int *)malloc(sizeof(int) * newLength);
            M2[i] = (int *)malloc(sizeof(int) * newLength);
            M3[i] = (int *)malloc(sizeof(int) * newLength);
            M4[i] = (int *)malloc(sizeof(int) * newLength);
            M5[i] = (int *)malloc(sizeof(int) * newLength);
            M6[i] = (int *)malloc(sizeof(int) * newLength);
            M7[i] = (int *)malloc(sizeof(int) * newLength);
 
            AResult[i] = (int *)malloc(sizeof(int) * newLength);
            BResult[i] = (int *)malloc(sizeof(int) * newLength);
        }
        
        /*拆分成小矩阵*/ 
        for (int i = 0; i < N / 2; i ++)
        {
            for (int j = 0; j < N / 2; j ++)
            {
                A11[i][j] = MatrixA[i][j];
                A12[i][j] = MatrixA[i][j + N / 2];
                A21[i][j] = MatrixA[i + N / 2][j];
                A22[i][j] = MatrixA[i + N / 2][j + N / 2];
 
                B11[i][j] = MatrixB[i][j];
                B12[i][j] = MatrixB[i][j + N / 2];
                B21[i][j] = MatrixB[i + N / 2][j];
                B22[i][j] = MatrixB[i + N / 2][j + N / 2];
 
             }
        }
 
        //计算M1-M7 
        //M1[][]
        ADD(A11, A22, AResult, HalfSize);
        ADD(B11, B22, BResult, HalfSize);
        Strassen(AResult, BResult, M1, HalfSize);
 
 
        //M2[][]
        ADD(A21, A22, AResult, HalfSize);
        Strassen(AResult, B11, M2, HalfSize);
 
        //M3[][]
        SUB(B12, B22, BResult, HalfSize);
        Strassen(A11, BResult, M3, HalfSize);
 
        //M4[][]
        SUB(B21, B11, BResult, HalfSize);
        Strassen(A22, BResult, M4, HalfSize);
 
        //M5[][]
        ADD(A11, A12, AResult, HalfSize);
        Strassen(AResult, B22, M5, HalfSize);
 

        //M6[][]
        SUB(A21, A11, AResult, HalfSize);
        ADD(B11, B12, BResult, HalfSize);
        Strassen(AResult, BResult, M6, HalfSize);
 
        //M7[][]
        SUB(A12, A22, AResult, HalfSize);
        ADD(B21, B22, BResult, HalfSize);
        Strassen(AResult, BResult, M7, HalfSize);
 
        //C11 = M1 + M4 - M5 + M7;
        ADD(M1, M4, AResult, HalfSize);
        SUB(M7, M5, BResult, HalfSize);
        ADD(AResult, BResult, C11, HalfSize);
 
        //C12 = M3 + M5;
        ADD(M3, M5, C12, HalfSize);
 
        //C21 = M2 + M4;
        ADD(M2, M4, C21, HalfSize);
 
        //C22 = M1 + M3 - M2 + M6;
        ADD(M1, M3, AResult, HalfSize);
        SUB(M6, M2, BResult, HalfSize);
        ADD(AResult, BResult, C22, HalfSize);
 
        //小矩阵组合成大矩阵 
        for (int i = 0; i < N / 2 ; i ++)
        {
            for (int j = 0 ; j < N / 2 ; j ++)
            {
                MatrixC[i][j] = C11[i][j];
                MatrixC[i][j + N / 2] = C12[i][j];
                MatrixC[i + N / 2][j] = C21[i][j];
                MatrixC[i + N / 2][j + N / 2] = C22[i][j];
            }
        }
        
        //释放内存 
        for (int i = 0; i < newLength; i ++)
        {
            free(A11[i]); free(A12[i]);
			free(A21[i]); free(A22[i]);
 
            free(B11[i]); free(B12[i]);
			free(B21[i]); free(B22[i]);
            
			free(C11[i]); free(C12[i]);
			free(C21[i]); free(C22[i]);
			
            free(M1[i]); free(M2[i]); free(M3[i]); free(M4[i]);
            free(M5[i]); free(M6[i]); free(M7[i]);
            
            free(AResult[i]); free(BResult[i]);
        }
        free(A11); free(A12); free(A21); free(A22);
        
        free(B11); free(B12); free(B21); free(B22);
        
        free(C11); free(C12); free(C21); free(C22);
        
        free(M1); free(M2); free(M3); free(M4);
		free(M5); free(M6); free(M7);
		
        free(AResult); free(BResult);
    }
}

#endif

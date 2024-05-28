#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 10
#define TRUE 1
#define FALSE 0

typedef struct num
{
    int negative;
    int inte[N];
    int deci[N];
    int base;
    int length1; //��������
    int length2; //С������
} num;

num* initNUM()
{	// ��ʼ���ṹ�� 
	num* tmp = (num*)malloc(sizeof(num));
	tmp->base = 0;
	tmp->negative = 0;
	for(int i = 0; i < MAX; i ++)
	{
		tmp->inte[i] = 0;
		tmp->deci[i] = 0;
	}
	return tmp;
}

int max(int a, int b)
{
    return (a > b ? a : b);
}

int CompareAbs(num *A, num *B) //�ȽϾ���ֵ��С
{
    if (A->length1 > B->length1)
        return TRUE;
    if (A->length1 == B->length1)
    {
        for (int i = A->length1 - 1; i >= 0; i--)
        {
            if (A->inte[i] > B->inte[i])
                return TRUE;
            if (A->inte[i] < B->inte[i])
                return FALSE;
        }
        for (int i = 0; i < max(A->length2, B->length2) - 1; i++)
        {
            if (A->deci[i] > B->deci[i])
                return TRUE;
            if (A->deci[i] < B->deci[i])
                return FALSE;
        }
    }
    return FALSE;
}

num *AddAbs(num *A, num *B) //���о���ֵA+B
{
    num *C = InitNum();
    int k = 0;
    for (int i = max(A->length2, B->length2) - 1; i >= 0; i--) //С����
    {
        C->deci[i] = (A->deci[i] + B->deci[i] + k) % A->base;
        k = (A->deci[i] + B->deci[i] + k) / A->base;
    }
    for (int i = 0; i <= max(A->length1, B->length2); i++) //������
    {
        C->inte[i] = (A->inte[i] + B->inte[i] + k) % A->base;
        k = (A->inte[i] + B->inte[i] + k) / A->base;
    }
    C->negative = A->negative;
    k = N - 1;
    for (; C->inte[k] == 0 && k > 0;)
        k--;
    C->length1 = k + 1; //�ж���������
    k = N - 1;
    for (; C->deci[k] == 0 && k > 0;)
        k--;
    C->length2 = k + 1; //�ж�С������
    return C;
}
num *SubtractAbs(num *A, num *B) //���о���ֵA-B
{
    num *C = InitNum();
    int k = 0;
    for (int i = max(A->length2, B->length2) - 1; i >= 0; i--) //С����
    {
        if (A->deci[i] + k >= B->deci[i])
        {
            C->deci[i] = A->deci[i] + k - B->deci[i];
            k = 0;
        }
        else
        {
            C->deci[i] = A->deci[i] + k + A->base - B->deci[i];
            k = -1;
        }
    }

    for (int i = 0; i <= max(A->length1, B->length1) - 1; i++) //������
    {
        if (A->inte[i] + k >= B->inte[i])
        {
            C->inte[i] = A->inte[i] + k - B->inte[i];
            k = 0;
        }
        else
        {
            C->inte[i] = A->inte[i] + k + A->base - B->inte[i];
            k = -1;
        }
    }

    k = N - 1;
    for (; C->inte[k] == 0 && k > 0;)
        k--;
    C->length1 = k + 1;
    k = N - 1;
    for (; C->deci[k] == 0 && k > 0;)
        k--;
    C->length2 = k + 1;
    C->negative = A->negative;
    return C;
}

num *SubtractRight(num *A, num *B) //��������������ֵ��С�жϼӼ�˳��
{
    if (CompareAbs(A, B)) //��A����ֵ����B ��A-B
        return SubtractAbs(A, B);
    else
        return SubtractAbs(B, A); //����B-A
}

num *Add(num *A, num *B) //��
{
    if (A->negative == B->negative)
        return AddAbs(A, B);
    else
        return SubtractRight(A, B);
}
num *Subtract(num *A, num *B) //��
{
    if (A->negative != B->negative)
        return AddAbs(A, B);
    else
        return SubtractRight(A, B);
}


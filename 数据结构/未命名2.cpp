#include <stdio.h>
#define MAX 100
int main()
{
	int a[MAX * 2];
	int point1 = 1, point2 = 1;
	int i, j;
	for(i = 0; i < MAX * 2; i ++)
		a[i] = 0;
	a[0] = 5;
	a[4] = 2;
	for(i = MAX * 2; a[i] == 0; i --);		//i是高精度数最高位，0是最低位 
	j = i - (point1 + point2) + 1;					//点的位置 
	char res[MAX * 2];
	for(int k = 0; k <= MAX * 2; k ++)
		res[k] = '0';						//初始化字符串 
	res[j] = '.';
	for(int k = j + 1; k <= i + 1; k ++)				//低位往高位赋值为小数部分 
		res[k] = a[i + 1 - k] + 48;
	for(int k = 0; k < j; k ++)
		res[k] = a[i - k] + 48;
	int k;
	for(k = MAX * 2 - 1; res[k] == '0'; k --);
	printf("%s", res);
	printf("%c", res[200]);
}

/*
void mul_num(int a, int n[])
{	// 10进制下数字乘高精度数 
	int i;
	for(i = 0; i < MAX; i ++)
	{
		n[i] *= a;
	}
	for(i = MAX - 1; i >= 1; i --)
	{
		if(n[i] >= 10)
		{
			n[i - 1] += n[i] / 10;
			n[i] %= 10;
		}
	}
}

void mul_arr(int a[], int b[])
{	// 10进制下高精度数乘高精度数 
	int c[MAX];
	for (int i = 0; i < MAX; i ++)
    {
        c[i] = 0;
    }
    int n, m;
    for(n = 0; a[n] == 0; n ++);
    for(m = 0; b[m] == 0; m ++);
    
    for(int i = MAX - 1; i >= n; i --)
    {
        for(int j = MAX - 1; j >= m; j --)
        {
			c[i + j + 1 - MAX] += a[i] * b[j];
		}
    }
    for(int i = MAX - 1; i > 0; i--)
    {
        if(c[i] >= 10)
        {
            c[i - 1] = c[i - 1] + c[i] / 10;
            c[i] = c[i] % 10;
        }
    }
    
    for (int i = 0; i < MAX; i++)
    {
        a[i] = c[i];
    }
}

void sub(int a[], int b[], int base)
{	// base进制下高精度数减法 
	int i;
	for(i = 0; i < MAX; i ++)
	{
		a[i] -= b[i];
	}
	for(i = MAX - 1; i >= 0; i --)
	{
		if(a[i] < 0)
		{
			a[i] += base;
			a[i - 1] --;
		}
	}
}

void add(int a[], int b[], int base)
{	// base进制下高精度数加法 
	int i;
	for(i = 0; i < MAX; i ++)
	{
		a[i] += b[i];
	}
	for(i = MAX - 1; i >= 0; i --)
	{
		if(a[i] >= base)
		{
			a[i] -= base;
			a[i - 1] ++;
		}
	}
}

void loadin(float coe[], int ind[], int ite) 
{	// 录入多项式 
	for(int i = 0; i < ite; i ++)
	{
		scanf("%f", &coe[i]);
		scanf("%d", &ind[i]);
	}
}
*/

/*int ite;
	printf("输入多项式项数：");
	scanf("%d", &ite);
	float coe[ite];
	int ind[ite];
	loadin(coe, ind, ite);
	printf("输入高精度数x：");
	*/
	
num *move_point(int a[], int point1, int point2)
{	// point记录的是字符串中点的逆序位置，同时代表着小数的位数 
	int i, j;
	for(i = MAX * 2; a[i] == 0; i --);		//i是高精度数最高位，0是最低位 
	j = point1 + point2;					//点的位置 
	char res[MAX * 2];
	for(int k = 0; k < MAX * 2; k ++)
		res[k] = '0';						//初始化字符串 
	res[j] = '.';
	for(int k = 0; k < j; k ++)				//低位往高位赋值为小数部分 
		res[k] = a[k] + 48;
	for(int k = i; k > j; k ++)				//高位往低位赋值为整数部分 
		res[k] = a[k] + 48;
	num *A = initNUM();
	A = ReadFromString(res, 10);
	return A;
}

int *tran(num *A, int res[])
{
	int i, j;
	for(i = MAX; A->inte[i] == 0; i --);
	for(j = MAX; A->deci[j] == 0; j --);
	int inteh = i, decih = j;
	int len = i + j + 2;
	int k;
	for(k = 0; k < MAX * 2; k ++)
		res[k] = 0;
	for(k = 0; k < len; k ++)
	{
		if(k <= decih)
		{
			res[k] = A->deci[j];
			j --;
		}
		else if(k > decih)
		{
			res[k] = A->inte[k - decih - 1];
		}
	}
	
	return res;
}

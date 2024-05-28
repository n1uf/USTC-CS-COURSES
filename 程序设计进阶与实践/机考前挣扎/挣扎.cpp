#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//高精度数的运算
int Add(int a[], int b[], int ans[], int len)
{
	int i = 0;
	for(i = 0; i < len; i ++)
	{
		ans[i] = a[i] + b[i];
	}
	for(i = len - 1; i > 0; i --)
	{
		if(ans[i] >= 10)
		{
			ans[i - 1] ++;
			ans[i] -= 10;
		}
	}
}

int Sub(int a[], int b[], int ans[], int len)
{
	int i = 0;
	for(i = 0; i < len; i ++)
	{
		ans[i] = a[i] - b[i];
	}
	for(i = len - 1; i > 0; i --)
	{
		if(ans[i] < 0)
		{
			ans[i - 1] --;
			ans[i] += 10;
		}
	}
}

int Mul(int a[], int b[], int ans[], int len)
{
	int i, j;
	for(i = 0; a[i] == 0; i ++);
	for(j = 0; b[j] == 0; j ++);
	int m, n;
	for(m = len - 1; m > i; m --)
	{
		for(n = len - 1; n > j; n --)
		{
			ans[m + n + 1 - len] += a[n] * b[m];
		}
	}
	for(i = len - 1; i > 0; i --)
	{
		if(ans[i] > 10)
		{
			ans[i - 1] += ans[i] / 10;
			ans[i] %= 10;
		}
	}
}


//八皇后 
#define Queen 8
#define Max 1000
int result[Max][Queen];
int nowtry[Queen];
int cnt = 0;

void nqueen(int n)
{
	if(n == Queen)
	{
		memcpy(result[cnt], nowtry, sizeof(nowtry));
		cnt ++;
		return ;
	}
	int i;
	for(i = 0; i < Queen; i ++)
	{
		int j;
		for(j = 0; j < n; j ++)
		{
			if(i == nowtry[j] || abs(i - nowtry[j]) == abs(n - j))
			{
				break;
			}
		}
		if(j == n)
		{
			nowtry[n] = i;
			nqueen(n + 1);
		}
	}
}

//不考虑运算优先级的24点
int flag = 0;
char op[5] = {' ', '+', '-', '*', '/'};
float cal(float x, float y, int op)
{
	switch(op)
	{
		case 1: return x + y;
		case 2: return x - y;
		case 3: return x * y;
		case 4: return x / y;
	}
}

float _do(float a, float b, float c, float d, int op1, int op2, int op3)
{
	float result;
	result = cal(a, b, op1);
	result = cal(result, c, op2);
	result = cal(result, d, op3);
	return result;
}

int get(float a, float b, float c, float d)
{
	flag = 0;
	int op1, op2, op3;
	for(op1 = 1; op1 < 5; op1 ++)
	{
		for(op2 = 1; op2 < 5; op3 ++)
		{
			for(op3 = 1; op3 < 5; op3 ++)
			{
				int result;
				result = _do(a, b, c, d, op1, op2, op3);
				if(fabs(result - 24.0) < 1e-5)
				{
					printf("%.0f %c %.0f %c %.0f %c %.0f", a, op[op1], b, op[op2], c, op[op3], d);
					flag = 1;
					return flag;
				}
			}
		}
	}
}
int main(void)
{
	
	//高精度数加法减法 
	int a[20], b[20], ans[20];
	int len = 20, i;
	for(i = 0; i < len; i ++)
	{
		a[i] = i % 10;
		b[i] = i % 10;
	}
	Add(a, b, ans, len);
	for(i = 0; i < len; i ++)
	{
		printf("%d", ans[i]);
	}
	printf("\n");
	for(i = 0; i < len; i ++)
	{
		ans[i] = 0;
	}
	Sub(a, b, ans, len);
	for(i = 0; i < len; i ++)
	{
		printf("%d", ans[i]);
	}
	
	printf("\n\n");
	s
	
	//n皇后
	int n;
	nqueen(0);
	scanf("%d", &n);//第n个解 
	for(int i = 0; i < Queen; i ++)
	{
		printf("%d ", result[n - 1][i] + 1);
	}
	printf("\n");
	
	//24
	float num[4];
	for(i = 0; i < 4; i ++)
	{
		scanf("%f", &num[i]);
	}
	get(num[0], num[1], num[2], num[3]);
}

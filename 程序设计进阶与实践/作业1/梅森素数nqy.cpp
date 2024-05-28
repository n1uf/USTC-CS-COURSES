#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXNUM 1000
void mul_num(int a, int n[], int len);//a * n[]
void mul_arr(int a[], int b[], int len);//a[] * b[]
void sub(int a[], int b[], int len);//a[] - b[] for a > b
void copy(int a[], int b[], int len);//copy b to a
void mod_sub(int o[], int m[], int len);//use substract to calculate a[] % b []
int whether_0(int a[], int len);//if a[] = 0?
void half_arr(int a[], int len);//half the number when it's even
void quick_mod(int a[], int b[], int c[], int len);//a quick way to calculate (a ^ b) % c
void arr_sub1(int a[], int len);//a[] - 1
int compare(int a[], int b[], int len);//a[] == b[]?
int meisen(int po, int max);//whether 2 ^ p - 1 is a prime number
void print(int a[], int len);//print the answer
void judge_p(int p[]);//choose prime numbers in an array whose contents are numbers range from 2 to 1000

/*test*/
void test_mul_num(int a, int n[], int len)
{
	int A = a, B = 0;
	mul_num(a, n, len);
	int i;
	for(i = 0; n[i] == 0; i ++);
	for(; i < len; i ++)
	{
		B += pow(10, len - i - 1) * n[i];
	}
	if(A == B)
	{
		printf("mul_num is a correct calculation\n");
	}
}
void test_mul_arr(int a[], int b[], int len)
{
	int A = 0, B = 0, C = 0, D = 0;
	int i, j;
	for(i = 0; a[i] == 0; i ++);
	for(; i < len; i ++)
	{
		A += pow(10, len - i - 1) * a[i];
	}
	for(j = 0; b[j] == 0; j ++);
	for(; j < len; j ++)
	{
		B += pow(10, len - j - 1) * b[j];
	}
	C = A * B;
	mul_arr(a, b, len);
	for(i = 0; a[i] == 0; i ++);
	for(; i < len; i ++)
	{
		D += pow(10, len - i - 1) * a[i];
	}
	if(C == D)
	{
		printf("mul_arr is a correct calculation\n");
	}
}

int main()
{
	/*test part*/
	int test1[MAXNUM];
	memset(test1, 0, MAXNUM * sizeof(int));
	test1[MAXNUM - 1] = 1;
	test_mul_num(rand(), test1, MAXNUM);
	
	int test2[MAXNUM], test3[MAXNUM];
	memset(test2, 0, MAXNUM * sizeof(int));
	memset(test3, 0, MAXNUM * sizeof(int));
	test2[MAXNUM - 1] = rand() % 10;
	test3[MAXNUM - 1] = rand() % 10;
	test_mul_arr(test2, test3, MAXNUM);
	
	clock_t start,end;
	start = clock();
	
	int i;
	int p[999];
	for(i = 0; i <= 998; i ++)
	{
		p[i] = i + 2;
	}
    for (i = 0; p[i] != NULL; i++)
    {
        if (meisen(p[i], MAXNUM))
        {
            printf("%d\n\n", p[i]);
        }
    }
    
    end = clock();
    
	printf("time = %f\n", (double)(end-start)/CLK_TCK);
}

void mul_num(int a, int n[], int len)
{
	int i;
	for(i = 0; i < len; i ++)
	{
		n[i] *= a;
	}
	for(i = len - 1; i >= 1; i --)
	{
		if(n[i] >= 10)
		{
			n[i - 1] += n[i] / 10;
			n[i] %= 10;
		}
	}
}

void mul_arr(int a[], int b[], int len)
{
	int c[len];
	for (int i = 0; i < len; i ++)
    {
        c[i] = 0;
    }
    int n, m;
    for(n = 0; a[n] == 0; n ++);//avoid invalid figure
    for(m = 0; b[m] == 0; m ++);
    
    for(int i = len - 1; i >= n; i --)
    {
        for(int j = len - 1; j >= m; j --)
        {
			c[i + j + 1 - len] += a[i] * b[j];
		}
    }
    for(int i = len - 1; i > 0; i--)
    {
        if(c[i] >= 10)
        {
            c[i - 1] = c[i - 1] + c[i] / 10;
            c[i] = c[i] % 10;
        }
    }
    
    for (int i = 0; i < len; i++)
    {
        a[i] = c[i];
    }
}

void sub(int a[], int b[], int len)
{
	int i;
	for(i = 0; i < len; i ++)
	{
		a[i] -= b[i];
	}
	for(i = len - 1; i >= 0; i --)
	{
		if(a[i] < 0)
		{
			a[i] += 10;
			a[i - 1] --;
		}
	}
}

void copy(int a[], int b[], int len)//equal to memcpy but quicker
{
    for (int i = 0; i < len; i++)
    {
        a[i] = b[i];
    }
}

void mod_sub(int a[], int b[], int len)
{
    int c[len];
    copy(c, b, len);
    int i, j;
    for(i = 0; a[i] == 0; i ++);
	for(j = 0; b[j] == 0; j ++);
    int k = j - i;
    for (; k > 0; k --)
    {
        for (int m = 0; m < k - 1; m ++)//equal to "mul_num(pow(10, k - 1), b, len);"(it's slower) to lessen the complexity
        {
            mul_num(10, b, len);
        }
        int l = 0;
        for(l = 0; a[l] == b[l] && l < len; l ++);
        for(; a[l] - b[l] > 0 && l < len; )
		{
			sub(a, b, len);
			for(l = 0; a[l] == b[l] && l < len; l ++);
		}
        copy(b, c, len);
    }
}

int whether_0(int a[], int len)
{
	int i;
	for(i = 0; i < len; i ++)
	{
		if(a[i] != 0)
		{
			return 1;
		}
	}
	return 0;
}

void half_arr(int a[], int len)
{
	int i;
	for(i = 0; i < len; i ++)
	{
		if(a[i] % 2 != 0)
		{
			a[i + 1] += 10;
		}
		a[i] /= 2;
	}
}

void quick_mod(int a[], int b[], int c[], int len)
{
	int d[len];//result of mod
	memset(d, 0, len * sizeof(int));
	d[len - 1]++;//d = {0,0,...,1} initialize the result of the mod calculation
    
	mod_sub(a, c, len);
    while(whether_0(b, len))
    {
        if(b[len - 1] % 2 == 1)//if b is a single number
        {
            mul_arr(d, a, len);
            mod_sub(d, c, len);
            b[len - 1]--;
        }
        half_arr(b, len);
        mul_arr(a, a, len);
        mod_sub(a, c, len);
    }
    copy(a, d, len);
}//use mul_arr, mod_sub, whether_0, half_arr

/*
int PowerMod(int a, int b, int c)
{
	int ans = 1;
	a = a % c;
	while(b > 0)
	{
	if(b % 2 == 1)
	ans = (ans * a) % c;
	b = b / 2;
	a = (a * a) % c;
	}
	return ans;
}
*/

void arr_sub1(int a[], int len)
{
	a[len - 1] -= 1;
	int i;
	for(i = len - 1; i >= 0; i --)
	{
		if(a[i] < 0)
		{
			a[i - 1] --;
			a[i] += 10;
		}
	}
}

int compare(int a[], int b[], int len)
{
	int i;
	for(i = 0; i < len; i ++)
	{
		if(a[i] != b[i])
		{
			return 0;
		}
	}
	return 1;
}

void print(int a[], int len)
{
    int i;
    for(i = 0; a[i] == 0; i ++);
    while (i < len)
    {
        printf("%d", a[i]);
        i ++;
    }
    printf("\t");
}


int meisen(int p, int len)
{
    int two[len];//2 _ const 
    int p_1[len];//2 ^ p - 1 _ const 
	int p_2[len];//2 ^ p - 2 _ const 
    int _1[len];//1 _ const 
    int k[len];//dipose 
    
    
    memset(two, 0, len * sizeof(int));
    memset(p_1, 0, len * sizeof(int));
	memset(_1, 0, len * sizeof(int));
	memset(k, 0, len * sizeof(int));
	
	two[len - 1] = 2;
    k[len - 1] = 1;
    _1[len - 1] = 1;
    
    /*Miller-Rabin
    n = 2 ^ p - 1
    n - 1 = 2 ^ p - 2
    let n - 1 = m * 2 ^ t*/
    
    for (int l = 0; l < p; l ++)//2 ^ p
    {
        mul_num(2, k, len);
    }
    
    arr_sub1(k, len);//2 ^ p - 1
    for (int i = 0; i < len; i ++)
    {
        p_1[i] = k[i];
    } //p_1 is the number
    
    
    
    arr_sub1(k, len); //2 ^ p - 2
    
    for (int i = 0; i < len; i ++)
    {
        p_2[i] = k[i];
    } //K2 = 2 ^ n - 2
    int t = 0;
    while (k[len - 1] % 2 == 0)
    {
        t ++;
        half_arr(k, len);
    } //2 ^ p - 2 = m * 2 ^ t to calculate m and t 
    int P[5] = {3, 5, 7, 11, 13};//use several prime numbers to judge
    int cnt = 0;//count times
    for (int i = 0; i < 5; i ++)
    {
        int a = P[i];
        if (p < 4)//if the number is small then it's prime(actually they are 3 and 7)
        {
            cnt ++;
            continue;
        }
        int array[len];
        copy(array, _1, len);
        mul_num(a, array, len);
        quick_mod(array, k, p_1, len);//array = array ^ k % p_1
        for (int i = 0; i < t; i ++)
        {
            int temp[len];
            copy(temp, array, len);
            quick_mod(array, two, p_1, len);//array = array ^ two % p_1
            if (compare(array, _1, len))
            {
                if (!(compare(temp, _1, len)) && !(compare(temp, p_2, len)))
                {
                    return 0;
                }
            }
        }
        if (compare(array, _1, len))
        {
            cnt ++;
            continue;
        }//if array = 1, then check next prime number in P
        return 0;//if not then break;
    }
    if (cnt == 5)
    {
        print(p_1, len);
        return 1;
    }//5 times are all right
}

/*
bool Miller_Rabin(long long n)
{
	int m = n - 1;
	int t = 0;
 
	if (n == 2)
	{
		return true;
	}
	else if (n < 2 || !(n & 1))
	{
		return false;
	}
 
 	
	while (!(m & 1))
	{
		m >>= 1;
		t ++;
	}
 
	for (int i = 0; i < 20; i ++)
	{    
		
		long long a = rand() % (n - 1) + 1;
		
		long long x = qul_pow(a, m, n), y;
  		
		for (int j = 0; j < t; j ++)
		{
			y = qul_mul(x, x, n);  
   			
   			
			if (y==1 && x != 1 && x != n - 1)
			{
				return false;
			}
   
			x = y;
		}
  		
		if (x != 1)
		{
			return false;
		}
	}
	return true;
}*/

void judge_p(int *p)//simple 
{
	int i = 0, j = 0, k = 0;
	for(i = 0; p[i] != NULL; i ++)
	{
		if(p[i] == 2)
		{
			p[k] = 2;
			i ++;
			k ++; 
		}
		else if(p[i] % 2 == 0)
		{
			i ++;
		}
		for(j = sqrt(p[i]) + 1; j >= 2; j --)
		{
			if(p[i] % j == 0)
			{
				break;
			}
			else if(j == 2) 
			{
				p[k] = p[i];
				k ++;
			}
		}
	}
	for(i = k; i < 1000; i ++)
	{
		p[i] = NULL;
	}
}

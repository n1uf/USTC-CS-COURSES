#include <cstdint>
#include <iostream>
#include <fstream>
#define MAXLEN 100
#ifndef LENGTH
#define LENGTH 3
#endif

int16_t lab1(int16_t a, int16_t b)
{
	int result=0;
	for(int i = 0; i < 16 - b; i ++)
		a += a;	// 左移a得到低b位 
	for(int i = 0; i < b; i ++, a += a) // 每判断一位左移 
	{
		if(a < 0)
			result++;// 当前判断是否为1 
	}
	return result;
}

int16_t lab2(int16_t p, int16_t q, int16_t n)
{
    if(n == 0 || n == 1)
		return 1;
    int a = 1, b = 1, c = 0; // 当前N的斐波那契数 
	int a0, b0, c0;	// N+1的 
    for(int i = 0; i < n - 1; i ++)
	{
		a0 = a;
		b0 = b;
		while(a >= 0)
			a -= p;
		a += p;	// a % p
		while(b >= 0)
			b -= q;
		b += q;	// b % q
		c0 = a + b;
		a = b0;
		b = c0;
	}
	return c0;
}

int16_t lab3(int16_t n, char str[])
{
    int i = 0, nowlen = 1, result = 1;
	    while (i < n) 
		{
	        if (str[i] == str[i + 1])	// 更新当前长度 
	            nowlen ++;
	        else
			{
	            if (nowlen > result)	// 更新最长长度 
	                result = nowlen;
	            nowlen = 1;
	        }
	    i ++;
	    }
	    return result;
}

void lab4(int16_t score[], int16_t *a, int16_t *b)
{
    int i, j, t;
    *a = 0, *b = 0;
    for(i = 0; i < 16 - 1; i ++)//冒泡排序
	    {
	        for(j = 0; j < 16 - i - 1; j ++)
	        {
	            if(score[j] > score[j + 1])
	            {
	               t = score[j + 1];
	               score[j + 1] = score[j];
	               score[j] = t;
	            }
	        }
	    }
	for(i = 15; i >= 12; i--)	// 前25%中判断 
	{
		if(score[i] >= 85)
			*a = *a + 1;
	}
	for(i = 15; i >= 8; i --)	// 前50%中判断 
	{
		if(score[i] >= 75)
			*b = *b + 1;
	}
	*b = *b - *a;	// 重复了前25%的部分 
}

int main() 
{
	std::fstream file;
	file.open("test.txt", std::ios::in);
	// lab1
	int16_t a = 0, b = 0;
	for (int i = 0; i < LENGTH; ++i) 
	{
		file >> a >> b;
		std::cout << lab1(a, b) << std::endl;
	}
	// lab2
	int16_t p = 0, q = 0, n = 0;
	for (int i = 0; i < LENGTH; ++i) 
	{
		file >> p >> q >> n;
		std::cout << lab2(p, q, n) << std::endl;
	}
	// lab3
	char s[MAXLEN];
	for (int i = 0; i < LENGTH; ++i) 
	{
		file >> n >> s;
		std::cout << lab3(n, s) << std::endl;
	}
	// lab4
	int16_t score[16];
	for (int i = 0; i < LENGTH; ++i) 
	{
		for (int j = 0; j < 16; ++j) 
		{
			file >> score[j];
		}
		lab4(score, &a, &b);
		for (int j = 0; j < 16; ++j) 
		{
			std::cout << score[j] << " ";
		}
		std::cout << std::endl << a << " " << b << std::endl;
	}
	file.close();
	return 0;
}

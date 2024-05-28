#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

int flag = 0;

char op[5] = { '#', '+', '-', '*', '/', };

float cal(float x, float y, int op)
{
	switch (op)									//将运算符初始化为1,2,3,4四个数字
	{
	case 1:return x + y;
	case 2:return x - y;
	case 3:return x * y;
	case 4:return x / y;
	}
}
//对应表达式((AoB)oC)oD
float cal1(float i, float j, float k, float t, int op1, int op2, int op3)
{
	float r1, r2, r3;
	r1 = cal(i, j, op1);
	r2 = cal(r1, k, op2);
	r3 = cal(r2, t, op3);
	return r3;
}
//对应表达式(Ao(BoC))oD
float cal2(float i, float j, float k, float t, int op1, int op2, int op3)
{
	float r1, r2, r3;
	r1 = cal(j, k, op2);
	r2 = cal(i, r1, op1);
	r3 = cal(r2, t, op3);
	return r3;
}
//对应表达式Ao(Bo(CoD))
float cal3(float i, float j, float k, float t, int op1, int op2, int op3)
{
	float r1, r2, r3;
	r1 = cal(k, t, op3);
	r2 = cal(j, r1, op2);
	r3 = cal(i, r2, op1);
	return r3;
}
//对应表达式Ao((BoC)oD)
float cal4(float i, float j, float k, float t, int op1, int op2, int op3)
{
	float r1, r2, r3;
	r1 = cal(j, k, op2);
	r2 = cal(r1, t, op3);
	r3 = cal(i, r2, op1);
	return r3;
}
//对应表达式(AoB)o(CoD)
float cal5(float i, float j, float k, float t, int op1, int op2, int op3)
{
	float r1, r2, r3;
	r1 = cal(i, j, op1);
	r2 = cal(k, t, op3);
	r3 = cal(r1, r2, op2);
	return r3;
}
int get24(int i, int j, int k, int t)
{
	flag = 0;
	int op1, op2, op3;
	for (op1 = 1; op1 <= 4; op1++){						//通过一个三重循坏列举了符号的变化情况
		for (op2 = 1; op2 <= 4; op2++){
			for (op3 = 1; op3 <= 4; op3++){
				if (cal1(i, j, k, t, op1, op2, op3) == 24)
				{
					printf("((%d%c%d)%c%d)%c%d=24\n", i, op[op1], j, op[op2], k, op[op3], t);
					flag = 1;
				}
				if (cal2(i, j, k, t, op1, op2, op3) == 24)
				{
					printf("(%d%c(%d%c%d))%c%d=24\n", i, op[op1], j, op[op2], k, op[op3], t);
					flag = 1;
				}
				if (cal3(i, j, k, t, op1, op2, op3) == 24)
				{
					printf("%d%c(%d%c(%d%c%d))=24\n", i, op[op1], j, op[op2], k, op[op3], t);
					flag = 1;
				}
				if (cal4(i, j, k, t, op1, op2, op3) == 24)
				{
					printf("%d%c((%d%c%d)%c%d)=24\n", i, op[op1], j, op[op2], k, op[op3], t);
					flag = 1;
				}
				if (cal5(i, j, k, t, op1, op2, op3) == 24)
				{
					printf("(%d%c%d)%c(%d%c%d)=24\n", i, op[op1], j, op[op2], k, op[op3], t);
					flag = 1;
				}
			}
		}
	}
	return flag;
}

int main(void)
{
    int num[4];
    int i, j, k, l;
	printf("输入四个数字，以空格隔开，若要停止程序，四个数字均输入为0\n\n"); 
    for(i = 0; ; i ++)
	{
		int cnt = 0;
		printf("请输入4个数字：");
		for(j = 0; j < 4; j ++)
		{
			scanf("%d", &num[j]); 
		}
		for(j = 0; j < 4; j ++)
		{
			if(num[j] == 0)
			{
				cnt ++;
			}
		}
		if(cnt == 4)
		{
			break;
		}
		get24(num[0],num[1],num[2],num[3]);
		if(!flag)
		{
			printf("没有24点的解\n"); 
		}
	}
}


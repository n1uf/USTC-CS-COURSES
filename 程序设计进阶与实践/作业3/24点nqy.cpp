/*���뷶ΧΪ0 ~ 20��24�㣬�н����һ���*/ 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<math.h>

int flag = 0;

char op[5] = { ' ', '+', '-', '*', '/', };

//���������ʼ��Ϊ1,2,3,4�ĸ�����
float cal(float x, float y, int op)
{
	switch (op)
	{
		case 1:return x + y;
		case 2:return x - y;
		case 3:return x * y;
		case 4:return x / y;
	}
}
//��Ӧ���ʽ((AoB)oC)oD
float cal1(float i, float j, float k, float t, int op1, int op2, int op3)
{
	float r1, r2, r3;
	r1 = cal(i, j, op1);
	r2 = cal(r1, k, op2);
	r3 = cal(r2, t, op3);
	return r3;
}
//��Ӧ���ʽ(Ao(BoC))oD
float cal2(float i, float j, float k, float t, int op1, int op2, int op3)
{
	float r1, r2, r3;
	r1 = cal(j, k, op2);
	r2 = cal(i, r1, op1);
	r3 = cal(r2, t, op3);
	return r3;
}
//��Ӧ���ʽAo(Bo(CoD))
float cal3(float i, float j, float k, float t, int op1, int op2, int op3)
{
	float r1, r2, r3;
	r1 = cal(k, t, op3);
	r2 = cal(j, r1, op2);
	r3 = cal(i, r2, op1);
	return r3;
}
//��Ӧ���ʽAo((BoC)oD)
float cal4(float i, float j, float k, float t, int op1, int op2, int op3)
{
	float r1, r2, r3;
	r1 = cal(j, k, op2);
	r2 = cal(r1, t, op3);
	r3 = cal(i, r2, op1);
	return r3;
}
//��Ӧ���ʽ(AoB)o(CoD)
float cal5(float i, float j, float k, float t, int op1, int op2, int op3)
{
	float r1, r2, r3;
	r1 = cal(i, j, op1);
	r2 = cal(k, t, op3);
	r3 = cal(r1, r2, op2);
	return r3;
}
int get24(float i, float j, float k, float t)
{
	flag = 0;
	int op1, op2, op3;
	//ͨ��һ������ѭ���о��˷��ŵı仯���
	for (op1 = 1; op1 <= 4; op1++)
	{						
		for (op2 = 1; op2 <= 4; op2++)
		{
			for (op3 = 1; op3 <= 4; op3++)
			{
				if (fabs(cal1(i, j, k, t, op1, op2, op3) - 24.0) < 1e-5)
				{
					printf("((%.0f %c %.0f) %c %.0f )%c %.0f = 24 \n", i, op[op1], j, op[op2], k, op[op3], t);
					flag = 1;
					return flag;
				}
				if (fabs(cal2(i, j, k, t, op1, op2, op3) - 24.0) < 1e-5)
				{
					printf("(%.0f %c (%.0f %c %.0f ))%c %.0f = 24 \n", i, op[op1], j, op[op2], k, op[op3], t);
					flag = 1;
					return flag;
				}
				if (fabs(cal3(i, j, k, t, op1, op2, op3) - 24.0) < 1e-5)
				{
					printf("%.0f %c (%.0f %c (%.0f %c %.0f)) = 24 \n", i, op[op1], j, op[op2], k, op[op3], t);
					flag = 1;
					return flag;
				}
				if (fabs(cal4(i, j, k, t, op1, op2, op3) - 24.0) < 1e-5)
				{
					printf("%.0f %c ((%.0f %c %.0f )%c %.0f) = 24 \n", i, op[op1], j, op[op2], k, op[op3], t);
					flag = 1;
					return flag;
				}
				if (fabs(cal5(i, j, k, t, op1, op2, op3) - 24.0) < 1e-5)
				{
					printf("(%.0f %c %.0f )%c (%.0f %c %.0f) = 24\n", i, op[op1], j, op[op2], k, op[op3], t);
					flag = 1;
					return flag;
				}
			}
		}
	}
	return flag;
}

int main(void)
{
    float num[4];
    int i, j, k, l;
	printf("�����ĸ�������(��ΧΪ[1,20])���Կո��������Ҫֹͣ�����ĸ����־�����Ϊ1\n\n"); 
    for(i = 0; ; i ++)
	{
		int cnt = 0;
		while(1)
		{
			printf("������4����������");
			int judgeflag = 0;
			for(j = 0; j < 4; j ++)
			{
				scanf("%f", &num[j]);
			}
			for(j = 0; j < 4; j ++)
			{
				if(num[j] > 20 || num[j] <1)
				{
					judgeflag = 1;
					printf("���벻����Ҫ��\n");
					break;
				}
			}
			if(judgeflag) continue;
			else break;
		}
		
		for(j = 0; j < 4; j ++)
		{
			if(num[j] == 1)
			{
				cnt ++;
			}
		}
		if(cnt == 4)
		{
			break;
		}
		for(i = 0; i < 4; i ++) //�ĸ����ֵ�ȫ���� 
		{
			for(j = 0; j < 4; j ++)
			{
				if(j == i)
				{
					continue;
				}
				for(k = 0; k < 4; k ++)
				{
					if(k == i || k == j)
					{
						continue;
					}
					for(l = 0; l < 4; l ++)
					{
						if(l == k || l == j || l == i)
						{
							continue;
						}
						get24(num[i], num[j], num[k], num[l]);
						if(flag)
						{
							goto out;
						}
					}
				}
			}
		}
out:	if(!flag)
		{
			printf("û��24��Ľ�\n");
		}
	}
	printf("�������");
}

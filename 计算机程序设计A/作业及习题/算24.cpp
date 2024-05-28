#include <stdio.h>
#include <math.h>

char mark[4]={'+', '-', '*', '/'}; 
 
/*定义四种运算*/ 
double cal(double x, double y, int mark);

/*定义四个数字的每一种运算*/ 
double calculate_1(double a, double b, double c, double d, int mark1, int mark2, int mark3);
double calculate_2(double a, double b, double c, double d, int mark1, int mark2, int mark3);
double calculate_3(double a, double b, double c, double d, int mark1, int mark2, int mark3);
double calculate_4(double a, double b, double c, double d, int mark1, int mark2, int mark3);
double calculate_5(double a, double b, double c, double d, int mark1, int mark2, int mark3);

/*定义遍历*/ 
double get(int w,int x,int y,int z);//返回值代表成立与否 

int main()
{
    int w, x, y, z;
    int i, j;
    int a[100];
    for(i = 0; ; i ++)
	{
		/*输入*/ 
		scanf("%d %d %d %d", &w, &x, &y, &z);
		
		/*判断*/ 
		if(w == 0 && x == 0 && y == 0 && z == 0)
		{
			break;
		}
		/*判断结果存在数组a里*/ 
		if(get(w, x, y, z))
		{
			a[i] = 1;
		}
		else
		{
			a[i] = 0;
		}
	}
	
	/*输出*/ 
	j = i;
	for(i = 0; i < j; i ++)
	{
		printf("%d\n",a[i]);
	}
}

double cal(double x, double y, int mark)
{
    switch(mark)
    {
        case 0:return x + y;
        case 1:return x - y;
        case 2:return x * y;
        case 3:return x / y;
    }
    return 0;
}

double calculate_1(double a, double b, double c, double d, int mark1, int mark2, int mark3)
{
    double r1, r2, r3;
    r1 = cal(a, b, mark1);
    r2 = cal(r1, c, mark2);
    r3 = cal(r2, d, mark3);
    return r3;
}

double calculate_2(double a, double b, double c, double d, int mark1, int mark2, int mark3)
{
    double r1, r2, r3;
    r1 = cal(b, c, mark1);
    r2 = cal(a, r1, mark2);
    r3 = cal(r2, d, mark3);
    return r3;
}

double calculate_3(double a, double b, double c, double d, int mark1, int mark2, int mark3)
{
    double r1, r2, r3;
    r1 = cal(c, d, mark1);
    r2 = cal(b, r1, mark2);
    r3 = cal(a, r2, mark3);
    return r3;
}

double calculate_4(double a, double b, double c, double d, int mark1, int mark2, int mark3)
{
    double r1,r2,r3;
    r1=cal(b, c, mark1);
    r2=cal(r1, d, mark2);
    r3=cal(a, r2, mark3);
    return r3;
}

double calculate_5(double a, double b, double c, double d, int mark1, int mark2, int mark3)
{
    double r1, r2, r3;
    r1 = cal(a, b, mark1);
    r2 = cal(c, d, mark2);
    r3 = cal(r1, r2, mark3);
    return r3;
}

double get(int w, int x, int y, int z)
{
    int mark1, mark2, mark3;
    int j;
    int a, b, c, d;
    double flag = 0;
    for(j = 1; j <= 24; j ++)
    {
    	/*枚举*/ 
        switch (j)
    	{
			case 1: a = w,b = x,c = y,d = z; break;
			case 2: a = w,b = x,c = z,d = y; break;
			case 3: a = w,b = y,c = x,d = z; break;
			case 4: a = w,b = y,c = z,d = x; break;
			case 5: a = w,b = z,c = x,d = y; break;
			case 6: a = w,b = z,c = y,d = x; break;
			case 7: a = x,b = w,c = y,d = z; break;
			case 8: a = x,b = w,c = z,d = y; break;
			case 9: a = x,b = y,c = w,d = z; break;
			case 10: a = x,b = y,c = z,d = w; break;
			case 11: a = x,b = z,c = w,d = y; break;
			case 12: a = x,b = z,c = y,d = w; break;
			case 13: a = y,b = w,c = x,d = z; break;
			case 14: a = y,b = w,c = z,d = x; break;
			case 15: a = y,b = x,c = w,d = z; break;
			case 16: a = y,b = x,c = z,d = w; break;
			case 17: a = y,b = z,c = w,d = x; break;
			case 18: a = y,b = z,c = x,d = w; break;
			case 19: a = z,b = w,c = x,d = y; break;
			case 20: a = z,b = w,c = y,d = x; break;
            case 21: a = z,b = x,c = w,d = y; break;
        	case 22: a = z,b = x,c = y,d = w; break;
            case 23: a = z,b = y,c = w,d = x; break;
            case 24: a = z,b = y,c = x,d = w; break;
        }
		for(mark1 = 0; mark1 < 4; mark1 ++)
    	{
        	for(mark2 = 0; mark2 < 4; mark2 ++)
        	{
            	for(mark3 = 0; mark3 < 4; mark3 ++)
            	{
                	//第一种排列
                	if(fabs(calculate_1(a, b, c, d, mark1, mark2, mark3) - 24.0) < 1e-6)
					{
						flag = 1;
                	}
                	//第二种排列
                	if(fabs(calculate_2(a, b, c, d, mark1, mark2, mark3) - 24.0) < 1e-6)
					{
						flag = 1;
					}
					//第三种排列
					if(fabs(calculate_3(a, b, c, d, mark1, mark2, mark3) - 24.0) < 1e-6)
					{
						flag = 1;
					}
					//第四种排列
					if(fabs(calculate_4(a, b, c, d, mark1, mark2, mark3) - 24.0) < 1e-6)
					{
						flag = 1;
					}
					//第五种排列
					if(fabs(calculate_5(a, b, c, d, mark1, mark2, mark3) - 24.0) < 1e-6)
					{
					   flag = 1;
					}
            	}
        	}
    	}
	}
	return (flag);
}

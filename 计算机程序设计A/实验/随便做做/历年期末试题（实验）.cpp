#include <stdio.h>
#include <math.h>

int main()

/*2.17{
	int num = 0;
	while(num <= 2)
	{
		num ++;
		printf("%d\n", num);
	}
}*/

/*2.21{
	int x, i;
	for(i = 0; i < 100; i ++)
	{
		x = i;
		if(++ x % 2 == 0)
		{
			if(++ x %3 == 0)
			{
				if(++ x % 7 == 0)
				{
					printf("%d ", x);
				}
			}
		}
	}
}*/

/*4.33{
	int a, i;
	const long k = 555555;
	for(i = 100; i < 1000; i++)
	{
		if(k % i == 0)
		{
			a = i;
		}
	}
	printf("%d", a);
}*/

/*4.34{
	double s = 1.0, x, i = 1.0;
	scanf("%lf", &x);
	for(i = 1.0; 1.0 / pow(x, i) > 0.000001; i ++)
	{
		s = s + 1.0 / pow(x ,i);
	}
	printf("%lf", s);
}*/

/*判断闰年闰月 
{
	int year, month;
	scanf("%d%d", &year, &month);
	if(month == 2)
	{
		if(year % 100 != 0 && year % 4 == 0 || year % 400 == 0)
		{
			printf("29天");
		}
		else
		{
			printf("28天");
		}
	}
	else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		printf("31天");
	}
	else
	{
		printf("30天"); 
	}
}*/



#include <stdio.h>
void delet1(char str[], int i);
void delet2(char str[], int i);
void a_A(char str[], int i); 
int main()
{
	char str[1024];
	int j, i;
	/*为了便于分辨，用ASCII码运算的地方都用ASCII码表示*/ 
	
	/*输入*/ 
	for (j = 0; j < 1024; j ++)
	{
	begin://#为结束 
		scanf("%c", &str[j]);
		if (str[j] == 35)
		{
			break;
		}
		if (str[j] == 35 || str[j] == 94|| str[j] == 36 || str[j] == 32||   str[j] == 44 || str[j] == 46 || str[j] == 10 || 
		   (str[j] >= 48 && str[j] <= 57) || (str[j] >= 64 && str[j] <= 90) || (str[j] >= 97 && str[j] <= 122))
		{
			continue;
		}
		else
			goto begin;
	}

	/*操作*/ 
	for (i = 0; i < 1024; i ++)
	{
		if (str[i] == '@') delet1(str, i);
		if (str[i] == '$') delet2(str, i);
		if (str[i] == '^') a_A(str, i);
		if (str[i] == '#')
		{
			for (j = 0; j < 1024; j ++)
			{
				if (str[j] == 64 || str[j] == 36 || str[j] == 94) 
				{
					str[j] = '-';
				}
			}
			for (j = 0; j < 1024; j++)
			{
				if (str[j] != '-' && str[j] != '#')
				{
					printf("%c", str[j]);
				}
				else if (str[j] == '#')
				{
					break;
				}
			}
		}
	}
	return 0;
}

/*@ 删除 */
void delet1(char str[], int i)
{
	int y = 1;
	for (; ; i++)
	{
		if (str[i] == '@')
		{
			str[i - y] = '-';
			y = y + 2;
		}
		else
		{
			break;
		}
	}
}

/*$ 删除 */
void delet2(char str[], int i)
{
	int j, k;
	for (j = 1; j < i + 2; j ++)
	{
		if ((i - j) < 0 || str[i - j] == '\n' )
		{
			for (k = 1; k <= j; k ++)
			{
				str[i - j + k] = '-';
			}
			break;
		}
	}
}

/*^ 大写 */
void a_A(char str[], int i)
{
	int j;
	for (j = 1; j <= i + 1; j ++)
	{
		if (str[i - j] >= 65 && str[i - j] <= 90)
		{
			break;
		}
		else if ((str[i - j] == ' ' || str[i - j] == '\n' || i - j < 0) && 
		         (str[i - j + 1] >= 97 && str[i - j + 1] <= 122))
		{
			str[i - j + 1] = str[i - j + 1] - 32;
			break;
		}
	}
}

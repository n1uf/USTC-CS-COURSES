#include<stdio.h>
#include<string.h>
int main()
{
	char N[10]={'0','1','2','3','4','5','6','7','8','9'},n[1024];
	char s[516],num[516],index[516],e[1024] = {"E"};
	gets(s);
	int i,j,k,a = 2;
	/*分情况讨论*/
	
	/*当只有一位，没有'.'时*/ 
	if(strlen(s) == 1)
	{
		num[0] = s[0];
		n[0] = '+';
		n[1] = '0';
		puts(strcat(strcat(num,e),n));goto end;
	}
	
	/*当形式为'x.abcd...'时*/ 
	if(s[1] == '.')
	{
		if(strlen(s) != 3) num[1] = '.';
		if(s[0] == '0')
		{
			n[0] = '-';
			for(j = 2; j < strlen(s) + 1; j ++)
			{
				if(s[j] != '0')
				{
					k =  j - 1;
					num[0] = s[j];
					num[a] = s[j + 1];break;
				}
			}
			for(; j < strlen(s) - 1; j ++,a ++)
			{
				num[a] = s[j + 1];
			}
			n[1] = N[k];
			puts(strcat(strcat(num,e),n));
		}
		else
		{
			num[0] = s[0];
			for(j = 2; j < strlen(s); j ++)
			{
				num[j] = s [j];
			}
			n[0] = '+';
			n[1] = '0';
			puts(strcat(strcat(num,e),n));
		}
	}
	
	/*当形式为'.abc...'时*/ 
	else if(s[0] == '.')
	{
		num[1] = '.';
		num[0] = '0';
		n[0] = '+';
		n[1] = '0';
		for(i = 2; i <= strlen(s); i ++)
		{
			num[i] = s[i - 1];
		}
		puts(strcat(strcat(num,e),n));
	}
	
	/*当形式为'abc....def...'时*/ 
	else
	{
		num[1] = '.';
		n[0] = '+';
		num[0] = s[0];
		for(i = 2; i <= strlen(s); i ++)
		{
			num[i] = s[i - 1];
			if(s[i - 1] == '.')
			{
				break;
			}
		}
		if(strlen(s) <= 10) n[1] = N[i - 2];
		else 
		{
			n[1] = '4';
			n[2] = '1';
		}
		for(; i <= strlen(s); i ++)
		{
			num[i] = s[i];
		}
		puts(strcat(strcat(num,e),n));
	}
	
end:	return 0;
}

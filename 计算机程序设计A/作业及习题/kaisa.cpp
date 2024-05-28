#include<stdio.h>
int main()
{
	char code[516],uncode[516];
	int i;
	gets(code);
	for(i = 0;i < 515 && code[i] != 0;i ++)
	{
		if(code[i] == 32)
		{
			uncode[i] = code[i];
		}
		else if(code[i] >= 70 && code[i] <= 90)
		{
			uncode[i] = code[i] - 5;
		}
		else if(code[i] >= 65 && code[i] <= 68)
		{
			uncode[i] = code[i] + 21;
		}
		else
		{
			uncode[i] = code[i];
		}
	}
	printf("%s",uncode);
 return 0;
}

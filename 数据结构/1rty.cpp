#include <stdio.h>

int main()
{
	int inte1[15], inte2[15];
	int deci1[15], deci2[15];
	int base1 = 10, base2 = 2;
	for(int i = 0; i < 15; ++i)
	{
		inte2[i] = 0;
		deci2[i] = 0;
		inte1[i] = 0;
		deci1[i] = 0;
	}
	inte1[0] = 3;
	inte1[1] = 1;
	deci1[0] = 2;
	deci1[1] = 5;
	for(int i = 0; i < 15; ++i)
	{
		for(int j = 0; j < 15; ++j)
			inte2[j] *= base1;

		inte2[0] += inte1[15 - 1 - i];

		for(int j = 0; j < 15 - 1; ++j)
			if(inte2[j] >= base2)
			{
				inte2[j + 1] += inte2[j] / base2;
				inte2[j] = inte2[j] % base2;
			}
	}
	
	int i;
	for(i = 14; inte2[i] == 0; --i);
	
	for(; i >= 0; --i)
		if(inte2[i] < 10) 	 printf("%d",inte2[i]);
		else if(inte2[i] < 36) printf("%c",'a' + inte2[i] - 10);
		
	printf(".");
		
	for(i = 14; deci1[i] == 0; --i);
	int j;
	for(j = 0; j <= i; j ++)
	{
		if(deci1[j] < 10) 	 printf("%d",deci1[j]);
		else if(deci1[j] < 36) printf("%c",'a' + deci1[j]-10);
	}
	printf("\n");
}

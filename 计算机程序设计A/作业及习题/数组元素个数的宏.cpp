/*书面作业*/ 


#include <stdio.h>
#define ARRAY_SIZE(a) (sizeof((a))/sizeof((a[0])))
int main(void)
{
	int a[10], b;
	b = ARRAY_SIZE(a);
	printf("%d",b);
}


#include <stdio.h>
#define SWAP(type, x, y) {type *temp; temp = x; x = y; y = temp;}
int main(void)
{
	char a, b, *p1, *p2;
	p1 = &a;
	p2 = &b;
	scanf("%c %c", p1, p2);
	SWAP(char, p1, p2);
	printf("%c %c", *p1, *p2);
}



#include <stdio.h>
#define JUDGE(c) ((c >= 97 && c <= 122)?(0):(1))
int main(void)
{
	char a[100];
	gets(a);
	int i;
	for(i = 0; a[i] != NULL; i ++)
	{
		if(JUDGE(a[i]))
		{
			a[i] += 32;
		}
		else
		{
			a[i] -= 32;
		}
		printf("%c", a[i]);
	}
}


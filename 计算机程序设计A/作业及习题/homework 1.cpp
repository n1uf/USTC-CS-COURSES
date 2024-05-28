#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	switch(n-1)
	{
		case 1:
		printf(" 1 \n2 2\n 1");break;
		case 2:
		printf("  1  \n 2 2 \n3 3 3\n 2 2 \n  1");break;
		case 3:
		printf("   1   \n  2 2  \n 3 3 3 \n4 4 4 4\n 3 3 3 \n  2 2  \n   1");break;
		case 4:
		printf("    1    \n   2 2   \n  3 3 3  \n 4 4 4 4 \n5 5 5 5 5\n 4 4 4 4 \n  3 3 3  \n   2 2   \n    1");break;
		case 5:
		printf("     1     \n    2 2    \n   3 3 3   \n  4 4 4 4  \n 5 5 5 5 5 \n6 6 6 6 6 6\n 5 5 5 5 5 \n  4 4 4 4  \n   3 3 3   \n    2 2    \n     1     ");break;
		case 6:
		printf("      1      \n     2 2     \n    3 3 3    \n   4 4 4 4   \n  5 5 5 5 5  \n 6 6 6 6 6 6 \n7 7 7 7 7 7 7\n 6 6 6 6 6 6 \n  5 5 5 5 5  \n   4 4 4 4   \n    3 3 3    \n     2 2     \n      1");break;
		case 7:
		printf("       1       \n      2 2      \n     3 3 3     \n    4 4 4 4    \n   5 5 5 5 5   \n  6 6 6 6 6 6  \n 7 7 7 7 7 7 7 \n8 8 8 8 8 8 8 8\n 7 7 7 7 7 7 7 \n  6 6 6 6 6 6  \n   5 5 5 5 5   \n    4 4 4 4    \n     3 3 3     \n      2 2      \n       1");break;
		case 8:
		printf("        1        \n       2 2       \n      3 3 3      \n     4 4 4 4     \n    5 5 5 5 5    \n   6 6 6 6 6 6   \n  7 7 7 7 7 7 7  \n 8 8 8 8 8 8 8 8 \n9 9 9 9 9 9 9 9 9\n 8 8 8 8 8 8 8 8 \n  7 7 7 7 7 7 7  \n   6 6 6 6 6 6   \n    5 5 5 5 5    \n     4 4 4 4     \n      3 3 3      \n       2 2       \n        1");break;
		default:
		printf("ÒÑ¾­³¬³ö·¶Î§");
	}
	return 0;
}

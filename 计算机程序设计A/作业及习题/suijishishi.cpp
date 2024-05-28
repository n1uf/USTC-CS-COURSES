#include<stdio.h>
#include<stdlib.h>
int main()

int x = 0, y= 0, i;

srand(x + 10 * y);

for (i = 0; i < 26; i++) {

    int dir = rand() % 4;

    printf("%d\n", dir);
    
	return 0;

}

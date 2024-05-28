#include <stdio.h>
#include <stdlib.h>

#define N 100005

int G[N];
int suf[N];
int stack[N];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
        scanf("%d", &G[i]);

    int top = -1;

    for (int i = n; i >= 1; --i) {
        while (top != -1 && stack[top] > G[i])
            top--;

        suf[i] = top + 1;
        stack[++top] = G[i];
    }

    top = -1;

    for (int i = 1; i <= n; ++i) {
        while (top != -1 && stack[top] > G[i])
            top--;

        printf("%d ", suf[i] + top + 1);
        stack[++top] = G[i];
    }

    return 0;
}

#include <stdio.h>
// 将 n 个盘子从 a 柱移动到b柱，用c柱做中转
void Hanoi(int n, char a, char b, char c) {
// 递归的结束条件：只有1个盘子，直接从a柱移到b柱
if (n == 1) { printf("%c->%c\n", a, b); return; }
// ① 先将n-1个盘子，以b为中转，从a柱移动到c柱，
Hanoi(n-1, a, c, b);
// ② 将一个盘子从a移动到b
printf("%c->%c\n", a, b);
// ③ 将c柱上的n-1个盘子，以a为中转，移动到b柱
Hanoi(n-1, c, b, a);
}
int main() {
int N;
scanf("%d", &N);
Hanoi(N, 'A', 'B', 'C');
return 0;
}

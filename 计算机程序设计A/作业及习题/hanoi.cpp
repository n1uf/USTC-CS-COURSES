#include <stdio.h>
// �� n �����Ӵ� a ���ƶ���b������c������ת
void Hanoi(int n, char a, char b, char c) {
// �ݹ�Ľ���������ֻ��1�����ӣ�ֱ�Ӵ�a���Ƶ�b��
if (n == 1) { printf("%c->%c\n", a, b); return; }
// �� �Ƚ�n-1�����ӣ���bΪ��ת����a���ƶ���c����
Hanoi(n-1, a, c, b);
// �� ��һ�����Ӵ�a�ƶ���b
printf("%c->%c\n", a, b);
// �� ��c���ϵ�n-1�����ӣ���aΪ��ת���ƶ���b��
Hanoi(n-1, c, b, a);
}
int main() {
int N;
scanf("%d", &N);
Hanoi(N, 'A', 'B', 'C');
return 0;
}

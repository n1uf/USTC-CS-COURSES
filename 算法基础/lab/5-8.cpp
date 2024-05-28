#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ull unsigned long long
#define base 233
#define mod1 1000000007
#define mod2 2147483629
#define N 2005

char s[N];
ull hash1[N], hash2[N];

typedef struct HASH {
    ull num1;
    ull num2;
} HASH;

HASH t[N];

// 快速幂算法
ull qpow(ull base, ull exp, ull mod) {
    ull ans = 1;
    ull tmp = base;
    while (exp) {
        if (exp & 1)
            ans = (ans * tmp) % mod;
        tmp = (tmp * tmp) % mod;
        exp >>= 1;
    }
    return ans;
}

// 比较函数，用于排序
int up(const void *a, const void *b) {
    HASH *ha = (HASH *)a;
    HASH *hb = (HASH *)b;
    if (ha->num1 != hb->num1)
        return (ha->num1 < hb->num1) ? -1 : 1;
    else
        return (ha->num2 < hb->num2) ? -1 : ((ha->num2 == hb->num2) ? 0 : 1);
}

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", s + 1);
    ull num1 = 0, num2 = 0;
    // 计算字符串的哈希值
    for (int i = 1; i <= n; ++i) {
        num1 = (num1 * base + (s[i] - 'a' + 1)) % mod1;
        num2 = (num2 * base + (s[i] - 'a' + 1)) % mod2;
        hash1[i] = num1;
        hash2[i] = num2;
    }
    int ans = 0;
    ull base1 = 1, base2 = 1;
    // 枚举所有可能的子串长度
    for (int l = 0; l < n; ++l) {
        base1 = (base1 * base) % mod1;
        base2 = (base2 * base) % mod2;
        int cnt = 0;
        // 计算每个子串的哈希值
        for (int i = 1; i + l <= n; ++i) {
            t[++cnt].num1 = (hash1[i + l] - hash1[i - 1] * base1 % mod1 + mod1) % mod1;
            t[cnt].num2 = (hash2[i + l] - hash2[i - 1] * base2 % mod2 + mod2) % mod2;
        }
        // 对哈希值进行排序
        qsort(t + 1, cnt, sizeof(HASH), up);
        int tot = 1;
        // 统计相同哈希值的子串个数
        for (int i = 1; i <= cnt; ++i) {
            if (i > 1 && t[i].num1 == t[i - 1].num1 && t[i].num2 == t[i - 1].num2)
                ++tot;
            else {
                ans = (ans > tot * (l + 1)) ? ans : (tot * (l + 1));
                tot = 1;
            }
        }
        ans = (ans > tot * (l + 1)) ? ans : (tot * (l + 1));
    }
    printf("%d", ans);
    return 0;
}

#include <stdio.h>

#define ll long long
#define N 1000005
#define P 1000000007

int a[N], ainv[N];
int idcnt, atcid[N];
int pre[N << 1];
int w[N << 1];
int ans[N << 1];

int fd(int x) {
    return pre[x] ? pre[x] = fd(pre[x]) : x;
}

int qpow(int a, int b) {
    ll ans = 1;
    ll tmp = a % P;
    b %= P;
    while (b) {
        if (b & 1)
            ans *= tmp;
        ans %= P;
        tmp *= tmp;
        tmp %= P;
        b >>= 1;
    }
    return ans;
}

int main() {
    int n, m;
    int ansi = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        ainv[i] = qpow(a[i], P - 2);
        atcid[i] = i;
        w[i] = a[i];
    }
    idcnt = n;
    for (int i = 1, op, x, y; i <= m; ++i) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &x, &y);
            int fx = fd(atcid[x]);
            int fy = fd(atcid[y]);
            if (fx != fy) {
                pre[fy] = fx;
                w[fx] = 1ll * w[fx] * w[fy] % P;
            }
        } else if (op == 2) {
            scanf("%d", &x);
            int fx = fd(atcid[x]);
            ans[ansi] = w[fx];
            ansi++;
        } else if (op == 3) {
            scanf("%d%d", &x, &y);
            int fx = fd(atcid[x]);
            int fy = fd(atcid[y]);
            if (fx != fy) {
                atcid[x] = ++idcnt;
                w[fx] = 1ll * w[fx] * ainv[x] % P;
                w[atcid[x]] = 1ll * w[fy] * a[x] % P;
                pre[fy] = atcid[x];
            }
        }
    }
    for(int i = 0; i < ansi; ++i)
        printf("%d\n", ans[i]);
    return 0;
}

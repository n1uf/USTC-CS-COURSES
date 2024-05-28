#include <stdio.h>
#include <math.h>

#define N (1 << 22)
typedef long long ll;
const int mod = 998244353, g = 3, gi = 332748118;

int a[N], b[N], c[N];
int rev[N];

ll qpow(int a, int b) {
    ll ans = 1, tmp = a;
    while (b) {
        if (b & 1)
            ans *= tmp;
        ans %= mod;
        tmp *= tmp;
        tmp %= mod;
        b >>= 1;
    }
    return ans;
}

void FFT(int *a, int n, int inv) {
    for (int i = 0; i < n; ++i)
        if (i < rev[i]){
            int temp = a[i];
            a[i] = a[rev[i]];
            a[rev[i]] = temp;
        }
    for (int i = 1; i < n; i <<= 1) {
        ll gn = qpow(inv ? gi : g, (mod - 1) / (i << 1));
        for (int j = 0; j < n; j += (i << 1)) {
            ll g0 = 1;
            for (int k = 0; k < i; ++k, g0 = g0 * gn % mod) {
                ll x = a[j + k], y = g0 * a[j + i + k] % mod;
                a[j + k] = (x + y) % mod;
                a[j + i + k] = (x - y + mod) % mod;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int na = 0, nb = 0;
    for (int i = 0, x; i < n; ++i) {
        scanf("%d", &x);
        a[x] = 1;
        na = fmax(na, x);
    }
    for (int i = 0, x; i < m; ++i) {
        scanf("%d", &x);
        b[x] = 1;
        nb = fmax(nb, x);
    }
    n = na, m = nb;
    int bit = fmax((int)ceil(log2(n + m + 1)), 1);
    int len = 1 << bit;
    for (int i = 0; i < len; ++i)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    FFT(a, len, 0);
    FFT(b, len, 0);
    for (int i = 0; i <= len; ++i)
        c[i] = 1ll * a[i] * b[i] % mod;
    FFT(c, len, 1);
    ll inv = qpow(len, mod - 2);
    for (int i = 0; i <= n + m; ++i)
        c[i] = 1ll * c[i] * inv % mod;
    int ans = 0;
    for (int i = 0; i <= n + m; ++i)
        if (c[i])
            ++ans;
    printf("%d", ans);
    return 0;
}
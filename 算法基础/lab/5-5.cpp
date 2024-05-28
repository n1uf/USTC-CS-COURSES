#include <stdio.h>
#include <stdlib.h>

#define N 100005

typedef struct {
    int id;
    int opt;
    int x;
    int nx;
} OP;

OP op[N];
int cnt, f[N];
int paper[N], tr[N];

int lb(int x) {
    return x & (-x);
}

void add(int x, int v) {
    for (; x <= cnt; x += lb(x))
        tr[x] += v;
}

int query(int x) {
    int ans = 0;
    for (; x; x -= lb(x))
        ans += tr[x];
    return ans;
}

int ask(int k) {
    int l = 1, r = cnt;
    int ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        int now = query(mid);
        if (now < k)
            l = mid + 1;
        else {
            if (query(mid - 1) < k)
                return mid;
            r = mid - 1;
        }
    }
    return 0; // 处理未找到解的情况
}

int lrht(int nx) {
    if (paper[nx - 1])
        return nx - 1;
    int l = 1, r = nx - 2;
    int base = query(nx - 1);
    while (l <= r) {
        int mid = (l + r) >> 1;
        int now = query(mid);
        if (now == base)
            r = mid - 1;
        else {
            if (query(mid + 1) == base)
                return mid + 1;
            l = mid + 1;
        }
    }
    return 0; // 处理未找到解的情况
}

int hrlt(int nx) {
    int l = nx + 1, r = cnt;
    int base = query(nx);
    while (l <= r) {
        int mid = (l + r) >> 1;
        int now = query(mid);
        if (now == base)
            l = mid + 1;
        else {
            if (query(mid - 1) == base)
                return mid;
            r = mid - 1;
        }
    }
    return 0; // 处理未找到解的情况
}

int dx(const void *a, const void *b) {
    return (((OP *)a)->opt != 4 && ((OP *)b)->opt != 4) ? (((OP *)a)->x - ((OP *)b)->x) :
           ((((OP *)a)->opt == 4 && ((OP *)b)->opt == 4) ? (((OP *)a)->x - ((OP *)b)->x) :
                                                            (((OP *)b)->opt == 4 ? 1 : -1));
}

int fix(const void *a, const void *b) {
    return ((OP *)a)->id - ((OP *)b)->id;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        op[i].id = i;
        scanf("%d%d", &op[i].opt, &op[i].x);
    }

    qsort(op + 1, n, sizeof(OP), dx);

    op[0].x = op[1].x - 1;
    for (int i = 1; i <= n; ++i) {
        if (op[i].opt == 4)
            break;
        if (op[i].x != op[i - 1].x)
            f[++cnt] = op[i].x;
        op[i].nx = cnt;
    }

    qsort(op + 1, n, sizeof(OP), fix);

    for (int i = 1; i <= n; ++i) {
        int opt = op[i].opt;
        int k = op[i].x;
        int nx = op[i].nx;

        if (opt == 1) {
            add(nx, 1);
            ++paper[nx];
        }

        if (opt == 2) {
            if (paper[nx]) {
                add(nx, -1);
                --paper[nx];
            }
        }

        if (opt == 3)
            printf("%d\n", query(nx - 1) + 1);

        if (opt == 4)
            printf("%d\n", f[ask(k)]);

        if (opt == 5)
            printf("%d\n", f[lrht(nx)]);

        if (opt == 6)
            printf("%d\n", f[hrlt(nx)]);
    }

    return 0;
}

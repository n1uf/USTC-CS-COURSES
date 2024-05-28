#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 105
#define M 5005
#define INF 0x3f3f3f3f3f3f3f3fLL

int tot = 1;
int head[N];
int edge[M << 1], nxt[M << 1], val[M << 1];
int d[N];

void add(int u, int v, int c) {
    edge[++tot] = v, val[tot] = c, nxt[tot] = head[u], head[u] = tot;
    edge[++tot] = u, val[tot] = 0, nxt[tot] = head[v], head[v] = tot;
}

int bfs(int s, int t) {
    int queue[N];
    int front = 0, rear = 0;
    queue[rear++] = s;
    memset(d, 0, sizeof(d));
    d[s] = 1;

    while (front < rear) {
        int now = queue[front++];
        for (int i = head[now], go; go = edge[i]; i = nxt[i]) {
            if (val[i] <= 0 || d[go]) 
                continue;
            d[go] = d[now] + 1;
            if (go == t)
                return 1;
            queue[rear++] = go;
        }
    }
    return 0;
}

long long dinic(int now, int t, long long flow) {
    if (now == t)
        return flow;
    long long res = flow;
    int k;
    for (int i = head[now], go; (go = edge[i]) && res; i = nxt[i]) {
        if (d[go] != d[now] + 1 || val[i] <= 0)
            continue;
        k = dinic(go, t, res < val[i] ? res : val[i]);
        if (!k)
            d[go] = 0;
        val[i] -= k;
        val[i ^ 1] += k;
        res -= k;
    }
    return flow - res;
}

int main() {
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);

    for (int i = 1, u, v, c; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &c);
        add(u, v, c);
    }

    long long maxflow = 0;
    long long flow;

    while (bfs(s, t)) {
        while ((flow = dinic(s, t, INF))) {
            maxflow += flow;
        }
    }

    printf("%lld", maxflow);

    return 0;
}

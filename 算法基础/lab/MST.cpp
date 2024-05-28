#include <stdio.h>
#include <stdlib.h>

#define MAXN 5001
#define MAXM 100001

struct Edge{
    int u;
    int v;
    int weight;
};

int CompareEdges(const void *a, const void *b)
{
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

int FindSet(int node, int parent[])
{
    if(parent[node] == node)
        return node;
    return parent[node] = FindSet(parent[node], parent);
}

void UnionSets(int u, int v, int parent[])
{
    int uRoot = FindSet(u, parent);
    int vRoot = FindSet(v, parent);
    parent[vRoot] = uRoot;
}

int Calculate(struct Edge edges[], int n, int m)
{
    qsort(edges, m, sizeof(struct Edge), CompareEdges);

    int parent[n + 1];
    for(int i = 1; i < n + 1; i ++) // 初始化
        parent[i] = i;
    
    int MSTweight = 0;
    int Edgesnum = 0;

    for(int i = 0; i < m; i ++)
    {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        if(FindSet(u, parent) != FindSet(v, parent))
        {
            MSTweight += weight;
            UnionSets(u, v, parent);
            Edgesnum ++;
        }

        if(Edgesnum == n - 1)
            break;
    }

    if(Edgesnum != n - 1)
        return -1;

    return MSTweight;
}

int main()
{
    int n = 0;
    int m = 0;
    scanf("%d%d", &n, &m);
    struct Edge edges[m];
    for(int i = 0; i < m; i ++)
    {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    int MSTweight = Calculate(edges, n, m);
    printf("%d\n", MSTweight);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 501

int graph[MAXN][MAXN];
int match[MAXN];
bool visited[MAXN];

bool dfs(int u, int N)
{
    for(int v = 0; v < N; v ++)
    {
        if(graph[u][v] && !visited[v])
        {
            visited[v] = true;
            if(match[v] == -1 || dfs(match[v], N))
            {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int hungarian(int N)
{
    int cnt = 0;
    memset(match, -1, sizeof(match));
    for(int i = 0; i < N; i ++)
    {
        memset(visited, false, sizeof(visited));
        if(dfs(i, N))
            cnt ++;
    }
    return cnt;
}

int main()
{
    int N = 0, M = 0, E = 0;
    scanf("%d%d%d", &N, &M, &E);

    memset(graph, 0, sizeof(graph));

    for(int i = 0; i < E; i ++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        x --;
        y --;
        graph[x][y] = 1;
    }

    int MaxMatching = hungarian(N);
    printf("%d\n", MaxMatching);

    return 0;
}

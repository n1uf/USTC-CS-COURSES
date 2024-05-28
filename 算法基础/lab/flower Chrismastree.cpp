#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10001

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    int noDecor;
    int withDecor;
} DP;

Node* graph[MAX_N];
int values[MAX_N];
DP dp[MAX_N];

void initGraph(int n) {
    for (int i = 1; i <= n; i++) {
        graph[i] = NULL;
    }
}

void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = v;
    newNode->next = graph[u];
    graph[u] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->value = u;
    newNode->next = graph[v];
    graph[v] = newNode;
}

void dfs(int node, int parent) {
    for (Node* current = graph[node]; current != NULL; current = current->next) {
        int child = current->value;
        if (child != parent) {
            dfs(child, node);
            dp[node].noDecor += (dp[child].noDecor > dp[child].withDecor) ? dp[child].noDecor : dp[child].withDecor;
            dp[node].withDecor += dp[child].noDecor;
        }
    }
    dp[node].withDecor += values[node - 1];
}

int maxBeautyValue(int n) {
    dfs(1, 0);
    return (dp[1].noDecor > dp[1].withDecor) ? dp[1].noDecor : dp[1].withDecor;
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &values[i]);
    }

    initGraph(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    int result = maxBeautyValue(N);
    printf("%d\n", result);

    return 0;
}

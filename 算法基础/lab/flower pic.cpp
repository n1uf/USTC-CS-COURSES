#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 1005

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    struct Node* adjList[MAXN];
};

// 初始化图结构
void initGraph(struct Graph* graph, int N) {
    memset(graph->adjList, 0, sizeof(graph->adjList));
}

// 释放图结构的内存
void freeGraph(struct Graph* graph, int N) {
    for (int i = 1; i <= N; i++) {
        struct Node* current = graph->adjList[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

// 添加边到图
void addEdge(struct Graph* graph, int x, int y) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = y;
    newNode->next = graph->adjList[x];
    graph->adjList[x] = newNode;
}

// 使用BFS计算从顶点1到其他每个点的最短路的数量
void calculateShortestPaths(int N, int M, int edges[][2], int shortestPaths[]) {
    struct Graph graph;
    initGraph(&graph, N);

    // 构建图
    for (int i = 0; i < M; i++) {
        int x = edges[i][0];
        int y = edges[i][1];
        addEdge(&graph, x, y);
        addEdge(&graph, y, x);
    }

    int distances[MAXN];
    int count[MAXN];

    memset(distances, -1, sizeof(distances));
    memset(count, 0, sizeof(count));

    int queue[MAXN], front = 0, rear = -1;
    queue[++rear] = 1;
    distances[1] = 0;
    count[1] = 1;

    // BFS遍历图
    while (front <= rear) {
        int curr = queue[front++];
        struct Node* current = graph.adjList[curr];

        while (current != NULL) {
            int neighbor = current->vertex;

            if (distances[neighbor] == -1) {
                queue[++rear] = neighbor;
                distances[neighbor] = distances[curr] + 1;
                count[neighbor] = count[curr];
            } else if (distances[neighbor] == distances[curr] + 1) {
                count[neighbor] = (count[neighbor] + count[curr]) % MOD;
            }

            current = current->next;
        }
    }

    // 更新最短路的数量
    for (int i = 2; i <= N; i++) {
        shortestPaths[i] = count[i];
    }

    // 释放图结构的内存
    freeGraph(&graph, N);
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int edges[MAXN][2];

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &edges[i][0], &edges[i][1]);
    }

    int shortestPaths[MAXN];

    calculateShortestPaths(N, M, edges, shortestPaths);

    for (int i = 2; i <= N; i++) {
        printf("%d\n", shortestPaths[i]);
    }

    return 0;
}

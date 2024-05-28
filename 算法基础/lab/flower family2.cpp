#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MOD 1000000007
#define MAXN 5001

struct Node
{
    int vertex;
    struct Node* next;
};

struct Graph
{
    struct Node* adjList[MAXN];
    int indegree[MAXN];
    int dp[MAXN];
};

void initGraph(struct Graph* graph, int N) 
{
    for (int i = 1; i <= N; ++i)
    {
        graph->adjList[i] = NULL;
        graph->indegree[i] = 0;
        graph->dp[i] = 0;
    }
}

void freeGraph(struct Graph* graph, int N) 
{
    for (int i = 1; i <= N; ++i) 
    {
        struct Node* current = graph->adjList[i];
        while (current != NULL) 
        {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

void addEdge(struct Graph* graph, int x, int y) 
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = y;
    newNode->next = graph->adjList[x];
    graph->adjList[x] = newNode;
    graph->indegree[y]++;
}

int calculateFamilyChains(struct Graph* graph, int N) 
{
    int totalChains = 0;
    int queue[MAXN];
    int front = 0, rear = -1;

    for (int i = 1; i <= N; ++i) 
    {
        if (graph->indegree[i] == 0) 
        {
            rear++;
            queue[rear] = i;
            graph->dp[i] = 1;
        }
    }

    while (front <= rear) 
    {
        int x = queue[front++];
        struct Node* current = graph->adjList[x];

        while (current != NULL) 
        {
            int y = current->vertex;
            graph->indegree[y]--;
            graph->dp[y] = (graph->dp[y] + graph->dp[x]) % MOD;

            if (graph->indegree[y] == 0) 
            {
                rear++;
                queue[rear] = y;
            }

            current = current->next;
        }
    }

    for (int i = 1; i <= N; ++i) 
    {
        if (graph->adjList[i] == NULL) 
        {
            totalChains = (totalChains + graph->dp[i]) % MOD;
        }
    }

    return totalChains;
}

int main()
{
    int N, M;
    scanf("%d%d", &N, &M);

    struct Graph graph;
    initGraph(&graph, N);

    for (int i = 0; i < M; ++i) 
    {
        int x, y;
        scanf("%d%d", &x, &y);
        addEdge(&graph, x, y);
    }

    int result = calculateFamilyChains(&graph, N);

    printf("%d\n", result);

    freeGraph(&graph, N);

    return 0;
}

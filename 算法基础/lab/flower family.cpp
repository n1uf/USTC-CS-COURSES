#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
    memset(graph->adjList, 0, sizeof(graph->adjList));
    memset(graph->indegree, 0, sizeof(graph->indegree));
    memset(graph->dp, 0, sizeof(graph->dp));
}

void freeGraph(struct Graph* graph, int N) 
{
    for (int i = 1; i <= N; i++) 
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

int CalculateFamilyChains(int N, int M, int relationships[][2])
{
    struct Graph graph;
    initGraph(&graph, N);

    for(int i = 0; i < M; i ++)
    {
        int x = relationships[i][0];
        int y = relationships[i][1];
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->vertex = y;
        newNode->next = graph.adjList[x];
        graph.adjList[x] = newNode;
        graph.indegree[y] ++;
    }

    int TotalChains = 0;
    int Queue[MAXN];
    int front = 0, rear = -1;

    for(int i = 1; i <= N; i ++)
    {
        if(graph.indegree[i] == 0)
        {
            rear ++;
            Queue[rear] = i;
            graph.dp[i] = 1;
        }
    }

    while(front <= rear)
    {
        int x = Queue[front];
        front ++;

        struct Node* current = graph.adjList[x];
        while (current != NULL) 
        {
            int y = current->vertex;
            graph.indegree[y]--; 
            graph.dp[y] = (graph.dp[y] + graph.dp[x]) % MOD; 

            if (graph.indegree[y] == 0) 
            {
                rear ++;
                Queue[rear] = y;
            }

            current = current->next;
        }
    }

    for(int i = 1; i <= N; i ++)
    {
        if(graph.adjList[i] == NULL)
            TotalChains = (TotalChains + graph.dp[i]) % MOD;
    }

    freeGraph(&graph, N);

    return TotalChains;
}

int main()
{
    int N = 0;
    int M = 0;
    scanf("%d%d", &N, &M);

    int relationships[MAXN][2];

    for(int i = 0; i < M; i ++)
    {
        scanf("%d%d", &relationships[i][0], &relationships[i][1]);
    }

    int result = CalculateFamilyChains(N, M, relationships);

    printf("%d\n", result);

    return 0;
}
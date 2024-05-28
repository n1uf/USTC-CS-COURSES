#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <cstring>
using namespace std;

#define MAX_N 2500
#define MAX_M 6200

struct Edge {
    int vertex;
    long long weight;
};

struct Graph {
    std::vector<Edge> edges[MAX_N + 1];
};

void addEdge(Graph& graph, int x, int y, long long z) {
    graph.edges[x].push_back({y, z});
    graph.edges[y].push_back({x, z});
}

long long dijkstra(Graph& graph, int start, int end) {
    char visited[MAX_N + 1] = {0};
    long long distances[MAX_N + 1];

    for (int i = 1; i <= MAX_N; i++) {
        distances[i] = std::numeric_limits<long long>::max();
    }

    distances[start] = 0;

    // Priority queue for selecting the minimum distance vertex
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int current_vertex = pq.top().second;
        pq.pop();

        if (visited[current_vertex]) {
            continue;
        }

        visited[current_vertex] = 1;

        for (const Edge& edge : graph.edges[current_vertex]) {
            int neighbor = edge.vertex;
            long long weight = edge.weight;
            long long distance = distances[current_vertex] + weight;

            if (distance < distances[neighbor]) {
                distances[neighbor] = distance;
                pq.push({distance, neighbor});
            }
        }
    }

    return distances[end];
}

int main() {
    int N, M, S, T;
    std::cin >> N >> M >> S >> T;

    Graph graph;

    for (int i = 0; i < M; i++) {
        int x, y;
        long long z;
        std::cin >> x >> y >> z;
        addEdge(graph, x, y, z);
    }

    long long result = dijkstra(graph, S, T);
    std::cout << result << std::endl;

    return 0;
}

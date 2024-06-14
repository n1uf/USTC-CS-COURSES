#include <iostream>
#include <vector>
#include <limits>
#include <omp.h>

const int INF = std::numeric_limits<int>::max();

struct Edge {
    int u, v, w;
};

void bellman_ford(int V, int E, std::vector<Edge>& edges, int src) {
    std::vector<int> dist(V, INF);
    dist[src] = 0;

    // OpenMP 并行
    for (int i = 1; i <= V - 1; i++) {
        int updated = 0;
#pragma omp parallel for reduction(+ : updated)
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if (dist[u] != INF && dist[u] + w < dist[v]) {
#pragma omp critical
                {
                    dist[v] = dist[u] + w;
                }
                updated++;
            }
            if (dist[v] != INF && dist[v] + w < dist[u]) {
#pragma omp critical
                {
                    dist[u] = dist[v] + w;
                }
                updated++;
            }
        }
        // 没更新
        if (updated == 0)
            break;
    }

    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) {
            std::cout << "INF ";
        } else {
            std::cout << dist[i] << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    // 线程数
    omp_set_num_threads(1);

    int V, E, src;
    std::cin >> V >> E >> src;

    std::vector<Edge> edges(E);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }

    bellman_ford(V, E, edges, src);

    return 0;
}
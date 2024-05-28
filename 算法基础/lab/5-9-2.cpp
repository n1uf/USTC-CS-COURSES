#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

const int MAX_N = 2505;
const int INF = INT_MAX;

struct Edge {
    int to;
    string weight;
};

struct Graph {
    std::vector<Edge> edges[MAX_N + 1];
};

string dist[MAX_N];
bool visited[MAX_N];

void addEdge(Graph& graph, int x, int y, string z) {
    graph.edges[x].push_back({y, z});
    graph.edges[y].push_back({x, z});
}

std::string addStrings(const std::string& num1, const std::string& num2) {
    std::string result;
    
    int carry = 0;
    int i = num1.length() - 1;
    int j = num2.length() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j--] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;

        // 将当前位的数字添加到结果字符串的前面
        result = char(sum % 10 + '0') + result;
    }

    return result;
}

int compareStrings(const std::string& num1, const std::string& num2) {
    // 如果字符串长度不相等，直接返回比较结果
    if (num1.length() < num2.length()) {
        return 1;
    } else if (num1.length() > num2.length()) {
        return -1;
    }

    // 如果字符串长度相等，逐位比较
    for (int i = 0; i < num1.length(); ++i) {
        if (num1[i] < num2[i]) {
            return 1;
        } else if (num1[i] > num2[i]) {
            return -1;
        }
    }

    // 如果所有位都相等，则两个数字相等
    return 0;
}

string dijkstra(Graph& graph, int start, int n) {
    for (int i = 1; i <= n; ++i) {
        dist[i] = "1" + string(99, '0');  // 100位的字符串表示无穷大
        visited[i] = false;
    }

    dist[start] = "0";

    priority_queue<pair<string, int>, vector<pair<string, int>>, greater<pair<string, int>>> pq;
    pq.push({dist[start], start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        for (const Edge& edge : graph.edges[u]) {
            int v = edge.to;
            string w = edge.weight;

            if (!visited[v] && compareStrings(addStrings(dist[u], w) , dist[v])) {
                dist[v] = addStrings(dist[u] , w);
                pq.push({dist[v], v});
            }
        }
    }

    return dist[n];
}

int main() {
    int N, M, S, T;
    cin >> N >> M >> S >> T;

    Graph graph;

    for (int i = 0; i < M; ++i) {
        int x, y;
        string z;
        cin >> x >> y >> z;
        addEdge(graph, x, y, z);
    }

    string result = dijkstra(graph, S, T);

    cout << result << endl;

    return 0;
}

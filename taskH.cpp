#include <iostream>
#include <limits>
#include <queue>
#include <vector>

struct Edge {
  int to;
  int cost;
};

long double MinCost(int n, int m, int k, int s, int f,
                    std::vector<std::vector<Edge>> graph) {
  constexpr int kInf = std::numeric_limits<int>::max();
  std::vector<std::vector<long double>> dp(n + 1, std::vector<long double>(k + 1, kInf));
  dp[s][0] = 0;
  for (int j = 1; j <= k; j++) {
    for (int u = 1; u <= n; u++) {
      for (auto& edge : graph[u]) {
        int v = edge.to;
        long double cost = edge.cost;
        if (dp[u][j - 1] != kInf) {
          dp[v][j] = std::min(dp[v][k], dp[u][j - 1] + cost);
        }
      }
    }
  }
  long double min_cost = kInf;
  for (int j = 0; j <= k; j++) {
    min_cost = std::min(min_cost, dp[f][j]);
  }
  if (min_cost == kInf) {
    return -1;
  }
  return min_cost;
}

int main() {
  int n, m, k, s, f;
  std::cin >> n >> m >> k >> s >> f;
  std::vector<std::vector<Edge>> graph(n + 1);
  for (int i = 0; i < m; i++) {
    int from, to, cost;
    std::cin >> from >> to >> cost;
    graph[from].push_back({to, cost});
  }
  long double cost = MinCost(n, m, k, s, f, graph);
  std::cout << cost << std::endl;
  return 0;
}

#include <iostream>
#include <limits>
#include <queue>
#include <vector>

struct Edge {
  int to;
  int cost;
};

class Graph {
 private:
  int vertices_, edges_;
  std::vector<std::vector<Edge>> graph_;

 public:
  Graph(size_t v, size_t e) : vertices_(v), edges_(e) { graph_.resize(v + 1); }
  int NumOfVer() const { return vertices_; }
  void AddEdge() {
    int from, to, cost;
    for (int i = 0; i < edges_; i++) {
      std::cin >> from >> to >> cost;
      graph_[from].push_back({to, cost});
    }
  }
  std::vector<Edge> AdjEdges(size_t v) const { return graph_[v]; }
};

double MinCost(int n, int k, int s, int f, Graph& graph) {
  constexpr int kInf = std::numeric_limits<int>::max();
  std::vector<std::vector<double>> dp(n + 1, std::vector<double>(k + 1, kInf));
  dp[s][0] = 0;
  for (int j = 1; j <= k; j++) {
    for (int u = 1; u <= n; u++) {
      for (auto& edge : graph.AdjEdges(u)) {
        int v = edge.to;
        double cost = edge.cost;
        if (dp[u][j - 1] != kInf) {
          dp[v][j] = std::min(dp[v][j], dp[u][j - 1] + cost);
        }
      }
    }
  }
  double min_cost = kInf;
  for (int j = 1; j <= k; j++) {
    min_cost = std::min(min_cost, dp[f][j]);
  }
  if (s == f) {
    return 0;
  }
  if (min_cost == kInf) {
    return -1;
  }
  return min_cost;
}

int main() {
  int n, m, k, s, f;
  std::cin >> n >> m >> k >> s >> f;
  Graph graph(n, m);
  graph.AddEdge();
  double cost = MinCost(n, k, s, f, graph);
  std::cout << cost << std::endl;
  return 0;
}

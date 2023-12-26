#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

struct Edge {
  int to;
  double prob;
};

class Graph {
 private:
  int vertices_, edges_;
  std::vector<std::vector<Edge>> graph_;

 public:
  Graph(size_t v, size_t e) : vertices_(v), edges_(e) { graph_.resize(v + 1); }
  int NumOfVertices() const { return vertices_; }
  void AddEdge() {
    int u, v;
    double p;
    for (int i = 0; i < edges_; i++) {
      std::cin >> u >> v >> p;
      graph_[u].push_back({v, p / 100.0});
      graph_[v].push_back({u, p / 100.0});
    }
  }
  std::vector<Edge> AdjEdges(size_t v) const { return graph_[v]; }
};

void Relax(Graph& graph, int u, std::vector<double>& dist,
           std::priority_queue<std::pair<double, int>,
                               std::vector<std::pair<double, int>>,
                               std::greater<std::pair<double, int>>>& pq) {
  for (Edge& e : graph.AdjEdges(u)) {
    if (dist[u] + e.prob - dist[u] * e.prob < dist[e.to]) {
      dist[e.to] = dist[u] + e.prob - dist[u] * e.prob;
      pq.push({dist[e.to], e.to});
    }
  }
}

double MinProbability(int n, int start, int final, Graph& graph) {
  std::vector<double> dist(n + 1, std::numeric_limits<int>::max());
  dist[start] = 0;
  std::priority_queue<std::pair<double, int>,
                      std::vector<std::pair<double, int>>,
                      std::greater<std::pair<double, int>>>
      pq;
  pq.push({0, start});
  while (!pq.empty()) {
    double d = pq.top().first;
    int u = pq.top().second;
    pq.pop();
    if (d > dist[u]) {
      continue;
    }
    Relax(graph, u, dist, pq);
  }
  return dist[final];
}

int main() {
  int n, m, s, f;
  std::cin >> n >> m >> s >> f;
  Graph graph(n, m);
  graph.AddEdge();
  std::cout << std::setprecision(2) << MinProbability(n, s, f, graph)
            << std::endl;
  return 0;
}

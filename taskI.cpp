#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

struct Edge {
  int to;
  double prob;
};

double Probability(int n, int s, int f, std::vector<std::vector<Edge>> adj) {
  std::vector<double> dist(n + 1, std::numeric_limits<int>::max());
  dist[s] = 0;
  std::priority_queue<std::pair<double, int>,
                      std::vector<std::pair<double, int>>,
                      std::greater<std::pair<double, int>>>
      pq;
  pq.push({0, s});
  while (!pq.empty()) {
    double d = pq.top().first;
    int u = pq.top().second;
    pq.pop();
    if (d > dist[u]) {
      continue;
    }
    for (Edge& e : adj[u]) {
      if (dist[u] + e.prob - dist[u] * e.prob < dist[e.to]) {
        dist[e.to] = dist[u] + e.prob - dist[u] * e.prob;
        pq.push({dist[e.to], e.to});
      }
    }
  }
  return dist[f];
}

int main() {
  int n, m, s, f;
  std::cin >> n >> m >> s >> f;

  std::vector<std::vector<Edge>> adj(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    double p;
    std::cin >> u >> v >> p;
    adj[u].push_back({v, p / 100.0});
    adj[v].push_back({u, p / 100.0});
  }

  std::cout << std::setprecision(2) << Probability(n, s, f, adj) << std::endl;

  return 0;
}

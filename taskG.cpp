#include <iostream>
#include <queue>
#include <vector>

long double Dijkstra(int a, int b, int m, int x, int y) {
  constexpr int kInf = std::numeric_limits<int>::max();
  std::vector<long double> dist(m, kInf);
  dist[x] = 0;
  std::priority_queue<std::pair<long double, uint64_t>,
                      std::vector<std::pair<long double, uint64_t>>,
                      std::greater<std::pair<long double, uint64_t>>>
      min_heap;
  min_heap.push({0, x});
  while (!min_heap.empty()) {
    uint64_t u = min_heap.top().second;
    long double d = min_heap.top().first;
    min_heap.pop();
    if (d > dist[u]) {
      continue;
    }
    int v = (u + 1) % m;
    if (dist[u] + a < dist[v]) {
      dist[v] = dist[u] + a;
      min_heap.push({dist[v], v});
    }
    v = ((u * u) % m + 1) % m;
    if (dist[u] + b < dist[v]) {
      dist[v] = dist[u] + b;
      min_heap.push({dist[v], v});
    }
  }
  return dist[y];
}

int main() {
  int a, b, m, x, y;
  std::cin >> a >> b >> m >> x >> y;

  long double result = Dijkstra(a, b, m, x, y);

  std::cout << result << std::endl;

  return 0;
}

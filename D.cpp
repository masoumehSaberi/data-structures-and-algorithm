#include <climits>
#include <iostream>
#include <queue>
#include <vector>

class Graph {
 private:
  int vertices_, edges_;
  std::vector<std::vector<int>> graph_;

 public:
  Graph(int v, int e) : vertices_(v), edges_(e) { graph_.resize(v); }
  void AddEdge() {
    int v, u;
    for (int i = 0; i < edges_; i++) {
      std::cin >> v >> u;
      graph_[v - 1].push_back(u - 1);
      graph_[u - 1].push_back(v - 1);
    }
  }
  std::vector<int> AdjEdges(int v) const { return graph_[v]; }
};

void BFS(Graph& graph, int n, int source, std::vector<int>& distance) {
  std::queue<int> q;
  q.push(source);
  std::vector<bool> visited(n, false);
  visited[source] = true;
  distance[source] = 0;
  while (!q.empty()) {
    int k = q.front();
    q.pop();
    for (auto i : graph.AdjEdges(k)) {
      if (!visited[i]) {
        q.push(i);
        distance[i] = distance[k] + 1;
        visited[i] = true;
      }
    }
  }
}

int PathLength(Graph& graph, int n, int src1, int src2, int dest) {
  constexpr int kMaxInt = std::numeric_limits<int>::max();
  std::vector<int> leon_dist(n, kMaxInt), matilda_dist(n, kMaxInt),
      milk_dist(n, kMaxInt);
  BFS(graph, n, src1, leon_dist);
  BFS(graph, n, src2, matilda_dist);
  BFS(graph, n, dest, milk_dist);
  int answer = kMaxInt;
  for (int i = 0; i < n; i++) {
    if (leon_dist[i] + matilda_dist[i] + milk_dist[i] < answer) {
      answer = leon_dist[i] + matilda_dist[i] + milk_dist[i];
    }
  }
  return answer;
}

int main() {
  int n, m, src1, src2, dest;
  std::cin >> n >> m;
  std::cin >> src1 >> src2 >> dest;
  Graph graph(n, m);
  graph.AddEdge();
  std::cout << PathLength(graph, n, src1 - 1, src2 - 1, dest - 1) << std::endl;
  return 0;
}

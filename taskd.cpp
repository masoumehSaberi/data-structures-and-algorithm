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
  std::queue<int> nodes_que;
  nodes_que.push(source);
  std::vector<bool> visited(n, false);
  visited[source] = true;
  distance[source] = 0;
  while (!nodes_que.empty()) {
    int k = nodes_que.front();
    nodes_que.pop();
    for (auto i : graph.AdjEdges(k)) {
      if (!visited[i]) {
        nodes_que.push(i);
        distance[i] = distance[k] + 1;
        visited[i] = true;
      }
    }
  }
}

int PathLength(Graph& graph, int vertices, int leon, int matilda, int milk) {
  constexpr int kMaxInt = std::numeric_limits<int>::max();
  std::vector<int> leon_dist(vertices, kMaxInt),
      matilda_dist(vertices, kMaxInt), milk_dist(vertices, kMaxInt);
  BFS(graph, vertices, leon, leon_dist);
  BFS(graph, vertices, matilda, matilda_dist);
  BFS(graph, vertices, milk, milk_dist);
  int answer = kMaxInt;
  for (int i = 0; i < vertices; i++) {
    if (leon_dist[i] + matilda_dist[i] + milk_dist[i] < answer) {
      answer = leon_dist[i] + matilda_dist[i] + milk_dist[i];
    }
  }
  return answer;
}

int main() {
  int vertices, edges, leon, matilda, milk;
  std::cin >> vertices >> edges;
  std::cin >> leon >> matilda >> milk;
  Graph graph(vertices, edges);
  graph.AddEdge();
  std::cout << PathLength(graph, vertices, leon - 1, matilda - 1, milk - 1)
            << std::endl;
  return 0;
}

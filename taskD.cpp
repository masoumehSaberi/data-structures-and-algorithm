#include <iostream>
#include <queue>
#include <vector>

void AddEdge(std::vector<int>* graph, int u, int v) {
  graph[u].push_back(v);
  graph[v].push_back(u);
}

void BFS(std::vector<int>* graph, int n, int source,
         std::vector<int>& distance) {
  std::queue<int> q;
  q.push(source);
  std::vector<bool> visited(n, false);
  visited[source] = true;
  distance[source] = 0;
  while (!q.empty()) {
    int k = q.front();
    q.pop();
    for (auto i : graph[k]) {
      if (!visited[i]) {
        q.push(i);
        distance[i] = distance[k] + 1;
        visited[i] = true;
      }
    }
  }
}

int PathLength(std::vector<int>* graph, int n, int* sources) {
  std::vector<int> leon_dist(n, std::numeric_limits<int>::max()),
      matilda_dist(n, std::numeric_limits<int>::max()),
      milk_dist(n, std::numeric_limits<int>::max());
  BFS(graph, n, sources[0], leon_dist);
  BFS(graph, n, sources[1], matilda_dist);
  BFS(graph, n, sources[2], milk_dist);
  int answer = std::numeric_limits<int>::max();
  for (int i = 0; i < n; i++) {
    if ((leon_dist[i] + matilda_dist[i] + milk_dist[i]) < answer) {
      answer = leon_dist[i] + matilda_dist[i] + milk_dist[i];
    }
  }
  return answer;
}

int main() {
  int n, m, src1, src2, dest, v1, v2;
  std::cin >> n;
  std::cin >> m;
  std::cin >> src1 >> src2 >> dest;
  std::vector<int>* graph;
  graph = new std::vector<int>[n + 1];
  for (int i = 0; i < m; i++) {
    std::cin >> v1 >> v2;
    AddEdge(graph, v1 - 1, v2 - 1);
  }
  int sources[] = {src1 - 1, src2 - 1, dest - 1};
  std::cout << PathLength(graph, n, sources) << std::endl;
  delete[] graph;
  return 0;
}

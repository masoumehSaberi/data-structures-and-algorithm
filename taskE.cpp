#include <iostream>
#include <list>
#include <stack>

class Graph {
  int v_;
  std::list<int>* adj_;
  std::list<int>* reverse_adj_;
  bool IsCyclicUntil(int v, bool* visited, bool* rec_stack);
  void DFS1(int u, bool* visited1);
  void DFS2(int u, bool* visited2);
  void TopologicalSortUntil(int v, bool* visited, std::stack<int>& stack);

 public:
  Graph(int v);
  void AddEdge(int v, int w);
  bool IsCyclic();
  bool IsConnected();
  std::stack<int> TopologicalSort();
  ~Graph();
};

Graph::Graph(int v) {
  this->v_ = v;
  adj_ = new std::list<int>[v_];
  reverse_adj_ = new std::list<int>[v_];
}

Graph::~Graph() {
  delete[] adj_;
  delete[] reverse_adj_;
}

void Graph::AddEdge(int v, int w) {
  adj_[v].push_back(w);
  reverse_adj_[w].push_back(v);
}

bool Graph::IsCyclicUntil(int v, bool* visited, bool* rec_stack) {
  if (!visited[v]) {
    visited[v] = true;
    rec_stack[v] = true;
    std::list<int>::iterator i;
    for (i = adj_[v].begin(); i != adj_[v].end(); ++i) {
      if (!visited[*i] && IsCyclicUntil(*i, visited, rec_stack)) {
        return true;
      }
      if (rec_stack[*i]) {
        return true;
      }
    }
  }
  rec_stack[v] = false;
  return false;
}

bool Graph::IsCyclic() {
  bool* visited = new bool[v_];
  bool* rec_stack = new bool[v_];
  for (int i = 0; i < v_; i++) {
    visited[i] = false;
    rec_stack[i] = false;
  }
  for (int i = 0; i < v_; i++) {
    if (!visited[i] && IsCyclicUntil(i, visited, rec_stack)) {
      delete[] visited;
      delete[] rec_stack;
      return true;
    }
  }
  delete[] visited;
  delete[] rec_stack;
  return false;
}

void Graph::DFS1(int u, bool* visited1) {
  visited1[u] = true;
  for (auto i : adj_[u]) {
    if (!visited1[i]) {
      DFS1(i, visited1);
    }
  }
}

void Graph::DFS2(int u, bool* visited2) {
  visited2[u] = true;
  for (auto i : reverse_adj_[u]) {
    if (!visited2[i]) {
      DFS2(i, visited2);
    }
  }
}

bool Graph::IsConnected() {
  bool* visited1 = new bool[v_];
  bool* visited2 = new bool[v_];
  for (int u = 0; u < v_; u++) {
    for (int i = 0; i < v_; i++) {
      visited1[i] = false;
      visited2[i] = false;
    }
    DFS1(0, visited1);
    DFS1(0, visited2);
    for (int i = 0; i < v_; i++) {
      if (!visited1[i] && !visited2[i]) {
        delete[] visited1;
        delete[] visited2;
        return false;
      }
    }
  }
  delete[] visited1;
  delete[] visited2;
  return true;
}

void Graph::TopologicalSortUntil(int v, bool* visited, std::stack<int>& stack) {
  visited[v] = true;

  std::list<int>::iterator i;
  for (i = adj_[v].begin(); i != adj_[v].end(); ++i) {
    if (!visited[*i]) {
      TopologicalSortUntil(*i, visited, stack);
    }
  }
  stack.push(v);
}

std::stack<int> Graph::TopologicalSort() {
  std::stack<int> stck;
  bool* visited = new bool[v_];
  for (int i = 0; i < v_; i++) {
    visited[i] = false;
  }
  for (int i = 0; i < v_; i++) {
    if (!visited[i]) {
      TopologicalSortUntil(i, visited, stck);
    }
  }
  delete[] visited;
  return stck;
}

int main() {
  int n, m, v1, v2;
  std::cin >> n;
  Graph g(n);
  std::cin >> m;
  for (int i = 0; i < m; i++) {
    std::cin >> v1;
    std::cin >> v2;
    g.AddEdge(v1, v2);
  }
  if (g.IsCyclic()) {
    std::cout << "NO" << std::endl;
  } else {
    std::cout << "YES" << std::endl;
    std::stack<int> order = g.TopologicalSort();
    while (!order.empty()) {
      std::cout << order.top() << " ";
      order.pop();
    }
  }
  std::cout << std::endl;
  return 0;
}

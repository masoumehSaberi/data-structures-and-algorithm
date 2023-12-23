#include <iostream>
#include <vector>

class Graph {
 private:
  size_t vertices_, edges_;
  std::vector<std::vector<size_t>> graph_, transpose_;

 public:
  Graph(size_t v, size_t e) : vertices_(v), edges_(e) {
    graph_.resize(v);
    transpose_.resize(v);
  }
  size_t NumOfVer() const { return vertices_; }
  void AddEdge() {
    size_t v, u;
    for (size_t i = 1; i <= edges_; i++) {
      std::cin >> v >> u;
      graph_[v - 1].push_back(u - 1);
      transpose_[u - 1].push_back(v - 1);
    }
  }
  std::vector<size_t> AdjEdges(size_t v) const { return graph_[v]; }
  std::vector<size_t> AdjEdgesTr(size_t v) const { return transpose_[v]; }
};

void DFS(Graph& graph, std::vector<size_t>& tin, std::vector<size_t>& tout,
         std::vector<char>& color, std::pair<size_t, size_t>& timer) {
  size_t v = timer.first;
  color[v] = 'g';
  tin[timer.first] = timer.second++;
  for (auto to : graph.AdjEdges(v)) {
    timer.first = to;
    if (color[to] == 'w') {
      DFS(graph, tin, tout, color, timer);
    }
  }
  tout[v] = timer.second++;
  tin.push_back(v);
  color[v] = 'b';
}

void ChangeId(size_t v, size_t comp, std::vector<size_t>& id, Graph& graph,
              std::vector<char>& color) {
  color[v] = 'g';
  id[v] = comp;
  for (auto to : graph.AdjEdgesTr(v)) {
    if (color[to] == 'w') {
      ChangeId(to, comp, id, graph, color);
    }
  }
  color[v] = 'b';
}

void CompairDeg(Graph& graph, size_t comp, std::vector<size_t>& id,
                std::vector<size_t>& indeg, std::vector<size_t>& outdeg) {
  indeg.resize(comp, 0);
  outdeg.resize(comp, 0);
  for (int v = 0; v < graph.NumOfVer(); ++v) {
    for (auto to : graph.AdjEdges(v)) {
      if (id[v] != id[to]) {
        indeg[id[to]]++;
        outdeg[id[v]]++;
      }
    }
  }
}

size_t MinEdge(Graph& graph, size_t v) {
  std::vector<size_t> tin(v), tout(v), id(v, -1), indeg(0), outdeg(0);
  std::vector<char> color(v, 'w'), color_tr(v, 'w');
  std::pair<size_t, size_t> timer = std::make_pair(0, 0);
  size_t compair = 0, sum_in = 0, sum_out = 0;
  for (int u = 0; u < v; ++u) {
    timer.first = u;
    if (color[u] == 'w') {
      DFS(graph, tin, tout, color, timer);
    }
  }
  for (int v = 2 * graph.NumOfVer() - 1; v >= graph.NumOfVer(); --v) {
    if (color_tr[tin[v]] == 'w') {
      ChangeId(tin[v], compair, id, graph, color_tr);
      ++compair;
    }
  }
  if (compair == 1) {
    return 0;
  }
  CompairDeg(graph, compair, id, indeg, outdeg);
  for (int i = 0; i < compair; ++i) {
    if (indeg[i] == 0) {
      ++sum_in;
    }
    if (outdeg[i] == 0) {
      ++sum_out;
    }
  }
  return std::max(sum_in, sum_out);
}

int main() {
  size_t v, e;
  std::cin >> v >> e;
  Graph graph(v, e);
  graph.AddEdge();
  if (e == 0) {
    std::cout << 0;
  } else if (v == 1 && e == 0) {
    std::cout << 0;
  } else {
    std::cout << MinEdge(graph, v);
  }
  return 0;
}

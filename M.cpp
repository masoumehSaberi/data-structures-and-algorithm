#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

void DFS(size_t v, size_t p, std::vector<std::vector<size_t>>& adj,
         std::vector<size_t>& tin, std::vector<size_t>& tout, size_t& timer,
         std::vector<std::vector<size_t>>& up, size_t& l) {
  tin[v] = ++timer;
  up[v][0] = p;
  for (size_t i = 1; i <= l; ++i) {
    up[v][i] = up[up[v][i - 1]][i - 1];
  }

  for (size_t u : adj[v]) {
    if (u != p) {
      DFS(u, v, adj, tin, tout, timer, up, l);
    }
  }
  tout[v] = ++timer;
}

bool IsAncestor(size_t u, size_t v, std::vector<size_t>& tin,
                std::vector<size_t>& tout) {
  return tin[u] <= tin[v] && tout[u] >= tout[v];
}

size_t LCA(size_t u, size_t v, std::vector<size_t>& tin,
           std::vector<size_t>& tout, std::vector<std::vector<size_t>>& up,
           size_t& l) {
  if (IsAncestor(u, v, tin, tout)) {
    return u;
  }
  if (IsAncestor(v, u, tin, tout)) {
    return v;
  }
  for (int i = l; i >= 0; --i) {
    if (!IsAncestor(up[u][i], v, tin, tout)) {
      u = up[u][i];
    }
  }
  return up[u][0];
}

void Preprocess(size_t n, size_t root, std::vector<std::vector<size_t>>& adj,
                std::vector<size_t>& tin, std::vector<size_t>& tout,
                std::vector<std::vector<size_t>>& up, size_t& l) {
  size_t timer = 0;
  up.assign(n, std::vector<size_t>(l + 1));
  DFS(root, root, adj, tin, tout, timer, up, l);
}

void AddEdge(std::vector<std::vector<size_t>>& tree, size_t u, size_t v) {
  tree[u].push_back(v);
  tree[v].push_back(u);
}

int main() {
  size_t n, m, p, a1, a2, x, y, z, a2i_1, a2i, v = 0, sum = 0;
  std::cin >> n >> m;
  size_t l = ceil(log2(n));
  std::vector<std::vector<size_t>> tree(n);
  std::vector<size_t> tin(n + 1), tout(n);
  std::vector<std::vector<size_t>> up;
  for (int i = 1; i < n; i++) {
    std::cin >> p;
    AddEdge(tree, i, p);
  }
  Preprocess(n + 1, 0, tree, tin, tout, up, l);
  std::cin >> a1 >> a2 >> x >> y >> z;
  for (size_t i = 0; i < m; i++) {
    v = LCA((a1 + v) % n, a2, tin, tout, up, l);
    sum += v;
    a2i_1 = (x * a1 + y * a2 + z) % n;
    a2i = (x * a2 + y * a2i_1 + z) % n;
    a1 = a2i_1;
    a2 = a2i;
  }
  std::cout << sum << std::endl;
  return 0;
}

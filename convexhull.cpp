#include <algorithm>
#include <iostream>
#include <vector>

typedef std::pair<long long, long long> Point;

bool Compair(Point& a, Point& b) {
  if (a.first == b.first) return a.second < b.second;
  return a.first < b.first;
}

long long Clockwise(Point& a, Point& b, Point& c) {
  long long p = a.first * (b.second - c.second) +
                b.first * (c.second - a.second) +
                c.first * (a.second - b.second);

  return p < 0ll;
}

long long C_Clockwise(Point& a, Point& b, Point& c) {
  long long p = a.first * (b.second - c.second) +
                b.first * (c.second - a.second) +
                c.first * (a.second - b.second);

  return p > 0ll;
}

std::vector<Point> ConvexHull(std::vector<Point>& vertices, long long n) {
  sort(vertices.begin(), vertices.end(), Compair);
  if (n <= 3) {
    return vertices;
  }
  Point point1 = vertices[0], point2 = vertices[n - 1];
  std::vector<Point> up, down;
  up.push_back(point1);
  down.push_back(point1);
  for (int i = 1; i < n; i++) {
    if (i == n - 1 || !C_Clockwise(point1, vertices[i], point2)) {
      while (up.size() > 1 &&
             C_Clockwise(up[up.size() - 2], up[up.size() - 1], vertices[i])) {
        up.pop_back();
      }
      up.push_back(vertices[i]);
    }
    if (i == n - 1 || !Clockwise(point1, vertices[i], point2)) {
      while (down.size() > 1 && Clockwise(down[down.size() - 2],
                                          down[down.size() - 1], vertices[i])) {
        down.pop_back();
      }
      down.push_back(vertices[i]);
    }
  }
  for (int i = down.size() - 2; i > 0; i--) {
    up.push_back(down[i]);
  }
  up.resize(unique(up.begin(), up.end()) - up.begin());
  return up;
}

bool IsInside(std::vector<Point> vertices, Point allies_coordinates) {
  vertices.push_back(allies_coordinates);
  vertices = ConvexHull(vertices, vertices.size());
  for (auto x : vertices) {
    if (x == allies_coordinates) {
      return false;
    }
  }
  return true;
}

bool CheckAllPoints(std::vector<Point> vertices) {
  long long num_allies;
  std::cin >> num_allies;
  Point allies_coordinates;
  bool result = true;
  for (int i = 0; i < num_allies; i++) {
    std::cin >> allies_coordinates.first >> allies_coordinates.second;
    if (IsInside(vertices, allies_coordinates) == false) {
      result = false;
    }
  }
  return result;
}

std::vector<Point> SetVertices() {
  long long num_vertices;
  std::cin >> num_vertices;
  std::vector<Point> vertices(num_vertices);
  for (int i = 0; i < num_vertices; i++) {
    std::cin >> vertices[i].first >> vertices[i].second;
  }
  return vertices;
}

int main() {
  std::vector<Point> vertices = SetVertices();
  bool result = CheckAllPoints(vertices);
  if (result) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  return 0;
}

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

struct Point {
  double x, y, z;
  Point() : x(0), y(0), z(0) {}
  Point(double x, double y, double z) : x(x), y(y), z(z) {}
};

typedef std::pair<Point, Point> Segment;

double DistanceBetweenPoints(const Point& a, const Point& b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) +
              (a.z - b.z) * (a.z - b.z));
}

double DotProduct(const Point& a, const Point& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

constexpr double epsilon = std::numeric_limits<double>::epsilon();

Point MidPoint2(const Point& a, const Point& b) {
  return Point(b.x - a.x, b.y - a.y, b.z - a.z);
}

void Helper1(double& u1, double& v1, double& v2, double u2, double d1_d1,
             double d2_d2, double d1_d2, double d1_r, double d2_r) {
  u1 = (d1_d2 * d2_r - d2_d2 * d1_r);
  v1 = (d1_d1 * d2_r - d1_d2 * d1_r);
  if (u1 < 0.0) {
    u1 = 0.0;
    v1 = d2_r;
    v2 = d2_d2;
  } else if (u1 > u2) {
    u1 = u2;
    v1 = d2_r + d1_d2;
    v2 = d2_d2;
  }
}

void Helper2(double& u1, double& v1, double& u2, double d1_d1, double d1_r) {
  v1 = 0.0;
  if (-d1_r < 0.0) {
    u1 = 0.0;
  } else if (-d1_r > d1_d1) {
    u1 = u2;
  } else {
    u1 = -d1_r;
    u2 = d1_d1;
  }
}

void Helper3(double& u1, double& v1, double v2, double& u2, double d1_d1,
             double d1_d2, double d1_r) {
  v1 = v2;
  if ((-d1_r + d1_d2) < 0.0) {
    u1 = 0;
  } else if ((-d1_r + d1_d2) > d1_d1) {
    u1 = u2;
  } else {
    u1 = (-d1_r + d1_d2);
    u2 = d1_d1;
  }
}

double DistanceBetweenSegments(const Segment& seg1, const Segment& seg2) {
  Point d1 = MidPoint2(seg1.first, seg1.second);
  Point d2 = MidPoint2(seg2.first, seg2.second);
  Point r = MidPoint2(seg2.first, seg1.first);
  double d1_d1 = DotProduct(d1, d1);
  double d2_d2 = DotProduct(d2, d2);
  double d1_d2 = DotProduct(d1, d2);
  double d1_r = DotProduct(d1, r);
  double d2_r = DotProduct(d2, r);
  double denom = d1_d1 * d2_d2 - d1_d2 * d1_d2;
  double u, u1, v, v1, u2 = denom, v2 = denom;
  if (denom < epsilon) {
    u1 = 0.0;
    u2 = 1.0;
    v1 = d2_r;
    v2 = d2_d2;
  } else {
    Helper1(u1, v1, v2, u2, d1_d1, d2_d2, d1_d2, d1_r, d2_r);
  }
  if (v1 < 0.0) {
    Helper2(u1, v1, u2, d1_d1, d1_r);
  } else if (v1 > v2) {
    Helper3(u1, v1, v2, u2, d1_d1, d1_d2, d1_r);
  }
  u = (std::abs(u1) < epsilon) ? 0.0 : u1 / u2;
  v = (std::abs(v1) < epsilon) ? 0.0 : v1 / v2;
  Point p = {r.x + u * d1.x - v * d2.x, r.y + u * d1.y - v * d2.y,
             r.z + u * d1.z - v * d2.z};
  return DistanceBetweenPoints(p, Point(0, 0, 0));
}

Segment GetSegment() {
  Point a, b;
  std::cin >> a.x >> a.y >> a.z >> b.x >> b.y >> b.z;
  Segment segment(a, b);
  return segment;
}

int main() {
  Segment segment1 = GetSegment();
  Segment segment2 = GetSegment();
  std::cout << std::fixed << std::setprecision(6)
            << DistanceBetweenSegments(segment1, segment2) << std::endl;
  return 0;
}

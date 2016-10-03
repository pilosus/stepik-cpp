#include <cmath>
#include <iostream>
using namespace std;

struct Point {
  double x;
  double y;
};

struct Segment {
  Point p1;
  Point p2;
  double length() {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx - dy * dy);
  }
};

int main() {
  Segment s = {{6.3, 1.2}, {1.3, 0.2}};
  cout << s.length() << endl; // 4.89898
}


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define ll long long
#define ull unsigned long long
#define newl '\n'

using namespace std;
using point = pair<ll, ll>;
using edge = tuple<point, point>;
using polygon = vector<point>;

// References:
// - https://en.wikipedia.org/wiki/Even-odd_rule
// - https://www.geeksforgeeks.org/dsa/orientation-3-ordered-points
// - https://geeksforgeeks.org/dsa/check-if-two-given-line-segments-intersect

bool is_in_polygon(point &pt, polygon &poly) {
  ll x = pt.first;
  ll y = pt.second;
  int n = poly.size();
  bool inside = false;

  for (int i = 0; i < n; i++) {
    int j = (i + n - 1) % n;
    ll ax = poly[i].first;
    ll ay = poly[i].second;
    ll bx = poly[j].first;
    ll by = poly[j].second;

    if ((x == ax) && (y == ay)) {
      // point is a corner
      return true;
    }
    if ((ay > y) != (by > y)) {
      ll slope = (x - ax) * (by - ay) - (bx - ax) * (y - ay);

      if (slope == 0) {
        // point is on boundary
        return true;
      }
      // Long version: ((slope < 0) && (by > ay)) || ((slope > 0) && (by < ay))
      if ((slope < 0) != (by < ay)) {
        inside = !inside;
      }
    }
  }

  return inside;
}

bool is_on_segment(point &pt1, point &pt2, point &pt3) {
  return (pt2.first <= max(pt1.first, pt3.first) &&
          pt2.first >= min(pt1.first, pt3.first) &&
          pt2.second <= max(pt1.second, pt3.second) &&
          pt2.second >= min(pt1.second, pt3.second));
}

int get_orientation(point &pt1, point &pt2, point &pt3) {
  ll val = (pt2.second - pt1.second) * (pt3.first - pt2.first) -
           (pt2.first - pt1.first) * (pt3.second - pt2.second);

  if (val == 0) {
    // 0 for collinear
    return 0;
  }

  // 1 for clockwise, 2 for counterclockwise
  return (val > 0) ? 1 : 2;
}

bool is_intersected(edge &e1, edge &e2) {
  point e1_start = get<0>(e1);
  point e1_end = get<1>(e1);
  point e2_start = get<0>(e2);
  point e2_end = get<1>(e2);

  int o1 = get_orientation(e1_start, e1_end, e2_start);
  int o2 = get_orientation(e1_start, e1_end, e2_end);
  int o3 = get_orientation(e2_start, e2_end, e1_start);
  int o4 = get_orientation(e2_start, e2_end, e1_end);

  // general case
  if (o1 != o2 && o3 != o4) {
    return true;
  }

  // special cases
  if (o1 == 0 && is_on_segment(e1_start, e2_start, e1_end)) {
    return true;
  }
  if (o2 == 0 && is_on_segment(e1_start, e2_end, e1_end)) {
    return true;
  }
  if (o3 == 0 && is_on_segment(e2_start, e1_start, e2_end)) {
    return true;
  }
  if (o4 == 0 && is_on_segment(e2_start, e1_end, e2_end)) {
    return true;
  }

  return false;
}

ll calculate_area(point &pt1, point &pt2) {
  ll width = abs(pt1.first - pt2.first) + 1;
  ll height = abs(pt1.second - pt2.second) + 1;

  return width * height;
}

ll convert_str_to_ll(string num) {
  ll r = 0;
  int len = num.length();
  for (int i = 0; i < len; i++) {
    r += (num[len - i - 1] - '0') * pow(10, i);
  }
  return r;
}

int main() {
  string filename = "input.txt";
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "error: " << filename << " does not exist" << newl;
    return 1;
  }

  string line;
  polygon poly;
  int n = 0;
  ll answer = 0;

  while (getline(file, line)) {
    stringstream coord(line);
    string x, y;

    getline(coord, x, ',');
    getline(coord, y, ',');
    poly.push_back(make_pair(convert_str_to_ll(x), convert_str_to_ll(y)));
  }

  n = poly.size();

  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      point pt1 = poly[i];
      point pt2 = poly[j];
      bool intersected = false;
      ll area = calculate_area(pt1, pt2);

      if (area <= answer) {
        continue;
      }

      vector<point> rect_points = {
          {min(pt1.first, pt2.first) + 1, min(pt1.second, pt2.second) + 1},
          {max(pt1.first, pt2.first) - 1, min(pt1.second, pt2.second) + 1},
          {max(pt1.first, pt2.first) - 1, max(pt1.second, pt2.second) - 1},
          {min(pt1.first, pt2.first) + 1, max(pt1.second, pt2.second) - 1},
      };

      if (!is_in_polygon(rect_points[0], poly) ||
          !is_in_polygon(rect_points[1], poly) ||
          !is_in_polygon(rect_points[2], poly) ||
          !is_in_polygon(rect_points[3], poly)) {
        continue;
      }

      vector<edge> rect_edge = {
          {rect_points[0], rect_points[1]},
          {rect_points[1], rect_points[2]},
          {rect_points[2], rect_points[3]},
          {rect_points[3], rect_points[0]},
      };

      for (int k = 0; k < n; k++) {
        edge poly_edge = {
            poly[k],
            poly[(k + 1) % n],
        };

        for (edge e : rect_edge) {
          if (is_intersected(e, poly_edge)) {
            intersected = true;
            break;
          }
        }

        if (intersected) {
          break;
        }
      }

      if (intersected) {
        continue;
      }

      answer = area;
    }
  }

  cout << answer << newl;

  file.close();
}
